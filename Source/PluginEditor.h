/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "PluginProcessor.h"
#include "PluginEditorInteraction.h"
#include "PluginEditorComponents.h"
#include "Gui/Gui.hpp"
#include "Gui/GuiObject.hpp"

class CamomileAudioProcessorEditor : public AudioProcessorEditor, public Button::Listener,
protected Timer, public KeyListener,  public CamomileEditorInteractionManager
{
public:
    CamomileAudioProcessorEditor(CamomileAudioProcessor&);
    ~CamomileAudioProcessorEditor();
    void paint(Graphics&) final;
    void buttonClicked(Button* button) final;
    void timerCallback() final;
    
    //////////////////////////////////////////////////////////////////////////////////////////
    bool keyPressed(const KeyPress& key) final;
    bool keyStateChanged(bool isKeyDown) final;
    void modifierKeysChanged(const ModifierKeys& modifiers) final;
    bool keyPressed(const KeyPress& key, Component* originatingComponent) final;
    bool keyStateChanged(bool isKeyDown, Component* originatingComponent) final;
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void focusGained(FocusChangeType t) final;
private:
    
    class GWindow : public DocumentWindow
    {
    public:
        GWindow() : DocumentWindow(String(""), Gui::getColorBg(), DocumentWindow::closeButton, false) {}
        void closeButtonPressed() final { removeFromDesktop(); }
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GWindow)
    };
    
    CamomileAudioProcessor&     processor;
    GWindow                     window;
    CamomileEditorButton        button;
    OwnedArray<GuiObject>       objects;
    DrawableImage               background;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessorEditor)
};
