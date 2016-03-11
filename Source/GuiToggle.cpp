/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiToggle.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

GuiToggle::GuiToggle(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiToggle::paint(Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(getLocalBounds(), Gui::getBorderSize());
    if(getValue() != 0.f)
    {
        g.drawLine(0, 0, getWidth(), float(getHeight()), Gui::getBorderSize());
        g.drawLine(getWidth(), 0, 0, getHeight(), Gui::getBorderSize());
    }
}

void GuiToggle::mouseDown(const MouseEvent& event)
{
    startEdition();
    setValue(1.f - getValue());
    stopEdition();
}


