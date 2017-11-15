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
//char* global_plugin_name = "Camomile";

#ifdef JUCE_MAC
#define CAMOMILE_RESSOURCE_PATH juce::String("/Contents/Resources")
#else
#define CAMOMILE_RESSOURCE_PATH juce::String("")
#endif

CamomileAudioProcessor::CamomileAudioProcessor() :
AudioProcessor(BusesProperties()
               .withInput("Input", AudioChannelSet::stereo())
               .withOutput("Output", AudioChannelSet::stereo()))
{
    juce::File const plugin = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getFullPathName();
    if(plugin.exists())
    {
        juce::String name   = plugin.getFileNameWithoutExtension();
        juce::File   infos  = plugin.getFullPathName() + CAMOMILE_RESSOURCE_PATH +  juce::File::getSeparatorString() + name + juce::String(".txt");
        bind("camomile");
        open((plugin.getFullPathName() + CAMOMILE_RESSOURCE_PATH).toStdString(), name.toStdString() + std::string(".pd"));
        processReceive();
    }
}

CamomileAudioProcessor::~CamomileAudioProcessor()
{
}

//==============================================================================
const String CamomileAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CamomileAudioProcessor::acceptsMidi() const
{
    return m_midi_in_support;
}

bool CamomileAudioProcessor::producesMidi() const
{
   return m_midi_out_support;
}

bool CamomileAudioProcessor::isMidiEffect() const
{
    return m_midi_only;
}

double CamomileAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CamomileAudioProcessor::getNumPrograms()
{
    return m_programs.isEmpty() ? 1 : m_programs.size();
}

int CamomileAudioProcessor::getCurrentProgram()
{
    return m_program_current;
}

void CamomileAudioProcessor::setCurrentProgram (int index)
{
    if(index < m_programs.size())
    {
        m_program_current = index;
        Array<float> const& values = m_programs.getReference(index).values;
        std::string const sparam("param");
        OwnedArray<AudioProcessorParameter> const& parameters = AudioProcessor::getParameters();
        for(int i = 0; i < values.size(); ++i)
        {
            CamomileAudioParameter* p = static_cast<CamomileAudioParameter*>(parameters[i]);
            if(p)
            {
                p->setOriginalScaledValueNotifyingHost(values[i]);
                sendList(sparam, {float(i+1), p->getOriginalScaledValue()});
            }
        }
        sendFloat("program", static_cast<float>(index+1));
    }
    
}

const String CamomileAudioProcessor::getProgramName (int index)
{
    if(index < m_programs.size())
    {
        if(m_programs[index].alias.isNotEmpty())
            return m_programs[index].alias;
        else
            return m_programs[index].name;
    }
    return {};
}

void CamomileAudioProcessor::changeProgramName (int index, const String& newName)
{
    if(index < m_programs.size())
    {
        m_programs[index].alias = newName;
    }
}

//==============================================================================

bool CamomileAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const AudioChannelSet& mainOutput = layouts.getMainOutputChannelSet();
    const AudioChannelSet& mainInput  = layouts.getMainInputChannelSet();
    
    //sendList(std::string("buses"), {});
    //std::cout << "| Input : "<< mainInput.getDescription() << " | Output : " << mainOutput.getDescription() << " |\n";
    return true;
}

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    try
    {
        prepareDSP(AudioProcessor::getTotalNumInputChannels(),
                   AudioProcessor::getTotalNumOutputChannels(),
                   samplesPerBlock, sampleRate);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
    
    const BusesLayout& layouts(getBusesLayout());
    const std::string input = layouts.getMainInputChannelSet().getDescription().toStdString();
    const std::string output = layouts.getMainOutputChannelSet().getDescription().toStdString();
    sendList(std::string("buses"), {input, output});
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
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                     PLAY HEAD                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(m_play_head_support)
    {
        AudioPlayHead* playhead = getPlayHead();
        AudioPlayHead::CurrentPositionInfo infos;
        if(playhead && playhead->getCurrentPosition(infos))
        {
            std::string const splayhead("playhead");
            sendList(splayhead, {"bpm", static_cast<float>(infos.bpm)});
            sendList(splayhead, {"timeSigNumerator", static_cast<float>(infos.timeSigNumerator)});
            sendList(splayhead, {"timeSigDenominator", static_cast<float>(infos.timeSigDenominator)});
            sendList(splayhead, {"timeInSamples", static_cast<float>(infos.timeInSamples)});
            sendList(splayhead, {"timeInSeconds", static_cast<float>(infos.timeInSeconds)});
            sendList(splayhead, {"editOriginTime", static_cast<float>(infos.editOriginTime)});
            sendList(splayhead, {"ppqPosition", static_cast<float>(infos.ppqPosition)});
            sendList(splayhead, {"ppqPositionOfLastBarStart", static_cast<float>(infos.ppqPositionOfLastBarStart)});
            sendList(splayhead, {"frameRate", static_cast<float>(infos.frameRate)});
            sendList(splayhead, {"isPlaying", static_cast<float>(infos.isPlaying)});
            sendList(splayhead, {"isRecording", static_cast<float>(infos.isRecording)});
            sendList(splayhead, {"ppqLoopStart", static_cast<float>(infos.ppqLoopStart)});
            sendList(splayhead, {"ppqLoopEnd", static_cast<float>(infos.ppqLoopEnd)});
            sendList(splayhead, {"isLooping", static_cast<float>(infos.isLooping)});
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                          MIDI                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    if(m_midi_in_support)
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
    //                                          RETRIVE MESSAGE                             //
    //////////////////////////////////////////////////////////////////////////////////////////
    processReceive();
    
    if(m_midi_in_support)
    {
        midiMessages.swapWith(m_midi_buffer);
        m_midi_buffer.clear();
    }
}

//==============================================================================
bool CamomileAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
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


void CamomileAudioProcessor::receiveBang(const std::string& dest)
{
    ;
}

void CamomileAudioProcessor::receiveFloat(const std::string& dest, float num)
{
    ;
}

void CamomileAudioProcessor::receiveSymbol(const std::string& dest, const std::string& symbol)
{
    ;
}

void CamomileAudioProcessor::receiveList(const std::string& dest, const std::vector<pd::Atom>& list)
{
    
}

bool CamomileAudioProcessor::processParameters(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
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
                    else
                    {
                        std::cerr << "parameter set method index: out of range.\n";
                    }
                }
                else
                {
                    std::cerr << "parameter set method: wrong argument.\n";
                }
            }
            else if(method == "change")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    CamomileAudioParameter* param = static_cast<CamomileAudioParameter *>(getParameters()[index - 1]);
                    if(param)
                    {
                        if(static_cast<bool>(list[2].getFloat()))
                        {
                            param->beginChangeGesture();
                        }
                        else
                        {
                            param->endChangeGesture();
                        }
                    }
                    else
                    {
                        std::cerr << "parameter change method index: out of range.\n";
                    }
                }
                else
                {
                    std::cerr << "parameter set method: wrong argument.\n";
                }
            }
            else if(method == "define")
            {
                if(index == getParameters().size()+1)
                {
                    std::vector<pd::Atom> args(list.begin()+2, list.end());
                    addParameter(CamomileAudioParameter::parse(args));
                }
                else
                {
                    std::cerr << "parameter define method: index out of range.\n";
                }
            }
        }
        return true;
    }
    return false;
}

bool CamomileAudioProcessor::processPrograms(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("program"))
    {
        if(list.size() >= 2 && list[0].isSymbol() && list[1].isFloat())
        {
            std::string const method = list[0].getSymbol();
            int const index = static_cast<int>(list[1].getFloat());
            if(method == "define")
            {
                if(list.size() >= 3 && list[2].isSymbol())
                {
                    if(index == m_programs.size()+1)
                    {
                        m_programs.add({list[2].getSymbol(), "", Array<float>()});
                        for(int i = 3; i < list.size(); ++i)
                        {
                            m_programs.getReference(index-1).values.add(list[i].getFloat());
                        }
                    }
                    else { std::cerr << "program define method: index out of range.\n"; }
                }
                else { std::cerr << "program error syntax: define index name...\n"; }
            }
            else { std::cerr << "program unknown method: index out of range.\n"; }
        }
        else { std::cerr << "program error syntax: method index...\n"; }
        return true;
    }
    return false;
}

bool CamomileAudioProcessor::processMidi(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == "#noteout")
    {
        if(static_cast<int>(list[2].getFloat()) == 0)
        {
            m_midi_buffer.addEvent(MidiMessage::noteOff(static_cast<int>(list[0].getFloat()),
                                                        static_cast<int>(list[1].getFloat()),
                                                        uint8(0)), 0);
        }
        else
        {
            m_midi_buffer.addEvent(MidiMessage::noteOn(static_cast<int>(list[0].getFloat()),
                                                       static_cast<int>(list[1].getFloat()),
                                                       static_cast<uint8>(list[2].getFloat())), 0);
        }
    }
    else if(msg == "#controlchange")
    {
        m_midi_buffer.addEvent(MidiMessage::controllerEvent(static_cast<int>(list[0].getFloat()),
                                                            static_cast<int>(list[1].getFloat()),
                                                            static_cast<int>(list[2].getFloat())), 0);
    }
    else if(msg == "#programchange")
    {
        m_midi_buffer.addEvent(MidiMessage::programChange(static_cast<int>(list[0].getFloat()),
                                                          static_cast<int>(list[1].getFloat())), 0);
    }
    else if(msg == "#pitchbend")
    {
        m_midi_buffer.addEvent(MidiMessage::pitchWheel(static_cast<int>(list[0].getFloat()),
                                                       static_cast<int>(list[1].getFloat())), 0);
    }
    else if(msg == "#aftertouch")
    {
        m_midi_buffer.addEvent(MidiMessage::channelPressureChange(static_cast<int>(list[0].getFloat()),
                                                                  static_cast<int>(list[1].getFloat())), 0);
    }
    else if(msg == "#aftertouch")
    {
        m_midi_buffer.addEvent(MidiMessage::aftertouchChange(static_cast<int>(list[0].getFloat()),
                                                             static_cast<int>(list[1].getFloat()),
                                                             static_cast<int>(list[2].getFloat())), 0);
    }
    else
    {
        return false;
    }
    return true;
}

bool CamomileAudioProcessor::processOption(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("option"))
    {
        m_midi_in_support   = CamomileAtomParser::parseBool(list, "-midiin", m_midi_in_support);
        m_midi_out_support  = CamomileAtomParser::parseBool(list, "-midiout", m_midi_out_support);
        m_midi_only         = CamomileAtomParser::parseBool(list, "-midionly", m_midi_only);
        m_play_head_support = CamomileAtomParser::parseBool(list, "-playhead", m_midi_out_support);
        return true;
    }
    return false;
}

void CamomileAudioProcessor::receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(!processParameters(dest, msg, list) &&
       !processPrograms(dest, msg, list) &&
       !processMidi(dest, msg, list) &&
       !processOption(dest, msg, list))
    {
        std::cerr << "camomile unknow message : "<< msg << "\n";
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
