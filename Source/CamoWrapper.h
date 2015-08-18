/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__WRAPPER__
#define __CAMOMILE__WRAPPER__

#include "../JuceLibraryCode/JuceHeader.h"
//#include "../ThirdParty/Pd/cpp/PdBase.hpp"
//#include "../ThirdParty/Cream/c.library.hpp"

namespace camo
{
    /*
    class Gobj
    {
        juce::Path      m_path;         /*!< The path. *
        juce::Colour    m_color;        /*!< The color. *
        bool            m_fill;         /*!< If the path should be paint or stroke. *
        float           m_width;        /*!< The line width. *
        juce::Font      m_font;         /*!< The font of the graphical object. *
        t_symbol*       e_anchor;       /*!< The anchor of the graphical object. *
        t_symbol*       e_justify;      /*!< The justification of the graphical object. *
        t_symbol*       e_text;         /*!< The text of the graphical object. *
    };
    
    //! @brief The camomile counterpart of the t_ebox.
    //! @details This class is a wrapper for GUI object of the cicm wrapper.
    class Object
    {
    private:
        //! @brief The t_ebox pointer.
        void* m_handle;
        
    public:
        
        //! @brief The default constructor.
        Object() noexcept;
        
        //! @brief The attribute constructor.
        Object(void* handle) noexcept;
        
        //! @brief The copy constructor.
        Object(Object const& other) noexcept;
        
        //! @brief The copy operator.
        void operator=(Object const& other) noexcept;
        
        //! @brief The bool operator.
        inline operator bool() const noexcept {return bool(m_handle);}
        
        //! @brief The void* comparaison.
        inline bool operator==(void* handler) const noexcept {return m_handle == handler;}
        
        //! @brief The void* comparaison.
        inline bool operator!=(void* handler) const noexcept {return m_handle != handler;}
        
        //! @brief Gets the position.
        Point<int> getPosition() const noexcept;
        
        //! @brief Gets the abscissa.
        int getX() const noexcept;
        
        //! @brief Gets the ordinate.
        int getY() const noexcept;
        
        //! @brief Gets the size.
        Point<int> getSize() const noexcept;
        
        //! @brief Gets the width.
        int getWidth() const noexcept;
        
        //! @brief Gets the height.
        int getHeight() const noexcept;
        
        //! @brief Gets the bounds.
        Rectangle<int> getBounds() const noexcept;
        
        //! @brief Gets the box wants mouse events.
        bool wantMouse() const noexcept;
        
        //! @brief Gets the box wants keyboard events.
        bool wantKeyboard() const noexcept;
        
        //! @brief Gets the drawing parameters.
        DrawParameters getDrawParameters() const noexcept;
        
        //! @brief Calls the paint method.
        //std::tuple<int, t_elayer*> paint() const noexcept;
        
        void mouseMove(const MouseEvent& event) const noexcept;
        
        void mouseEnter(const MouseEvent& event) const noexcept;
        
        void mouseExit(const MouseEvent& event) const noexcept;
        
        void mouseDown(const MouseEvent& event) const noexcept;
        
        void mouseDrag(const MouseEvent& event) const noexcept;
        
        void mouseUp(const MouseEvent& event) const noexcept;
        
        void mouseDoubleClick(const MouseEvent& event) const noexcept;
        
        void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) const noexcept;

    };
    
    //! @brief Converts a t_rgba to a juce::Colour object.
    /*
    inline static juce::Colour toJuce(t_rgba const& rgba)
    {
        return juce::Colour::fromFloatRGBA(rgba.red, rgba.green, rgba.blue, rgba.alpha);
    }*/
    
    //! @brief Converts a t_edrawparams to a DrawParameters object.
    /*
    inline static DrawParameters toJuce(t_edrawparams const& param)
    {
        return DrawParameters(toJuce(param.d_boxfillcolor),
                              toJuce(param.d_bordercolor),
                              std::max(int(param.d_borderthickness), 0),
                              std::max(int(param.d_cornersize), 0));
    }*/
    
    //! @brief Converts a set of point to a juce::Path.
    /*
    inline static juce::Path toJuce(int size, t_pt* points)
    {
        juce::Path path;
        for(int i = 0; i < size; i++)
        {
            if(points[i].x == E_PATH_MOVE && i < size - 1)
            {
                path.startNewSubPath(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_LINE && i < size - 1)
            {
                path.lineTo(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_CURVE && i < size - 3)
            {
                path.cubicTo(points[i+1].x, points[i+1].y,
                             points[i+2].x, points[i+2].y,
                             points[i+3].x, points[i+3].y);
                i += 3;
            }
            else if(points[i].x == E_PATH_CLOSE)
            {
                path.closeSubPath();
            }
        }
       
        return path;
    }*/
}

#endif
