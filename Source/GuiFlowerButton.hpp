/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_FLOWER_BUTTON__
#define __CAMOMILE_GUI_FLOWER_BUTTON__

#include "InstanceProcessor.hpp"

// ==================================================================================== //
//                                      GUI FLOWER BUTTON                               //
// ==================================================================================== //

class GuiFlowerButton : public Button
{
public:
    GuiFlowerButton();    
    void paintButton(Graphics& g, bool over, bool down) final;
    void buttonStateChanged() final;
private:
    DrawableImage   m_image1;
    DrawableImage   m_image2;
    DrawableImage   m_image3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiFlowerButton)
};

#endif
