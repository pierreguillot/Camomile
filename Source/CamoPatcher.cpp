/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamoPatcher.h"

namespace camo
{
    /*
    Patcher::Patcher() noexcept : m_camomile(nullptr)
    {
        ;
    }
    
    Patcher::Patcher(pd::Patch const& other) noexcept :
    m_camomile(nullptr),
    m_patch(other)
    {
        t_canvas* cnv = (t_canvas *)(m_patch.handle());
        if(cnv)
        {
            for(t_gobj *y = cnv->gl_list; y; y = y->g_next)
            {
                if(eobj_getclassname(y) == gensym("c.camomile"))
                {
                    m_camomile = y;
                    return;
                }
            }
        }
    }
    
    Patcher::Patcher(Patcher const& other) noexcept :
    m_camomile(other.m_camomile),
    m_patch(other.m_patch)
    {
        
    }
    
    void Patcher::operator=(pd::Patch const& from) noexcept
    {
        m_patch = from;
        m_camomile = nullptr;
        t_canvas* cnv = (t_canvas *)(m_patch.handle());
        if(cnv)
        {
            for(t_gobj *y = cnv->gl_list; y; y = y->g_next)
            {
                if(eobj_getclassname(y) == gensym("c.camomile"))
                {
                    m_camomile = y;
                    return;
                }
            }
        }
    }
    
    void Patcher::operator=(Patcher const& from) noexcept
    {
        m_camomile = from.m_camomile;
        m_patch = from.m_patch;
    }
    
    std::vector<Object> Patcher::getObjects() const noexcept
    {
        std::vector<Object> objects;
        t_canvas* cnv = (t_canvas *)(m_patch.handle());
        if(cnv)
        {
            for(t_gobj *y = cnv->gl_list; y; y = y->g_next)
            {
                if(m_camomile != ((void *)(y)) && eobj_iscicm(y) && eobj_isbox(y))
                {
                    Object temp((void *)(y));
                    if(m_camomile.getBounds().contains(temp.getBounds()))
                    {
                        objects.push_back(temp);
                    }
                }
            }
        }
        return objects;
    }*/
}



