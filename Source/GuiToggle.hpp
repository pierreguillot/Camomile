/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_TOGGLE__
#define __CAMOMILE_GUI_TOGGLE__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

class GuiToggle : public GuiParameter
{
public:
    GuiToggle(InstanceProcessor& processor, pd::Gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
};


#endif
