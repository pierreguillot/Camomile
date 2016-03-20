/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.hpp"
#include "PdGui.hpp"

extern "C"
{
#include "z_pd.h"
}

namespace pd
{    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Patch() noexcept : m_ptr(nullptr), m_count(nullptr), m_instance()
    {
        
    }
    
    Patch::Patch(Instance& instance, void* ptr, std::string const& name, std::string const& path) noexcept :
    m_ptr(ptr), m_count(new std::atomic<size_t>(1)), m_instance(instance)
    {
    }
    
    Patch::Patch(Patch const& other) noexcept :
    m_ptr(other.m_ptr), m_count(other.m_count), m_instance(other.m_instance)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Patch::Patch(Patch&& other) noexcept :
    m_ptr(other.m_ptr), m_count(other.m_count), m_instance(other.m_instance)
    {
        other.m_ptr     = nullptr;
        other.m_count   = nullptr;
        other.m_instance = Instance();
    }
    
    Patch& Patch::operator=(Patch const& other) noexcept
    {
        if(m_ptr && m_count && --(*m_count) == 0)
        {
            if(m_instance.isValid())
            {
                m_instance.freePatch(*this);
                m_instance  = Instance();
            }
            m_ptr       = nullptr;
            m_count     = nullptr;
        }
        if(other.m_ptr && other.m_count)
        {
            ++(*m_count);
            m_ptr       = other.m_ptr;
            m_count     = other.m_count;
            m_instance  = other.m_instance;
        }
        return *this;
    }
    
    Patch& Patch::operator=(Patch&& other) noexcept
    {
        std::swap(m_count, other.m_count);
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_instance, other.m_instance);
        return *this;
    }
    
    Patch::~Patch() noexcept
    {
        if(m_ptr && m_count && --(*m_count) == 0)
        {
            if(m_instance.isValid())
            {
                m_instance.freePatch(*this);
                m_instance  = Instance();
            }
            m_ptr       = nullptr;
            m_count     = nullptr;
        }
    }
    
    bool Patch::isValid() const noexcept
    {
        return bool(m_ptr) && bool(m_count) && m_instance.isValid();
    }
    
    Instance Patch::getInstance() const noexcept
    {
        return m_instance;
    }
    
    std::string Patch::getName() const
    {
        return isValid() ? z_pd_patch_get_name(reinterpret_cast<z_patch *>(m_ptr)) : std::string();
    }
    
    std::string Patch::getPath() const
    {
        return isValid() ? z_pd_patch_get_path(reinterpret_cast<z_patch *>(m_ptr)) : std::string();
    }
    
    std::array<int, 2> Patch::getPosition() const noexcept
    {
        return isValid() ?
        std::array<int, 2>{z_pd_patch_get_x(reinterpret_cast<z_patch *>(m_ptr)), z_pd_patch_get_y(reinterpret_cast<z_patch *>(m_ptr))} :
        std::array<int, 2>{0, 0};
    }
    
    std::array<int, 2> Patch::getSize() const noexcept
    {
        return isValid() ?
        std::array<int, 2>{z_pd_patch_get_width(reinterpret_cast<z_patch *>(m_ptr)), z_pd_patch_get_height(reinterpret_cast<z_patch *>(m_ptr))} :
        std::array<int, 2>{0, 0};
    }
    
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> objects;
        if(isValid())
        {
            z_symbol* hsl = z_pd_get_symbol("hsl");
            z_symbol* vsl = z_pd_get_symbol("vsl");
            z_symbol* tgl = z_pd_get_symbol("tgl");
            z_symbol* nbx = z_pd_get_symbol("nbx");
            z_symbol* vra = z_pd_get_symbol("vradio");
            z_symbol* hra = z_pd_get_symbol("hradio");
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
    
    std::vector<Comment> Patch::getComments() const noexcept
    {
        std::vector<Comment> objects;
        if(isValid())
        {
            z_symbol* txt = z_pd_get_symbol("text");
            for(z_object *y = z_pd_patch_get_first_object(reinterpret_cast<z_patch *>(m_ptr)); y;
                y = z_pd_patch_get_next_object(reinterpret_cast<z_patch *>(m_ptr), y))
            {
                if(z_pd_object_get_name(y)== txt)
                {
                    objects.push_back(Comment(*this, reinterpret_cast<void *>(y)));
                }
            }
        }
        return objects;
    }
    
    std::array<float, 4> Patch::getGuiBounds(Gui const& gui) const noexcept
    {
        int todo;
        /*
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            t_object* obj = reinterpret_cast<t_object *>(gui.m_ptr);
            int x1, x2, y1, y2;
            obj->te_g.g_pd->c_wb->w_getrectfn(reinterpret_cast<t_gobj *>(gui.m_ptr),
                                              reinterpret_cast<struct _glist *>(m_ptr),
                                              &x1, &y1, &x2, &y2);
            return {float(x1) - cnv->gl_xmargin, float(y1) - cnv->gl_ymargin, float(x2 - x1), float(y2 - y1)};
        }*/
        return {0.f, 0.f, 0.f, 0.f};
    }
    
    std::array<float, 2> Patch::getGuiLabelPosition(Gui const& gui) const noexcept
    {
        int todo;
        /*
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            t_text* obj = reinterpret_cast<t_text *>(gui.m_ptr);
            t_iemgui* gi = reinterpret_cast<t_iemgui *>(gui.m_ptr);
            return {float(obj->te_xpix) - cnv->gl_xmargin + gi->x_ldx, float(obj->te_ypix) - cnv->gl_ymargin +  + gi->x_ldy};
        }*/
        return {0.f, 0.f};
    }
}



