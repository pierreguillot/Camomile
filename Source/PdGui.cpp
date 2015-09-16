/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdGui.h"

namespace pd
{
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    Gui::Gui() noexcept : Object(),
    m_background_color({0.f, 0.f, 0.f, 0.f}),
    m_border_color({0.f, 0.f, 0.f, 0.f}),
    m_border_size(0),
    m_corner_roundness(0)
    {
        
    }
    
    Gui::Gui(Patch const& patch, t_object* object) noexcept : Object(patch, object),
    m_background_color({0.f, 0.f, 0.f, 0.f}),
    m_border_color({0.f, 0.f, 0.f, 0.f}),
    m_border_size(0),
    m_corner_roundness(0)
    {
        t_eclass* c = getClass();
        if(isGui() && c->c_widget.w_getdrawparameters)
        {
            t_edrawparams params;
            c->c_widget.w_getdrawparameters(getObject(), NULL, &params);
            m_background_color = {params.d_boxfillcolor.red,
                params.d_boxfillcolor.green,
                params.d_boxfillcolor.blue,
                params.d_boxfillcolor.alpha};
            m_border_color = {params.d_bordercolor.red,
                params.d_bordercolor.green,
                params.d_bordercolor.blue,
                params.d_bordercolor.alpha};
            m_border_size = params.d_borderthickness;
            m_corner_roundness = params.d_cornersize;
        }
    }
    
    Gui::Gui(Gui const& other) noexcept : Object(other),
    m_background_color(other.m_background_color),
    m_border_color(other.m_border_color),
    m_border_size(other.m_border_size),
    m_corner_roundness(other.m_corner_roundness)
    {
        
    }
    
    Gui::Gui(Gui&& other) noexcept : Object(std::move(other)),
    m_background_color(other.m_background_color),
    m_border_color(other.m_border_color),
    m_border_size(other.m_border_size),
    m_corner_roundness(other.m_corner_roundness)
    {
        ;
    }
    
    Gui& Gui::operator=(Gui const& other) noexcept
    {
        m_background_color  = other.m_background_color;
        m_border_color      = other.m_border_color;
        m_border_size       = other.m_border_size;
        m_corner_roundness  = other.m_corner_roundness;
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
    
    Gui& Gui::operator=(Gui&& other) noexcept
    {
        std::swap(m_internal, other.m_internal);
        std::swap(m_background_color, other.m_background_color);
        std::swap(m_border_color, other.m_border_color);
        m_border_size       = other.m_border_size;
        m_corner_roundness  = other.m_corner_roundness;
        return *this;
    }
    
    bool Gui::wantMouse() const noexcept
    {
        t_eclass* c = getClass();
        return c && !(reinterpret_cast<t_ebox *>(getObject())->b_flags & EBOX_IGNORELOCKCLICK) &&
        (c->c_widget.w_mousedown ||
         c->c_widget.w_mousedrag ||
         c->c_widget.w_mouseenter ||
         c->c_widget.w_mouseleave ||
         c->c_widget.w_mousemove ||
         c->c_widget.w_mouseup ||
         c->c_widget.w_mousewheel ||
         c->c_widget.w_dblclick);
    }
    
    bool Gui::wantKeyboard() const noexcept
    {
        t_eclass* c = getClass();
        return c && (c->c_widget.w_key || c->c_widget.w_keyfilter);
    }
    
    bool Gui::hasTextEditor() const noexcept
    {
        t_eclass* c = getClass();
        return c && (c->c_widget.w_texteditor_keyfilter || c->c_widget.w_texteditor_keypress);
    }
    
    void Gui::mouseMove(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousemove)
        {
            instance.lock();
            c->c_widget.w_mousemove(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseenter)
        {
            instance.lock();
            c->c_widget.w_mouseenter(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseExit(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseleave)
        {
            instance.lock();
            c->c_widget.w_mouseleave(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseDown(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousedown)
        {
            instance.lock();
            c->c_widget.w_mousedown(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousedrag)
        {
            instance.lock();
            c->c_widget.w_mousedrag(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseUp(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseup)
        {
            instance.lock();
            c->c_widget.w_mouseup(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_dblclick)
        {
            instance.lock();
            c->c_widget.w_dblclick(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
            instance.unlock();
        }
    }
    
    void Gui::mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousewheel)
        {
            instance.lock();
            c->c_widget.w_mousewheel(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod, delta[0], delta[1]);
            instance.unlock();
        }
    }
    
    void Gui::textEditorKeyPress(TextEditor& editor, char ch) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_texteditor_keypress)
        {
            instance.lock();
            c->c_widget.w_texteditor_keypress(getObject(), editor.m_editor, (int)ch);
            instance.unlock();
        }
    }
    
    void Gui::textEditorKeyFilter(TextEditor& editor, int filter) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_texteditor_keyfilter)
        {
            instance.lock();
            c->c_widget.w_texteditor_keyfilter(getObject(), editor.m_editor, (ekey_flags)filter);
            instance.unlock();
        }
    }
    
    void Gui::popup(PopupMenu& menu, int item) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_popup)
        {
            instance.lock();
            c->c_widget.w_popup(getObject(), menu.m_popup, item);
            instance.unlock();
        }
    }
    
    void Gui::keyPressed(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_key)
        {
            instance.lock();
            c->c_widget.w_key(getObject(), NULL, key, mod);
            instance.unlock();
        }
    }
    
    void Gui::keyFilter(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_keyfilter)
        {
            instance.lock();
            c->c_widget.w_keyfilter(getObject(), NULL, key, mod);
            instance.unlock();
        }
    }
    
    std::tuple<std::string, float, bool, bool> Gui::getFont() const noexcept
    {
        int argc;
        t_atom* argv;
        std::string name;
        float size = 12.f;
        bool bold = false, italic = false;
        eobj_attr_getvalueof(getObject(), gensym("font"), &argc, &argv);
        if(argc && argv)
        {
            if(atom_gettype(argv) == A_SYMBOL)
            {
                name = std::string(atom_getsymbol(argv)->s_name);
            }
            if(argc > 1 && atom_gettype(argv+1) == A_FLOAT)
            {
                size = atom_getfloat(argv+1);
            }
            if(argc > 2 && atom_gettype(argv+2) == A_FLOAT)
            {
                bold = bool(atom_getfloat(argv+2));
            }
            if(argc > 3 && atom_gettype(argv+3) == A_FLOAT)
            {
                italic = bool(atom_getfloat(argv+3));
            }
            free(argv);
        }
        return std::make_tuple(name, size, bold, italic);
    }
    
    std::array<float, 4> Gui::getTextColor() const noexcept
    {
        int argc;
        t_atom* argv;
        std::array<float, 4> color({1.f, 1.f, 1.f, 1.f});
        eobj_attr_getvalueof(getObject(), gensym("txtcolor"), &argc, &argv);
        if(argc && argv)
        {
            if(atom_gettype(argv)  == A_FLOAT)
            {
                color[0] = atom_getfloat(argv);
            }
            if(argc > 1 && atom_gettype(argv+1) == A_FLOAT)
            {
                color[1] = atom_getfloat(argv+1);
            }
            if(argc > 2 && atom_gettype(argv+2) == A_FLOAT)
            {
                color[2] = atom_getfloat(argv+2);
            }
            if(argc > 3 && atom_gettype(argv+3) == A_FLOAT)
            {
                color[3] = atom_getfloat(argv+3);
            }
            free(argv);
        }
        return color;
    }
    
    std::vector<Atom> Gui::getAttr(std::string const& name) const noexcept
    {
        int argc;
        t_atom* argv;
        eobj_attr_getvalueof(getObject(), gensym(name.c_str()), &argc, &argv);
        std::vector<Atom> vec(argc);
        for(size_t i = 0; i < vec.size(); i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
            {
                vec[i] = atom_getfloat(argv+i);
            }
            if(atom_gettype(argv+i) == A_SYMBOL)
            {
                vec[i] = std::string(atom_getsymbol(argv+i)->s_name);
            }
        }
        return vec;
    }
    
    std::vector<Layer> Gui::paint() const noexcept
    {
        t_eclass* c = getClass();
        std::vector<Layer> objs;
        t_ebox* x = ((t_ebox *)getObject());
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_paint && x->b_ready_to_draw)
        {
            instance.lock();
            if(x->b_layers)
            {
                for(int i = 0; i < x->b_number_of_layers; i++)
                {
                    x->b_layers[i].e_state = EGRAPHICS_INVALID;
                }
            }
            c->c_widget.w_paint(getObject(), NULL);
            objs.resize(x->b_number_of_layers);
            for(size_t i = 0; i < objs.size(); i++)
            {
                objs[i] = ((t_ebox *)(getObject()))->b_layers+i;
            }
            instance.unlock();
        }
        
        return objs;
    }
    
    std::vector<Parameter> Gui::getParameters() const noexcept
    {
        t_ebox* x = ((t_ebox *)getObject());
        if(x->b_nparams)
        {
            std::vector<Parameter> params(x->b_nparams);
            for(size_t i = 0; i < x->b_nparams; i++)
            {
                if(x->b_params[i] && is_valid_symbol(x->b_params[i]->p_name))
                {
                    params[i] = Parameter(*this, std::string(x->b_params[i]->p_bind->s_name));
                }
            }
            return params;
        }
        return std::vector<Parameter>();
    }

}



