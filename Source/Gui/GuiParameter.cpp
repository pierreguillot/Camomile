/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI SLIDER                                      //
// ==================================================================================== //

GuiParameter::GuiParameter(InstanceProcessor& processor, xpd::Gui const& gui) :
m_processor(processor),
m_type(gui.getType()),
m_minimum(gui.getMinimum()),
m_maximum(gui.getMaximum()),
m_index(processor.getParameterIndex(gui.getReceivetie())+1),
m_value(0.f),
m_edited(false)
{
    xpd::Rectangle<int> bounds(gui.getBounds());
    setBounds(bounds.x, bounds.y, bounds.w, bounds.h);
    setOpaque(true);
    setValue(gui.getValue());
}

GuiParameter::~GuiParameter()
{
    
}

xpd::Gui::Type GuiParameter::getType() const noexcept
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
    if(m_minimum < m_maximum)
    {
        m_value = std::max(std::min(value, m_maximum), m_minimum);
    }
    else
    {
        m_value = std::max(std::min(value, m_minimum), m_maximum);
    }
    if(m_index)
    {
        m_processor.setParameterNonNormalizedNotifyingHost(int(m_index)-1, m_value);
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
        return (getValue() - getMinimum()) / (getMaximum() - getMinimum());
    }
    return 1.f - (getValue() - getMaximum()) / (getMinimum() - getMaximum());
}

void GuiParameter::setValueNormalized(float value, bool redraw)
{
    value = std::max(std::min(value, 1.f), 0.f);
    if(getMinimum() < getMaximum())
    {
        setValue(value * (getMaximum() - getMinimum()) + getMinimum());
    }
    else
    {
        setValue((1.f - value) * (getMinimum() - getMaximum()) + getMaximum());
    }
}

void GuiParameter::startEdition() noexcept
{
    m_value = m_processor.getParameterNonNormalized(int(m_index)-1);
    m_edited = true;
}

void GuiParameter::stopEdition() noexcept
{
    m_edited = false;
}

void GuiParameter::update()
{
    if(m_index && m_edited == false)
    {
        const float value = m_processor.getParameterNonNormalized(int(m_index)-1);
        if(value != m_value)
        {
            m_value = value;
            repaint();
        }
    }
}

