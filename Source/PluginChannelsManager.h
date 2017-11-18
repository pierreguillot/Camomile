/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "xpd/xpd.h"

class CamomileEffectManager : virtual AudioProcessor
{
public:
    bool acceptsMidi() const final { return m_midi_in_support; };
    bool producesMidi() const final { return m_midi_out_support; };
    bool isMidiEffect () const final { return m_midi_only; };
    bool wantPlayHead () const { return m_play_head_support; };
    
    bool supportInput(const String& name);
    bool supportOutput(const String& name);
    
    bool process(const std::vector<pd::Atom>& list);
    
private:
    bool    m_midi_in_support   =false;
    bool    m_midi_out_support  =false;
    bool    m_play_head_support =false;
    bool    m_midi_only         =false;
    
    AudioProcessor::BusesLayout m_layout_inputs;
    AudioProcessor::BusesLayout m_layout_outputs;
    StringArray m_input_sets;
    StringArray m_output_sets;
    
    void parseOptions(const std::vector<pd::Atom>& list);
    
    bool processParameters(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processPrograms(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processMidi(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    
    bool processPost(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list);
    bool processChannels(const std::string& msg, const std::vector<pd::Atom>& list);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEffectManager)
};
