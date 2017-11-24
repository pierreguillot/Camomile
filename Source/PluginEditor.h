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
    
    class GuiWindow : public DocumentWindow
    {
    public:
        GuiWindow() : DocumentWindow(String(""), Gui::getColorBg(), DocumentWindow::closeButton, false) {}
        void closeButtonPressed() final { removeFromDesktop(); }
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiWindow)
    };
    
    CamomileAudioProcessor& processor;
    GuiWindow               window;
    GuiFlowerButton         button;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessorEditor)
};
