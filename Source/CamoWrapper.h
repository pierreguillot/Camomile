/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__WRAPPER__
#define __CAMOMILE__WRAPPER__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../ThirdParty/Pd/cpp/PdBase.hpp"
#include "../ThirdParty/Cream/c.library.hpp"

namespace camo
{
    //! @brief The camomile counterpart of the t_drawparams.
    //! @details This class is a wrapper for the drawing parameters of the cicm wrapper.
    class DrawParameters
    {
    private:
        //! @brief The background color.
        juce::Colour m_background_color;
        //! @brief The border color.
        juce::Colour m_border_color;
        //! @brief The border size.
        int          m_border_size;
        //! @brief The corner roudness.
        int          m_corner_roundness;
        
    public:
        
        //! @brief The default constructor.
        DrawParameters() noexcept;
        
        //! @brief The attributes constructor.
        DrawParameters(juce::Colour const& bgcolor,
                       juce::Colour const& bdcolor,
                       int bordersize,
                       int cornersize) noexcept;
        
        //! @brief The copy constructor.
        DrawParameters(DrawParameters const& other) noexcept;
        
        //! @brief The copy operator.
        void operator=(DrawParameters const& other) noexcept;
        
        //! @brief Gets the background color.
        inline juce::Colour getBackgroundColor() const noexcept {return m_background_color;}
        
        //! @brief Gets the border color.
        inline juce::Colour getBorderColor() const noexcept {return m_border_color;}
        
        //! @brief Gets the border size.
        inline int getBorderSize() const noexcept {return m_border_size;}
        
        //! @brief Gets the border size.
        inline int getCornerRoundness() const noexcept {return m_corner_roundness;}
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
        
        //! @brief Gets the drawing parameters.
        DrawParameters getDrawParameters() const noexcept;
    };
    
    //! @brief Converts a t_rgba to a juce::Colour object.
    inline static juce::Colour toJuce(t_rgba& rgba)
    {
        return juce::Colour::fromFloatRGBA(rgba.red, rgba.green, rgba.blue, rgba.alpha);
    }
    
    //! @brief Converts a t_edrawparams to DrawParameters object.
    inline static DrawParameters toJuce(t_edrawparams& param)
    {
        return DrawParameters(toJuce(param.d_boxfillcolor),
                              toJuce(param.d_bordercolor),
                              std::max(int(param.d_borderthickness), 0),
                              std::max(int(param.d_cornersize), 0));
    }
}

#endif
