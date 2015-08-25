/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_TEXTEDITOR__
#define __CAMOMILE_PD_TEXTEDITOR__

#include "PdAtom.h"

namespace pd
{
    // ==================================================================================== //
    //                                      TEXT EDITOR                                     //
    // ==================================================================================== //
    
    class TextEditor
    {
    private:
        friend class Gui;
        t_etexteditor* m_editor;
    public:
        
        inline TextEditor(std::string const& name) noexcept : m_editor(etexteditor_getfromsymbol(gensym(name.c_str()))) {}
        inline TextEditor(TextEditor const& other) noexcept : m_editor(other.m_editor) {}
        inline operator bool() const noexcept {return bool(m_editor);}
        
        inline std::string getName() const noexcept {return m_editor->c_name->s_name;}
        inline bool isEmpty() const noexcept {return !m_editor->c_text || !m_editor->c_size;}
        inline std::string getText() const noexcept
        {return (isEmpty()) ? (std::string()) : (std::string(m_editor->c_text));}
        inline std::array<int,2> getPosition() const noexcept {return std::array<int,2>({getX(), getY()});}
        inline int getX() const noexcept {return int(m_editor->c_bounds.x);}
        inline int getY() const noexcept {return int(m_editor->c_bounds.y);}
        inline std::array<int,2> getSize() const noexcept {return std::array<int,2>({getWidth(), getHeight()});}
        inline int getWidth() const noexcept {return int(m_editor->c_bounds.width);}
        inline int getHeight() const noexcept {return int(m_editor->c_bounds.height);}
        inline std::array<int,4> getBounds() const noexcept
        {return std::array<int,4>({getX(),getY(),getWidth(),getHeight()});}
        inline bool shouldWrap() const noexcept {return m_editor->c_wrap;}
        inline std::array<float,4> getBackgroundColor() const noexcept
        {return std::array<float,4>({m_editor->c_bgcolor.red, m_editor->c_bgcolor.green, m_editor->c_bgcolor.blue, m_editor->c_bgcolor.alpha});}
        inline std::array<float,4> getTextColor() const noexcept
        {return std::array<float,4>({m_editor->c_txtcolor.red, m_editor->c_txtcolor.green, m_editor->c_txtcolor.blue, m_editor->c_txtcolor.alpha});}
        inline float getFontSize() const noexcept {return m_editor->c_font.c_size;}
        
        inline void setText(std::string const& text) const noexcept {etexteditor_settext(m_editor, text.c_str());}
    };
}

#endif
