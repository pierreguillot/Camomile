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
    static const pd::Gui::Type Horizontal = pd::Gui::Type::HorizontalRadio;
    static const pd::Gui::Type Vertical   = pd::Gui::Type::VerticalRadio;
    GuiRadio(InstanceProcessor& processor, pd::Gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
};


#endif
