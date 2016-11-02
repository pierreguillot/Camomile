/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_RADIO__
#define __CAMOMILE_GUI_RADIO__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI RADIO                                       //
// ==================================================================================== //

class GuiRadio : public GuiParameter
{
public:
    static const xpd::gui::type_t Horizontal = xpd::gui::radio_horizontal;
    static const xpd::gui::type_t Vertical   = xpd::gui::radio_vertical;
    GuiRadio(CamomileProcessor& processor, xpd::gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiRadio)
};


#endif
