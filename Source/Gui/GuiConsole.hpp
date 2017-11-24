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
    void paint(Graphics& g) final;
    int getNumRows() final { return static_cast<int>(m_size); }
    void paintRowBackground(Graphics& , int , int , int , bool ) final {}
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) final;
private:
    typedef CamomileConsole::Message Message;
    CamomileAudioProcessor& m_history;
    size_t          m_size = 0;
    TableListBox    m_table;
    Message::Level  m_level = Message::Level::Normal;
    
    class ClearButton : public Button
    {
    public:
        ClearButton();
        void paintButton(Graphics& g, bool over, bool down) final {};
        void buttonStateChanged() final;
    private:
        DrawableImage   m_image1;
        DrawableImage   m_image2;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClearButton)
    };
    
    class CopyButton : public Button
    {
    public:
        CopyButton();
        void paintButton(Graphics& g, bool over, bool down) final {};
        void buttonStateChanged() final;
    private:
        DrawableImage   m_image1;
        DrawableImage   m_image2;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CopyButton)
    };
    
    class LevelButton : public Button
    {
    public:
        LevelButton();
        void paintButton(Graphics& g, bool over, bool down) final {};
        void buttonStateChanged() final;
    private:
        DrawableImage   m_image1;
        DrawableImage   m_image2;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelButton)
    };
    
    ClearButton  m_clear_button;
    CopyButton   m_copy_button;
    LevelButton  m_level_button;
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiConsole)
};

