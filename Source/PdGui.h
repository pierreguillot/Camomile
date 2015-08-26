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
        inline float fontSize() const noexcept {return obj->e_font.c_size;}
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
    
    class Gui : public Object
    {
        friend class Patch;
    private:
        //! @brief The background color.
        std::array<float, 4> m_background_color;
        //! @brief The border color.
        std::array<float, 4> m_border_color;
        //! @brief The border size.
        int          m_border_size;
        //! @brief The corner roudness.
        int          m_corner_roundness;
        
    public:
        
        Gui() {};
        //! @brief The Contructor.
        Gui(void* handle);
        
        //! @brief The destructor.
        inline virtual ~Gui() {};
        
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
    };
}

#endif
