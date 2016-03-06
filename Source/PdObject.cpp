/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.hpp"
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
    
    class Object::Internal : public LeakDetector<Internal>
    {
    public:
        Patch               patch;
        t_object*           object;
        std::atomic<size_t> counter;
        
        Internal(Patch const& _patch, t_object* _object);
        ~Internal();
    };
    
    Object::Internal::Internal(Patch const& _patch, t_object* _object) :
    patch(_patch), object(_object), counter(1)
    {
        
    }
    
    Object::Internal::~Internal()
    {
        patch = Patch();
        object = nullptr;
    }
    
    Object::Object() noexcept : m_internal(nullptr)
    {
        
    }
    
    Object::Object(Patch const& patch, void* object) noexcept :
    m_internal(new Internal(patch, reinterpret_cast<t_object *>(object)))
    {
        
    }
    
    Object::Object(Object const& other) noexcept : m_internal(other.m_internal)
    {
        if(m_internal)
        {
            m_internal->counter++;
        }
    }
    
    Object::Object(Object&& other) noexcept : m_internal(other.m_internal)
    {
        other.m_internal = nullptr;
    }
    
    Object& Object::operator=(Object const& other) noexcept
    {
        if(other.m_internal)
        {
            other.m_internal->counter++;
            m_internal = other.m_internal;
        }
        else
        {
            m_internal = nullptr;
        }
        return *this;
    }
    
    Object& Object::operator=(Object&& other) noexcept
    {
        std::swap(m_internal, other.m_internal);
        return *this;
    }
    
    Object::~Object() noexcept
    {
        if(m_internal && m_internal->counter)
        {
            --m_internal->counter;
            if(!m_internal->counter)
            {
                delete m_internal;
            }
        }
    }
    
    bool Object::isValid() const noexcept
    {
        return bool(m_internal) && bool(m_internal->object);
    }
    
    std::string Object::getClassName() const
    {
        if(isValid())
        {
            return std::string(class_getname(m_internal->object->te_g.g_pd));
        }
        return std::string();
    }
    
    
    
    Slider::Slider() : Object()
    {
        
    }
    
    Slider::Slider(Patch const& patch, void* object) : Object(patch, object)
    {
        
    }
    
    Slider::Slider(Slider const& other) : Object(other)
    {
        
    }
    
    Slider::Slider(Slider&& other) : Object(std::move(other))
    {
        
    }
    
    Slider::~Slider() noexcept
    {
        
    }
    
    std::string Slider::getName() const
    {
        if(isValid())
        {
            std::string name(reinterpret_cast<t_iemgui *>(m_internal->object)->x_lab->s_name);
            auto pos = name.find("_");
            while(pos != std::string::npos)
            {
                name.replace(pos, 1, " ");
            }
            pos = name.find("@");
            if(pos != std::string::npos)
            {
                name.erase(name.begin()+pos, name.end());
            }
            return name;
        }
        return std::string();
    }
    
    std::string Slider::getLabel() const
    {
        if(isValid())
        {
            int aki;
            std::string name(reinterpret_cast<t_iemgui *>(m_internal->object)->x_lab->s_name);
            auto pos = name.find("@");
            if(pos != std::string::npos)
            {
                name.erase(name.begin(), name.begin()+pos+1);
            }
            else
            {
                return std::string();
            }
            pos = name.find("_");
            while(pos != std::string::npos)
            {
                name.replace(pos, 1, " ");
            }
            return name;
        }
        return std::string();
    }
    
    void* Slider::getBindingPtr() const
    {
        if(isValid())
        {
            return reinterpret_cast<t_iemgui *>(m_internal->object)->x_rcv;
        }
        return nullptr;
    }
    
    float Slider::getMinimum() const noexcept
    {
        if(isValid())
        {
            return reinterpret_cast<t_hslider *>(m_internal->object)->x_min;
        }
        return 0.f;
    }
    
    float Slider::getMaximum() const noexcept
    {
        if(isValid())
        {
            return reinterpret_cast<t_hslider *>(m_internal->object)->x_max;
        }
        return 1.f;
    }
    
    float Slider::getValue() const noexcept
    {
        if(isValid())
        {
            return reinterpret_cast<t_hslider *>(m_internal->object)->x_fval;
        }
        return 0.f;
    }
    
    std::array<float, 4> Slider::getBounds() const noexcept
    {
        if(isValid())
        {
            int x1, x2, y1, y2;
            m_internal->object->te_g.g_pd->c_wb->w_getrectfn(
            reinterpret_cast<t_gobj *>(m_internal->object),
            reinterpret_cast<struct _glist *>(m_internal->patch.getPtr()),
            &x1, &y1, &x2, &y2);
            return {float(x1), float(y1), float(x2 - x1), float(y2 - y1)};
        }
        return {0.f, 0.f, 0.f, 0.f};
    }
    
    std::array<float, 2> Slider::getLabelPosition() const noexcept
    {
        if(isValid())
        {
            return {float(reinterpret_cast<t_iemgui *>(m_internal->object)->x_ldx), float(reinterpret_cast<t_iemgui *>(m_internal->object)->x_ldy)};
        }
        return {0.f, 0.f};
    }
}



