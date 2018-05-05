/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginEditorComponents.h"
#include "PluginEditorConsole.hpp"
#include "PluginLookAndFeel.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      ABOUT PATCH                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

class AboutPatch : public TextEditor
{
public:
    AboutPatch()
    {
        setMultiLine(true);
        setReadOnly(true);
        setScrollbarsShown(false);
        setCaretVisible(false);
        setPopupMenuEnabled(true);
        setFont(CamoLookAndFeel::getDefaultFont());
        setWantsKeyboardFocus(true);
        setText(CamoLookAndFeel::getDescription());
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutPatch)
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      ABOUT CAMOMILE                                      //
//////////////////////////////////////////////////////////////////////////////////////////////

class AboutCamomile : public TextEditor
{
public:
    AboutCamomile()
    {
        setMultiLine(true);
        setReadOnly(true);
        setScrollbarsShown(false);
        setCaretVisible(false);
        setPopupMenuEnabled(true);
        setFont(CamoLookAndFeel::getDefaultFont());
        setWantsKeyboardFocus(true);
        if(PluginHostType::getPluginLoadedAs() == AudioProcessor::wrapperType_AudioUnit)
        {
            setText(String::createStringFromData(BinaryData::CreditsAU, BinaryData::CreditsAUSize));
        }
        else
        {
            setText(String::createStringFromData(BinaryData::CreditsVST, BinaryData::CreditsVSTSize));
        }
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutCamomile)
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      WINDOW                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

class CamomileEditorWindow : public DocumentWindow
{
public:
    CamomileEditorWindow() : DocumentWindow(String(""), Colours::lightgrey, DocumentWindow::closeButton, false)
    {
        setAlwaysOnTop(true);
        setUsingNativeTitleBar(true);
        setBounds(50, 50, 300, 370);
        setResizable(true, true);
        setDropShadowEnabled(true);
        setVisible(true);
        setWantsKeyboardFocus(true);
    }

    void closeButtonPressed() { removeFromDesktop(); }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorWindow)
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUTTON                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

CamomileEditorButton::CamomileEditorButton(CamomileAudioProcessor& processor) : Button("CamomileButton"),
m_processor(processor), m_window(new CamomileEditorWindow())
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
    
    m_window->setBounds(m_processor.getConsoleWindowBounds());
}

CamomileEditorButton::~CamomileEditorButton()
{
    m_processor.setConsoleWindowBounds(m_window->getBounds());
}

void CamomileEditorButton::buttonStateChanged()
{
    m_petals.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}

void CamomileEditorButton::clicked()
{
    if(m_window->isVisible() && m_window->isShowing())
    {
        m_window->toFront(true);
        m_window->grabKeyboardFocus();
        if(m_processor.getTrackProperties().name.isNotEmpty()) {
            m_window->setName(String(CamomileEnvironment::getPluginName()) + ": " + m_processor.getTrackProperties().name); }
    }
    else
    {
        TabbedComponent* tc = new TabbedComponent(TabbedButtonBar::TabsAtTop);
        if(tc)
        {
            tc->setBounds(0, 0, 300, 370);
            tc->addTab("Console", Colours::lightgrey, new PluginEditorConsole(m_processor), true);
            tc->addTab(CamomileEnvironment::getPluginName(), Colours::lightgrey, new AboutPatch(), true);
            tc->addTab("About Camomile", Colours::lightgrey, new AboutCamomile(), true);
            tc->setTabBarDepth(24);
            
            String const trackname = m_processor.getTrackProperties().name;
            String const name = String(CamomileEnvironment::getPluginName()) + (trackname.isEmpty() ? "" : trackname);
            m_window->setName(name);
            m_window->setContentOwned(tc, false);
            m_window->addToDesktop();
            m_window->toFront(true);
            m_window->grabKeyboardFocus();
        }
        
    }
}

