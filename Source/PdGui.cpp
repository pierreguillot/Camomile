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
    
    std::string Gui::getName() const
    {
        if(isValid())
        {
            t_symbol* s = reinterpret_cast<t_iemgui *>(m_ptr)->x_lab;
            if(s)
            {
                std::string name(s->s_name);
                auto pos = name.find("_");
                if(pos != std::string::npos)
                {
                    name.erase(name.begin()+pos, name.end());
                }
                return name;
            }
        }
        return std::string();
    }
    
    std::string Gui::getLabel() const
    {
        t_symbol* s = reinterpret_cast<t_iemgui *>(m_ptr)->x_lab;
        if(s)
        {
            std::string name(s->s_name);
            auto pos = name.find("_");
            if(pos != std::string::npos)
            {
                name.erase(name.begin(), name.begin()+pos+1);
            }
            return name;
        }
        return std::string();
    }
    
    void* Gui::getBindingPtr() const
    {
        int to_wrap;
        if(isValid())
        {
            return reinterpret_cast<t_iemgui *>(m_ptr)->x_rcv;
        }
        return nullptr;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(isValid())
        {
            if(m_type == Type::HorizontalSlider)
            {
                return reinterpret_cast<t_hslider *>(m_ptr)->x_min;
            }
            else if(m_type == Type::VecticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_min;
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
            else if(m_type == Type::VecticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_max;
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
            else if(m_type == Type::VecticalSlider)
            {
                return reinterpret_cast<t_vslider *>(m_ptr)->x_fval;
            }
        }
        return 0.f;
    }
    
    std::array<float, 4> Gui::getBounds() const noexcept
    {
        int to_clean;
        if(isValid())
        {
            t_object* obj = reinterpret_cast<t_object *>(m_ptr);
            int x1, x2, y1, y2;
            obj->te_g.g_pd->c_wb->w_getrectfn(reinterpret_cast<t_gobj *>(m_ptr),
                                              reinterpret_cast<struct _glist *>(m_patch.getRawPtr()),
                                              &x1, &y1, &x2, &y2);
            return {float(x1), float(y1), float(x2 - x1), float(y2 - y1)};
        }
        return {0.f, 0.f, 0.f, 0.f};
    }
    
    std::array<float, 2> Gui::getLabelPosition() const noexcept
    {
        if(isValid())
        {
            return {float(reinterpret_cast<t_iemgui *>(m_ptr)->x_ldx), float(reinterpret_cast<t_iemgui *>(m_ptr)->x_ldy)};
        }
        return {0.f, 0.f};
    }
}



