/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

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
    void paint(Graphics& g) final;
    bool keyPressed(const KeyPress& key) final;
    
    int getNumRows() final { return static_cast<int>(m_size); }
    void paintRowBackground(Graphics& , int , int , int , bool ) final {}
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) final;
    void deleteKeyPressed(int lastRowSelected) final;
private:
    
    void clearSelection();
    void copySelection();
    
    typedef CamomileAudioProcessor::ConsoleLevel ConsoleLevel;
    CamomileAudioProcessor& m_history;
    size_t          m_size = 0;
    TableListBox    m_table;
    ConsoleLevel    m_level = ConsoleLevel::Normal;
    
    class GButton : public Button
    {
    public:
        GButton(Image const& image1, Image const& image2, int index);
        void paintButton(Graphics& g, bool over, bool down) final {};
        void buttonStateChanged() final;
    private:
        DrawableImage   m_image1;
        DrawableImage   m_image2;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GButton)
    };
    
    GButton m_level_button;
    GButton m_clear_button;
    GButton m_copy_button;
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiConsole)
};

