/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginParser.h"
#include "PluginParameter.h"
#include "PluginEditor.h"
#include "PluginEnvironment.h"

#include <iostream>
#include <exception>

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //

CamomileAudioProcessor::CamomileAudioProcessor() :
AudioProcessor(getDefaultBusesProperties(JucePlugin_Build_VST3)),
pd::Instance("camomile"), CamomileConsole(4),
m_name(CamomileEnvironment::getPluginName()),
m_accepts_midi(CamomileEnvironment::wantsMidi()),
m_produces_midi(CamomileEnvironment::producesMidi()),
m_is_midi_effect(CamomileEnvironment::isMidiOnly()),
m_tail_length(static_cast<double>(CamomileEnvironment::getTailLengthSeconds())),
m_programs(CamomileEnvironment::getPrograms())
{
    add(ConsoleLevel::Normal, std::string("Camomile ") + std::string(JucePlugin_VersionString)
        + std::string(" for Pd ") + CamomileEnvironment::getPdVersion());
    for(auto const& error : CamomileEnvironment::getErrors()) {
        add(ConsoleLevel::Error, std::string("camomile ") + error); }
    logBusesLayoutsInformation();
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

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDSP(getTotalNumInputChannels(), getTotalNumOutputChannels(), sampleRate);
    sendCurrentBusesLayoutInformation();
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
    processPrints();
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
    if(m_accepts_midi)
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
    if(m_produces_midi)
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
    const bool midi_consume = m_accepts_midi;
    const bool midi_produce = m_produces_midi;
    
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

bool CamomileAudioProcessor::dequeueGui(MessageGui& message)
{
    return m_queue_gui.try_dequeue(message);
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
        if(CamomileEnvironment::hasAutoProgram())
        {
            CamomileAudioParameter::loadStateInformation(*xml, getParameters());            
        }
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

Rectangle<int> CamomileAudioProcessor::getConsoleWindowBounds() const
{
    return m_console_bounds;
}

void CamomileAudioProcessor::setConsoleWindowBounds(Rectangle<int> const& rect)
{
    m_console_bounds = rect;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
