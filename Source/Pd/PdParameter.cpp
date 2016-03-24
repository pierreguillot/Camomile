/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdParameter.hpp"

namespace pd
{
    
    Parameter::Parameter()
    : m_valid(false), m_value (0.f), m_min(0.f), m_max(0.f),
    m_name (""), m_label(""), m_bname(), m_nsteps(0)
    {
        
    }
    
    Parameter::Parameter(Parameter const& other)
    : m_valid(other.m_valid), m_value (other.m_value),
    m_min(other.m_min), m_max(other.m_max),
    m_name (other.m_name), m_label(other.m_label),
    m_bname(other.m_bname), m_nsteps(other.m_nsteps)
    {
        
    }
    
    Parameter::Parameter(pd::Gui const& gui)
    : m_valid(true), m_value (0.f),
    m_min(gui.getMinimum()),
    m_max(gui.getMaximum()),
    m_name(gui.getName()),
    m_label(gui.getLabel()),
    m_bname(gui.getReceiveTie()),
    m_nsteps(gui.getNumberOfSteps())
    {
        setValueNonNormalized(gui.getValue());
    }
    
    Parameter::~Parameter()
    {
        
    }
    
    Parameter& Parameter::operator=(Parameter const& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        m_name  = other.m_name;
        m_label = other.m_label;
        m_bname = other.m_bname;
        m_nsteps= other.m_nsteps;
        return *this;
    }
    
    Parameter& Parameter::operator=(Parameter&& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        std::swap(m_name, other.m_name);
        std::swap(m_label, other.m_label);
        m_bname = other.m_bname;
        m_nsteps= other.m_nsteps;
        return *this;
    }
    
    void Parameter::setValueNormalized(float value)
    {
        value = std::min(std::max(value, 0.f), 1.f);
        if(m_nsteps)
        {
            const float step = (1.f/ float(m_nsteps - 1));
            m_value = std::round(value / step) * step;
        }
        else
        {
            m_value = value;
        }
    }
    
    
    float Parameter::getValueNormalized(float value)
    {
        if(m_min < m_max)
        {
            return std::min(std::max((value - m_min) / (m_max - m_min), 0.f), 1.f);
        }
        return std::min(std::max(1.f  - ((value - m_max) / (m_min - m_max)), 0.f), 1.f);
    }
}