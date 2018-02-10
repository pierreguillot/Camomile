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
    if(buses_supported.empty())
    {
        return BusesProperties().withInput("Input",  AudioChannelSet::stereo())
        .withOutput ("Output", AudioChannelSet::stereo());
    }
    size_t i = 1;
    for(auto& buse : buses_supported)
    {
#if JucePlugin_Build_VST3
        if(buse.first)
            ioconfig.addBus(true, String("Input ") + String(i), AudioChannelSet::canonicalChannelSet(buse.first), i == 1);
        if(buse.second)
            ioconfig.addBus(false, String("Ouput ") + String(i), AudioChannelSet::canonicalChannelSet(buse.second), i == 1);
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

CamomileAudioProcessor::CamomileAudioProcessor() : AudioProcessor(getBusesProperties()),
m_programs(CamomileEnvironment::getPrograms())
{
    bind("camomile");
    add(ConsoleLevel::Normal, std::string("Camomile ") + std::string(JucePlugin_VersionString)
        + std::string(" for Pd ") + CamomileEnvironment::getPdVersion());
    for(auto const& error : CamomileEnvironment::getErrors()) {
        add(ConsoleLevel::Error, std::string("camomile ") + error); }
    
    if(CamomileEnvironment::isValid())
    {
        m_atoms_param.resize(2);
        m_atoms_playhead.reserve(3);
        m_atoms_playhead.resize(1);
        prepareDSP(getBusesLayout().getMainInputChannelSet().size(),
                   getBusesLayout().getMainOutputChannelSet().size(),
                   getBlockSize() < 64 ? 64 : getBlockSize(), getSampleRate());
        
        setLatencySamples(CamomileEnvironment::getLatencySamples());
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
            if(p) {
                addParameter(p); }
        }
        m_params_states.resize(getParameters().size());
        std::fill(m_params_states.begin(), m_params_states.end(), false);
        openPatch(CamomileEnvironment::getPatchPath(), CamomileEnvironment::getPatchName());
        processMessages();
    }
}


void CamomileAudioProcessor::setCurrentProgram(int index)
{
    if(index < m_programs.size())
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
    if(index < m_programs.size()) { return String(m_programs[index]); }
    return {};
}

void CamomileAudioProcessor::changeProgramName(int index, const String& newName)
{
    if(index < m_programs.size()) { m_programs[index] = newName.toStdString(); }
}

//==============================================================================

bool CamomileAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const int nins  = layouts.getMainInputChannels();
    const int nouts  = layouts.getMainOutputChannels();
    auto& buses_supported = CamomileEnvironment::getBuses();
    if(buses_supported.empty())
    {
        return nins <= 2 && nouts <= 2;
    }
    for(auto& buse : buses_supported)
    {
        if(buse.first == nins && buse.second == nouts)
        {
            return true;
        }
    }
    return false;
}

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    BusesLayout const& layouts(getBusesLayout());
    AudioChannelSet const inputs  = layouts.getMainInputChannelSet();
    AudioChannelSet const outputs = layouts.getMainOutputChannelSet();
    
    if(samplesPerBlock < 64) {
        add(ConsoleLevel::Error, "DSP block is inferior to 64 samples implying "
            + std::to_string(64 - samplesPerBlock) + " samples delay.."); }
    prepareDSP(inputs.size(), outputs.size(), samplesPerBlock, sampleRate);
    startDSP();
    
    String insdesc  = inputs.getDescription().toLowerCase();
    String outsdesc = outputs.getDescription().toLowerCase();
    if(insdesc.contains("discrete")) {
        insdesc = "discrete"; }
    if(outsdesc.contains("discrete")) {
        outsdesc = "discrete"; }
    sendMessage(std::string("channels"), std::string("inputs"), {static_cast<float>(inputs.size()), insdesc.toStdString()});
    sendMessage(std::string("channels"), std::string("outputs"), {static_cast<float>(outputs.size()), outsdesc.toStdString()});
    processMessages();
}

void CamomileAudioProcessor::releaseResources()
{
    releaseDSP();
}

void CamomileAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int numSamples  = buffer.getNumSamples();
    const float ** arrayOfReadPointers = buffer.getArrayOfReadPointers();
    float ** arrayOfWritePointers = buffer.getArrayOfWritePointers();
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    for(int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, numSamples);
    }
    
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
        MidiBuffer::Iterator it(midiMessages);
        int position = midiMessages.getFirstEventTime();
        while(it.getNextEvent(message, position)) {
            if(message.isNoteOn()) {
                sendNoteOn(message.getChannel(), message.getNoteNumber(), message.getVelocity()); }
            else if(message.isNoteOff()) {
                sendNoteOn(message.getChannel(), message.getNoteNumber(), 0); }
            else if(message.isController()) {
                sendControlChange(message.getChannel(), message.getControllerNumber(), message.getControllerValue()); }
            else if(message.isPitchWheel()) {
                sendPitchBend(message.getChannel(), message.getPitchWheelValue()); }
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
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          RETRIEVE MESSAGES                           //
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
    performDSP(numSamples, totalNumInputChannels, arrayOfReadPointers, totalNumOutputChannels, arrayOfWritePointers);
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          MIDI OUT                                    //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(CamomileEnvironment::producesMidi())
    {
        processMidi();
        midiMessages.swapWith(m_midi_buffer);
        m_midi_buffer.clear();
    }
}


void CamomileAudioProcessor::receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
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
        if(list.size() >= 1) {
            if(list[0].isSymbol()) {
                m_queue_gui.try_enqueue({std::string("openpanel"), list[0].getSymbol()});
                if(list.size() > 1) { add(ConsoleLevel::Error,
                                          "camomile openpanel method extra arguments"); }
            }
        }
        else {
            m_queue_gui.try_enqueue({std::string("openpanel"), std::string()}); }
    }
    else if(msg == std::string("savepanel"))
    {
        if(list.size() >= 1) {
            if(list[0].isSymbol()) {
                m_queue_gui.try_enqueue({std::string("savepanel"), list[0].getSymbol()});
                if(list.size() > 1) { add(ConsoleLevel::Error,
                                          "camomile savepanel method extra arguments"); }
            }
        }
        else {
            m_queue_gui.try_enqueue({std::string("savepanel"), std::string()}); }
    }
    else {  add(ConsoleLevel::Error,
                "camomile unknow message : " + msg); }
}

bool CamomileAudioProcessor::dequeueGui(MessageGui& message)
{
    return m_queue_gui.try_dequeue(message);
}

void CamomileAudioProcessor::receiveNoteOn(const int channel, const int pitch, const int velocity)
{
    if(velocity == 0) {
        m_midi_buffer.addEvent(MidiMessage::noteOff(channel, pitch, uint8(0)), 0.); }
    else {
        m_midi_buffer.addEvent(MidiMessage::noteOn(channel, pitch, static_cast<uint8>(velocity)), 0.); }
}

void CamomileAudioProcessor::receiveControlChange(const int channel, const int controller, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::controllerEvent(channel, controller, value), 0.);
}

void CamomileAudioProcessor::receiveProgramChange(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::programChange(channel, value), 0.);
}

void CamomileAudioProcessor::receivePitchBend(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::pitchWheel(channel, value), 0.);
}

void CamomileAudioProcessor::receiveAftertouch(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::channelPressureChange(channel, value), 0.);
}

void CamomileAudioProcessor::receivePolyAftertouch(const int channel, const int pitch, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::aftertouchChange(channel, pitch, value), 0.);
}

void CamomileAudioProcessor::receiveMidiByte(const int port, const int byte)
{
    m_midi_buffer.addEvent(MidiMessage(byte), 0.);
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
    if(isNonRealtime())
    {
        dequeueMessages();
        processMessages();
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


void CamomileAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml(String("CamomileSettings"));
    CamomileAudioParameter::saveStateInformation(xml, getParameters());
    copyXmlToBinary(xml, destData);
}

void CamomileAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<const XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if(xml && xml->hasTagName("CamomileSettings"))
    {
        CamomileAudioParameter::loadStateInformation(*xml, getParameters());
    }
}

void CamomileAudioProcessor::updateTrackProperties(const TrackProperties& properties)
{
    m_track_properties = properties;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
