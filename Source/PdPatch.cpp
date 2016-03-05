/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.h"
#include "PdObject.h"
#include "PdGui.h"

#include <iomanip>

namespace pd
{    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Internal::Internal(Instance const& _instance, std::string const& _name, std::string const& _path) :
    instance(_instance),
    canvas(nullptr),
    counter(1),
    name(_name),
    path(_path)
    {
        if(instance)
        {
            instance.lock();
            if(!name.empty() && !path.empty())
            {
                canvas = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
                canvas->gl_edit = 0;
            }
            else if(!name.empty())
            {
                canvas = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym("")));
                canvas->gl_edit = 0;
            }
            instance.unlock();
        }
        
    }
    
    Patch::Internal::~Internal()
    {
        if(canvas && instance)
        {
            instance.lock();
            canvas_free(const_cast<t_canvas*>(canvas));
            instance.unlock();
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
    
    std::vector<Object> Patch::getObjects() const noexcept
    {
        std::vector<Object> objects;
        if(bool(*this))
        {
            m_internal->instance.lock();
            for(t_gobj *y = m_internal->canvas->gl_list; y; y = y->g_next)
            {
                if(eobj_iscicm(y))
                {
                    objects.push_back(Object(*this, reinterpret_cast<t_object *>(y)));
                }
            }
            m_internal->instance.unlock();
        }
        return objects;
    }
    
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> objects;
        if(bool(*this))
        {
            m_internal->instance.lock();
            for(t_gobj *y = m_internal->canvas->gl_list; y; y = y->g_next)
            {
                if(eobj_iscicm(y) && eobj_isbox(y))
                {
                    objects.push_back(Gui(*this, reinterpret_cast<t_object *>(y)));
                }
            }
            m_internal->instance.unlock();
        }
        return objects;
    }
    
    Gui Patch::getCamomile() const noexcept
    {
        const std::string camostring("c.camomile");
        Gui camo;
        if(bool(*this))
        {
            m_internal->instance.lock();
            for(t_gobj *y = m_internal->canvas->gl_list; y; y = y->g_next)
            {
                if(eobj_iscicm(y) && eobj_isbox(y) && std::string(eobj_getclassname(y)->s_name) == camostring)
                {
                    camo = Gui(*this, reinterpret_cast<t_object *>(y));
                }
            }
            m_internal->instance.unlock();
        }
        return camo;
    }
}



