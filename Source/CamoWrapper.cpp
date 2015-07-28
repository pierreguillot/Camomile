/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamoWrapper.h"

namespace camo
{
    DrawParameters::DrawParameters() noexcept :
    m_background_color(juce::Colours::white),
    m_border_color(juce::Colours::white),
    m_border_size(0),
    m_corner_roundness(0)
    {
        
    }
    
    DrawParameters::DrawParameters(juce::Colour const& bgcolor,
                                   juce::Colour const& bdcolor,
                                   int bordersize,
                                   int cornersize) noexcept :
    m_background_color(bgcolor),
    m_border_color(bdcolor),
    m_border_size(std::max(bordersize, 0)),
    m_corner_roundness(std::max(cornersize, 0))
    {
        
    }
    
    DrawParameters::DrawParameters(DrawParameters const& other) noexcept :
    m_background_color(other.m_background_color),
    m_border_color(other.m_border_color),
    m_border_size(other.m_border_size),
    m_corner_roundness(other.m_corner_roundness)
    {
        
    }
    
    void DrawParameters::operator=(DrawParameters const& other) noexcept
    {
        m_background_color  = other.m_background_color;
        m_border_color      = other.m_border_color;
        m_border_size       = other.m_border_size;
        m_corner_roundness  = other.m_corner_roundness;
    }
    
    Object::Object() noexcept : m_handle(nullptr)
    {
        
    }
    
    Object::Object(void* handle) noexcept : m_handle(handle)
    {
        
    }
    
    Object::Object(Object const& other) noexcept : m_handle(other.m_handle)
    {
        
    }
    
    void Object::operator=(Object const& other) noexcept
    {
        m_handle = other.m_handle;
    }
    
    Point<int> Object::getPosition() const noexcept
    {
        return Point<int>(getX(), getY());
    }
    
    int Object::getX() const noexcept
    {
        return int(((t_object *)(m_handle))->te_xpix);
    }
    
    int Object::getY() const noexcept
    {
        return int(((t_object *)(m_handle))->te_ypix);
    }
    
    Point<int> Object::getSize() const noexcept
    {
        return Point<int>(getWidth(), getHeight());
    }
    
    int Object::getWidth() const noexcept
    {
        return int(((t_ebox *)(m_handle))->b_rect.width);
    }
    
    int Object::getHeight() const noexcept
    {
        return int(((t_ebox *)(m_handle))->b_rect.height);
    }
    
    Rectangle<int> Object::getBounds() const noexcept
    {
        return Rectangle<int>(getX(), getY(), getWidth(), getHeight());
    }
    
    DrawParameters Object::getDrawParameters() const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_getdrawparameters)
        {
            t_edrawparams params;
            c->c_widget.w_getdrawparameters(m_handle, NULL, &params);
            return toJuce(params);
        }
        return DrawParameters();
    }
}



