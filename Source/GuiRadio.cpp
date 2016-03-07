/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiRadio.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI RADIO                                       //
// ==================================================================================== //

GuiRadio::GuiRadio(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiRadio::paint(Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(getLocalBounds(), Gui::getBordersize());
    if(getType() == Horizontal)
    {
        const float width = float(getWidth()) / getMaximum();
        for(size_t i = 1; i < size_t(getMaximum()); ++i)
        {
            g.drawLine(width * float(i), 0.f, width * float(i), float(getHeight()), Gui::getBordersize());
        }
        g.fillRect(width * getValue() + width * 0.125f, float(getHeight()) * 0.125f, width * 0.75f, float(getHeight()) * 0.75f);
    }
    else
    {
        const float height = float(getHeight()) / getMaximum();
        for(size_t i = 1; i < size_t(getMaximum()); ++i)
        {
            g.drawLine(0.f, height * float(i), float(getWidth()), height * float(i), Gui::getBordersize());
        }
        g.fillRect(float(getWidth()) * 0.125f, height * getValue() + height * 0.125f, float(getWidth()) * 0.75f, height  * 0.75f);
    }
}

void GuiRadio::mouseDown(const MouseEvent& event)
{
    startEdition();
    if(getType() == Horizontal)
    {
        const float width = float(getWidth()) / getMaximum();
        setValue(std::floor(float(event.x) / width));
    }
    else
    {
        const float width = float(getHeight()) / getMaximum();
        setValue(std::floor(float(event.y) / width));
    }
    stopEdition();
}


