/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_GUI_INCLUDE_HPP
#define CAMO_GUI_INCLUDE_HPP

#include "camo_processor.hpp"
#include "../../JuceLibraryCode/JuceHeader.h"

namespace camo
{
    // ==================================================================================== //
    //                                  CAMOMILE GRAPHICS                                   //
    // ==================================================================================== //

    class graphics
    {
        static inline Font get_font()
        {
#ifdef __APPLE__
            return Font(String("Monaco"), 13.f, juce::Font::plain).withStyle(Font::bold);
#else
            return Font(String("DejaVu Sans Mono"), 12.f, juce::Font::plain).withStyle(Font::bold);
#endif
        }
        
        static inline int get_border_size() noexcept {return 1;}
        static inline Colour const& get_color_bg() noexcept {return Colours::lightgrey;}
        static inline Colour const& get_color_bd() noexcept {return Colours::darkgrey;}
        static inline Colour const& get_color_txt() noexcept {return Colours::darkgrey;}
        static inline Colour const& get_color_inv() noexcept {static Colour c(Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f)); return c;};
        
        
        class interface;
        class comment;
        class patch;
    };
    
    // ==================================================================================== //
    //                                  CAMOMILE INTERFACE                                  //
    // ==================================================================================== //
    
    class graphics::interface : public virtual Component
    {
    public:
        typedef xpd::gui::type_t type_t;
        
        interface(processor& processor, xpd::gui const& g);
        virtual ~interface() = default;
        inline type_t type() const noexcept {return m_gui.type();}
        inline float maximum() const noexcept {return m_gui.maximum();}
        inline float minimum() const noexcept {return m_gui.minimum();}
        inline float get() const noexcept {return m_gui.value();}
        void update();
        
        class bang;
        class toggle;
        class numbox;
        
    protected:
        
        void begin_changes() noexcept;
        void stop_changes() noexcept;
        void set(float value, bool normalized = true);
    private:
        static xpd::symbol get_symbol_float();
        processor&      m_processor;
        xpd::gui const& m_gui;
    };
    
    
    // ==================================================================================== //
    //                                  CAMOMILE BANG                                       //
    // ==================================================================================== //
    
    class graphics::interface::bang : public graphics::interface
    {
    public:
        bang(processor& processor, xpd::gui const& g);
        void paint(Graphics& g) final;
        void mouseDown(const MouseEvent& event) final;
        void mouseUp(const MouseEvent& event) final;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(bang)
    };
    
    // ==================================================================================== //
    //                                  CAMOMILE TOGGLE                                     //
    // ==================================================================================== //
    
    class graphics::interface::toggle : public graphics::interface
    {
    public:
        toggle(processor& processor, xpd::gui const& g);
        void paint(Graphics& g) final;
        void mouseDown(const MouseEvent& event) final;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(toggle)
    };
    
    // ==================================================================================== //
    //                                  CAMOMILE TOGGLE                                     //
    // ==================================================================================== //
    
    class graphics::interface::numbox : public graphics::interface, public Label::Listener
    {
    public:
        numbox(processor& processor, xpd::gui const& g);
        void paint(Graphics& g) final;
        void mouseDown(const MouseEvent& event) final;
        void mouseDrag(const MouseEvent& event) final;
        void mouseUp(const MouseEvent& event) final;
        void mouseDoubleClick(const MouseEvent&) final;
        
        void labelTextChanged(Label* label);
        void editorShown(Label*, TextEditor&) final;
        void editorHidden(Label*, TextEditor&) final;
    private:
        bool  m_shift;
        float m_value;
        Label m_label;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(numbox)
    };
    
    
    // ==================================================================================== //
    //                                  CAMOMILE COMMENT                                    //
    // ==================================================================================== //
    
    class graphics::comment : public Component
    {
    public:
        comment(xpd::object const& cmt);
        void paint(Graphics& g) final;
    private:
        const std::string m_text;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(comment)
    };
    
    // ==================================================================================== //
    //                                  CAMOMILE PATCH                                      //
    // ==================================================================================== //
    
    class jPatch : public Component
    {
    public:
        jPatch(xpd::patch const& patch);
        ~jPatch() = default;
        
    private:
        OwnedArray<Component>   m_objects;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jPatch)
    };
}

#endif // CAMO_GUI_INCLUDE_HPP
