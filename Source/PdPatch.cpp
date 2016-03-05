/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.hpp"
#include "PdInstance.hpp"
#include "Pd.hpp"

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
}

namespace pd
{    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    class Patch::Internal : public LeakDetector<Internal>
    {
    public:
        Instance            instance;
        t_canvas*           canvas;
        std::atomic<size_t> counter;
        const std::string   name;
        const std::string   path;
        
        Internal(Instance const& _instance, std::string const& _name, std::string const& _path);
        ~Internal();
    };
    
    Patch::Internal::Internal(Instance const& _instance, std::string const& _name, std::string const& _path) :
    instance(_instance),
    canvas(nullptr),
    counter(1),
    name(_name),
    path(_path)
    {
        if(instance.isValid())
        {
            canvas = reinterpret_cast<t_canvas*>(instance.createCanvas(_name, _path));
        }
        
    }
    
    Patch::Internal::~Internal()
    {
        if(canvas && instance.isValid())
        {
            instance.freeCanvas(canvas);
        }
    }
    
    Patch::Patch() noexcept : m_internal(nullptr)
    {
        
    }
    
    Patch::Patch(Instance const& istance, std::string const& name, std::string const& path) noexcept :
    m_internal(new Internal(istance, name, path))
    {
        
    }
    
    Patch::Patch(Patch const& other) noexcept : m_internal(other.m_internal)
    {
        if(m_internal)
        {
            m_internal->counter++;
        }
    }
    
    Patch::Patch(Patch&& other) noexcept : m_internal(other.m_internal)
    {
        other.m_internal = nullptr;
    }
    
    Patch& Patch::operator=(Patch const& other) noexcept
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
    
    Patch& Patch::operator=(Patch&& other) noexcept
    {
        std::swap(m_internal, other.m_internal);
        return *this;
    }
    
    Patch::~Patch() noexcept
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
    
    bool Patch::isValid() const noexcept
    {
        return bool(m_internal) && bool(m_internal->canvas);
    }
    
    Instance Patch::getInstance() const noexcept
    {
        return bool(m_internal) ? m_internal->instance : Instance();
    }
    
    std::string Patch::getName() const
    {
        return bool(m_internal) ? m_internal->name : std::string();
    }
    
    std::string Patch::getPath() const
    {
        return bool(m_internal) ? m_internal->path : std::string();
    }
    
    std::array<float, 2> Patch::getSize() const noexcept
    {
        if(isValid())
        {
            return {static_cast<float>(m_internal->canvas->gl_pixwidth), static_cast<float>(m_internal->canvas->gl_pixheight)};
        }
        return {0.f, 0.f};
    }
    
    std::vector<Object> Patch::getGuis() const noexcept
    {
        std::vector<Object> objects;
        if(isValid())
        {
            t_symbol* hsl = gensym("hsl");
            t_symbol* vsl = gensym("vsl");
            for(t_gobj *y = m_internal->canvas->gl_list; y; y = y->g_next)
            {
                if(y->g_pd->c_name == hsl || y->g_pd->c_name ==  vsl)
                {
                    objects.push_back(Object(*this, reinterpret_cast<void *>(y)));
                }
            }
        }
        return objects;
    }
}



