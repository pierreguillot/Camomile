/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_OBJECT__
#define __CAMOMILE_PD_OBJECT__

#include "PdAtom.hpp"
#include "PdMisc.hpp"

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
    //! @brief The basic Object.
    //! @details The Object is a wrapper for the pd's native t_object.
    //! With the default constructor, the Object won't be initialized. A valid Object
    //! should be retrieved from a Patch. The Object has some kind of smart pointer
    //! behavior so when no Patch internally in pd the Object is no more valid.
    class Object
    {
    protected:
        class Internal;
        Internal* m_internal;
    public:
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! another class.
        Object() noexcept;
        
        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! Patch to retrieve an Object.
        Object(Patch const& patch, void* object) noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Object(Object const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Object without incrementing his counter. The
        //! Object Patch will be useless.
        Object(Object&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Object& operator=(Object const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Object without incrementing his counter. The other
        //! Object will be destroyed if needed.
        Object& operator=(Object&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Object() noexcept;
        
        //! @brief Gets if the Object is valid.
        bool isValid() const noexcept;
        
        //! @brief The class name of the Object.
        std::string getClassName() const;
    };
    
    class Slider : public Object
    {
    public:
        
        //! @brief The constructor for an empty Slider.
        //! @details Creates an Object that can be used as an empty reference inside
        //! @details another class.
        Slider();
        
        //! @brief The constructor for a new Slider.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! @details Patch to retrieve an Object.
        Slider(Patch const& patch, void* object);
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Slider and increments his counter.
        Slider(Slider const& other);
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Slider without incrementing his counter. The
        //! @details Object Patch will be useless.
        Slider(Slider&& other);
        
        //! @brief The destructor.
        //! @details The Slider will be destroyed if no other copy exists.
        virtual ~Slider() noexcept;
        
        std::string getName() const;
        
        std::string getLabel() const;
        
        void* getBindingPtr() const;
        
        float getMinimum() const noexcept;
        
        float getMaximum() const noexcept;
        
        float getValue() const noexcept;
        
        std::array<float, 4> getBounds() const noexcept;
        
        std::array<float, 2> getLabelPosition() const noexcept;
    };
    
    
}

#endif
