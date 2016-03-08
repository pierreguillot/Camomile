/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdGui.hpp"

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
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Patch() noexcept : m_ptr(nullptr), m_count(nullptr), m_instance()
    {
        
    }
    
    Patch::Patch(Instance& instance, void* ptr, std::string const& name, std::string const& path) noexcept :
    m_ptr(ptr), m_count(new std::atomic<size_t>(1)), m_name(name), m_path(path), m_instance(instance)
    {
    }
    
    Patch::Patch(Patch const& other) noexcept :
    m_ptr(other.m_ptr), m_count(other.m_count), m_name(other.m_name), m_path(other.m_path), m_instance(other.m_instance)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Patch::Patch(Patch&& other) noexcept :
    m_ptr(other.m_ptr), m_count(other.m_count), m_name(other.m_name), m_path(other.m_path), m_instance(other.m_instance)
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
        std::swap(m_name, other.m_name);
        std::swap(m_path, other.m_path);
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
        return m_name;
    }
    
    std::string Patch::getPath() const
    {
        return m_path;
    }
    
    std::array<float, 2> Patch::getSize() const noexcept
    {
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            return {static_cast<float>(cnv->gl_pixwidth), static_cast<float>(cnv->gl_pixheight)};
        }
        return {0.f, 0.f};
    }
    
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> objects;
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            t_symbol* hsl = gensym("hsl");
            t_symbol* vsl = gensym("vsl");
            t_symbol* tgl = gensym("tgl");
            t_symbol* nbx = gensym("nbx");
            t_symbol* vra = gensym("vradio");
            t_symbol* hra = gensym("hradio");
            for(t_gobj *y = cnv->gl_list; y; y = y->g_next)
            {
                if(y->g_pd->c_name == hsl)
                {
                    objects.push_back(Gui(*this, Gui::Type::HorizontalSlider, reinterpret_cast<void *>(y)));
                }
                else if(y->g_pd->c_name == vsl)
                {
                    objects.push_back(Gui(*this, Gui::Type::VerticalSlider, reinterpret_cast<void *>(y)));
                }
                else if(y->g_pd->c_name == tgl)
                {
                    objects.push_back(Gui(*this, Gui::Type::Toggle, reinterpret_cast<void *>(y)));
                }
                else if(y->g_pd->c_name == nbx)
                {
                    objects.push_back(Gui(*this, Gui::Type::Number, reinterpret_cast<void *>(y)));
                }
                else if(y->g_pd->c_name == vra)
                {
                    objects.push_back(Gui(*this, Gui::Type::VerticalRadio, reinterpret_cast<void *>(y)));
                }
                else if(y->g_pd->c_name == hra)
                {
                    objects.push_back(Gui(*this, Gui::Type::HorizontalRadio, reinterpret_cast<void *>(y)));
                }
            }
        }
        return objects;
    }
    
    std::array<float, 4> Patch::getGuiBounds(Gui const& gui) const noexcept
    {
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            t_object* obj = reinterpret_cast<t_object *>(gui.m_ptr);
            int x1, x2, y1, y2;
            obj->te_g.g_pd->c_wb->w_getrectfn(reinterpret_cast<t_gobj *>(gui.m_ptr),
                                              reinterpret_cast<struct _glist *>(m_ptr),
                                              &x1, &y1, &x2, &y2);
            return {float(x1) - cnv->gl_xmargin, float(y1) - cnv->gl_ymargin, float(x2 - x1), float(y2 - y1)};
        }
        return {0.f, 0.f, 0.f, 0.f};
    }
    
    std::array<float, 2> Patch::getGuiLabelPosition(Gui const& gui) const noexcept
    {
        if(isValid())
        {
            t_canvas* cnv = reinterpret_cast<t_canvas*>(m_ptr);
            t_text* obj = reinterpret_cast<t_text *>(gui.m_ptr);
            t_iemgui* gi = reinterpret_cast<t_iemgui *>(gui.m_ptr);
            return {float(obj->te_xpix) - cnv->gl_xmargin + gi->x_ldx, float(obj->te_ypix) - cnv->gl_ymargin +  + gi->x_ldy};
        }
        return {0.f, 0.f};
    }
}



