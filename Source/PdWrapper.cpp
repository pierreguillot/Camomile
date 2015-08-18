/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamoWrapper.h"
#include "../ThirdParty/Cream/c.library.hpp"

namespace camo
{
    /*
    inline static juce::Colour toJuce(t_rgba const& rgba)
    {
        return juce::Colour::fromFloatRGBA(rgba.red, rgba.green, rgba.blue, rgba.alpha);
    }
    
    //! @brief Converts a t_edrawparams to a DrawParameters object.
    
     inline static DrawParameters toJuce(t_edrawparams const& param)
     {
     return DrawParameters(toJuce(param.d_boxfillcolor),
     toJuce(param.d_bordercolor),
     std::max(int(param.d_borderthickness), 0),
     std::max(int(param.d_cornersize), 0));
     }
    
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
    
    bool Object::wantMouse() const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && !(((t_ebox *)m_handle)->b_flags & EBOX_IGNORELOCKCLICK))
        {
            return c->c_widget.w_mousedown ||
            c->c_widget.w_mousedrag ||
            c->c_widget.w_mouseenter ||
            c->c_widget.w_mouseleave ||
            c->c_widget.w_mousemove ||
            c->c_widget.w_mouseup ||
            c->c_widget.w_mousewheel ||
            c->c_widget.w_dblclick;
        }
        return false;
    }
    
    bool Object::wantKeyboard() const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && (c->c_widget.w_key || c->c_widget.w_keyfilter))
        {
            return c->c_widget.w_key || c->c_widget.w_keyfilter;
        }
        return false;
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
    
    /*
    std::tuple<int, t_elayer*> Object::paint() const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        
        for(int i = 0; i < ((t_ebox *)m_handle)->b_number_of_layers; i++)
        {
            ((t_ebox *)m_handle)->b_layers[i].e_state = EGRAPHICS_INVALID;
        }
        if(c && c->c_widget.w_paint)
        {
            c->c_widget.w_paint(m_handle, NULL);
            return std::tuple<int, t_elayer*>(int(((t_ebox *)(m_handle))->b_number_of_layers), ((t_ebox *)(m_handle))->b_layers);
        }
        return std::tuple<int, t_elayer*>(0, nullptr);
    }*/
    
    /*
    void Object::mouseMove(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mousemove)
        {
            c->c_widget.w_mousemove(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseEnter(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mouseenter)
        {
            c->c_widget.w_mouseenter(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseExit(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mouseleave)
        {
            c->c_widget.w_mouseleave(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseDown(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mousedown)
        {
            c->c_widget.w_mousedown(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseDrag(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mousedrag)
        {
            c->c_widget.w_mousedrag(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseUp(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mouseup)
        {
            c->c_widget.w_mouseup(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseDoubleClick(const MouseEvent& event) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_dblclick)
        {
            c->c_widget.w_dblclick(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags());
        }
    }
    
    void Object::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) const noexcept
    {
        t_eclass* c = eobj_getclass(m_handle);
        if(c && c->c_widget.w_mousewheel)
        {
            c->c_widget.w_mousewheel(m_handle, NULL, t_pt({float(event.x), float(event.y)}), (long)event.mods.getRawFlags(), wheel.deltaY, wheel.deltaY);
        }
    }*/
    
}



