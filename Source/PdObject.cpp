/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.h"

namespace pd
{
    // ==================================================================================== //
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
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
    
    Object::Object(Patch const& patch, t_object* object) noexcept :
    m_internal(new Internal(patch, object))
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
}



