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
    updatePatch();
    addAndMakeVisible(m_button);
    startTimer(25);
}

CamomileEditor::~CamomileEditor() {}

void CamomileEditor::updatePatch()
{
    auto const bounds = m_processor.getPatch().getBounds();
    int const width  = bounds[2] > 0 ? std::max(bounds[2], 100) : 400;
    int const height = bounds[3] > 0 ? std::max(bounds[3], 100) : 300;
    if(width != getWidth() || height != getHeight())
    {
        setSize(width, height);
        if(m_image.getImage().isValid())
        {
            m_image.setTransformToFit(getBounds().toType<float>(), RectanglePlacement::fillDestination + RectanglePlacement::xLeft + RectanglePlacement::yTop);
            if(!m_image.isVisible())
            {
                addAndMakeVisible(m_image, 0);
            }
        }
    }
    updateObjects();
}

void CamomileEditor::updateObjects()
{
    m_labels.clear();
    m_objects.clear();
    auto const pbounds = m_processor.getPatch().getBounds();
    const auto bounds = getLocalBounds().expanded(2).translated(1, 1);
    for(auto& gui : m_processor.getPatch().getGuis())
    {
        PluginEditorObject* obj = PluginEditorObject::createTyped(*this, gui);
        if(obj)
        {
            obj->setTopLeftPosition(obj->getX() - pbounds[0], obj->getY() - pbounds[1]);
            if(bounds.contains(obj->getBounds()))
            {
                addAndMakeVisible(m_objects.add(obj));
            }
        }
    }
}

void CamomileEditor::timerCallback()
{
    CamomileEditorMessageManager::processMessages();
    for(auto object : m_objects)
    {
        object->updateValue();
    }
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
    updatePatch();
}

void CamomileEditor::guiRedraw()
{
    updateObjects();
}



