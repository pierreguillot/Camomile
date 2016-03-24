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
    g.drawRect(getLocalBounds(), Gui::getBorderSize());
    if(getType() == Horizontal)
    {
        const float width = float(getHeight());
        for(size_t i = 1; i < size_t(getMaximum()) + 1; ++i)
        {
            g.drawLine(width * float(i), 0.f, width * float(i), width, Gui::getBorderSize());
        }
        const float offset = std::max(float(getHeight()) * 0.125f, Gui::getBorderSize() + 1.f);
        g.fillRect(width * getValue() + offset, offset, width - offset * 2.f, width - offset * 2.f);
    }
    else
    {
        const float height = float(getWidth());
        for(size_t i = 1; i < size_t(getMaximum()) + 1; ++i)
        {
            g.drawLine(0.f, height * float(i), height, height * float(i), Gui::getBorderSize());
        }
        const float offset = std::max(float(getWidth()) * 0.125f, Gui::getBorderSize() + 1.f);
        g.fillRect(offset, height * getValue() + offset, height - offset * 2.f, height - offset * 2.f);
    }
}

void GuiRadio::mouseDown(const MouseEvent& event)
{
    startEdition();
    if(getType() == Horizontal)
    {
        const float width = float(getWidth()) / (getMaximum() + 1.f);
        setValue(std::floor(float(event.x) / width));
    }
    else
    {
        const float width = float(getHeight()) / (getMaximum() + 1.f);
        setValue(std::floor(float(event.y) / width));
    }
    stopEdition();
}


