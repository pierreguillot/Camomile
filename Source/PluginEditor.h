/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "PluginProcessor.h"
#include "Gui/Gui.hpp"

class CamomileAudioProcessorEditor : public AudioProcessorEditor, public Button::Listener
{
public:
    CamomileAudioProcessorEditor(CamomileAudioProcessor&);
    ~CamomileAudioProcessorEditor();
    void paint(Graphics&) final;
    void buttonClicked(Button* button) final;
private:
    
    class GWindow : public DocumentWindow
    {
    public:
        GWindow() : DocumentWindow(String(""), Gui::getColorBg(), DocumentWindow::closeButton, false) {}
        void closeButtonPressed() final { removeFromDesktop(); }
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GWindow)
    };
    
    class FlowerButton : public Button
    {
    public:
        FlowerButton();
        void paintButton(Graphics& g, bool over, bool down) final {};
        void buttonStateChanged() final;
    private:
        DrawableImage   m_center;
        DrawableImage   m_petals;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowerButton)
    };

    
    CamomileAudioProcessor& processor;
    GWindow                window;
    FlowerButton            button;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessorEditor)
};
