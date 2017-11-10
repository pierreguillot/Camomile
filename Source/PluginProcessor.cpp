/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginParameter.h"
#include "PluginEditor.h"
#include <iostream>

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
    std::cout << "Load Camomile :\n";
    juce::File const plugin = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getFullPathName();
    if(plugin.exists())
    {
        juce::String name   = plugin.getFileNameWithoutExtension();
        juce::File   infos  = plugin.getFullPathName() + CAMOMILE_RESSOURCE_PATH +  juce::File::getSeparatorString() + name + juce::String(".txt");
        bind("camomile");
        
        open((plugin.getFullPathName() + CAMOMILE_RESSOURCE_PATH).toStdString(), name.toStdString() + std::string(".pd"));
        processReceive();

        std::cout << "nparams " << getNumParameters() << "\n";
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
    return true;
}

void CamomileAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDSP(AudioProcessor::getTotalNumInputChannels(),
            AudioProcessor::getTotalNumOutputChannels(),
            samplesPerBlock, sampleRate);
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
    
    {
        /*
        OwnedArray<AudioProcessorParameter> const& parameters = AudioProcessor::getParameters();
        for(int i = 0; i < parameters.size(); ++i)
        {
            CamomileAudioParameter const*p = static_cast<CamomileAudioParameter const*>(parameters.getUnchecked(i));
            sendFloat(std::string("param") + std::to_string(i+1), p->getOriginalScaledValue());
        }
         */
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

//==============================================================================
void CamomileAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CamomileAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void CamomileAudioProcessor::receiveBang(const std::string& dest)
{
    std::cout << "receiveBang\n";
}

void CamomileAudioProcessor::receiveFloat(const std::string& dest, float num)
{
    std::cout << "receiveFloat\n";
}

void CamomileAudioProcessor::receiveSymbol(const std::string& dest, const std::string& symbol)
{
    std::cout << "receiveSymbol\n";
}

void CamomileAudioProcessor::receiveList(const std::string& dest, const std::vector<pd::Atom>& list)
{
    
}

void CamomileAudioProcessor::parseParameter(const std::vector<pd::Atom>& list)
{
    addParameter(new CamomileAudioParameter((list.size() > 0 && list[0].isSymbol()) ? list[0].getSymbol() : "",
                                            (list.size() > 1 && list[1].isSymbol()) ? list[1].getSymbol() : "",
                                            (list.size() > 2 && list[2].isFloat()) ? list[2].getFloat() : 0,
                                            (list.size() > 3 && list[3].isFloat()) ? list[3].getFloat() : 1,
                                            (list.size() > 4 && list[4].isFloat()) ? list[4].getFloat() : 0,
                                            (list.size() > 5 && list[5].isFloat()) ? static_cast<int>(list[5].getFloat()) : 0,
                                            (list.size() > 6 && list[6].isFloat()) ? static_cast<bool>(list[6].getFloat()) : true,
                                            (list.size() > 7 && list[7].isFloat()) ? static_cast<bool>(list[7].getFloat()) : false));
    /*
    std::cout << "New Parameter : ";
    std::cout << "name " << ((list.size() > 0 && list[0].isSymbol()) ? list[0].getSymbol() : "") << " ";
    std::cout << "label " << ((list.size() > 1 && list[1].isSymbol()) ? list[1].getSymbol() : "") << " ";
    std::cout << "min " << ((list.size() > 2 && list[2].isFloat()) ? list[2].getFloat() : 0) << " ";
    std::cout << "max " << ((list.size() > 3 && list[3].isFloat()) ? list[3].getFloat() : 1) << " ";
    std::cout << "default " << ((list.size() > 4 && list[4].isFloat()) ? list[4].getFloat() : 0) << " ";
    std::cout << "nsteps " << ((list.size() > 5 && list[5].isFloat()) ? static_cast<int>(list[5].getFloat()) : 0) << " ";
    std::cout << "auto " << ((list.size() > 6 && list[6].isFloat()) ? static_cast<bool>(list[6].getFloat()) : true) << " ";
    std::cout << "meta " << ((list.size() > 7 && list[7].isFloat()) ? static_cast<bool>(list[7].getFloat()) : false);
    std::cout << "\n";
     */
}

void CamomileAudioProcessor::receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("param"))
    {
        parseParameter(list);
    }
    /*
    
     */
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CamomileAudioProcessor();
}
