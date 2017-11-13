/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginParameter.h"
#include "PluginEditor.h"
#include <iostream>
#include <exception>

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //

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
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CamomileAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CamomileAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CamomileAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CamomileAudioProcessor::getNumPrograms()
{
    return 1;
}

int CamomileAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CamomileAudioProcessor::setCurrentProgram (int index)
{
}

const String CamomileAudioProcessor::getProgramName (int index)
{
    return {};
}

void CamomileAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

bool CamomileAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const AudioChannelSet& mainOutput = layouts.getMainOutputChannelSet();
    const AudioChannelSet& mainInput  = layouts.getMainInputChannelSet();
    
    //sendList(std::string("buses"), {});
    std::cout << "| Input : "<< mainInput.getDescription() << " | Output : " << mainOutput.getDescription() << " |\n";
    return true;
}

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDSP(AudioProcessor::getTotalNumInputChannels(),
            AudioProcessor::getTotalNumOutputChannels(),
            samplesPerBlock, sampleRate);
    
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
    
    // Play Head
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
    
    // Parameters
    {
        std::string const sparam("param");
        OwnedArray<AudioProcessorParameter> const& parameters = AudioProcessor::getParameters();
        for(int i = 0; i < parameters.size(); ++i)
        {
            sendList(sparam, {float(i+1), static_cast<CamomileAudioParameter const*>(parameters.getUnchecked(i))->getOriginalScaledValue()});
        }
    }
    
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

    performDSP(buffer.getNumSamples(),
            getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
            getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    
    processReceive();
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

void CamomileAudioProcessor::receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("param"))
    {
        if(list.size() >= 2 && list[0].isFloat() && list[1].isFloat())
        {
            CamomileAudioParameter* param = static_cast<CamomileAudioParameter *>(getParameters()[int(list[0].getFloat()) - 1]);
            if(param)
            {
                param->setOriginalScaledValueNotifyingHost(list[1].getFloat());
            }
            else
            {
                // Parameter out of range
            }
        }
        else
        {
            try
            {
                addParameter(CamomileAudioParameter::parse(list));
            }
            catch (std::exception& e)
            {
                std::cout << e.what();
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
