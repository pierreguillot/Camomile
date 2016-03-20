/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdGui.hpp"

extern "C"
{
#include "z_pd.h"
}

namespace pd
{
    // ==================================================================================== //
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
    Gui::Gui() noexcept : m_ptr(nullptr), m_type(Type::Invalid), m_patch()
    {
        
    }
    
    Gui::Gui(Patch const& patch, Type type, void* ptr) noexcept :
    m_ptr(ptr), m_type(type), m_patch(patch)
    {
        ;
    }
    
    Gui::Gui(Gui const& other) noexcept :
    m_ptr(other.m_ptr), m_type(other.m_type), m_patch(other.m_patch)
    {
        ;
    }
    
    Gui::Gui(Gui&& other) noexcept :
    m_ptr(other.m_ptr), m_type(other.m_type), m_patch(other.m_patch)
    {
        other.m_ptr   = nullptr;
        other.m_type  = Type::Invalid;
        other.m_patch = Patch();
    }
    
    Gui& Gui::operator=(Gui const& other) noexcept
    {
        m_ptr   = other.m_ptr;
        m_type  = other.m_type;
        m_patch = other.m_patch;
        return *this;
    }
    
    Gui& Gui::operator=(Gui&& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_type, other.m_type);
        std::swap(m_patch, other.m_patch);
        return *this;
    }
    
    Gui::~Gui() noexcept
    {
        m_ptr = nullptr;
        m_patch = Patch();
    }
    
    bool Gui::isValid() const noexcept
    {
        return bool(m_ptr) && m_patch.isValid();
    }
    
    Gui::Type Gui::getType() const noexcept
    {
        return m_type;
    }
    
    bool Gui::isParameter() const noexcept
    {
        return isValid() && !getName().empty() && getReceiveTie() != Tie();
    }
    
    std::string Gui::getName() const
    {
        if(isValid())
        {
            z_symbol* s = z_pd_gui_get_label(reinterpret_cast<z_gui *>(m_ptr));
            if(s)
            {
                std::string name(z_pd_symbol_get_name(s));
                if(!name.empty() && name != "empty")
                {
                    auto pos = name.find("_");
                    if(pos != std::string::npos)
                    {
                        name.erase(name.begin()+pos, name.end());
                    }
                    return name;
                }
            }
        }
        return std::string();
    }
    
    std::string Gui::getLabel() const
    {
        if(isValid())
        {
            z_symbol* s = z_pd_gui_get_label(reinterpret_cast<z_gui *>(m_ptr));
            if(s)
            {
                std::string name(z_pd_symbol_get_name(s));
                if(!name.empty() && name != "empty")
                {
                    auto pos = name.find("_");
                    if(pos != std::string::npos)
                    {
                        name.erase(name.begin(), name.begin()+pos+1);
                        return name;
                    }
                }
            }            
        }
        return std::string();
    }
    
    
    Tie Gui::getReceiveTie() const
    {
        if(isValid())
        {
            z_symbol* s = z_pd_gui_get_receive_symbol(reinterpret_cast<z_gui *>(m_ptr));
            if(s && s != z_pd_get_symbol("empty"))
            {
                return Tie(s);
            }
        }
        return Tie();
    }
    
    size_t Gui::getNumberOfSteps() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_number_of_steps(reinterpret_cast<z_gui *>(m_ptr));
        }
        return 0.f;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_minimum_value(reinterpret_cast<z_gui *>(m_ptr));
        }
        return 0.f;
    }
    
    float Gui::getMaximum() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_maximum_value(reinterpret_cast<z_gui *>(m_ptr));
        }
        return 1.f;
    }
    
    float Gui::getValue() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_value(reinterpret_cast<z_gui *>(m_ptr));
        }
        return 0.f;
    }
    
    std::array<int, 4> Gui::getBounds() const noexcept
    {
        int x = 0, y = 0, w = 0, h = 0;
        if(isValid())
        {
            z_pd_gui_get_bounds(reinterpret_cast<z_gui *>(m_ptr),
                               reinterpret_cast<z_patch *>(m_patch.m_ptr),
                               &x, &y, &w, &h);
        }
        return {x, y, w, h};
    }
    
    std::array<int, 2> Gui::getLabelPosition() const noexcept
    {
        int x = 0, y = 0;
        if(isValid())
        {
            z_pd_gui_get_label_position(reinterpret_cast<z_gui *>(m_ptr),
                                reinterpret_cast<z_patch *>(m_patch.m_ptr),
                                &x, &y);
        }
        return {x, y};
    }
    
    // ==================================================================================== //
    //                                      COMMENT                                         //
    // ==================================================================================== //
    
    
    Comment::Comment() noexcept : m_ptr(nullptr), m_patch()
    {
        
    }
    
    Comment::Comment(Patch const& patch, void* ptr) noexcept :
    m_ptr(ptr), m_patch(patch)
    {
        ;
    }
    
    Comment::Comment(Comment const& other) noexcept :
    m_ptr(other.m_ptr), m_patch(other.m_patch)
    {
        ;
    }
    
    Comment::Comment(Comment&& other) noexcept :
    m_ptr(other.m_ptr), m_patch(other.m_patch)
    {
        other.m_ptr   = nullptr;
        other.m_patch = Patch();
    }
    
    Comment& Comment::operator=(Comment const& other) noexcept
    {
        m_ptr   = other.m_ptr;
        m_patch = other.m_patch;
        return *this;
    }
    
    Comment& Comment::operator=(Comment&& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_patch, other.m_patch);
        return *this;
    }
    
    Comment::~Comment() noexcept
    {
        m_ptr = nullptr;
        m_patch = Patch();
    }
    
    bool Comment::isValid() const noexcept
    {
        return bool(m_ptr) && m_patch.isValid();
    }
    
    std::string Comment::getText() const
    {
        int todo;
        /*
        if(isValid())
        {
            char* text = nullptr;
            int size = 0;
            binbuf_gettext(reinterpret_cast<t_text *>(m_ptr)->te_binbuf, &text, &size);
            if(text && size)
            {
                return std::string(text, size);
            }
        }*/
        return std::string();
    }
    
    float Comment::getX() const noexcept
    {
        int todo;
        /*
        if(isValid())
        {
            std::array<float, 2> margin(m_patch.getMargin());
            return float(reinterpret_cast<t_text *>(m_ptr)->te_xpix) - margin[0];
        }*/
        return 0;
    }
    
    float Comment::getY() const noexcept
    {
        int todo;
        /*
        if(isValid())
        {
            std::array<float, 2> margin(m_patch.getMargin());
            return float(reinterpret_cast<t_text *>(m_ptr)->te_ypix) - margin[1];
        }*/
        return 0;
    }
    
    float Comment::getWidth() const noexcept
    {
        int todo;
        /*
        if(isValid())
        {
            return float(reinterpret_cast<t_text *>(m_ptr)->te_width);
        }*/
        return 0;
    }
}



