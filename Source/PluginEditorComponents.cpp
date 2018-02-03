/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginEditorComponents.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      INTERACTION                                         //
//////////////////////////////////////////////////////////////////////////////////////////////
CamomileEditorButton::CamomileEditorButton() : Button("CamomileButton")
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
/*
void CamomileEditorButton::clicked()
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
            about->setText(Camomile_About_UTF8);
            about->setBounds(0, 0, 300, 370);
            
            window.setContentOwned(about, false);
            window.setName("About Camomile " + String(JucePlugin_VersionString));
            window.addToDesktop();
            window.toFront(false);
            window.grabKeyboardFocus();
            if(CamomileEnvironment::wantsKey())
            {
                window.addKeyListener(this);
            }
        }
    }
    else if(result == 2)
    {
        window.setContentOwned(new GuiConsole(processor), false);
        window.setName("Camomile Console");
        window.addToDesktop();
        window.toFront(true);
        window.grabKeyboardFocus();
        if(CamomileEnvironment::wantsKey())
        {
            window.addKeyListener(this);
        }
    }
}
*/

