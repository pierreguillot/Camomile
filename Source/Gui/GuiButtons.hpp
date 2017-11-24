/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

// ==================================================================================== //
//                                      GUI BUTTONS                                     //
// ==================================================================================== //

class GuiFlowerButton : public Button
{
public:
    GuiFlowerButton();    
    void paintButton(Graphics& g, bool over, bool down) final;
    void buttonStateChanged() final;
private:
    DrawableImage   m_center;
    DrawableImage   m_petals;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiFlowerButton)
};

class GuiClearButton : public Button
{
public:
    GuiClearButton();
    void paintButton(Graphics& g, bool over, bool down) final;
    void buttonStateChanged() final;
private:
    DrawableImage   m_image1;
    DrawableImage   m_image2;
    DrawableImage   m_image3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiClearButton)
};

class GuiCopyButton : public Button
{
public:
    GuiCopyButton();
    void paintButton(Graphics& g, bool over, bool down) final;
    void buttonStateChanged() final;
private:
    DrawableImage   m_image1;
    DrawableImage   m_image2;
    DrawableImage   m_image3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiCopyButton)
};

class GuiLevelButton : public Button
{
public:
    GuiLevelButton();
    void paintButton(Graphics& g, bool over, bool down) final;
    void buttonStateChanged() final;
private:
    DrawableImage   m_image1;
    DrawableImage   m_image2;
    DrawableImage   m_image3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiLevelButton)
};

