/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../PluginProcessor.h"

// ==================================================================================== //
//                                      GUI CONSOLE                                      //
// ==================================================================================== //

class GuiConsole : public juce::Component, public juce::Timer,
public juce::Button::Listener, public juce::TableListBoxModel
{
public:
    GuiConsole(CamomileAudioProcessor& p);
    ~GuiConsole();
    void timerCallback() final;
    void buttonClicked(Button* button) final;
    
    int getNumRows() final;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) final;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) final;
    bool keyPressed(const KeyPress& key) final;
private:
    CamomileAudioProcessor& m_processor;
    size_t          m_size;
    TableListBox    m_table;
    /*
    GuiClearButton  m_clear_button;
    GuiCopyButton   m_copy_button;
    GuiLevelButton  m_level_button;
     */
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiConsole)
};

