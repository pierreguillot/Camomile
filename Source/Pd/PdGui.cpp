/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PdGui.hpp"
#include "PdInstance.hpp"
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
    //                                      GUI                                             //
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

    
    Gui::Gui() noexcept : Object(), m_type(Type::Undefined)
    {
        
    }
    
    Gui::Gui(void* ptr, void* patch, Instance* instance) noexcept :
    Object(ptr, patch, instance), m_type(Type::Undefined)
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
    
    bool Gui::isIEM() const noexcept
    {
        return m_ptr && m_type != Type::Undefined && m_type < Type::Comment;
    }
    
    bool Gui::isAtom() const noexcept
    {
        return m_type == Type::AtomNumber || m_type == Type::AtomSymbol;
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
        m_instance->enqueueDirectMessages(m_ptr, value);
        
    }
    
    bool Gui::jumpOnClick() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_steady == 0;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_steady == 0;
        }
        return false;
    }
    
    bool Gui::isLogScale() const noexcept
    {
        if(!m_ptr)
            return 0.f;
        if(m_type == Type::HorizontalSlider)
        {
            return (static_cast<t_hslider*>(m_ptr))->x_lin0_log1 != 0;
        }
        else if(m_type == Type::VerticalSlider)
        {
            return (static_cast<t_vslider*>(m_ptr))->x_lin0_log1 != 0;
        }
        return false;
    }
    
    std::string Gui::getSymbol() const noexcept
    {
        if(!m_ptr || m_type != Type::AtomSymbol)
            return std::string();
        else
        {
            m_instance->setThis();
            return atom_getsymbol(&(static_cast<t_fake_gatom*>(m_ptr)->a_atom))->s_name;
        }
    }
    
    void Gui::setSymbol(std::string const& value) noexcept
    {
        if(!m_ptr || m_type != Type::AtomSymbol)
            return;
        m_instance->enqueueDirectMessages(m_ptr, value);
    }
    
    int Gui::getFontSize() const noexcept
    {
        if(!m_ptr )
            return 0;
        if(isIEM())
        {
            return (static_cast<t_iemgui*>(m_ptr))->x_fontsize + 2;
        }
        else
        {
            m_instance->setThis();
            return glist_fontheight(static_cast<t_canvas*>(m_patch));
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
            bounds[2] = bounds[2] < 1.f ? 360 : bounds[2] / 2;
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
    
    Graph Gui::getGraph() const noexcept
    {
        if(m_type == Type::Array)
        {
            return Graph(static_cast<t_canvas*>(m_ptr)->gl_list, *(m_instance));
        }
        return Graph();
    }
    
    Label Gui::getLabel() const noexcept
    {
        m_instance->setThis();
        if(isIEM())
        {
            t_symbol const* sym = canvas_realizedollar(static_cast<t_iemgui*>(m_ptr)->x_glist, static_cast<t_iemgui*>(m_ptr)->x_lab);
            if(sym)
            {
                std::string const text = sym->s_name;
                if(text != std::string("empty"))
                {
                    unsigned int const color = fromIemColors(((static_cast<t_iemgui*>(m_ptr))->x_fcol));
                    std::array<int, 4> const bounds = getBounds();
                    t_iemgui const* iemgui = static_cast<t_iemgui*>(m_ptr);
                    return Label(text, color, bounds[0] + iemgui->x_ldx, bounds[1] + iemgui->x_ldy);
                }
            }
        }
        else if(isAtom())
        {
            t_symbol const* sym = canvas_realizedollar(static_cast<t_fake_gatom*>(m_ptr)->a_glist, static_cast<t_fake_gatom*>(m_ptr)->a_label);
            if(sym)
            {
                std::string const text = sym->s_name;
                std::array<int, 4> const bounds = getBounds();
                t_fake_gatom const* gatom = static_cast<t_fake_gatom*>(m_ptr);
                if (gatom->a_wherelabel == 0) // Left
                {
                    return Label(text, 0xff000000, bounds[0] - 2 - static_cast<int>(text.size() / 2) * glist_fontwidth(static_cast<t_fake_gatom*>(m_ptr)->a_glist), bounds[1] + getFontSize() / 2);
                }
                else if (gatom->a_wherelabel == 1) // Right
                {
                    return Label(text, 0xff000000, bounds[0] + bounds[2] + 2, bounds[1] + getFontSize() / 2);
                }
                else if (gatom->a_wherelabel == 2) // Up
                {
                    return Label(text, 0xff000000, bounds[0] - 1, bounds[1] - 1 - getFontSize() / 2);
                }
                return Label(text, 0xff000000, bounds[0] - 1, bounds[1] + bounds[3] + 2 + getFontSize() / 2); // Down
            }
        }
        return Label();
    }
    
    // ==================================================================================== //
    //                                      LABEL                                           //
    // ==================================================================================== //
    
    Label::Label() noexcept :
    m_text(""),
    m_color(0xff000000),
    m_position({0, 0})
    {
    }
    
    Label::Label(Label const& other) noexcept :
    m_text(other.m_text),
    m_color(other.m_color),
    m_position(other.m_position)
    {
    }
    
    Label::Label(std::string const& text, unsigned int color, int x, int y) noexcept :
    m_text(text),
    m_color(color),
    m_position({x, y})
    {
        
    }
    
    // ==================================================================================== //
    //                                      GRAPH                                           //
    // ==================================================================================== //
    
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
    
    Graph::Graph() noexcept :
    m_instance(nullptr), m_name(""), m_drawing_mode(0), m_is_gop(false), m_scale({-1, 1})
    {
        
    }
    
    Graph::Graph(Graph const& other) noexcept :
    m_instance(other.m_instance),
    m_name(other.m_name),
    m_drawing_mode(other.m_drawing_mode),
    m_is_gop(other.m_is_gop),
    m_scale(other.m_scale)
    {
        
    }
    
    Graph::Graph(Instance& instance, std::string const& name) noexcept :
    m_instance(&instance),
    m_name(name),
    m_drawing_mode(1),
    m_is_gop(false),
    m_scale({-1, 1})
    {
        ;
    }
    
    Graph::Graph(void* ptr, Instance& instance) noexcept :
    m_instance(&instance),
    m_name(""),
    m_drawing_mode(0),
    m_is_gop(true),
    m_scale({-1, 1})
    {
        if(ptr)
        {
            t_fake_garray const * ar = static_cast<t_fake_garray*>(ptr);
            if(ar && ar->x_realname && ar->x_scalar)
            {
                m_name = std::string(ar->x_realname->s_name);
                m_instance->setThis();
                t_scalar *scalar = ar->x_scalar;
                t_template *scalartplte = template_findbyname(scalar->sc_template);
                if(scalartplte)
                {
                    m_drawing_mode = static_cast<size_t>(template_getfloat(scalartplte, gensym("style"), scalar->sc_vec, 0));
                }
            }
            if(ar && ar->x_glist)
            {
                m_scale = {static_cast<float>(ar->x_glist->gl_y2), static_cast<float>(ar->x_glist->gl_y1)};
            }
        }
    }
    
    std::string Graph::getName() const noexcept
    {
        return m_name;
    }
    
    bool Graph::isDrawingPoints() const noexcept
    {
        return m_drawing_mode == 0;
    }
    
    bool Graph::isDrawingLine() const noexcept
    {
        return m_drawing_mode == 1;
    }
    
    bool Graph::isDrawingCurve() const noexcept
    {
        return m_drawing_mode == 2;
    }
    
    bool Graph::isGOP() const noexcept
    {
        return m_is_gop;
    }
    
    std::array<float, 2> Graph::getScale() const noexcept
    {
        return m_scale;
    }
    
    void Graph::read(std::vector<float>& output) const
    {
        m_instance->setThis();
        m_instance->readArray(m_name, output);
    }
    
    void Graph::write(std::vector<float> const& input)
    {
        m_instance->setThis();
        m_instance->writeArray(m_name, input);
    }
    
    void Graph::writeSample(const size_t pos, float const input)
    {
        m_instance->setThis();
        m_instance->writeArraySample(m_name, pos, input);
    }
}



