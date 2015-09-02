/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_GUI__
#define __CAMOMILE_PD_GUI__

#include "PdObject.h"
#include "PdWidget.h"

namespace pd
{
    // ==================================================================================== //
    //                                       PATH                                           //
    // ==================================================================================== //
    
    class Gobj
    {
    private:
        t_egobj* obj;
    public:
        
        enum Type
        {
            Invalid = 0,
            Path    = 1,
            Rect    = 2,
            Arc     = 3,
            Oval    = 4,
            Text    = 5
        };
        
        enum Justification
        {
            Left                            = 1,
            Right                           = 2,
            HorizontallyCentred             = 4,
            Top                             = 8,
            Bottom                          = 16,
            VerticallyCentred               = 32,
            horizontallyJustified           = 64,
            Centred                         = 36,
            CentredLeft                     = 33,
            CentredRight                    = 34,
            CentredTop                      = 12,
            CentredBottom                   = 20,
            TopLeft                         = 9,
            TopRight                        = 10,
            BottomLeft                      = 17,
            BottomRight                     = 18
        };
        
        inline constexpr Gobj() noexcept : obj(nullptr) {}
        inline constexpr Gobj(t_egobj* obj) noexcept : obj(obj) {}
        inline Type type() const noexcept {return Type(obj->e_type);}
        inline bool filled() const noexcept {return bool(obj->e_filled);}
        inline int witdh() const noexcept {return int(obj->e_width);}
        inline std::string text() const noexcept {return std::string(obj->e_text);}
        inline Justification justification() const noexcept {return Justification(obj->e_justify);}
        inline float fontSize() const noexcept {return obj->e_font.size;}
        inline bool wrapText() const noexcept {return false;}
        inline std::vector<t_pt> points() const noexcept {
            return std::vector<t_pt>(obj->e_points, obj->e_points+obj->e_npoints);}
        inline std::array<float, 4> color() const noexcept {
            return std::array<float, 4>({obj->e_color.red, obj->e_color.green, obj->e_color.blue, obj->e_color.alpha});
        }
    };
    
    // ==================================================================================== //
    //                                      LAYER                                           //
    // ==================================================================================== //
    
    class Layer
    {
    private:
        t_elayer* layer;
    public:
        
        enum State
        {
            Open    =  0,
            Closed  = -1,
            Invalid = -2,
            Todraw  = -3
        };
        
        inline constexpr Layer() noexcept : layer(nullptr) {}
        inline constexpr Layer(t_elayer* _layer) : layer(_layer) {}
        inline Layer& operator=(t_elayer* _layer) noexcept {layer = _layer; return *this;}
        inline State state() const noexcept {return (layer) ? (State(layer->e_state)) : Invalid;}
        inline size_t size() const noexcept {return size_t(layer->e_number_objects);}
        inline bool empty() const noexcept {return bool(layer->e_number_objects);}
        inline Gobj operator[](size_t index) const noexcept {return Gobj(layer->e_objects+index);}
        inline void close() noexcept {layer->e_state = Closed;}
    };
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    //! @brief The Graphical User Interface.
    //! @details The Gui is a wrapper for the cream's native t_ebox.
    //! @details With the default constructor, the Gui won't be initialized. A valid Gui
    //! @details should be retrieved from a Patch. The GUI has some kind of smart pointer
    //! @details behavior so when no Patch internally in pd the Object is no more valid.
    class Gui : public Object
    {
    private:
        std::array<float, 4> m_background_color;
        std::array<float, 4> m_border_color;
        int          m_border_size;
        int          m_corner_roundness;
        
    public:
        
        //! @brief The constructor for an empty Gui.
        //! @details Creates a Gui that can be used as an empty reference inside
        //! @details another class.
        Gui() noexcept;
        
        //! @brief The constructor for a new Gui.
        //! @details Creates a new valid Gui. You should never have to use it. Use the
        //! @details Patch to retrieve a Gui.
        Gui(Patch const& patch, t_object* object) noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Gui and increments his counter.
        Gui(Gui const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Gui without incrementing his counter. The
        //! @details Gui Patch will be useless.
        Gui(Gui&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Gui and increments his counter.
        Gui& operator=(Gui const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Object without incrementing his counter. The other
        //! @details Object will be destroyed if needed.
        Gui& operator=(Gui&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Gui() noexcept {};
        
        //! @brief Gets if the Object is valid.
        inline virtual operator bool() const noexcept {return bool(m_internal) && bool(m_internal->object) && bool(m_internal->patch) && eobj_iscicm(m_internal->object) && eobj_isbox(m_internal->object);};
        
        //! @brief Gets the preset name.
        bool hasPresetName() const noexcept;
        
        //! @brief Gets the preset name.
        std::string getPresetName() const noexcept;
        
        //! @brief Gets if the GUI wants the mouse events.
        bool wantMouse() const noexcept;
        
        //! @brief Gets the GUI wants keyboard events.
        bool wantKeyboard() const noexcept;
        
        //! @brief Gets the GUI has a text editor.
        bool hasTextEditor() const noexcept;
        
        //! @brief Gets the width.
        inline int getWidth() const noexcept override {
            return int(reinterpret_cast<t_ebox *>(getObject())->b_rect.width);}
        
        //! @brief Gets the height.
        inline int getHeight() const noexcept override {
            return int(reinterpret_cast<t_ebox *>(getObject())->b_rect.height);}
        
        //! @brief Calls the mouse move method.
        void mouseMove(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse enter method.
        void mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse exist method.
        void mouseExit(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse down method.
        void mouseDown(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse drag method.
        void mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse up method.
        void mouseUp(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse double click method.
        void mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse wheel method.
        void mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept;
        
        //! @brief Calls the text editor key press method.
        void textEditorKeyPress(TextEditor& editor, char c) noexcept;
        
        //! @brief Calls the text editor key filter method.
        void textEditorKeyFilter(TextEditor& editor, int filter) noexcept;
        
        //! @brief Calls the popup method.
        void popup(PopupMenu& menu, int item) noexcept;
        
        //! @brief Calls the key method.
        void keyPressed(const char key, const long mod) noexcept;
        
        //! @brief Calls the key filter method.
        void keyFilter(const char key, const long mod) noexcept;
        
        //! @brief Gets the background color.
        inline std::array<float, 4> getBackgroundColor() const noexcept {return m_background_color;}
        
        //! @brief Gets the border color.
        inline std::array<float, 4> getBorderColor() const noexcept {return m_border_color;}
        
        //! @brief Gets the border size.
        inline int getBorderSize() const noexcept {return m_border_size;}
        
        //! @brief Gets the border size.
        inline int getCornerRoundness() const noexcept {return m_corner_roundness;}
        
        //! @brief Calls the paint method and return a set of object to paint.
        std::vector<Layer> paint() const noexcept;
        
        //! @brief Gets if the Gui has parameters.
        inline int hasParameters() const noexcept {
            return bool(is_valid_symbol(reinterpret_cast<t_ebox *>(getObject())->b_preset_id)) ? bool(reinterpret_cast<t_ebox *>(getObject())->b_nparams) : 0;}
        
        //! @brief Gets the number of parameters.
        inline int getNumberOfParameters() const noexcept {
            return bool(is_valid_symbol(reinterpret_cast<t_ebox *>(getObject())->b_preset_id)) ? int(reinterpret_cast<t_ebox *>(getObject())->b_nparams) : 0;}
        
        //! @brief Gets the parameters.
        std::vector<Parameter> getParameters() const noexcept;
    };
}

#endif
