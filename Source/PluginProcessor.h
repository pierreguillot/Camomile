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
    
    bool processParameters(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processPrograms(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processMidi(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processOption(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processPost(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processChannels(const std::string& msg, const std::vector<pd::Atom>& list);
    
    bool            m_midi_in_support   =false;
    bool            m_midi_out_support  =false;
    bool            m_midi_only         =false;
    bool            m_play_head_support =false;
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
