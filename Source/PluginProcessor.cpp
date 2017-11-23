/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginAtomParser.h"
#include "PluginParameter.h"
#include "PluginEditor.h"
#include <iostream>
#include <exception>

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //


CamomileAudioProcessor::CamomileAudioProcessor() : AudioProcessor(),
m_programs(CamomileEnvironment::getPrograms())
{
    bind("camomile");
    if(CamomileEnvironment::isValid())
    {
        std::vector<std::string> errors = CamomileEnvironment::getErrors();
        open(CamomileEnvironment::getPatchPath(), CamomileEnvironment::getPatchName());
        processMessages();
        setLatencySamples(CamomileEnvironment::getLatencySamples());
        m_programs = CamomileEnvironment::getPrograms();
        
        std::vector<std::string> const& params = CamomileEnvironment::getParams();
        for(size_t i = 0; i < params.size(); ++i)
        {
            CamomileAudioParameter::parse(params[i], errors);
        }
        for(size_t i = 0; i < errors.size(); ++i)
        {
            std::cerr << errors[i] << "\n";
        }
    }
}


void CamomileAudioProcessor::setCurrentProgram(int index)
{
    if(index < m_programs.size())
    {
        m_program_current = index;
        sendFloat("program", static_cast<float>(index+1));
    }
    processMessages();
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
    const int nins  = layouts.getMainInputChannelSet().size();
    const int nouts  = layouts.getMainOutputChannelSet().size();
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

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    BusesLayout const& layouts(getBusesLayout());
    AudioChannelSet const inputs  = layouts.getMainInputChannelSet();
    AudioChannelSet const outputs = layouts.getMainOutputChannelSet();
    
    if(samplesPerBlock < 64)
    {
        std::cerr << "block size must not be inferior to 64, the DSP won't be proceed.\n";
    }
    prepareDSP(inputs.size(), outputs.size(), samplesPerBlock, sampleRate);
    
    String ins_desc     = inputs.getDescription().toLowerCase();
    String outs_desc    = outputs.getDescription().toLowerCase();
    if(ins_desc.contains("discrete"))
    {
        ins_desc = "discrete";
    }
    if(outs_desc.contains("discrete"))
    {
        outs_desc = "discrete";
    }
    sendMessage(std::string("channels"), std::string("inputs"), {inputs.size(), ins_desc.toStdString()});
    sendMessage(std::string("channels"), std::string("outputs"), {outputs.size(), outs_desc.toStdString()});
    
    processMessages();
}

void CamomileAudioProcessor::releaseResources()
{
    releaseDSP();
}

void CamomileAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for(int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    if(buffer.getNumSamples() < 64)
    {
        for(int i = 0; i < totalNumInputChannels; ++i)
        {
            buffer.clear(i, 0, buffer.getNumSamples());
        }
        return;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                     PLAY HEAD                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(CamomileEnvironment::wantsPlayHead())
    {
        AudioPlayHead* playhead = getPlayHead();
        AudioPlayHead::CurrentPositionInfo infos;
        if(playhead && playhead->getCurrentPosition(infos))
        {
            std::string const splayhead("playhead");
            sendMessage(splayhead, std::string("bpm"), {static_cast<float>(infos.bpm)});
            sendMessage(splayhead, std::string("timeSigNumerator"), {static_cast<float>(infos.timeSigNumerator)});
            sendMessage(splayhead, std::string("timeSigDenominator"), {static_cast<float>(infos.timeSigDenominator)});
            sendMessage(splayhead, std::string("timeInSamples"), {static_cast<float>(infos.timeInSamples)});
            sendMessage(splayhead, std::string("timeInSeconds"), {static_cast<float>(infos.timeInSeconds)});
            sendMessage(splayhead, std::string("editOriginTime"), {static_cast<float>(infos.editOriginTime)});
            sendMessage(splayhead, std::string("ppqPosition"), {static_cast<float>(infos.ppqPosition)});
            sendMessage(splayhead, std::string("ppqPositionOfLastBarStart"), {static_cast<float>(infos.ppqPositionOfLastBarStart)});
            sendMessage(splayhead, std::string("frameRate"), {static_cast<float>(infos.frameRate)});
            sendMessage(splayhead, std::string("isPlaying"), {static_cast<float>(infos.isPlaying)});
            sendMessage(splayhead, std::string("isRecording"), {static_cast<float>(infos.isRecording)});
            sendMessage(splayhead, std::string("ppqLoopStart"), {static_cast<float>(infos.ppqLoopStart)});
            sendMessage(splayhead, std::string("ppqLoopEnd"), {static_cast<float>(infos.ppqLoopEnd)});
            sendMessage(splayhead, std::string("isLooping"), {static_cast<float>(infos.isLooping)});
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
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //                                  PARAMETERS                                          //
    //////////////////////////////////////////////////////////////////////////////////////////
    {
        std::string const sparam("param");
        OwnedArray<AudioProcessorParameter> const& parameters = AudioProcessor::getParameters();
        for(int i = 0; i < parameters.size(); ++i)
        {
            sendList(sparam, {float(i+1), static_cast<CamomileAudioParameter const*>(parameters.getUnchecked(i))->getOriginalScaledValue()});
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          AUDIO                                       //
    //////////////////////////////////////////////////////////////////////////////////////////
    performDSP(buffer.getNumSamples(),
            getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
            getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          RETRIEVE MESSAGE                             //
    //////////////////////////////////////////////////////////////////////////////////////////
    processMessages();
    
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
            int const index = static_cast<int>(list[1].getFloat());
            if(method == "set")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    CamomileAudioParameter* param = static_cast<CamomileAudioParameter *>(getParameters()[index - 1]);
                    if(param)
                    {
                        param->setOriginalScaledValueNotifyingHost(list[2].getFloat());
                    }
                    else { std::cerr << "parameter set method index: out of range.\n"; }
                }
                else { std::cerr << "parameter set method: wrong argument.\n"; }
            }
            else if(method == "change")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    AudioProcessorParameter* param = getParameters()[index - 1];
                    if(param)
                    {
                        static_cast<bool>(list[2].getFloat()) ? param->beginChangeGesture() : param->endChangeGesture();
                    }
                    else { std::cerr << "parameter change method index: out of range.\n"; }
                }
                else { std::cerr << "parameter change method: wrong argument.\n"; }
            }
            else { std::cerr << "param no method: " << method << "\n"; }
        }
        else { std::cerr << "param error syntax: method index...\n"; }
    }
    else {  std::cerr << "camomile unknow message : "<< msg << "\n"; }
}


void CamomileAudioProcessor::receiveNoteOn(const int channel, const int pitch, const int velocity)
{
    if(velocity == 0) {
        m_midi_buffer.addEvent(MidiMessage::noteOff(channel, pitch, uint8(0)), 0); }
    else {
        m_midi_buffer.addEvent(MidiMessage::noteOn(channel, pitch, static_cast<uint8>(velocity)), 0); }
}

void CamomileAudioProcessor::receiveControlChange(const int channel, const int controller, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::controllerEvent(channel, controller, value), 0);
}

void CamomileAudioProcessor::receiveProgramChange(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::programChange(channel, value), 0);
}

void CamomileAudioProcessor::receivePitchBend(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::pitchWheel(channel, value), 0);
}

void CamomileAudioProcessor::receiveAftertouch(const int channel, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::channelPressureChange(channel, value), 0);
}

void CamomileAudioProcessor::receivePolyAftertouch(const int channel, const int pitch, const int value)
{
    m_midi_buffer.addEvent(MidiMessage::aftertouchChange(channel, pitch, value), 0);
}

void CamomileAudioProcessor::receiveMidiByte(const int port, const int byte)
{
    
}

//==============================================================================
bool CamomileAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* CamomileAudioProcessor::createEditor()
{
    return new CamomileAudioProcessorEditor(*this);
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

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
