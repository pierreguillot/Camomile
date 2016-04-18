/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiLabel.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI LABEL                                       //
// ==================================================================================== //


GuiLabel::GuiLabel(InstanceProcessor& processor, pd::Gui const& gui) :
Label("label", String(gui.getName()) + " " + gui.getLabel())
{
    pd::Point<int> labelpos(gui.getLabelPosition());
    setFont(Gui::getFont());
    setJustificationType(Justification::topLeft);
    setColour(Label::backgroundColourId, Gui::getColorInv());
    setColour(Label::textColourId, Gui::getColorTxt());
    setBorderSize(BorderSize<int>());
    setBounds(labelpos.x, labelpos.y - Gui::getFont().getHeight() * 0.5, 1000, 200);
    setInterceptsMouseClicks(false, false);
}

GuiLabel::~GuiLabel()
{
    
}