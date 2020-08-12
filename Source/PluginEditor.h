/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "PluginProcessor.h"
#include "PluginEditorInteraction.h"
#include "PluginEditorComponents.h"
#include "PluginEditorObject.hpp"

class CamomileEditor
: public AudioProcessorEditor
, protected Timer
, public CamomileEditorInteractionManager
{
public:
    CamomileEditor(CamomileAudioProcessor&);
    ~CamomileEditor();
    void paint(Graphics&) final;
    void timerCallback() final;
    void resized() override;
    //////////////////////////////////////////////////////////////////////////////////////////
    bool keyPressed(const KeyPress& key) final;
    bool keyStateChanged(bool isKeyDown) final;
    void modifierKeysChanged(const ModifierKeys& modifiers) final;
    
    void guiResize() final;
    void guiRedraw() final;
    
    void reloadPatch();
private:
    
    using object_uptr = std::unique_ptr<PluginEditorObject>;
    using label_uptr = std::unique_ptr<Component>;
    using object_pair = std::pair<object_uptr, label_uptr>;
    
    CamomileAudioProcessor&         m_processor;
    std::unique_ptr<GuiPatch>       m_patch;
    CamomileEditorButton            m_button;
    DrawableImage                   m_image;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileEditor)
};
