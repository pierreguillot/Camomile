/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_GUI__
#define __CAMOMILE_PD_GUI__

#include "PdPatch.hpp"

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    //! @brief The Pure Data GUI.
    //! @details The Instance is a wrapper for the Pure Data's native GUI.
    //! With the default constructor, the Gui won't be initialized. A valid
    //! Gui should be created via a Patch. The Gui should be used as tempory object,
    //! because it locks the Patch.
    class Gui
    {
    public:
        
        enum class Type : size_t
        {
            Invalid          = 0,
            HorizontalSlider = 1,
            VerticalSlider   = 2,
            Toggle           = 3,
            Number           = 4,
            HorizontalRadio  = 5,
            VerticalRadio    = 6
        };
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! another class.
        Gui() noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Gui(Gui const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Object without incrementing his counter. The
        //! Object Patch will be useless.
        Gui(Gui&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Gui& operator=(Gui const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Object without incrementing his counter. The other
        //! Object will be destroyed if needed.
        Gui& operator=(Gui&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Gui() noexcept;
        
        //! @brief Gets if the Object is valid.
        bool isValid() const noexcept;
        
        //! @brief The class name of the Object.
        Type getType() const noexcept;
        
        //! @brief The Name of the Object.
        std::string getName() const;
        
        std::string getLabel() const;
        
        BindingName getBindingName() const;
        
        bool isParameter() const noexcept;
        
        float getMinimum() const noexcept;
        
        float getMaximum() const noexcept;
        
        float getValue() const noexcept;
        
        size_t getNumberOfSteps() const noexcept;
        
        std::array<float, 4> getBounds() const noexcept;
        
        std::array<float, 2> getLabelPosition() const noexcept;
        
    private:

        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! Patch to retrieve an Object.
        Gui(Patch const& patch, Type type, void* ptr) noexcept;
        
        void*       m_ptr;
        Type        m_type;
        Patch       m_patch;
        friend class Patch;
    };
    
    
    //! @brief The Pure Data Comment.
    //! @details The Instance is a wrapper for the Pure Data's native comment.
    //! With the default constructor, theCommentGui won't be initialized. A valid
    //! Comment should be created via a Patch. The Gui should be used as tempory object,
    //! because it locks the Patch.
    class Comment
    {
    public:

        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! another class.
        Comment() noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Comment(Comment const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Object without incrementing his counter. The
        //! Object Patch will be useless.
        Comment(Comment&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Comment& operator=(Comment const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Object without incrementing his counter. The other
        //! Object will be destroyed if needed.
        Comment& operator=(Comment&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Comment() noexcept;
        
        //! @brief Gets if the Object is valid.
        bool isValid() const noexcept;
        
        //! @brief The Text of the Object.
        std::string getText() const;
        
        float getX() const noexcept;
        
        float getY() const noexcept;
        
        float getWidth() const noexcept;
        
    private:
        
        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! Patch to retrieve an Object.
        Comment(Patch const& patch, void* ptr) noexcept;
        
        void*       m_ptr;
        Patch       m_patch;
        friend class Patch;
    };
    
}

#endif
