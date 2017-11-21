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


class CamomileAudioProcessor : public AudioProcessor, pd::instance
{
public:
    //==============================================================================
    CamomileAudioProcessor();
    ~CamomileAudioProcessor() {}

    //==============================================================================
    bool isBusesLayoutSupported (const BusesLayout& layouts) const final;
    void prepareToPlay (double sampleRate, int samplesPerBlock) final;
    void releaseResources() final;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) final;

    //==============================================================================
    AudioProcessorEditor* createEditor() final;
    bool hasEditor() const final;

    const String getName() const final { return CamomileEnvironment::getPluginName(); }
    bool acceptsMidi() const final { return CamomileEnvironment::wantsMidi(); }
    bool producesMidi() const final { return CamomileEnvironment::producesMidi(); }
    bool isMidiEffect () const final { return CamomileEnvironment::isMidiOnly(); }
    double getTailLengthSeconds() const final { return static_cast<float>(CamomileEnvironment::getTailLengthSeconds()); }

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    void receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list) override;

private:
    
    bool processParameters(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processPrograms(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processMidi(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processOption(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processPost(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processChannels(const std::string& msg, const std::vector<pd::Atom>& list);
    
    MidiBuffer      m_midi_buffer;
    
    typedef struct
    {
        String       name;
        String       alias;
        Array<float> values;
    } Program;
    
    Array<Program>  m_programs;
    int             m_program_current = 0;
    
    StringArray m_input_sets;
    StringArray m_output_sets;
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessor)
};
