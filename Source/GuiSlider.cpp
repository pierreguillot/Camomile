/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiSlider.hpp"

// ==================================================================================== //
//                                      GUI SLIDER                                      //
// ==================================================================================== //

GuiSlider::GuiSlider(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    
}

void GuiSlider::paint(Graphics& g)
{
    g.fillAll(GuiParameter::getColorBg());
    g.setColour(GuiParameter::getColorBd());
    g.drawRect(getLocalBounds(), GuiParameter::getBordersize());
    if(getType() == Horizontal)
    {
        const float pos = getValueNormalized() * float(getWidth() - 4.) + 2.f;
        g.drawLine(pos, 0.f, pos, float(getHeight()), getBordersize());
    }
    else
    {
        const float pos = (1.f - getValueNormalized())* float(getHeight() - 4.) + 2.f;
        g.drawLine(0.f, pos, getWidth(), pos, getBordersize());
    }
}

void GuiSlider::mouseDown(const MouseEvent& event)
{
    startEdition();
    if(getType() == Horizontal)
    {
        
        setValueNormalized(std::min(std::max(float(event.x) - 2.f, 0.f), float(getWidth()) - 4.f) / (float(getWidth()) - 4.f));
    }
    else
    {
        setValueNormalized(std::min(std::max((float(getHeight()) - float(event.y)) - 2.f, 0.f), float(getHeight()) - 4.f) / (float(getHeight()) - 4.f));
    }
}

void GuiSlider::mouseDrag(const MouseEvent& event)
{
    if(getType() == Horizontal)
    {
        setValueNormalized(std::min(std::max(float(event.x) - 2.f, 0.f), float(getWidth()) - 4.f) / (float(getWidth()) - 4.f));
    }
    else
    {
        setValueNormalized(std::min(std::max((float(getHeight()) - float(event.y)) - 2.f, 0.f), float(getHeight()) - 4.f) / (float(getHeight()) - 4.f));
    }
}

void GuiSlider::mouseUp(const MouseEvent& event)
{
    stopEdition();
}

