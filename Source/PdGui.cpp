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
    
    Gui::Gui(void* handle)// : Object(handle)
    {
        t_eclass* c = getClass();
        if(!c || !eobj_iscicm(getHandle()) || !eobj_isbox(getHandle()))
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "The object isn't a GUI !";}
            };
        }
        else if(c && c->c_widget.w_getdrawparameters)
        {
            t_edrawparams params;
            c->c_widget.w_getdrawparameters(getHandle(), NULL, &params);
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
    
    bool Gui::hasPresetName() const noexcept
    {
        return is_valid_symbol(reinterpret_cast<t_ebox *>(getHandle())->b_preset_id);
    }
    
    std::string Gui::getPresetName() const noexcept
    {
        if(hasPresetName())
        {
            t_ebox* box = reinterpret_cast<t_ebox *>(getHandle());
            return std::string(box->b_preset_id->s_name);
        }
        return std::string();
    }
    
    bool Gui::wantMouse() const noexcept
    {
        t_eclass* c = getClass();
        return c && !(reinterpret_cast<t_ebox *>(getHandle())->b_flags & EBOX_IGNORELOCKCLICK) &&
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
        if(c && c->c_widget.w_mousemove)
        {
            c->c_widget.w_mousemove(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseenter)
        {
            c->c_widget.w_mouseenter(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseExit(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseleave)
        {
            c->c_widget.w_mouseleave(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDown(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedown)
        {
            c->c_widget.w_mousedown(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedrag)
        {
            c->c_widget.w_mousedrag(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseUp(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseup)
        {
            c->c_widget.w_mouseup(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_dblclick)
        {
            c->c_widget.w_dblclick(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousewheel)
        {
            c->c_widget.w_mousewheel(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod, delta[0], delta[1]);
        }
    }
    
    void Gui::textEditorKeyPress(TextEditor& editor, char ch) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_texteditor_keypress)
        {
            c->c_widget.w_texteditor_keypress(getHandle(), editor.m_editor, (int)ch);
        }
    }
    
    void Gui::textEditorKeyFilter(TextEditor& editor, int filter) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_texteditor_keyfilter)
        {
            c->c_widget.w_texteditor_keyfilter(getHandle(), editor.m_editor, (ekey_flags)filter);
        }
    }
    
    void Gui::keyPressed(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_key)
        {
            c->c_widget.w_key(getHandle(), NULL, key, mod);
        }
    }
    
    void Gui::keyFilter(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_keyfilter)
        {
            c->c_widget.w_keyfilter(getHandle(), NULL, key, mod);
        }
    }
    
    std::vector<Layer> Gui::paint() const noexcept
    {
        t_eclass* c = getClass();
        std::vector<Layer> objs;
        t_ebox* x = ((t_ebox *)getHandle());
        if(c && c->c_widget.w_paint && x->b_ready_to_draw)
        {
            if(x->b_layers)
            {
                for(int i = 0; i < x->b_number_of_layers; i++)
                {
                    x->b_layers[i].e_state = EGRAPHICS_INVALID;
                }
            }
            c->c_widget.w_paint(m_handle, NULL);
            objs.resize(x->b_number_of_layers);
            for(size_t i = 0; i < objs.size(); i++)
            {
                objs[i] = ((t_ebox *)(m_handle))->b_layers+i;
            }
        }
        
        return objs;
    }

}



