/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.hpp"

extern "C"
{
#include "z_pd.h"
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
    
    Object::Object(Object&& other) noexcept :
    m_ptr(other.m_ptr), m_patch(other.m_patch)
    {
        other.m_ptr   = nullptr;
        other.m_patch = Patch();
    }
    
    Object& Object::operator=(Object const& other) noexcept
    {
        m_ptr   = other.m_ptr;
        m_patch = other.m_patch;
        return *this;
    }
    
    Object& Object::operator=(Object&& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_patch, other.m_patch);
        return *this;
    }
    
    Object::~Object() noexcept
    {
        m_ptr = nullptr;
        m_patch = Patch();
    }
    
    bool Object::isValid() const noexcept
    {
        return bool(m_ptr) && m_patch.isValid();
    }
    
    std::string Object::getText() const
    {
        if(isValid())
        {
            char* text = nullptr;
            int size = 0;
            z_pd_object_get_text(reinterpret_cast<z_object *>(m_ptr), &size, &text);
            if(text && size)
            {
                std::string txt(text, size);
                free(text);
                return txt;
            }
        }
        return std::string();
    }
    
    std::array<int, 4> Object::getBounds() const noexcept
    {
        int x = 0, y = 0, w = 0, h = 0;
        if(isValid())
        {
            z_pd_object_get_bounds(reinterpret_cast<z_object *>(m_ptr),
                                reinterpret_cast<z_patch *>(m_patch.m_ptr),
                                &x, &y, &w, &h);
        }
        return {x, y, w, h};
    }
    
    void* Object::getPatchPtr() const noexcept
    {
        return isValid() ? m_patch.m_ptr : nullptr;
    }
    
    void* Object::getPtr() const noexcept
    {
        return isValid() ? m_ptr : nullptr;
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
    
    Gui::Gui(Gui&& other) noexcept :
    Object(std::move(other)), m_type(other.m_type)
    {
        other.m_type  = Type::Invalid;
    }
    
    Gui& Gui::operator=(Gui const& other) noexcept
    {
        Object::operator=(other);
        m_type  = other.m_type;
        return *this;
    }
    
    Gui& Gui::operator=(Gui&& other) noexcept
    {
        Object::operator=(std::move(other));
        std::swap(m_type, other.m_type);
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
    
    bool Gui::isParameter() const noexcept
    {
        return isValid() && !getName().empty() && getReceiveTie() != Tie();
    }
    
    std::string Gui::getName() const
    {
        if(isValid())
        {
            z_symbol* s = z_pd_gui_get_label(reinterpret_cast<z_gui *>(getPtr()));
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
            z_symbol* s = z_pd_gui_get_label(reinterpret_cast<z_gui *>(getPtr()));
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
            z_symbol* s = z_pd_gui_get_receive_symbol(reinterpret_cast<z_gui *>(getPtr()));
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
            return z_pd_gui_get_number_of_steps(reinterpret_cast<z_gui *>(getPtr()));
        }
        return 0.f;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_minimum_value(reinterpret_cast<z_gui *>(getPtr()));
        }
        return 0.f;
    }
    
    float Gui::getMaximum() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_maximum_value(reinterpret_cast<z_gui *>(getPtr()));
        }
        return 1.f;
    }
    
    float Gui::getValue() const noexcept
    {
        if(isValid())
        {
            return z_pd_gui_get_value(reinterpret_cast<z_gui *>(getPtr()));
        }
        return 0.f;
    }
    
    std::array<int, 2> Gui::getLabelPosition() const noexcept
    {
        int x = 0, y = 0;
        if(isValid())
        {
            z_pd_gui_get_label_position(reinterpret_cast<z_gui *>(getPtr()),
                                reinterpret_cast<z_patch *>(getPatchPtr()),
                                &x, &y);
        }
        return {x, y};
    }
}



