/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_SLIDER__
#define __CAMOMILE_GUI_SLIDER__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI SLIDER                                      //
// ==================================================================================== //

class GuiSlider : public GuiParameter
{
public:
    static const pd::Gui::Type Horizontal = pd::Gui::Type::HorizontalSlider;
    static const pd::Gui::Type Vertical   = pd::Gui::Type::VerticalSlider;
    GuiSlider(InstanceProcessor& processor, pd::Gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
    void mouseDrag(const MouseEvent& event) final;
    void mouseUp(const MouseEvent& event) final;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiSlider)
};


#endif
