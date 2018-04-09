/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginParser.h"
#include "PluginParameter.h"
#include "PluginEditor.h"
#include <iostream>
#include <exception>

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //

AudioProcessor::BusesProperties CamomileAudioProcessor::getBusesProperties()
{
    BusesProperties ioconfig;
    auto& buses_supported = CamomileEnvironment::getBuses();
    if(!CamomileEnvironment::isMidiOnly() && buses_supported.empty())
    {
        return BusesProperties().withInput("Input",  AudioChannelSet::stereo())
        .withOutput ("Output", AudioChannelSet::stereo());
    }
    size_t i = 1;
    for(auto& buse : buses_supported)
    {
#if JucePlugin_Build_VST3
        if(buse.first)
            ioconfig.addBus(true, String("Input ") + String(i),
                            AudioChannelSet::canonicalChannelSet(static_cast<int>(buse.first)), i == 1);
        if(buse.second)
            ioconfig.addBus(false, String("Ouput ") + String(i),
                            AudioChannelSet::canonicalChannelSet(static_cast<int>(buse.second)), i == 1);
#else
        if(buse.first)
            ioconfig.addBus(true, String("Input ") + String(i), AudioChannelSet::discreteChannels(buse.first), i == 1);
        if(buse.second)
            ioconfig.addBus(false, String("Ouput ") + String(i), AudioChannelSet::discreteChannels(buse.second), i == 1);
#endif
        ++i;
    }
    return ioconfig;
}

CamomileAudioProcessor::CamomileAudioProcessor() :
AudioProcessor(getBusesProperties()),
pd::Instance("camomile"),
m_programs(CamomileEnvironment::getPrograms())
{
    add(ConsoleLevel::Normal, std::string("Camomile ") + std::string(JucePlugin_VersionString)
        + std::string(" for Pd ") + CamomileEnvironment::getPdVersion());
    for(auto const& error : CamomileEnvironment::getErrors()) {
        add(ConsoleLevel::Error, std::string("camomile ") + error); }
    
    if(CamomileEnvironment::isValid())
    {
        m_atoms_param.resize(2);
        m_atoms_playhead.reserve(3);
        m_atoms_playhead.resize(1);
        m_midi_buffer_in.ensureSize(2048);
        m_midi_buffer_out.ensureSize(2048);
        m_midi_buffer_temp.ensureSize(2048);
        prepareDSP(getTotalNumInputChannels(), getTotalNumOutputChannels(), getSampleRate());
        setLatencySamples(CamomileEnvironment::getLatencySamples() + Instance::getBlockSize());
        m_programs = CamomileEnvironment::getPrograms();
        
        auto const& params = CamomileEnvironment::getParams();
        for(size_t i = 0; i < params.size(); ++i)
        {
            AudioProcessorParameter* p = nullptr;
            try
            {
                p = CamomileAudioParameter::parse(params[i]);
            }
            catch(std::string const& message)
            {
                add(ConsoleLevel::Error, std::string("camomile parameter ") + std::to_string(i+1) + std::string(": ") + message);
            }
            if(p)
            {
                addParameter(p);
            }
        }
        m_params_states.resize(getParameters().size());
        std::fill(m_params_states.begin(), m_params_states.end(), false);
        openPatch(CamomileEnvironment::getPatchPath(), CamomileEnvironment::getPatchName());
        processMessages();
    }
}


void CamomileAudioProcessor::setCurrentProgram(int index)
{
    if(static_cast<size_t>(index) < m_programs.size())
    {
        m_program_current = index;
        if(isSuspended())
        {
            sendFloat("program", static_cast<float>(index+1));
            processMessages();
        }
        else
        {
            enqueueMessages("program", "float", {static_cast<float>(index+1)});
        }
    }
}

const String CamomileAudioProcessor::getProgramName (int index)
{
    if(static_cast<size_t>(index) < m_programs.size())
    {
        return String(m_programs[index]);
    }
    return String();
}

void CamomileAudioProcessor::changeProgramName(int index, const String& newName)
{
    if(static_cast<size_t>(index) < m_programs.size())
    {
        m_programs[index] = newName.toStdString();
    }
}

void CamomileAudioProcessor::fileChanged()
{
    reloadPatch();
}

void CamomileAudioProcessor::reloadPatch()
{
    suspendProcessing(true);
    releaseResources();
    openPatch(CamomileEnvironment::getPatchPath(), CamomileEnvironment::getPatchName());
    processMessages();
    prepareToPlay(getSampleRate(), AudioProcessor::getBlockSize());
    AudioProcessorEditor* editor = getActiveEditor();
    if(editor)
    {
        CamomileEditor* cd = dynamic_cast<CamomileEditor*>(editor);
        if(cd)
        {
            cd->guiResize();
        }
    }
    add(ConsoleLevel::Normal, "camomile: the patch \"" + CamomileEnvironment::getPatchName() + "\" has been reloaded");
    suspendProcessing(false);
}

//==============================================================================

bool CamomileAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const size_t nins  = static_cast<size_t>(layouts.getMainInputChannels());
    const size_t nouts  = static_cast<size_t>(layouts.getMainOutputChannels());
    auto& buses_supported = CamomileEnvironment::getBuses();
    for(auto& buse : buses_supported)
    {
        if(buse.first == nins && buse.second == nouts)
        {
            return true;
        }
    }
    return false;
}

void CamomileAudioProcessor::sendBusInformation(Bus const *bus)
{
    if(bus && bus->isEnabled())
    {
        std::string const name = bus->getName().toStdString();
        auto const& layout = bus->getDefaultLayout();
        String description = layout.getDescription().toLowerCase();
        if(description.contains("discrete")) { description = "discrete"; }
        sendMessage(std::string("bus"), bus->isInput() ? std::string("input") : std::string("output"),
                    {static_cast<float>(layout.size()), description.toStdString(), name});
    }
}

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDSP(getTotalNumInputChannels(), getTotalNumOutputChannels(), sampleRate);
    
    {
        // For backward compatibility can be deprecated
        sendMessage(std::string("channels"), std::string("inputs"),
                    {static_cast<float>(getTotalNumInputChannels())});
        sendMessage(std::string("channels"), std::string("outputs"),
                    {static_cast<float>(getTotalNumOutputChannels())});
    }
    const int nbuses = std::max(getBusCount(true), getBusCount(false));
    for(int i = 0; i < nbuses; ++i)
    {
        sendBusInformation(getBus(true, i));
        sendBusInformation(getBus(false, i));
    }
    
    m_audio_advancement = 0;
    const size_t blksize = static_cast<size_t>(Instance::getBlockSize());
    const size_t nins = std::max(static_cast<size_t>(getTotalNumInputChannels()), static_cast<size_t>(2));
    const size_t nouts = std::max(static_cast<size_t>(getTotalNumOutputChannels()), static_cast<size_t>(2));
    m_audio_buffer_in.resize(nins * blksize);
    m_audio_buffer_out.resize(nouts * blksize);
    std::fill(m_audio_buffer_out.begin(), m_audio_buffer_out.end(), 0.f);
    std::fill(m_audio_buffer_in.begin(), m_audio_buffer_in.end(), 0.f);
    m_midi_buffer_in.clear();
    m_midi_buffer_out.clear();
    m_midi_buffer_temp.clear();
    startDSP();
    processMessages();
}

void CamomileAudioProcessor::releaseResources()
{
    releaseDSP();
    processMessages();
    m_audio_buffer_in.clear();
    m_audio_buffer_out.clear();
    std::fill(m_audio_buffer_out.begin(), m_audio_buffer_out.end(), 0.f);
    std::fill(m_audio_buffer_in.begin(), m_audio_buffer_in.end(), 0.f);
    m_audio_advancement = 0;
}

void CamomileAudioProcessor::processInternal()
{
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                     DEQUEUE MESSAGES                                 //
    //////////////////////////////////////////////////////////////////////////////////////////
    dequeueMessages();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                     PLAY HEAD                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    int const phl = CamomileEnvironment::getPlayHeadLevel();
    if(phl)
    {
        AudioPlayHead* playhead = getPlayHead();
        AudioPlayHead::CurrentPositionInfo infos;
        if(playhead && playhead->getCurrentPosition(infos))
        {
            std::string const splayhead("playhead");
            m_atoms_playhead[0] = static_cast<float>(infos.isPlaying);
            sendMessage(splayhead, std::string("playing"), m_atoms_playhead);
            m_atoms_playhead[0] = static_cast<float>(infos.isRecording);
            sendMessage(splayhead, std::string("recording"), m_atoms_playhead);
            m_atoms_playhead[0] = static_cast<float>(infos.isLooping);
            m_atoms_playhead.push_back(static_cast<float>(infos.ppqLoopStart));
            m_atoms_playhead.push_back(static_cast<float>(infos.ppqLoopEnd));
            sendMessage(splayhead, std::string("looping"), m_atoms_playhead);
            m_atoms_playhead.resize(1);
            m_atoms_playhead[0] = static_cast<float>(infos.editOriginTime);
            sendMessage(splayhead, std::string("edittime"), m_atoms_playhead);
            m_atoms_playhead[0] = static_cast<float>(infos.frameRate);
            sendMessage(splayhead, std::string("framerate"), m_atoms_playhead);
            
            m_atoms_playhead[0] = static_cast<float>(infos.bpm);
            sendMessage(splayhead, std::string("bpm"), m_atoms_playhead);
            m_atoms_playhead[0] = static_cast<float>(infos.ppqPositionOfLastBarStart);
            sendMessage(splayhead, std::string("lastbar"), m_atoms_playhead);
            m_atoms_playhead[0] = static_cast<float>(infos.timeSigNumerator);
            m_atoms_playhead.push_back(static_cast<float>(infos.timeSigDenominator));
            sendMessage(splayhead, std::string("timesig"), m_atoms_playhead);
            
            m_atoms_playhead[0] = static_cast<float>(infos.ppqPosition);
            m_atoms_playhead[1] = static_cast<float>(infos.timeInSamples);
            m_atoms_playhead.push_back(static_cast<float>(infos.timeInSeconds));
            sendMessage(splayhead, std::string("position"), m_atoms_playhead);
            m_atoms_playhead.resize(1);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          MIDI IN                                     //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(CamomileEnvironment::wantsMidi())
    {
        MidiMessage message;
        MidiBuffer::Iterator it(m_midi_buffer_in);
        int position = 0;
        while(it.getNextEvent(message, position)) {
            if(message.isNoteOn()) {
                sendNoteOn(message.getChannel(), message.getNoteNumber(), message.getVelocity()); }
            else if(message.isNoteOff()) {
                sendNoteOn(message.getChannel(), message.getNoteNumber(), 0); }
            else if(message.isController()) {
                sendControlChange(message.getChannel(), message.getControllerNumber(), message.getControllerValue()); }
            else if(message.isPitchWheel()) {
                sendPitchBend(message.getChannel(), message.getPitchWheelValue() - 8192); }
            else if(message.isChannelPressure()) {
                sendAfterTouch(message.getChannel(), message.getChannelPressureValue()); }
            else if(message.isAftertouch()) {
                sendPolyAfterTouch(message.getChannel(), message.getNoteNumber(), message.getAfterTouchValue()); }
            else if(message.isProgramChange()) {
                sendProgramChange(message.getChannel(), message.getProgramChangeNumber()); }
            else if(message.isSysEx()) {
                for(int i = 0; i < message.getSysExDataSize(); ++i)  {
                    sendSysEx(0, static_cast<int>(message.getSysExData()[i]));
                }
            }
            else if(message.isMidiClock() || message.isMidiStart() || message.isMidiStop() || message.isMidiContinue() ||
                    message.isActiveSense() || (message.getRawDataSize() == 1 && message.getRawData()[0] == 0xff)) {
                for(int i = 0; i < message.getRawDataSize(); ++i)  {
                    sendSysRealTime(0, static_cast<int>(message.getRawData()[i]));
                }
            }
            else
            {
                for(int i = 0; i < message.getRawDataSize(); ++i)  {
                    sendMidiByte(0, static_cast<int>(message.getRawData()[i]));
                }
            }
        }
        m_midi_buffer_in.clear();
    }
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                  RETRIEVE MESSAGES                                   //
    //////////////////////////////////////////////////////////////////////////////////////////
    processMessages();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                  PARAMETERS                                          //
    //////////////////////////////////////////////////////////////////////////////////////////
    {
        std::string const sparam("param");
        OwnedArray<AudioProcessorParameter> const& parameters = AudioProcessor::getParameters();
        for(int i = 0; i < parameters.size(); ++i)
        {
            m_atoms_param[0] = static_cast<float>(i+1);
            m_atoms_param[1] = static_cast<CamomileAudioParameter const*>(parameters.getUnchecked(i))->getOriginalScaledValue();
            sendList(sparam, m_atoms_param);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          AUDIO                                       //
    //////////////////////////////////////////////////////////////////////////////////////////
    performDSP(m_audio_buffer_in.data(), m_audio_buffer_out.data());
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          MIDI OUT                                    //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(CamomileEnvironment::producesMidi())
    {
        m_midi_buffer_out.clear();
        processMidi();
    }
}

void CamomileAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int blocksize = Instance::getBlockSize();
    const int nsamples  = buffer.getNumSamples();
    const int adv       = m_audio_advancement >= 64 ? 0 : m_audio_advancement;
    const int nleft     = blocksize - adv;
    const int nins      = getTotalNumInputChannels();
    const int nouts     = getTotalNumOutputChannels();
    const float **bufferin = buffer.getArrayOfReadPointers();
    float **bufferout = buffer.getArrayOfWritePointers();
    const bool midi_consume = CamomileEnvironment::wantsMidi();
    const bool midi_produce = CamomileEnvironment::producesMidi();
    
    for(int i = nins; i < nouts; ++i)
    {
        buffer.clear(i, 0, nsamples);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    
    // If the current number of samples in this block
    // is inferior to the number of samples required
    if(nsamples < nleft)
    {
        // we save the input samples and we output
        // the missing samples of the previous tick.
        for(int j = 0; j < nins; ++j)
        {
            const int index = j*blocksize+adv;
            std::copy_n(bufferin[j], nsamples, m_audio_buffer_in.data()+index);
        }
        for(int j = 0; j < nouts; ++j)
        {
            const int index = j*blocksize+adv;
            std::copy_n(m_audio_buffer_out.data()+index, nsamples, bufferout[j]);
        }
        if(midi_consume)
        {
            m_midi_buffer_in.addEvents(midiMessages, 0, nsamples, adv);
        }
        if(midi_produce)
        {
            midiMessages.clear();
            midiMessages.addEvents(m_midi_buffer_out, adv, nsamples, -adv);
        }
        m_audio_advancement += nsamples;
    }
    // If the current number of samples in this block
    // is superior to the number of samples required
    else
    {
        //////////////////////////////////////////////////////////////////////////////////////
        
        // we save the missing input samples, we output
        // the missing samples of the previous tick and
        // we call DSP perform method.
        MidiBuffer const& midiin = midi_produce ? m_midi_buffer_temp : midiMessages;
        if(midi_produce)
        {
            m_midi_buffer_temp.swapWith(midiMessages);
            midiMessages.clear();
        }
        
        for(int j = 0; j < nins; ++j)
        {
            const int index = j*blocksize+adv;
            std::copy_n(bufferin[j], nleft, m_audio_buffer_in.data()+index);
        }
        for(int j = 0; j < nouts; ++j)
        {
            const int index = j*blocksize+adv;
            std::copy_n(m_audio_buffer_out.data()+index, nleft, bufferout[j]);
        }
        if(midi_consume)
        {
            m_midi_buffer_in.addEvents(midiin, 0, nleft, adv);
        }
        if(midi_produce)
        {
            midiMessages.addEvents(m_midi_buffer_out, adv, nleft, -adv);
        }
        m_audio_advancement = 0;
        processInternal();
        
        //////////////////////////////////////////////////////////////////////////////////////

        // If there are other DSP ticks that can be
        // performed, then we do it now.
        int pos = nleft;
        while((pos + blocksize) <= nsamples)
        {
            for(int j = 0; j < nins; ++j)
            {
                const int index = j*blocksize;
                std::copy_n(bufferin[j]+pos, blocksize, m_audio_buffer_in.data()+index);
            }
            for(int j = 0; j < nouts; ++j)
            {
                const int index = j*blocksize;
                std::copy_n(m_audio_buffer_out.data()+index, blocksize, bufferout[j]+pos);
            }
            if(midi_consume)
            {
                m_midi_buffer_in.addEvents(midiin, pos, blocksize, 0);
            }
            if(midi_produce)
            {
                midiMessages.addEvents(m_midi_buffer_out, 0, blocksize, pos);
            }
            processInternal();
            pos += blocksize;
        }
        
        //////////////////////////////////////////////////////////////////////////////////////

        // If there are samples that can't be
        // processed, then save them for later
        // and outputs the remaining samples
        const int remaining = nsamples - pos;
        if(remaining > 0)
        {
            for(int j = 0; j < nins; ++j)
            {
                const int index = j*blocksize;
                std::copy_n(bufferin[j]+pos, remaining, m_audio_buffer_in.data()+index);
            }
            for(int j = 0; j < nouts; ++j)
            {
                const int index = j*blocksize;
                std::copy_n(m_audio_buffer_out.data()+index, remaining, bufferout[j]+pos);
            }
            if(midi_consume)
            {
                m_midi_buffer_in.addEvents(midiin, pos, remaining, 0);
            }
            if(midi_produce)
            {
                midiMessages.addEvents(m_midi_buffer_out, 0, remaining, pos);
            }
            m_audio_advancement = remaining;
        }
    }
}

void CamomileAudioProcessor::processBlockBypassed (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dequeueMessages();
    processMessages();
    const int nsamples  = buffer.getNumSamples();
    const int nins      = getTotalNumInputChannels();
    const int nouts     = getTotalNumOutputChannels();
    for(int i = nins; i < nouts; ++i)
    {
        buffer.clear(i, 0, nsamples);
    }
}

void CamomileAudioProcessor::receiveMessage(const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("param"))
    {
        if(list.size() >= 2 && list[0].isSymbol() && list[1].isFloat())
        {
            std::string const method = list[0].getSymbol();
            int const index = static_cast<int>(list[1].getFloat()) - 1;
            if(method == "set")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    CamomileAudioParameter* param = static_cast<CamomileAudioParameter *>(getParameters()[index]);
                    if(param)
                    {
                        param->setOriginalScaledValueNotifyingHost(list[2].getFloat());
                        if(list.size() > 3) { add(ConsoleLevel::Error,
                                                  "camomile parameter set method extra arguments"); }
                    }
                    else { add(ConsoleLevel::Error,
                                    "camomile parameter set method index: out of range"); }
                }
                else { add(ConsoleLevel::Error,
                           "camomile parameter set method: wrong argument"); }
            }
            else if(method == "change")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    AudioProcessorParameter* param = getParameters()[index];
                    if(param)
                    {
                        if(list[2].getFloat() > std::numeric_limits<float>::epsilon())
                        {
                            if(m_params_states[index])
                            {
                                add(ConsoleLevel::Error,
                                    "camomile parameter change " + std::to_string(index+1) + " already started");
                            }
                            else
                            {
                                param->beginChangeGesture();
                                m_params_states[index] = true;
                                if(list.size() > 3) { add(ConsoleLevel::Error,
                                                          "camomile parameter change method extra arguments"); }
                            }
                        }
                        else
                        {
                            if(!m_params_states[index])
                            {
                                add(ConsoleLevel::Error,
                                    "camomile parameter change " + std::to_string(index+1) + " not started");
                            }
                            else
                            {
                                param->endChangeGesture();
                                m_params_states[index] = false;
                                if(list.size() > 3) { add(ConsoleLevel::Error,
                                                          "camomile parameter change method extra arguments"); }
                            }
                        }
                    }
                    else { add(ConsoleLevel::Error,
                               "camomile parameter change method index: out of range"); }
                }
                else { add(ConsoleLevel::Error,
                           "camomile parameter change method: wrong argument"); }
            }
            else { add(ConsoleLevel::Error,
                       "camomile param no method: " + method); }
        }
        else { add(ConsoleLevel::Error,
                   "camomile param error syntax: method index..."); }
    }
    else if(msg == std::string("openpanel"))
    {
        parseOpenPanel(list);
    }
    else if(msg == std::string("savepanel"))
    {
        parseSavePanel(list);
    }
    else if(msg == std::string("array"))
    {
        parseArray(list);
    }
    else if(msg == std::string("save"))
    {
        parseSaveInformation(list);
    }
    else if(msg == std::string("gui"))
    {
        parseGui(list);
    }
    else if(msg == std::string("audio"))
    {
        parseAudio(list);
    }
    else {  add(ConsoleLevel::Error, "camomile unknow message : " + msg); }
}

void CamomileAudioProcessor::parseOpenPanel(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list.size() > 1)
            {
                if(list[1].isSymbol())
                {
                    if(list[1].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("openpanel"), list[0].getSymbol(), std::string("-s")});
                    }
                    else if(list[0].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("openpanel"), list[1].getSymbol(), std::string("-s")});
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile openpanel one argument must be a flag \"-s\"");
                    }
                    if(list.size() > 2)
                    {
                        add(ConsoleLevel::Error, "camomile openpanel method extra arguments");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile openpanel second argument must be a symbol");
                }
            }
            else
            {
                if(list[0].getSymbol() == "-s")
                {
                    m_queue_gui.try_enqueue({std::string("openpanel"), std::string(), std::string("-s")});
                }
                else
                {
                    m_queue_gui.try_enqueue({std::string("openpanel"), list[0].getSymbol(), std::string()});
                }
            }
        }
        else
        {
            add(ConsoleLevel::Error, "camomile openpanel method argument must be a symbol");
        }
    }
    else
    {
        m_queue_gui.try_enqueue({std::string("openpanel"), std::string(), std::string()});
    }
}

void CamomileAudioProcessor::parseSavePanel(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list.size() > 1)
            {
                if(list[1].isSymbol())
                {
                    if(list[1].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("savepanel"), list[0].getSymbol(), std::string("-s")});
                    }
                    else if(list[0].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("savepanel"), list[1].getSymbol(), std::string("-s")});
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile savepanel one argument must be a flag \"-s\"");
                    }
                    if(list.size() > 2)
                    {
                        add(ConsoleLevel::Error, "camomile savepanel method extra arguments");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile savepanel second argument must be a symbol");
                }
            }
            else
            {
                if(list[0].getSymbol() == "-s")
                {
                    m_queue_gui.try_enqueue({std::string("savepanel"), std::string(), std::string("-s")});
                }
                else
                {
                    m_queue_gui.try_enqueue({std::string("savepanel"), list[0].getSymbol(), std::string()});
                }
            }
        }
        else
        {
            add(ConsoleLevel::Error, "camomile savepanel method argument must be a symbol");
        }
    }
    else
    {
        m_queue_gui.try_enqueue({std::string("savepanel"), std::string(), std::string()});
    }
}

void CamomileAudioProcessor::parseArray(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            m_queue_gui.try_enqueue({std::string("array"), list[0].getSymbol(), ""});
            if(list.size() > 1)
            {
                add(ConsoleLevel::Error, "camomile array method extra arguments");
            }
        }
        else { add(ConsoleLevel::Error, "camomile array method argument must be a symbol"); }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile array needs a name");
    }
}

void CamomileAudioProcessor::parseGui(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            m_queue_gui.try_enqueue({std::string("gui"), list[0].getSymbol(), ""});
            if(list.size() > 1)
            {
                add(ConsoleLevel::Error, "camomile gui method extra arguments");
            }
        }
        else { add(ConsoleLevel::Error, "camomile gui method argument must be a symbol"); }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile gui needs a command");
    }
}

void CamomileAudioProcessor::parseAudio(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list[0].getSymbol() == std::string("latency"))
            {
                if(list.size() >= 2 && list[1].isFloat())
                {
                    const int latency = static_cast<int>(list[1].getFloat());
                    if(latency >= 0)
                    {
                        setLatencySamples(latency + Instance::getBlockSize());
                        if(list.size() > 2)
                        {
                            add(ConsoleLevel::Error, "camomile audio method: latency option extra arguments");
                        }
                        if(CamomileEnvironment::isLatencyInitialized())
                        {
                            add(ConsoleLevel::Error, "camomile audio method: latency overwrites the preferences");
                        }
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile audio method: latency must be positive or null");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile audio method: latency option expects a number");
                }
            }
            else
            {
                add(ConsoleLevel::Error, "camomile audio method: unknown option \"" + list[0].getSymbol() + "\"");
            }
            /*
            else if(list[0].getSymbol() == std::string("taillength"))
            {
                if(list.size() >= 2 && list[1].isFloat())
                {
                    const float taillength = list[1].getFloat();
                    if(taillength >= 0)
                    {
                        if(list.size() > 2)
                        {
                            add(ConsoleLevel::Error, "camomile audio method: taillength option extra arguments");
                        }
                        if(CamomileEnvironment::isTailLengthInitialized())
                        {
                            add(ConsoleLevel::Error, "camomile audio method: taillength overwrites the preferences");
                        }
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile audio method: taillength must be positive or null");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile audio method: taillength option expects a number");
                }
            }
             */
        }
        else
        {
            add(ConsoleLevel::Error, "camomile audio method: first argument must be an option");
        }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile audio method: expects arguments");
    }
}

bool CamomileAudioProcessor::dequeueGui(MessageGui& message)
{
    return m_queue_gui.try_dequeue(message);
}

void CamomileAudioProcessor::receiveNoteOn(const int channel, const int pitch, const int velocity)
{
    if(velocity == 0) {
        m_midi_buffer_out.addEvent(MidiMessage::noteOff(channel, pitch, uint8(0)), m_audio_advancement); }
    else {
        m_midi_buffer_out.addEvent(MidiMessage::noteOn(channel, pitch, static_cast<uint8>(velocity)), m_audio_advancement); }
}

void CamomileAudioProcessor::receiveControlChange(const int channel, const int controller, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::controllerEvent(channel, controller, value), m_audio_advancement);
}

void CamomileAudioProcessor::receiveProgramChange(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::programChange(channel, value), m_audio_advancement);
}

void CamomileAudioProcessor::receivePitchBend(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::pitchWheel(channel, value + 8192), m_audio_advancement);
}

void CamomileAudioProcessor::receiveAftertouch(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::channelPressureChange(channel, value), m_audio_advancement);
}

void CamomileAudioProcessor::receivePolyAftertouch(const int channel, const int pitch, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::aftertouchChange(channel, pitch, value), m_audio_advancement);
}

void CamomileAudioProcessor::receiveMidiByte(const int port, const int byte)
{
    m_midi_buffer_out.addEvent(MidiMessage(byte), m_audio_advancement);
}

void CamomileAudioProcessor::receivePrint(const std::string& message)
{
    if(!message.empty())
    {
        if(!message.compare(0, 6, "error:"))
        {
            std::string const temp(message.begin()+7, message.end());
            add(ConsoleLevel::Error, temp);
        }
        else if(!message.compare(0, 11, "verbose(4):"))
        {
            std::string const temp(message.begin()+12, message.end());
            add(ConsoleLevel::Error, temp);
        }
        else if(!message.compare(0, 5, "tried"))
        {
            add(ConsoleLevel::Log, message);
        }
        else if(!message.compare(0, 16, "input channels ="))
        {
            add(ConsoleLevel::Log, message);
        }
        else
        {
            add(ConsoleLevel::Normal, message);
        }
    }
}

void CamomileAudioProcessor::messageEnqueued()
{
    if(isNonRealtime() || isSuspended())
    {
        dequeueMessages();
        processMessages();
    }
    else
    {
        const CriticalSection& cs = getCallbackLock();
        if(cs.tryEnter())
        {
            dequeueMessages();
            processMessages();
            cs.exit();
        }
    }
}

//==============================================================================
bool CamomileAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* CamomileAudioProcessor::createEditor()
{
    return new CamomileEditor(*this);
}

void CamomileAudioProcessor::parseSaveInformation(const std::vector<pd::Atom>& list)
{
    if(m_temp_xml)
    {
        XmlElement* patch = m_temp_xml->getChildByName("patch");
        if(!patch)
        {
            patch = m_temp_xml->createNewChildElement("patch");
            if(!patch)
            {
                add(ConsoleLevel::Error, "can't allocate memory for saving plugin state.");
                return;
            }
        }
        const int nchilds = patch->getNumChildElements();
        XmlElement* preset = patch->createNewChildElement(String("list") + String(nchilds+1));
        if(preset)
        {
            for(size_t i = 0; i < list.size(); ++i)
            {
                if(list[i].isFloat()) {
                    preset->setAttribute(String("float") + String(i+1), list[i].getFloat()); }
                else if(list[i].isSymbol())  {
                    preset->setAttribute(String("string") + String(i+1), String(list[i].getSymbol())); }
                else {
                    preset->setAttribute(String("atom") + String(i+1), String("unknown")); }
            }
        }
        else
        {
            add(ConsoleLevel::Error, "can't allocate memory for saving plugin state.");
        }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile save method should be called after plugin save notification.");
    }
}

void CamomileAudioProcessor::loadInformation(XmlElement const& xml)
{
    bool loaded = false;
    XmlElement const* patch = xml.getChildByName(juce::StringRef("patch"));
    if(patch)
    {
        const int nlists = patch->getNumChildElements();
        std::vector<pd::Atom> vec;
        for(int i = 0; i < nlists; ++i)
        {
            XmlElement const* list = patch->getChildElement(i);
            if(list)
            {
                const int natoms = list->getNumAttributes();
                vec.resize(natoms);
                
                for(int j = 0; j < natoms; ++j)
                {
                    String const& name = list->getAttributeName(j);
                    if(name.startsWith("float")) {
                        vec[j] = static_cast<float>(list->getDoubleAttribute(name)); }
                    else if(name.startsWith("string")){
                        vec[j] = list->getStringAttribute(name).toStdString(); }
                    else {
                        vec[j] = std::string("unknown"); }
                }
                
                sendList(std::string("load"), vec);
                loaded = true;
            }
        }
    }
    
    if(!loaded)
    {
        sendBang(std::string("load"));
    }
}

void CamomileAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    suspendProcessing(true);
    XmlElement xml(String("CamomileSettings"));
    m_temp_xml = &xml;
    CamomileAudioParameter::saveStateInformation(xml, getParameters());
    sendBang(std::string("save"));
    processMessages();
    copyXmlToBinary(xml, destData);
    m_temp_xml = nullptr;
    
    XmlElement* cbounds = xml.createNewChildElement("console");
    if(cbounds)
    {
        cbounds->setAttribute(String("x"), m_console_bounds.getX());
        cbounds->setAttribute(String("y"), m_console_bounds.getX());
        cbounds->setAttribute(String("width"), m_console_bounds.getWidth());
        cbounds->setAttribute(String("height"), m_console_bounds.getHeight());
    }
    
    suspendProcessing(false);
}

void CamomileAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing(true);
    ScopedPointer<const XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if(xml && xml->hasTagName("CamomileSettings"))
    {
        CamomileAudioParameter::loadStateInformation(*xml, getParameters());
        loadInformation(*xml);
        XmlElement const* cbounds = xml->getChildByName(juce::StringRef("console"));
        if(cbounds)
        {
            m_console_bounds.setX(cbounds->getIntAttribute(String("x")));
            m_console_bounds.setY(cbounds->getIntAttribute(String("y")));
            m_console_bounds.setWidth(cbounds->getIntAttribute(String("width")));
            m_console_bounds.setHeight(cbounds->getIntAttribute(String("height")));
        }
    }
    else
    {
        sendBang(std::string("load"));
    }
    suspendProcessing(false);
}

void CamomileAudioProcessor::updateTrackProperties(const TrackProperties& properties)
{
    m_track_properties = properties;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
