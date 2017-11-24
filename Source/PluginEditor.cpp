/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEnvironment.h"
#include "Gui/LookAndFeel.hpp"
#include "Gui/Gui.hpp"
#include "Pd/PdPatch.h"



CamomileAudioProcessorEditor::CamomileAudioProcessorEditor(CamomileAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    setOpaque(true);
    setWantsKeyboardFocus(true);
    auto size = p.getPatch().getSize();
    if(size.first && size.second)
    {
        setSize(std::max(size.first, 100), std::max(size.second, 100));
    }
    else
    {
        setSize(400, 300);
    }
    addAndMakeVisible(m_button);
    m_button.addListener(this);
}

CamomileAudioProcessorEditor::~CamomileAudioProcessorEditor()
{
}

void CamomileAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    if(!processor.getPatch().isGraph())
    {
        g.setColour(Gui::getColorTxt().withAlpha(0.5f));
        g.drawText("No Graph On Parent Available", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
}

void CamomileAudioProcessorEditor::buttonClicked(Button* button)
{
    if(button)
    {
        juce::PopupMenu m;
        m.addItem(1, "About");
        m.addItem(2, "Console");
        const int result = m.showAt(button->getScreenBounds().translated(-2, 3));
        
        if(result == 1)
        {
            m_window.setContentOwned(new GuiAbout(), false);
            m_window.setName("About Camomile " + String(JucePlugin_VersionString));
            m_window.addToDesktop();
            m_window.toFront(false);
            m_window.setAlwaysOnTop(true);
        }
        else if(result == 2)
        {
            /*
            m_window.setContentOwned(new GuiConsole(m_processor), false);
            m_window.setName("Camomile Console");
            m_window.addToDesktop();
            m_window.grabKeyboardFocus();
            m_window.toFront(true);
            m_window.setAlwaysOnTop(true);
             */
        }
    }
}

