/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PdObject.hpp"
#include <iostream>
#include <limits>
#include <cmath>
#include <array>

extern "C"
{
#include <z_libpd.h>
#include <m_pd.h>
#include <m_imp.h>
#include <g_canvas.h>
#include <g_all_guis.h>
#include "x_libpd_multi.h"
}

namespace pd
{
    // ==================================================================================== //
    //                                      COMMENT                                         //
    // ==================================================================================== //
    
    
    Object::Object() noexcept : m_ptr(nullptr), m_patch()
    {
        
    }
    
    Object::Object(void* ptr, Patch const& patch) noexcept :
    m_ptr(ptr), m_patch(patch)
    {
        ;
    }
    
    Object::Object(Object const& other) noexcept :
    m_ptr(other.m_ptr), m_patch(other.m_patch)
    {
        ;
    }
    

    Object& Object::operator=(Object const& other) noexcept
    {
        m_ptr   = other.m_ptr;
        m_patch = other.m_patch;
        return *this;
    }
    
    Object::~Object() noexcept
    {
        m_ptr = nullptr;
    }
    
    std::string Object::getText() const
    {
        if(m_ptr != nullptr)
        {
            char* text = nullptr;
            int size = 0;
            m_patch.m_instance->setThis();
            binbuf_gettext(static_cast<t_text*>(m_ptr)->te_binbuf, &text, &size);
            if(text && size)
            {
                std::string txt(text, size);
                freebytes(static_cast<void*>(text), static_cast<size_t>(size) * sizeof(char));
                return txt;
            }
            
        }
        return std::string();
    }
    
    std::string Object::getName() const
    {
        if(m_ptr != nullptr && static_cast<t_text*>(m_ptr)->te_g.g_pd->c_name)
        {
            return std::string(static_cast<t_text*>(m_ptr)->te_g.g_pd->c_name->s_name);
        }
        return std::string();
    }
    
    std::array<int, 4> Object::getBounds() const noexcept
    {
        if(m_ptr != nullptr)
        {
            struct _widgetbehavior const* wb = static_cast<t_text*>(m_ptr)->te_g.g_pd->c_wb;
            if(static_cast<t_text*>(m_ptr)->te_g.g_pd->c_patchable && wb && wb->w_getrectfn)
            {
                int x = 0, y = 0, w = 0, h = 0;
                m_patch.m_instance->setThis();
                wb->w_getrectfn(static_cast<t_gobj*>(m_ptr), static_cast<t_canvas*>(m_patch.m_ptr), &x, &y, &w, &h);
                w = w - x + 1;
                h = h - y + 1;
                x = x - static_cast<t_canvas*>(m_patch.m_ptr)->gl_xmargin - 1;
                y = y - static_cast<t_canvas*>(m_patch.m_ptr)->gl_ymargin - 1;
                return {{x, y, w, h}};
            }
        }
        return {{0, 0, 0, 0}};
    }
    
    // ==================================================================================== //
    //                                      GUI                                          //
    // ==================================================================================== //
    
    // False GATOM
    typedef struct _fake_gatom
    {
        t_text      a_text;
        t_atom      a_atom;
        t_glist*    a_glist;
        t_float a_toggle;
        t_float a_draghi;
        t_float a_draglo;
        t_symbol *a_label;
        t_symbol *a_symfrom;
        t_symbol *a_symto;
        char a_buf[40];
        char a_shift;
        char a_wherelabel;      // 0-3 for left, right, above, below
        t_symbol *a_expanded_to;
    } t_fake_gatom;
    
    // False GARRAY
    typedef struct _fake_garray
    {
        t_gobj x_gobj;
        t_scalar *x_scalar;
        t_glist *x_glist;
        t_symbol *x_name;
        t_symbol *x_realname;
        char x_usedindsp;
        char x_saveit;
        char x_listviewing;
        char x_hidename;
    } t_fake_garray;

    
    Gui::Gui() noexcept : Object(), m_type(Type::Undefined)
    {
        
    }
    
    Gui::Gui(void* ptr, Patch const& patch) noexcept :
    Object(ptr, patch), m_type(Type::Undefined)
    {
        const std::string name = getName();
        if(name == "bng")
        {
           m_type = Type::Bang;
        }
        else if(name == "hsl")
        {
           m_type = Type::HorizontalSlider;
        }
        else if(name == "vsl")
        {
           m_type = Type::VerticalSlider;
        }
        else if(name == "tgl")
        {
           m_type = Type::Toggle;
        }
        else if(name == "nbx")
        {
           m_type = Type::Number;
        }
        else if(name == "vradio")
        {
           m_type = Type::VerticalRadio;
        }
        else if(name == "hradio")
        {
           m_type = Type::HorizontalRadio;
        }
        else if(name == "cnv")
        {
           m_type = Type::Panel;
        }
        else if(name == "vu")
        {
           m_type = Type::VuMeter;
        }
        else if(name == "text")
        {
           m_type = Type::Comment;
        }
        else if(name == "gatom")
        {
            if(static_cast<t_fake_gatom*>(m_ptr)->a_atom.a_type == A_FLOAT)
                m_type = Type::AtomNumber;
            else if(static_cast<t_fake_gatom*>(m_ptr)->a_atom.a_type == A_SYMBOL)
                m_type = Type::AtomSymbol;
        }
        else if(name == "canvas")
        {
            if(static_cast<t_canvas*>(m_ptr)->gl_list)
            {
                t_class* c = static_cast<t_canvas*>(m_ptr)->gl_list->g_pd;
                if(c && c->c_name && std::string(c->c_name->s_name) == std::string("array"))
                {
                    m_type = Type::Array;
                }
            }
        }
    }
    
    Gui::Gui(Gui const& other) noexcept :
    Object(other), m_type(other.m_type)
    {
        ;
    }
    
    Gui& Gui::operator=(Gui const& other) noexcept
    {
        Object::operator=(other);
        m_type  = other.m_type;
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
    
    size_t Gui::getNumberOfSteps() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::Toggle)
        {
            return 2;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_number;
        }
        else if(m_type == Type::AtomNumber)
        {
            return static_cast<t_text*>(m_ptr)->te_width == 1;
        }
        return 0.f;
    }
    
    float Gui::getMinimum() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_min;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_min;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_min;
        }
        else if(m_type == Type::AtomNumber)
        {
            t_fake_gatom const* gatom = static_cast<t_fake_gatom const*>(m_ptr);
            if(std::abs(gatom->a_draglo) > std::numeric_limits<float>::epsilon() &&
               std::abs(gatom->a_draghi) > std::numeric_limits<float>::epsilon())
            {
                return gatom->a_draglo;
            }
            return -std::numeric_limits<float>::max();
        }
        return 0.f;
    }
    
    float Gui::getMaximum() const noexcept
    {
        if(!m_ptr)
            return 1.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_max;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_max;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_max;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_number - 1;
        }
        else if(m_type == Type::Bang)
        {
            return 1;
        }
        else if(m_type == Type::AtomNumber)
        {
            t_fake_gatom const* gatom = static_cast<t_fake_gatom const*>(m_ptr);
            if(std::abs(gatom->a_draglo) > std::numeric_limits<float>::epsilon() &&
               std::abs(gatom->a_draghi) > std::numeric_limits<float>::epsilon())
            {
                return gatom->a_draghi;
            }
            return std::numeric_limits<float>::max();
        }
        return 1.f;
    }
    
    float Gui::getValue() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_fval;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_fval;
        }
        else if(m_type == Type::Toggle)
        {
            return (static_cast<t_toggle*>(m_ptr))->x_on;
        }
        else if(m_type == Type::Number)
        {
            return (static_cast<t_my_numbox*>(m_ptr))->x_val;
        }
        else if(m_type == Type::HorizontalRadio)
        {
            return (static_cast<t_hdial*>(m_ptr))->x_on;
        }
        else if(m_type == Type::VerticalRadio)
        {
            return (static_cast<t_vdial*>(m_ptr))->x_on;
        }
        else if(m_type == Type::Bang)
        {
            return (static_cast<t_bng*>(m_ptr))->x_flashed;
        }
        else if(m_type == Type::VuMeter)
        {
            return 0;
        }
        else if(m_type == Type::AtomNumber)
        {
            return atom_getfloat(&(static_cast<t_fake_gatom*>(m_ptr)->a_atom));
        }
        return 0.f;
    }
    
    void Gui::setValue(float value) noexcept
    {
        if(!m_ptr || m_type == Type::Comment || m_type == Type::AtomSymbol)
            return;
        m_patch.m_instance->enqueueDirectMessages(m_ptr, value);
        
    }
    
    std::string Gui::getSymbol() const noexcept
    {
        if(!m_ptr || m_type != Type::AtomSymbol)
            return std::string();
        else
        {
            m_patch.m_instance->setThis();
            return atom_getsymbol(&(static_cast<t_fake_gatom*>(m_ptr)->a_atom))->s_name;
        }
    }
    
    void Gui::setSymbol(std::string const& value) noexcept
    {
        if(!m_ptr || m_type != Type::AtomSymbol)
            return;
        m_patch.m_instance->enqueueDirectMessages(m_ptr, value);
    }
    
    int Gui::getFontSize() const noexcept
    {
        if(!m_ptr )
            return 0;
        if(m_type >= Type::Comment)
        {
            m_patch.m_instance->setThis();
            return glist_fontheight(static_cast<t_canvas*>(m_patch.m_ptr));
        }
        else
        {
            return (static_cast<t_iemgui*>(m_ptr))->x_fontsize + 2;
        }
    }
    
    static unsigned int fromIemColors(int const color)
    {
        unsigned int const c = static_cast<unsigned int>(color << 8 | 0xFF);
        return ((0xFF << 24) | ((c >> 24) << 16) | ((c >> 16) << 8) | (c >> 8));
    }
    
    unsigned int Gui::getBackgroundColor() const noexcept
    {
        if(!m_ptr || m_type == Type::Undefined || m_type >= Type::Comment)
            return 0xffffffff;
        return fromIemColors(((static_cast<t_iemgui*>(m_ptr))->x_bcol));
    }
    
    unsigned int Gui::getForegroundColor() const noexcept
    {
        if(!m_ptr || m_type == Type::Undefined || m_type >= Type::Comment)
            return 0xff000000;
        return fromIemColors(((static_cast<t_iemgui*>(m_ptr))->x_fcol));
    }
    
    unsigned int Gui::getLabelColor() const noexcept
    {
        if(!m_ptr || m_type == Type::Undefined || m_type >= Type::Comment)
            return 0xff000000;
        return fromIemColors(((static_cast<t_iemgui*>(m_ptr))->x_lcol));
    }
    
    std::string Gui::getLabel() const noexcept
    {
        if(!m_ptr || m_type == Type::Undefined || m_type == Type::Comment)
            return std::string();
        if(m_type < Type::Comment && (static_cast<t_iemgui*>(m_ptr))->x_lab)
        {
            t_symbol const* label = canvas_realizedollar(static_cast<t_iemgui*>(m_ptr)->x_glist, static_cast<t_iemgui*>(m_ptr)->x_lab);
            std::string const str(label->s_name);
            if(str != std::string("empty"))
                return str;
            return std::string();
        }
        else if((m_type == Type::AtomNumber || m_type == Type::AtomSymbol)
                && static_cast<t_fake_gatom*>(m_ptr)->a_label)
        {
            t_symbol const* label = canvas_realizedollar(static_cast<t_fake_gatom*>(m_ptr)->a_glist, static_cast<t_fake_gatom*>(m_ptr)->a_label);
            return std::string(label->s_name);
        }
        return std::string();
    }
    
    std::array<int, 2> Gui::getLabelPosition() const noexcept
    {
        if(!m_ptr || m_type == Type::Undefined || m_type == Type::Comment)
            return {0, 0};
        if(m_type < Type::Comment && (static_cast<t_iemgui*>(m_ptr))->x_lab)
        {
            std::array<int, 4> const bounds = getBounds();
            t_iemgui const* iemgui = static_cast<t_iemgui*>(m_ptr);
            return {bounds[0] + iemgui->x_ldx, bounds[1] + iemgui->x_ldy};
        }
        else if((m_type == Type::AtomNumber || m_type == Type::AtomSymbol)
                && static_cast<t_fake_gatom*>(m_ptr)->a_label)
        {
            std::array<int, 4> const bounds = getBounds();
            t_fake_gatom const* gatom = static_cast<t_fake_gatom*>(m_ptr);
            if (gatom->a_wherelabel == 0) { // Left
                return {bounds[0] - 3 - static_cast<int>(getLabel().size()) * getFontSize(), bounds[1] + 2}; }
            else if (gatom->a_wherelabel == 1) { // Right
                return {bounds[0] + bounds[2] + 2, bounds[1] + 2}; }
            else if (gatom->a_wherelabel == 2) {  // Up
                return {bounds[0] - 1, bounds[1] - 1 - getFontSize()}; }
            return {bounds[0] - 1, bounds[1] + bounds[3] + 3}; // Down
        }
        return {0, 0};
    }
    
    std::array<int, 4> Gui::getBounds() const noexcept
    {
        std::array<int, 4> bounds = Object::getBounds();
        if(m_type == Type::Panel)
        {
            bounds[2] = static_cast<t_my_canvas*>(m_ptr)->x_vis_w + 1;
            bounds[3] = static_cast<t_my_canvas*>(m_ptr)->x_vis_h + 1;
        }
        else if(m_type == Type::Comment)
        {
            bounds[2] = bounds[2] < 1.f ? 360 : bounds[2] * 6;
            bounds[3] = 200;
        }
        else if(m_type == Type::AtomNumber || m_type == Type::AtomSymbol)
        {
            const int ow = static_cast<t_text*>(m_ptr)->te_width;
            const int offset = (ow + ow % 2) - 4;
            bounds[2] = (bounds[2] - offset) / 2;
            bounds[3] = bounds[3] - 1;
        }
        return bounds;
    }
    
    std::string Gui::getArraySymbol() const noexcept
    {
        if(m_type == Type::Array)
        {
            t_fake_garray* ar = reinterpret_cast<t_fake_garray*>(static_cast<t_canvas*>(m_ptr)->gl_list);
            if(ar && ar->x_realname)
            {
                return std::string(ar->x_realname->s_name);
            }
        }
        return std::string();
    }
}



