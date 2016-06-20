/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamomileParameter.hpp"
#include <cmath>

namespace camo
{
    Parameter::Parameter() :
    m_valid(false),
    m_value (0.f),
    m_min(0.f),
    m_max(0.f),
    m_name (""),
    m_label(""),
    m_nsteps(0),
    m_bname()
    {
        
    }
    
    Parameter::Parameter(Parameter const& other) :
    m_valid(other.m_valid),
    m_value(other.m_value),
    m_min(other.m_min),
    m_max(other.m_max),
    m_name (other.m_name),
    m_label(other.m_label),
    m_nsteps(other.m_nsteps),
    m_bname(other.m_bname)
    {
        
    }

    /*
    Parameter::Parameter(xpd::gui const& gui) :
    m_valid(true),
    m_value (0.f),
    m_min(gui.minimum()),
    m_max(gui.maximum()),
    m_name(gui.name()),
    m_label(gui.label()),
    m_nsteps(gui.nsteps()),
    m_bname(gui.send_tie())
    {
        setValueNonNormalized(gui.value());
    }
     */
    
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
        std::swap(m_valid, other.m_valid);
        std::swap(m_value, other.m_value);
        std::swap(m_min, other.m_min);
        std::swap(m_max, other.m_max);
        std::swap(m_name, other.m_name);
        std::swap(m_label, other.m_label);
        std::swap(m_bname, other.m_bname);
        std::swap(m_nsteps, other.m_nsteps);
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

