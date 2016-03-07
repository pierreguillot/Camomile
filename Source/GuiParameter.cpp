/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiParameter.hpp"
#include "PatchEditor.h"

// ==================================================================================== //
//                                      GUI SLIDER                                      //
// ==================================================================================== //

GuiParameter::GuiParameter(InstanceProcessor& processor, pd::Gui const& gui) :
m_processor(processor),
m_type(gui.getType()),
m_minimum(gui.getMinimum()),
m_maximum(gui.getMaximum()),
m_index(processor.getParameterIndex(gui.getBindingName())+1),
m_value(gui.getValue())
{
    std::array<float, 4> bounds(gui.getBounds());
    setBounds(int(bounds[0]), int(bounds[1]), int(bounds[2]), int(bounds[3]));
    if(m_index)
    {
        startTimer(25);
    }
}

GuiParameter::~GuiParameter()
{
    
}

pd::Gui::Type GuiParameter::getType() const noexcept
{
    return m_type;
}

float GuiParameter::getMaximum() const noexcept
{
    return m_maximum;
}

float GuiParameter::getMinimum() const noexcept
{
    return m_minimum;
}

float GuiParameter::getValue() const noexcept
{
    return m_value;
}

void GuiParameter::setValue(float value, bool redraw)
{
    if(m_index)
    {
        m_processor.setParameterNonNormalizedNotifyingHost(m_index-1, m_value);
    }
    
    if(redraw)
    {
        repaint();
    }
}

float GuiParameter::getValueNormalized() const noexcept
{
    if(getMinimum() < getMaximum())
    {
        return (getValue() - getMinimum()) / (getMaximum() / getMinimum());
    }
    return 1.f - (getValue() - getMaximum() / (getMinimum() / getMaximum()));
}

void GuiParameter::setValueNormalized(float value, bool redraw)
{
    if(getMinimum() < getMaximum())
    {
        setValue(value * (getMaximum() / getMinimum()) + getMinimum());
    }
    setValue((1.f - value) * (getMinimum() / getMaximum()) + getMaximum());
}

void GuiParameter::timerCallback()
{
    m_value = m_processor.getParameterNonNormalized(m_index-1);
    repaint();
}

