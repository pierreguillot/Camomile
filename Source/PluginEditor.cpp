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
    static CamoLookAndFeel laf;
    LookAndFeel::setDefaultLookAndFeel(&laf);
    
    setOpaque(true);
    setWantsKeyboardFocus(true);
    setInterceptsMouseClicks(true, true);
    m_image.setImage(CamoLookAndFeel::getImage());
    if(m_image.getImage().isNull() && !CamomileEnvironment::getImageName().empty())
    {
        m_processor.add(CamomileAudioProcessor::ConsoleLevel::Error,
                        "background image " + CamomileEnvironment::getImageName() +
                        " is invalid or doesn't exist.");
    }
    addAndMakeVisible(m_button);
    reloadPatch();
    startTimer(25);
}

CamomileEditor::~CamomileEditor() {}

void CamomileEditor::timerCallback()
{
    CamomileEditorMessageManager::processMessages();
    if(m_patch != nullptr)
    {
        m_patch->updateObjectsValues();
    }
}

void CamomileEditor::paint(Graphics& g)
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

void CamomileEditor::resized()
{
    if(m_image.getImage().isValid())
    {
        m_image.setTransformToFit(getBounds().toType<float>(), RectanglePlacement::fillDestination + RectanglePlacement::xLeft + RectanglePlacement::yTop);
        if(!m_image.isVisible())
        {
            addAndMakeVisible(m_image, 0);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileEditor::keyPressed(const KeyPress& key)
{
    return CamomileEditorKeyManager::keyPressed(key);
}

bool CamomileEditor::keyStateChanged(bool isKeyDown)
{
    return CamomileEditorKeyManager::keyStateChanged(isKeyDown);
}

void CamomileEditor::modifierKeysChanged(const ModifierKeys& modifiers)
{
    CamomileEditorKeyManager::keyModifiersChanged(modifiers);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileEditor::guiResize()
{
    if(m_patch != nullptr)
    {
        m_patch->updateSize();
        setSize(m_patch->getWidth(), m_patch->getHeight());
    }
}

void CamomileEditor::guiRedraw()
{
    if(m_patch != nullptr)
    {
        m_patch->updateObjects();
    }
}

void CamomileEditor::reloadPatch()
{
    m_patch = std::make_unique<GuiPatch>(*this, m_processor.getPatch());
    if(m_patch)
    {
        addAndMakeVisible(m_patch.get(), 0);
        setSize(m_patch->getWidth(), m_patch->getHeight());
    }
}
