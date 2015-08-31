/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdWidget.h"
#include "PdGui.h"
#include <limits>

namespace pd
{
    // ==================================================================================== //
    //                                      PARAMETER                                       //
    // ==================================================================================== //
    
    Parameter::Parameter() noexcept : m_parameter(nullptr)
    {
        
    }
    
    Parameter::Parameter(Gui const& gui, const std::string& name) noexcept :
    m_instance(gui.getInstance()),
    m_parameter(eparameter_getfromsymbol(gensym(name.c_str())))
    {
        
    }
    
    Parameter::Parameter(Parameter const& other) noexcept : m_parameter(other.m_parameter)
    {
        
    }
    
    Parameter::~Parameter()
    {
        
    }
    
    Parameter& Parameter::operator=(Parameter const& other)
    {
        m_parameter = other.m_parameter;
        return *this;
    }
    
    std::string Parameter::getName() const
    {
        if(bool(*this) && is_valid_symbol(m_parameter->p_name))
        {
            return std::string(m_parameter->p_name->s_name);
        }
        return std::string();
    }
    
    std::string Parameter::getLabel() const
    {
        if(bool(*this) && is_valid_symbol(m_parameter->p_label))
        {
            return std::string(m_parameter->p_label->s_name);
        }
        return std::string();
    }
    
    bool Parameter::isAutomatable() const
    {
        return bool(*this) ? bool(m_parameter->p_auto) : true;
    }
    
    bool Parameter::isMetaParameter() const
    {
        return bool(*this) ? bool(m_parameter->p_meta) : false;
    }
    
    float Parameter::getStep() const
    {
        return bool(*this) ? m_parameter->p_step : std::numeric_limits<float>::epsilon();
    }
    
    float Parameter::getNormalizedStep() const
    {
        if(bool(*this))
        {
            if(m_parameter->p_max == m_parameter->p_min)
            {
                return 1.f;
            }
            else if(m_parameter->p_max > m_parameter->p_min)
            {
                return m_parameter->p_step / (m_parameter->p_max - m_parameter->p_min);
            }
            else
            {
                return m_parameter->p_step / (m_parameter->p_min - m_parameter->p_max);
            }
        }
        return std::numeric_limits<float>::epsilon();
    }
    
    size_t Parameter::getNumberOfStep() const
    {
        if(bool(*this))
        {
            if(m_parameter->p_max == m_parameter->p_min)
            {
                return 1;
            }
            else if(m_parameter->p_max > m_parameter->p_min)
            {
                return (m_parameter->p_max - m_parameter->p_min) / m_parameter->p_step + 1;
            }
            else
            {
                return (m_parameter->p_min - m_parameter->p_max) / m_parameter->p_step + 1;
            }
        }
        return 1.f / std::numeric_limits<float>::epsilon();
    }
    
    bool Parameter::isInverted() const
    {
        return bool(*this) ? bool(m_parameter->p_min > m_parameter->p_max) : false;
    }
    
    float Parameter::getValue() const
    {
        return bool(*this) ? eparameter_getvalue(m_parameter) : 0.f;
    }
    
    float Parameter::getNormalizedValue() const
    {
        return bool(*this) ? eparameter_getvalue_normalized(m_parameter) : 0.f;
    }
    
    void Parameter::setValue(const float value)
    {
        if(bool(*this))
        {
            std::lock_guard<std::mutex> guard2(m_instance.m_internal->mutex);
            std::lock_guard<std::mutex> guard(m_instance.s_mutex);
            eparameter_setvalue(m_parameter, value);
        }
    }
    
    void Parameter::setNormalizedValue(const float value)
    {
        if(bool(*this))
        {
            std::lock_guard<std::mutex> guard2(m_instance.m_internal->mutex);
            std::lock_guard<std::mutex> guard(m_instance.s_mutex);
            eparameter_setvalue_normalized(m_parameter, value);
        }
    }
    
    std::string Parameter::getTextValue() const
    {
        if(bool(*this))
        {
            char text[MAXPDSTRING];
            eparameter_getvalue_text(m_parameter, text);
            return std::string(text);
        }
        return std::string();
    }
    
    void Parameter::setTextValue(const std::string& text) const
    {
        if(bool(*this))
        {
            std::lock_guard<std::mutex> guard2(m_instance.m_internal->mutex);
            std::lock_guard<std::mutex> guard(m_instance.s_mutex);
            eparameter_setvalue_text(m_parameter, text.c_str());
        }
    }
}



