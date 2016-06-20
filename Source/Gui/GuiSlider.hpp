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
    static const xpd::gui::type_t Horizontal = xpd::gui::type_t::slider_horizontal;
    static const xpd::gui::type_t Vertical   = xpd::gui::type_t::slider_vertical;
    GuiSlider(InstanceProcessor& processor, xpd::gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
    void mouseDrag(const MouseEvent& event) final;
    void mouseUp(const MouseEvent& event) final;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiSlider)
};


#endif
