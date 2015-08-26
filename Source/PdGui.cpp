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
    
    
    bool Gui::hasPresetName() const noexcept
    {
        return is_valid_symbol(reinterpret_cast<t_ebox *>(getObject())->b_preset_id);
    }
    
    std::string Gui::getPresetName() const noexcept
    {
        if(hasPresetName())
        {
            t_ebox* box = reinterpret_cast<t_ebox *>(getObject());
            return std::string(box->b_preset_id->s_name);
        }
        return std::string();
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
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mousemove(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseenter)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mouseenter(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseExit(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseleave)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mouseleave(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDown(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousedown)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mousedown(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousedrag)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mousedrag(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseUp(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mouseup)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mouseup(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_dblclick)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_dblclick(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_mousewheel)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_mousewheel(getObject(), NULL, t_pt({pos[0], pos[1]}), (long)mod, delta[0], delta[1]);
        }
    }
    
    void Gui::textEditorKeyPress(TextEditor& editor, char ch) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_texteditor_keypress)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_texteditor_keypress(getObject(), editor.m_editor, (int)ch);
        }
    }
    
    void Gui::textEditorKeyFilter(TextEditor& editor, int filter) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_texteditor_keyfilter)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_texteditor_keyfilter(getObject(), editor.m_editor, (ekey_flags)filter);
        }
    }
    
    void Gui::popup(PopupMenu& menu, int item) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_popup)
        {
            int tocheck_recursion;
            //std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_popup(getObject(), menu.m_popup, item);
        }
    }
    
    void Gui::keyPressed(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_key)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_key(getObject(), NULL, key, mod);
        }
    }
    
    void Gui::keyFilter(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_keyfilter)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
            c->c_widget.w_keyfilter(getObject(), NULL, key, mod);
        }
    }
    
    std::vector<Layer> Gui::paint() const noexcept
    {
        t_eclass* c = getClass();
        std::vector<Layer> objs;
        t_ebox* x = ((t_ebox *)getObject());
        Instance instance(getInstance());
        if(instance && c && c->c_widget.w_paint && x->b_ready_to_draw)
        {
            std::lock_guard<std::mutex> guard(instance.m_internal->mutex);
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
        }
        
        return objs;
    }
    
    std::vector<Parameter> Gui::getParameters() const noexcept
    {
        t_ebox* x = ((t_ebox *)getObject());
        if(is_valid_symbol(x->b_preset_id))
        {
            std::vector<Parameter> params(x->b_nparams);
            for(size_t i = 0; i < x->b_nparams; i++)
            {
                params[i] = Parameter(x->b_params+i);
            }
            return params;
        }
        return std::vector<Parameter>();
    }

}



