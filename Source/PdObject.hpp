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
    //! @details With the default constructor, the Object won't be initialized. A valid Object
    //! @details should be retrieved from a Patch. The Object has some kind of smart pointer
    //! @details behavior so when no Patch internally in pd the Object is no more valid.
    class Object
    {
    protected:
        class Internal;
        Internal* m_internal;
    public:
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! @details another class.
        Object() noexcept;
        
        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! @details Patch to retrieve an Object.
        Object(Patch const& patch, void* object) noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Object(Object const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Object without incrementing his counter. The
        //! @details Object Patch will be useless.
        Object(Object&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Object& operator=(Object const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Object without incrementing his counter. The other
        //! @details Object will be destroyed if needed.
        Object& operator=(Object&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Object() noexcept;
        
        /*
        //! @brief Gets if the Object is valid.
        virtual bool isValid() const noexcept;
        
        //! @brief Compare two Object objects.
        inline bool operator ==(Object const& other) const noexcept;
        
        //! @brief Compare two Object objects.
        inline bool operator !=(Object const& other) const noexcept;
        
        //! @brief Gets the Patch that owns the Object.
        inline Patch getPatch() const noexcept;
        
        //! @brief Gets the Instance that owns the Object.
        inline Instance getInstance() const noexcept;
        
        //! @brief Gets the class name of the object.
        inline std::string getClassName() const noexcept;
         */
    };
}

#endif
