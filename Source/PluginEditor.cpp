/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEnvironment.h"
#include "PluginLookAndFeel.hpp"
#include "Pd/PdPatch.hpp"

CamomileEditor::CamomileEditor(CamomileAudioProcessor& p) :
AudioProcessorEditor (&p), CamomileEditorInteractionManager(p), m_processor (p), m_button(p)
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    
    setOpaque(true);
    setWantsKeyboardFocus(true);
    setInterceptsMouseClicks(true, true);
    if(p.getPatch().isGraph())
    {
        auto bounds = p.getPatch().getBounds();
        setSize(std::max(bounds[2], 100), std::max(bounds[3], 100));
    }
    else
    {
        setSize(400, 300);
    }
    
    Image const& img = CamoLookAndFeel::getImage();
    if(img.isValid())
    {
        m_image.setImage(img);
        m_image.setTransformToFit(getBounds().toType<float>(), RectanglePlacement::stretchToFit);
        addAndMakeVisible(m_image, 0);
    }
    else
    {
        p.add(CamomileAudioProcessor::ConsoleLevel::Error,
                      "background image " + CamomileEnvironment::getImageName() + " is invalid or doesn't exist.");
    }
    
    if(p.getPatch().isGraph())
    {
        for(auto& gui : p.getPatch().getGuis()) {
            addAndMakeVisible(m_objects.add(PluginEditorObject::createTyped(*this, gui))); }
    }
    addAndMakeVisible(m_button);
    startTimer(25);
}

CamomileEditor::~CamomileEditor() {}

void CamomileEditor::timerCallback()
{
    CamomileEditorPanelManager::processMessages();
    for(auto object : m_objects) {
        object->update(); }
}


void CamomileEditor::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    if(!CamomileEnvironment::isValid())
    {
        g.setColour(Colours::black);
        g.drawText("Plugin Not Valid", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
    else if(!m_processor.getPatch().isGraph())
    {
        g.setColour(Colours::black);
        g.drawText("No Graphical User Interface Available", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileEditor::keyPressed(const KeyPress& key) {
    return CamomileEditorKeyManager::keyPressed(key); }

bool CamomileEditor::keyStateChanged(bool isKeyDown) {
    return CamomileEditorKeyManager::keyStateChanged(isKeyDown); }

void CamomileEditor::modifierKeysChanged(const ModifierKeys& modifiers) {
    CamomileEditorKeyManager::keyModifiersChanged(modifiers); }




