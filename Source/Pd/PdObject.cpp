/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.h"

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
    
    Object::Object(Patch const& patch, void* ptr) noexcept :
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
        m_patch = Patch();
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
                free(text);
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
    
    std::pair<std::pair<int, int>, std::pair<int, int>> Object::getBounds() const noexcept
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
                return {{x, y}, {w, h}};
            }
        }
        return {{0, 0}, {0, 0}};
    }
    
    // ==================================================================================== //
    //                                      GUI                                          //
    // ==================================================================================== //
    
    Gui::Gui() noexcept : Object(), m_type(Type::Invalid)
    {
        
    }
    
    Gui::Gui(Patch const& patch, Type type, void* ptr) noexcept :
    Object(patch, ptr), m_type(type)
    {
        ;
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
    
    /*
    Tie Gui::getReceiveTie() const
    {
        if(isValid())
        {
            z_symbol* s = z_pd_gui_get_receive_symbol(reinterpret_cast<z_gui *>(getPtr()));
            if(s && s != z_pd_symbol_create("empty"))
            {
                return Smuggler::createTie(s);
            }
        }
        return Tie();
    }
     */
    
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
            return 0;
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
        return 0.f;
    }
}



