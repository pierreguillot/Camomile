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

#define Camomile_About "Author:\n" + String(JucePlugin_Manufacturer) + "\n\nOrganizations:\nCICM | Université Paris 8 | Labex Arts H2H\n\nWebsite:\n" + String(JucePlugin_ManufacturerWebsite)+ "/wiki\n\nCredits:\nPure Data by Miller Puckette and others\nJuce by ROLI Ltd.\nlibPd by the Pure Data community"

#ifdef JucePlugin_Build_VST
#define Steinberg_About "\nVST PlugIn Technology by Steinberg Media Technologies"
#elif JucePlugin_Build_VST3
#define Steinberg_About"\nVST PlugIn Technology by Steinberg Media Technologies"
#else
#define Steinberg_About ""
#endif

CamomileAudioProcessorEditor::CamomileAudioProcessorEditor(CamomileAudioProcessor& p) : AudioProcessorEditor (&p),
processor (p)
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
    addAndMakeVisible(button);
    button.addListener(this);
    
    window.setUsingNativeTitleBar(true);
    window.setBounds(50, 50, 300, 370);
    window.setResizable(false, false);
    window.setAlwaysOnTop(false);
    window.setDropShadowEnabled(true);
    window.setVisible(true);
    window.setBackgroundColour(Gui::getColorBg());
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
            TextEditor* about = new TextEditor();
            if(about)
            {
                about->setMultiLine(true);
                about->setReadOnly(true);
                about->setScrollbarsShown(false);
                about->setCaretVisible(false);
                about->setPopupMenuEnabled(true);
                about->setFont(Gui::getFont());
                about->setText(Camomile_About + Steinberg_About);
                about->setBounds(0, 0, 300, 370);
                
                window.setContentOwned(about, false);
                window.setName("About Camomile " + String(JucePlugin_VersionString));
                window.addToDesktop();
                window.toFront(false);
                window.setAlwaysOnTop(true);
            }
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

