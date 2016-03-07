/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiToggle.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

GuiToggle::GuiToggle(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiToggle::paint(Graphics& g)
{
    g.fillAll(GuiParameter::getColorBg());
    g.setColour(GuiParameter::getColorBd());
    g.drawRect(getLocalBounds(), GuiParameter::getBordersize());
    if(getValue() != 0.f)
    {
        g.drawLine(0, 0, getWidth(), float(getHeight()), getBordersize());
        g.drawLine(getWidth(), 0, 0, getHeight(), getBordersize());
    }
}

void GuiToggle::mouseDown(const MouseEvent& event)
{
    startEdition();
    setValue(1.f - getValue());
    stopEdition();
}


