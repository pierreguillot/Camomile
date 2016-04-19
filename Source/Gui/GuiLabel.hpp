/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_LABEL__
#define __CAMOMILE_GUI_LABEL__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI LABEL                                       //
// ==================================================================================== //

class GuiLabel : public Label
{
public:
    GuiLabel(InstanceProcessor& processor, xpd::Gui const& gui);
    ~GuiLabel();
};


#endif
