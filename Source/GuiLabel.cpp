/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiLabel.hpp"

// ==================================================================================== //
//                                      GUI LABEL                                       //
// ==================================================================================== //


GuiLabel::GuiLabel(InstanceProcessor& processor, pd::Gui const& gui) :
Label("label", String(gui.getName()) + " " + gui.getLabel())
{
    std::array<float, 2> labelpos(gui.getLabelPosition());
    setFont(GuiParameter::getFont());
    setJustificationType(Justification::topLeft);
    setColour(Label::backgroundColourId, GuiParameter::getColorInv());
    setColour(Label::textColourId, GuiParameter::getColorTxt());
    setBorderSize(BorderSize<int>());
    setBounds(labelpos[0], labelpos[1] - GuiParameter::getFont().getHeight() * 0.5, 1000, 200);
    setInterceptsMouseClicks(false, false);
}

GuiLabel::~GuiLabel()
{
    
}