/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdGui.hpp"
#include "PdPatch.hpp"
#include "PdInstance.hpp"
#include "Pd.hpp"

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
#include "../ThirdParty/PureData/src/g_all_guis.h"
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
        return isValid() && !getName().empty() && getBindingName() != nullptr;
    }
    
    std::string Gui::getName() const
    {
        if(isValid())
        {
            t_symbol* s = reinterpret_cast<t_iemgui *>(m_ptr)->x_lab;
            if(s)
            {
                std::string name(s->s_name);
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
            t_symbol* s = reinterpret_cast<t_iemgui *>(m_ptr)->x_lab;
            if(s)
            {
                std::string name(s->s_name);
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
    
    
    BindingName Gui::getBindingName() const
    {
        if(isValid())
        {
            if(reinterpret_cast<t_iemgui *>(m_ptr)->x_rcv != gensym("empty"))
            {
                return BindingName(reinterpret_cast<t_iemgui *>(m_ptr)->x_rcv);
            }
        }
        return BindingName(nullptr);
    }
    
    size_t Gui::getNumberOfSteps() const noexcept
    {
        if(isValid())
        {
            if(m_type == Type::HorizontalSlider)
            {
                return 0;
            }
            else if(m_type == Type::VerticalSlider)
            {
                return 0;
            }
            else if(m_type == Type::Number)
            {
                return 0;
            }
            else if(m_type == Type::Toggle)
            {
                return 2;
            }
            else if(m_type == Type::HorizontalRadio)
            {
                return reinterpret_cast<t_hradio *>(m_ptr)->x_number;
            }
            else if(m_type == Type::VerticalRadio)
            {
                return reinterpret_cast<t_vradio *>(m_ptr)->x_number;
            }
        }
        return 0.f;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(isValid())
        {
            if(m_type == Type::HorizontalSlider)
            {
                return reinterpret_cast<t_hslider *>(m_ptr)->x_min;
            }
            else if(m_type == Type::VerticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_min;
            }
            else if(m_type == Type::Number)
            {
                return reinterpret_cast<t_my_numbox *>(m_ptr)->x_min;
            }
            else if(m_type == Type::Toggle)
            {
                return 0;
            }
            else if(m_type == Type::HorizontalRadio)
            {
                return 0;
            }
            else if(m_type == Type::VerticalRadio)
            {
                return 0;
            }
        }
        return 0.f;
    }
    
    float Gui::getMaximum() const noexcept
    {
        if(isValid())
        {
            if(m_type == Type::HorizontalSlider)
            {
                return reinterpret_cast<t_hslider *>(m_ptr)->x_max;
            }
            else if(m_type == Type::VerticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_max;
            }
            else if(m_type == Type::Number)
            {
                return reinterpret_cast<t_my_numbox *>(m_ptr)->x_max;
            }
            else if(m_type == Type::Toggle)
            {
                return 1;
            }
            else if(m_type == Type::HorizontalRadio)
            {
                return reinterpret_cast<t_hradio *>(m_ptr)->x_number - 1;
            }
            else if(m_type == Type::VerticalRadio)
            {
                return reinterpret_cast<t_vradio *>(m_ptr)->x_number - 1;
            }
        }
        return 1.f;
    }
    
    float Gui::getValue() const noexcept
    {
        if(isValid())
        {
            if(m_type == Type::HorizontalSlider)
            {
                return reinterpret_cast<t_hslider *>(m_ptr)->x_fval;
            }
            else if(m_type == Type::VerticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_fval;
            }
            else if(m_type == Type::Number)
            {
                return reinterpret_cast<t_my_numbox *>(m_ptr)->x_val;
            }
            else if(m_type == Type::Toggle)
            {
                return reinterpret_cast<t_toggle *>(m_ptr)->x_on;
            }
            else if(m_type == Type::HorizontalRadio)
            {
                return reinterpret_cast<t_hradio *>(m_ptr)->x_on;
            }
            else if(m_type == Type::VerticalRadio)
            {
                return reinterpret_cast<t_vradio *>(m_ptr)->x_on;
            }
        }
        return 0.f;
    }
    
    std::array<float, 4> Gui::getBounds() const noexcept
    {
        if(isValid())
        {
            return m_patch.getGuiBounds(*this);
        }
        return {0.f, 0.f, 0.f, 0.f};
    }
    
    std::array<float, 2> Gui::getLabelPosition() const noexcept
    {
        if(isValid())
        {
            return m_patch.getGuiLabelPosition(*this);
        }
        return {0.f, 0.f};
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
        if(isValid())
        {
            char* text = nullptr;
            int size = 0;
            binbuf_gettext(reinterpret_cast<t_text *>(m_ptr)->te_binbuf, &text, &size);
            if(text && size)
            {
                return std::string(text, size);
            }
        }
        return std::string();
    }
    
    float Comment::getX() const noexcept
    {
        if(isValid())
        {
            std::array<float, 2> margin(m_patch.getMargin());
            return float(reinterpret_cast<t_text *>(m_ptr)->te_xpix) - margin[0];
        }
        return 0;
    }
    
    float Comment::getY() const noexcept
    {
        if(isValid())
        {
            std::array<float, 2> margin(m_patch.getMargin());
            return float(reinterpret_cast<t_text *>(m_ptr)->te_ypix) - margin[1];
        }
        return 0;
    }
    
    float Comment::getWidth() const noexcept
    {
        if(isValid())
        {
            return float(reinterpret_cast<t_text *>(m_ptr)->te_width);
        }
        return 0;
    }
}



