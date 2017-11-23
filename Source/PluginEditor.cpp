/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEnvironment.h"
#include "Gui/Gui.hpp"
#include "Pd/PdPatch.h"


CamomileAudioProcessorEditor::CamomileAudioProcessorEditor(CamomileAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setOpaque(true);
    setWantsKeyboardFocus(true);
    auto size = p.getPatch().getSize();
    if(size.first && size.second)
    {
        setSize(std::max(size.first, 100), std::max(size.second + 20, 120));
    }
    else
    {
        setSize(400, 300);
    }
}

CamomileAudioProcessorEditor::~CamomileAudioProcessorEditor()
{
}

void CamomileAudioProcessorEditor::paint (Graphics& g)
{
    String const text = CamomileEnvironment::getPluginName().empty() ?
    String("Invalid Patch") : String(CamomileEnvironment::getPluginName());
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(getBounds().withZeroOrigin(), Gui::getBorderSize());
    g.drawLine(0.f, 20.f, getWidth(), 20.f, Gui::getBorderSize());
    g.setFont(Gui::getFont());
    g.setColour(Gui::getColorTxt());
    g.drawText(text, 0, 0, getWidth(), 20 + Gui::getFont().getDescent() , juce::Justification::centred);
    
    if(!processor.getPatch().isGraph())
    {
        g.drawText("No Graph On Parent Available", 0, 20, getWidth(), getHeight()-20, juce::Justification::centred);
    }
}

void CamomileAudioProcessorEditor::resized()
{
    
}
