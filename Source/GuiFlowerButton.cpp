/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiFlowerButton.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI BUTTON                                      //
// ==================================================================================== //

GuiFlowerButton::GuiFlowerButton() : Button("CamomileButton")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::flower1_png, BinaryData::flower1_pngSize));
    m_image2.setImage(ImageCache::getFromMemory(BinaryData::flower1_png, BinaryData::flower1_pngSize));
    m_image3.setImage(ImageCache::getFromMemory(BinaryData::flower2_png, BinaryData::flower2_pngSize));
    m_image1.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
    m_image3.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
    m_image1.setOverlayColour(Gui::getColorTxt());
    m_image2.setOverlayColour(Gui::getColorTxt().interpolatedWith(Gui::getColorBg(), 0.5f));
    addAndMakeVisible(m_image1, 0);
    addChildComponent(m_image2, 0);
    addAndMakeVisible(m_image3, -1);
    m_image3.setAlwaysOnTop(true);
    setBounds(3, 3, 15, 15);
}

void GuiFlowerButton::paintButton(Graphics& g, bool over, bool down)
{
    
}

void GuiFlowerButton::buttonStateChanged()
{
    if(isDown() || isOver())
    {
        m_image1.setVisible(false);
        m_image2.setVisible(true);
    }
    else
    {
        m_image1.setVisible(true);
        m_image2.setVisible(false);
    }
}



GuiClearButton::GuiClearButton() : Button("ClearButton")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::clear0_png, BinaryData::clear0_pngSize));
    m_image2.setImage(ImageCache::getFromMemory(BinaryData::clear1_png, BinaryData::clear1_pngSize));
    m_image1.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
    m_image1.setOverlayColour(Gui::getColorTxt());
    m_image2.setOverlayColour(Gui::getColorTxt().interpolatedWith(Gui::getColorBg(), 0.5f));
    addAndMakeVisible(m_image1, 0);
    addChildComponent(m_image2, 0);

    setBounds(3, 353, 15, 15);
}

void GuiClearButton::paintButton(Graphics& g, bool over, bool down)
{
    
}

void GuiClearButton::buttonStateChanged()
{
    if(isDown() || isOver())
    {
        m_image1.setVisible(false);
        m_image2.setVisible(true);
    }
    else
    {
        m_image1.setVisible(true);
        m_image2.setVisible(false);
    }
}
