/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiSlider.hpp"
#include "PatchEditor.h"

// ==================================================================================== //
//                                      GUI SLIDER                                      //
// ==================================================================================== //

GuiSlider::GuiSlider(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiSlider::paint(Graphics& g)
{
    g.fillAll(PatchEditor::getColorBg());
    g.setColour(PatchEditor::getColorBd());
    g.drawRect(getLocalBounds(), PatchEditor::getBordersize());
    if(getType() == Horizontal)
    {
        const float pos = (getMinimum() < getMaximum()) ?
        getValueNormalized() * float(getWidth() - 4.) + 2.f :
        (1.f - getValueNormalized()) * float(getWidth() - 4.) + 2.f;
        g.drawLine(pos, 0.f, pos, float(getHeight()), 1.f);
    }
    else
    {
        const float pos = (getMinimum() < getMaximum()) ?
        getValueNormalized() * float(getHeight() - 4.) + 2.f :
        (1.f - getValueNormalized()) * float(getHeight() - 4.) + 2.f;
        g.drawLine(0.f, pos, getWidth(), pos, 1.f);
    }
}

void GuiSlider::mouseDown(const MouseEvent& event)
{
    const float pos = (getType() == Horizontal) ? float(event.x) : float(event.y);
    const float wid = (getType() == Horizontal) ? float(getWidth()): float(getHeight());
    setValueNormalized(std::min(std::max(pos - 2.f, 0.f), wid - 4.f) / (wid - 4.f));
    pd::Pd::addConsole(std::to_string(std::min(std::max(pos - 2.f, 0.f), wid - 4.f) / (wid - 4.f)) + "\n");
}

void GuiSlider::mouseDrag(const MouseEvent& event)
{
    const float pos = (getType() == Horizontal) ? float(event.x) : float(event.y);
    const float wid = (getType() == Horizontal) ? float(getWidth()): float(getHeight());
    setValueNormalized(std::min(std::max(pos - 2.f, 0.f), wid - 4.f) / (wid - 4.f));
    pd::Pd::addConsole(std::to_string(std::min(std::max(pos - 2.f, 0.f), wid - 4.f) / (wid - 4.f)) + "\n");
}

