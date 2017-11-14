/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "xpd/xpd.h"

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //

class CamomileAudioProcessor  : public AudioProcessor, pd::instance
{
public:
    //==============================================================================
    CamomileAudioProcessor();
    ~CamomileAudioProcessor();

    //==============================================================================
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    void receiveBang(const std::string& dest) override;
    void receiveFloat(const std::string& dest, float num) override;
    void receiveSymbol(const std::string& dest, const std::string& symbol) override;
    void receiveList(const std::string& dest, const std::vector<pd::Atom>& list) override;
    void receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list) override;

private:
    MidiBuffer      m_midi_buffer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessor)
};
