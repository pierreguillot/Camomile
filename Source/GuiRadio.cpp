/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiRadio.hpp"
#include "PatchEditor.h"

// ==================================================================================== //
//                                      GUI RADIO                                       //
// ==================================================================================== //

GuiRadio::GuiRadio(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiRadio::paint(Graphics& g)
{
    g.fillAll(PatchEditor::getColorBg());
    g.setColour(PatchEditor::getColorBd());
    g.drawRect(getLocalBounds(), PatchEditor::getBordersize());
    if(getType() == Horizontal)
    {
        const float width = (float(getWidth()) - getMaximum()) / getMaximum();
        for(size_t i = 1; i < size_t(getMaximum()); ++i)
        {
            g.drawLine(width * float(i) + float(i), 0.f, width * float(i) + float(i), float(getHeight()));
        }
        const float ratio = float(getWidth()) / getMaximum();
        g.fillRect(ratio * getValueNormalized() + ratio * 0.125f, ratio * 0.125f,
                   ratio * 0.75f, ratio * 0.75f);
    }
    else
    {
        const float height = (float(getHeight()) - getMaximum()) / getMaximum();
        for(size_t i = 1; i < size_t(getMaximum()); ++i)
        {
            g.drawLine(0.f, height * float(i) + float(i), float(getWidth()), height * float(i) + float(i));
        }
        const float ratio = float(getHeight()) / float(getMaximum());
        g.fillRect(ratio * 0.125f, ratio * getValueNormalized() + ratio * 0.125f,
                   ratio * 0.75f, ratio * 0.75f);
    }
}

void GuiRadio::mouseDown(const MouseEvent& event)
{
    if(getType() == Horizontal)
    {
        setValueNormalized(std::round((float(event.x) * getMaximum()) / getWidth()));
    }
    else
    {
        setValueNormalized(std::round((float(event.y) * getMaximum()) / getHeight()));
    }
}


