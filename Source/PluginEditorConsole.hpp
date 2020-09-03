/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "PluginProcessor.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          CONSOLE                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

class PluginEditorConsole : public Component, public Timer, public Button::Listener, public ListBoxModel
{
public:
    PluginEditorConsole(CamomileAudioProcessor& p);
    ~PluginEditorConsole();
    void timerCallback() final;
    void buttonClicked(Button* button) final;
    void paint(Graphics& g) final;
    bool keyPressed(const KeyPress& key) final;
    void resized() final;
    
    int getNumRows() final { return static_cast<int>(m_size); }
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) final;
    void deleteKeyPressed(int lastRowSelected) final;
private:
    
    void clearSelection();
    void copySelection();
    typedef CamomileAudioProcessor::ConsoleLevel ConsoleLevel;
    CamomileAudioProcessor& m_history;
    size_t                  m_size = 0;
    ListBox                 m_table;
    ConsoleLevel            m_level = ConsoleLevel::Normal;
    std::unique_ptr<Button>   m_level_button;
    std::unique_ptr<Button>   m_clear_button;
    std::unique_ptr<Button>   m_copy_button;
    std::unique_ptr<Button>   m_reload_button;
    Font                    m_font;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditorConsole)
};

