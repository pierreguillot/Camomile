/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.h"

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
    
    Patch::Patch() noexcept : m_ptr(nullptr) {}
    
    Patch::Patch(void* ptr) noexcept : m_ptr(ptr) {}
    
    Patch::Patch(Patch const& other) noexcept : m_ptr(other.m_ptr) {}
    
    Patch& Patch::operator=(Patch const& other) noexcept
    {
        m_ptr = other.m_ptr;
        return *this;
    }
    
    Patch::~Patch() noexcept {}
    int Patch::getDollarZero() { return static_cast<bool>(m_ptr) ? libpd_getdollarzero(m_ptr) : 0; }
    bool Patch::isGraph() const noexcept {
        return static_cast<bool>(m_ptr) ? static_cast<bool>(static_cast<t_canvas*>(m_ptr)->gl_isgraph ): false; }
    
    std::pair<int, int> Patch::getPosition() const noexcept
    {
        t_canvas const* cnv = static_cast<t_canvas*>(m_ptr);
        if(static_cast<bool>(m_ptr) && cnv->gl_isgraph)
        {
            return std::pair<int, int>{cnv->gl_xmargin, cnv->gl_ymargin};
        }
        return std::pair<int, int>{0, 0};
    }
    
    std::pair<int, int> Patch::getSize() const noexcept
    {
        t_canvas const* cnv = static_cast<t_canvas*>(m_ptr);
        if(static_cast<bool>(m_ptr) && cnv->gl_isgraph)
        {
            return std::pair<int, int>{cnv->gl_pixwidth, cnv->gl_pixheight};
        }
        return std::pair<int, int>{0, 0};
    }
    /*
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> objects;
        if(isValid())
        {
            z_symbol* hsl = z_pd_symbol_create("hsl");
            z_symbol* vsl = z_pd_symbol_create("vsl");
            z_symbol* tgl = z_pd_symbol_create("tgl");
            z_symbol* nbx = z_pd_symbol_create("nbx");
            z_symbol* vra = z_pd_symbol_create("vradio");
            z_symbol* hra = z_pd_symbol_create("hradio");
            for(z_object *y = z_pd_patch_get_first_object(reinterpret_cast<z_patch *>(m_ptr)); y;
                y = z_pd_patch_get_next_object(reinterpret_cast<z_patch *>(m_ptr), y))
            {
                if(z_pd_object_get_name(y) == hsl)
                {
                    objects.push_back(Gui(*this, Gui::Type::HorizontalSlider, reinterpret_cast<void *>(y)));
                }
                else if(z_pd_object_get_name(y) == vsl)
                {
                    objects.push_back(Gui(*this, Gui::Type::VerticalSlider, reinterpret_cast<void *>(y)));
                }
                else if(z_pd_object_get_name(y) == tgl)
                {
                    objects.push_back(Gui(*this, Gui::Type::Toggle, reinterpret_cast<void *>(y)));
                }
                else if(z_pd_object_get_name(y) == nbx)
                {
                    objects.push_back(Gui(*this, Gui::Type::Number, reinterpret_cast<void *>(y)));
                }
                else if(z_pd_object_get_name(y) == vra)
                {
                    objects.push_back(Gui(*this, Gui::Type::VerticalRadio, reinterpret_cast<void *>(y)));
                }
                else if(z_pd_object_get_name(y) == hra)
                {
                    objects.push_back(Gui(*this, Gui::Type::HorizontalRadio, reinterpret_cast<void *>(y)));
                }
            }
        }
        return objects;
    }
    
    std::vector<Object> Patch::getComments() const noexcept
    {
        std::vector<Object> objects;
        if(isValid())
        {
            z_symbol* txt = z_pd_symbol_create("text");
            for(z_object *y = z_pd_patch_get_first_object(reinterpret_cast<z_patch *>(m_ptr)); y;
                y = z_pd_patch_get_next_object(reinterpret_cast<z_patch *>(m_ptr), y))
            {
                if(z_pd_object_get_name(y)== txt)
                {
                    objects.push_back(Object(*this, reinterpret_cast<void *>(y)));
                }
            }
        }
        return objects;
    }
     */
}



