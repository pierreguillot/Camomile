/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEnvironment.h"
#include "Gui/LookAndFeel.hpp"
#include "Gui/Gui.hpp"
#include "Gui/GuiConsole.hpp"
#include "Pd/PdPatch.hpp"

CamomileAudioProcessorEditor::CamomileAudioProcessorEditor(CamomileAudioProcessor& p) :
AudioProcessorEditor (&p), CamomileEditorInteractionManager(p), processor (p), button(p)
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    setOpaque(true);
    setWantsKeyboardFocus(true);
    if(p.getPatch().isGraph())
    {
        auto bounds = p.getPatch().getBounds();
        setSize(std::max(bounds[2], 100), std::max(bounds[3], 100));
    }
    else
    {
        setSize(400, 300);
    }
    addAndMakeVisible(button);
    setInterceptsMouseClicks(true, true);
    
    if(processor.getPatch().isGraph())
    {
        auto guis(p.getPatch().getGuis());
        for(auto& gui : guis)
        {
            addAndMakeVisible(objects.add(GuiObject::createTyped(*this, gui)));
        }
    }
   
    if(!CamomileEnvironment::getImageName().empty())
    {
        File f(CamomileEnvironment::getPatchPath() + File::getSeparatorString() + String(CamomileEnvironment::getImageName()));
        if(f.exists())
        {
            Image img = ImageFileFormat::loadFrom(f);
            if(img.isValid())
            {
                background.setImage(img);
                background.setTransformToFit(getBounds().toType<float>(), RectanglePlacement::stretchToFit);
                addAndMakeVisible(background, 0);
            }
            else
            {
                processor.add(CamomileAudioProcessor::ConsoleLevel::Error,
                              "background image " + CamomileEnvironment::getImageName() + " is invalid");
            }
        }
        else
        {
            processor.add(CamomileAudioProcessor::ConsoleLevel::Error,
                               "background image " + CamomileEnvironment::getImageName() + " doesn't exist");
        }
    }
    startTimer(25);
}

CamomileAudioProcessorEditor::~CamomileAudioProcessorEditor()
{
    ;
}

void CamomileAudioProcessorEditor::timerCallback()
{
    CamomileEditorPanelManager::processMessages();
    for(auto object : objects)
    {
        object->update();
    }
}


void CamomileAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    if(!CamomileEnvironment::isValid())
    {
        g.setColour(Colours::black);
        g.drawText("Plugin Not Valid", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
    else if(!processor.getPatch().isGraph())
    {
        g.setColour(Colours::black);
        g.drawText("No Graphical User Interface Available", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileAudioProcessorEditor::keyPressed(const KeyPress& key)
{
    return CamomileEditorKeyManager::keyPressed(key);
}

bool CamomileAudioProcessorEditor::keyStateChanged(bool isKeyDown)
{
    return CamomileEditorKeyManager::keyStateChanged(isKeyDown);
}

void CamomileAudioProcessorEditor::modifierKeysChanged(const ModifierKeys& modifiers)
{
    CamomileEditorKeyManager::keyModifiersChanged(modifiers);
}




