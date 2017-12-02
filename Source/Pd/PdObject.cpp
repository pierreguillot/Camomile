/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.hpp"

extern "C"
{
#include <z_libpd.h>
#include <m_pd.h>
#include <m_imp.h>
#include <g_canvas.h>
#include <g_all_guis.h>
#include "x_libpd_multi.h"
}

namespace pd
{
    
    // ==================================================================================== //
    //                                      COMMENT                                         //
    // ==================================================================================== //
    
    
    Object::Object() noexcept : m_ptr(nullptr), m_patch()
    {
        
    }
    
    Object::Object(void* ptr, Patch const& patch) noexcept :
    m_ptr(ptr), m_patch(patch)
    {
        ;
    }
    
    Object::Object(Object const& other) noexcept :
    m_ptr(other.m_ptr), m_patch(other.m_patch)
    {
        ;
    }
    

    Object& Object::operator=(Object const& other) noexcept
    {
        m_ptr   = other.m_ptr;
        m_patch = other.m_patch;
        return *this;
    }
    
    Object::~Object() noexcept
    {
        m_ptr = nullptr;
    }
    
    std::string Object::getText() const
    {
        if(m_ptr != nullptr)
        {
            char* text = nullptr;
            int size = 0;
            binbuf_gettext(static_cast<t_text*>(m_ptr)->te_binbuf, &text, &size);
            if(text && size)
            {
                std::string txt(text, size);
                freebytes(static_cast<void*>(text), static_cast<size_t>(size) * sizeof(char));
                return txt;
            }
        }
        return std::string();
    }
    
    std::string Object::getName() const
    {
        if(m_ptr != nullptr && static_cast<t_text*>(m_ptr)->te_g.g_pd->c_name)
        {
            return std::string(static_cast<t_text*>(m_ptr)->te_g.g_pd->c_name->s_name);
        }
        return std::string();
    }
    
    std::array<int, 4> Object::getBounds() const noexcept
    {
        if(m_ptr != nullptr)
        {
            struct _widgetbehavior const* wb = static_cast<t_text*>(m_ptr)->te_g.g_pd->c_wb;
            if(static_cast<t_text*>(m_ptr)->te_g.g_pd->c_patchable && wb && wb->w_getrectfn)
            {
                int x = 0, y = 0, w = 0, h = 0;
                wb->w_getrectfn(static_cast<t_gobj*>(m_ptr), static_cast<t_canvas*>(m_patch.m_ptr), &x, &y, &w, &h);
                w = w - x;
                h = h - y;
                x = x - static_cast<t_canvas*>(m_patch.m_ptr)->gl_xmargin;
                y = y - static_cast<t_canvas*>(m_patch.m_ptr)->gl_ymargin;
                return {{x, y, w, h}};
            }
        }
        return {{0, 0, 0, 0}};
    }
    
    // ==================================================================================== //
    //                                      GUI                                          //
    // ==================================================================================== //
    
    Gui::Gui() noexcept : Object(), m_type(Type::Undefined)
    {
        
    }
    
    Gui::Gui(void* ptr, Patch const& patch) noexcept :
    Object(ptr, patch), m_type(Type::Undefined)
    {
        if(getName() == "bng")
        {
           m_type = Type::Bang;
        }
        else if(getName() == "hsl")
        {
           m_type = Type::HorizontalSlider;
        }
        else if(getName() == "vsl")
        {
           m_type = Type::VerticalSlider;
        }
        else if(getName() == "tgl")
        {
           m_type = Type::Toggle;
        }
        else if(getName() == "nbx")
        {
           m_type = Type::Number;
        }
        else if(getName() == "vradio")
        {
           m_type = Type::VerticalRadio;
        }
        else if(getName() == "hradio")
        {
           m_type = Type::HorizontalRadio;
        }
        else if(getName() == "cnv")
        {
           m_type = Type::Panel;
        }
        else if(getName() == "vu")
        {
           m_type = Type::VuMeter;
        }
        else if(getName() == "text")
        {
           m_type = Type::Comment;
        }
    }
    
    Gui::Gui(Gui const& other) noexcept :
    Object(other), m_type(other.m_type)
    {
        ;
    }
    
    Gui& Gui::operator=(Gui const& other) noexcept
    {
        Object::operator=(other);
        m_type  = other.m_type;
        return *this;
    }
    
    Gui::~Gui() noexcept
    {
        ;
    }
    
    Gui::Type Gui::getType() const noexcept
    {
        return m_type;
    }
    
    
    size_t Gui::getNumberOfSteps() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::Toggle)
        {
            return 2;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_number;
        }
        return 0.f;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_min;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_min;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_min;
        }
        return 0.f;
    }
    
    float Gui::getMaximum() const noexcept
    {
        if(!m_ptr)
            return 1.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_max;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_max;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_max;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::Bang)
        {
            return 1;
        }
        return 1.f;
    }
    
    float Gui::getValue() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_fval;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_fval;
        }
        else if(m_type == Type::Toggle)
        {
            return (static_cast<t_toggle*>(m_ptr))->x_on;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_val;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_on;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_on;
        }
        else if(m_type == Type::Bang)
        {
            return (static_cast<t_bng*>(m_ptr))->x_flashed;
        }
        else if(m_type == Type::VuMeter)
        {
            return 0;
        }
        return 0.f;
    }
    
    void Gui::setValue(float value) noexcept
    {
        if(!m_ptr || m_type == Type::Comment)
            return;
        m_patch.m_instance->setThis();
        pd_float(static_cast<t_pd*>(m_ptr), value);
    }
    
    int Gui::getFontSize() const noexcept
    {
        if(!m_ptr )
            return 0;
        if(m_type == Type::Comment)
        {
            return (static_cast<t_canvas*>(m_patch.m_ptr))->gl_font;
        }
        else
        {
            return (static_cast<t_iemgui*>(m_ptr))->x_fontsize;
        }
    }
}



