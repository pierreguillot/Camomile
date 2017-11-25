/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.h"
#include "PdObject.h"

extern "C"
{
#include <z_libpd.h>
#include <m_pd.h>
#include <g_canvas.h>
#include "x_libpd_multi.h"
}

namespace pd
{    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Patch() noexcept : m_ptr(nullptr), m_instance(nullptr) {}
    
    Patch::Patch(void* ptr, Instance* instance) noexcept : m_ptr(ptr), m_instance(instance) {}
    
    Patch::Patch(Patch const& other) noexcept : m_ptr(other.m_ptr), m_instance(other.m_instance) {}
    
    Patch& Patch::operator=(Patch const& other) noexcept
    {
        m_ptr = other.m_ptr;
        m_instance = other.m_instance;
        return *this;
    }
    
    Patch::~Patch() noexcept {}
    
    int Patch::getDollarZero() { return static_cast<bool>(m_ptr) ? libpd_getdollarzero(m_ptr) : 0; }
    bool Patch::isGraph() const noexcept {
        return static_cast<bool>(m_ptr) ? static_cast<bool>(static_cast<t_canvas*>(m_ptr)->gl_isgraph ): false; }
    
    std::array<int, 4> Patch::getBounds() const noexcept
    {
        t_canvas const* cnv = static_cast<t_canvas*>(m_ptr);
        if(static_cast<bool>(m_ptr) && cnv->gl_isgraph)
        {
            return {cnv->gl_xmargin, cnv->gl_ymargin, cnv->gl_pixwidth, cnv->gl_pixheight};
        }
        return {0, 0, 0, 0};
    }
    
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> objects;
        if(!m_ptr)
            return objects;
        
        for(t_gobj *y = static_cast<t_canvas*>(m_ptr)->gl_list; y; y = y->g_next)
        {
            Gui gui(static_cast<void*>(y), *this);
            if(gui.getType() != Gui::Type::Undefined)
            {
                objects.push_back(gui);
            }
        }
        return objects;
    }
}



