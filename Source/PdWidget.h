/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_WIDGET__
#define __CAMOMILE_PD_WIDGET__

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
    
    // ==================================================================================== //
    //                                      POPUP MENU                                      //
    // ==================================================================================== //
    
    class PopupMenu
    {
    private:
        friend class Gui;
        t_epopup* m_popup;
    public:
        
        inline PopupMenu(std::string const& name) noexcept : m_popup(epopupmenu_getfromsymbol(gensym(name.c_str()))) {}
        inline PopupMenu(PopupMenu const& other) noexcept : m_popup(other.m_popup) {}
        inline operator bool() const noexcept {return bool(m_popup);}
        
        inline std::string getName() const noexcept {return m_popup->c_name->s_name;}
        inline bool isEmpty() const noexcept {return !m_popup->c_items || !m_popup->c_size;}
        inline int getNumberOfItems() const noexcept {return m_popup->c_size;}
        inline int getItemId(int index) const noexcept {return m_popup->c_items[index].c_id;}
        inline std::string getItemLabel(int index) const noexcept {return std::string(m_popup->c_items[index].c_label);}
        inline bool isItemChecked(int index) const noexcept {return int(m_popup->c_items[index].c_checked);}
        inline bool isItemDisable(int index) const noexcept {return int(m_popup->c_items[index].c_disable);}
        inline bool isItemSeparator(int index) const noexcept {return int(m_popup->c_items[index].c_separator);}
        
        inline std::array<int,2> getPosition() const noexcept {return std::array<int,2>({getX(), getY()});}
        inline int getX() const noexcept {return int(m_popup->c_bounds.x);}
        inline int getY() const noexcept {return int(m_popup->c_bounds.y);}
        inline std::array<int,2> getSize() const noexcept {return std::array<int,2>({getWidth(), getHeight()});}
        inline int getWidth() const noexcept {return int(m_popup->c_bounds.width);}
        inline int getHeight() const noexcept {return int(m_popup->c_bounds.height);}
        inline std::array<int,4> getBounds() const noexcept
        {return std::array<int,4>({getX(),getY(),getWidth(),getHeight()});}
        
        inline std::array<float,4> getBackgroundColor() const noexcept
        {return std::array<float,4>({m_popup->c_bgcolor.red, m_popup->c_bgcolor.green, m_popup->c_bgcolor.blue, m_popup->c_bgcolor.alpha});}
        inline std::array<float,4> getTextColor() const noexcept
        {return std::array<float,4>({m_popup->c_txtcolor.red, m_popup->c_txtcolor.green, m_popup->c_txtcolor.blue, m_popup->c_txtcolor.alpha});}
        inline float getFontSize() const noexcept {return m_popup->c_font.c_size;}
    };
    
    // ==================================================================================== //
    //                                      POPUP MENU                                      //
    // ==================================================================================== //
    
    class Parameter
    {
    private:
        friend class Gui;
        t_eparam* m_parameter;
        
    public:
        
        Parameter() noexcept : m_parameter(nullptr) {}
        
        Parameter(Parameter const& other) noexcept : m_parameter(other.m_parameter) {}
        
        Parameter(t_eparam* param) noexcept : m_parameter(param) {}
        
        inline float getNormalizedValue() const {
            return bool(m_parameter) ? ebox_parameter_get(m_parameter->p_owner, m_parameter->p_name) : 0.f;}
        
        inline void setNormalizedValue(float value) {
            if(bool(m_parameter)) {ebox_parameter_set(m_parameter->p_owner, m_parameter->p_name, value);}}
        
        inline float getDefaultNormalizedValue() const{
            return bool(m_parameter) ? ebox_parameter_getdefault(m_parameter->p_owner, m_parameter->p_name) : 0.f;}
        
        inline std::string getName() const {
            return bool(m_parameter) ? std::string(m_parameter->p_name->s_name) : std::string();}
        
        inline std::string getObjectName() const {
            return bool(m_parameter) ? std::string(m_parameter->p_owner->b_preset_id->s_name) : std::string();}
        
        inline std::string getFullName() const {return getObjectName() + " : " + getName();}
        
        inline std::string getLabel() const {
            return bool(m_parameter) ? std::string(m_parameter->p_label->s_name) : std::string();}
        
        std::string getTextForValue(float value) const {
            std::string text;
            if(bool(m_parameter))
            {
                char* text = NULL;
                ebox_parameter_gettextforvalue(m_parameter->p_owner, m_parameter->p_name, &text, value);
                if(text)
                {
                    text = text;
                    free(text);
                }
            }
            return text;
        }
        
        float getValueForText(const std::string& text) const {
            return bool(m_parameter) ? ebox_parameter_getvaluefortext(m_parameter->p_owner, m_parameter->p_name, text.c_str()) : 0.f;}
        
        inline bool isAutomatable() const {return bool(m_parameter->p_auto);}
        
        inline bool isMetaParameter() const {return bool(m_parameter->p_meta);}
    };
}

#endif
