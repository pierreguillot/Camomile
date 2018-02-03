/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginEditorComponents.h"
#include "Gui/Gui.hpp"
#include "Gui/GuiConsole.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      WINDOW                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

CamomileEditorWindow::CamomileEditorWindow() :
DocumentWindow(String(""), Colours::lightgrey, DocumentWindow::closeButton, false)
{
    setAlwaysOnTop(true);
    setUsingNativeTitleBar(true);
    setBounds(50, 50, 300, 370);
    setResizable(true, true);
    setDropShadowEnabled(true);
    setVisible(true);
    setWantsKeyboardFocus(true);
}

void CamomileEditorWindow::closeButtonPressed() { removeFromDesktop(); }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUTTON                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

CamomileEditorButton::CamomileEditorButton(CamomileAudioProcessor& processor) : Button("CamomileButton"),
m_processor(processor)
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_center.setImage(ImageCache::getFromMemory(BinaryData::flower_center_png, BinaryData::flower_center_pngSize));
    m_petals.setImage(ImageCache::getFromMemory(BinaryData::flower_petals_png, BinaryData::flower_petals_pngSize));
    m_center.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 18.f, 18.f), RectanglePlacement::stretchToFit);
    m_petals.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 18.f, 18.f), RectanglePlacement::stretchToFit);
    m_center.setAlwaysOnTop(true);
    addAndMakeVisible(m_center, -1);
    addAndMakeVisible(m_petals, 0);
    m_petals.setOverlayColour(Colours::black);
    m_petals.setAlpha(0.5f);
    setBounds(3, 3, 18, 18);
}

void CamomileEditorButton::buttonStateChanged()
{
    m_petals.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}

void CamomileEditorButton::clicked()
{
    juce::PopupMenu m;
    m.addItem(1, "About");
    m.addItem(2, "Console");
    const int result = m.showAt(getScreenBounds().translated(-2, 3));
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
            
#if defined(JucePlugin_Build_VST) || defined(JucePlugin_Build_VST3)
            about->setText(String::createStringFromData(BinaryData::CreditsVST, BinaryData::CreditsVSTSize));
#else
            about->setText(String::createStringFromData(BinaryData::CreditsAU, BinaryData::CreditsAUSize));
#endif
            about->setBounds(0, 0, 300, 370);
            about->setWantsKeyboardFocus(true);
            
            m_window.setContentOwned(about, false);
            m_window.setName("About Camomile " + String(JucePlugin_VersionString));
            m_window.addToDesktop();
            m_window.toFront(true);
            m_window.grabKeyboardFocus();
        }
    }
    else if(result == 2)
    {
        m_window.setContentOwned(new GuiConsole(m_processor), false);
        m_window.setName("Camomile Console");
        m_window.addToDesktop();
        m_window.toFront(true);
        m_window.grabKeyboardFocus();
    }
}

