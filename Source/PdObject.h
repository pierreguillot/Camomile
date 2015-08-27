/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_OBJECT__
#define __CAMOMILE_PD_OBJECT__

#include "PdPatch.h"

namespace pd
{
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
        struct Internal : public LeakDetector<Internal>
        {
            Patch               patch;
            t_object*           object;
            std::atomic<size_t> counter;
            
            Internal(Patch const& _patch, t_object* _object);
            ~Internal();
        };
        Internal* m_internal;
    public:
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! @details another class.
        Object() noexcept;
        
        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! @details Patch to retrieve an Object.
        Object(Patch const& patch, t_object* object) noexcept;
        
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
        
        //! @brief Gets if the Object is valid.
        inline virtual operator bool() const noexcept {
            return bool(m_internal) && bool(m_internal->object) && bool(m_internal->patch);};
        
        //! @brief Compare two Object objects.
        inline bool operator ==(Object const& other) const noexcept {
            return bool(*this) && bool(other) && other.getObject() == getObject();};
        
        //! @brief Compare two Object objects.
        inline bool operator !=(Object const& other) const noexcept {return !(*this == other);};
        
        //! @brief Checks if the object is Cicm.
        inline bool isCicm() const noexcept {return bool(*this) && bool(eobj_iscicm(m_internal->object));}
        
        //! @brief Checks if the object is GUI.
        inline bool isGui() const noexcept {return isCicm() && bool(eobj_isbox(m_internal->object));}
        
        //! @brief Checks if the object is DSP.
        inline bool isDsp() const noexcept {return isCicm() && bool(eobj_isdsp(m_internal->object));}
        
        //! @brief Gets the Patch that owns the Object.
        inline Patch getPatch() const noexcept {
            return bool(m_internal) ? m_internal->patch : Patch();};
        
        //! @brief Gets the Instance that owns the Object.
        inline Instance getInstance() const noexcept {
            Patch patch(getPatch());
            return bool(patch) ? patch.getInstance() : Instance();};
        
        //! @brief Gets the class name of the object.
        inline virtual std::string getName() const noexcept {
            return (bool(*this)) ? (std::string(eobj_getclassname(getObject())->s_name)) : std::string();}
        
        //! @brief Gets the binding name of the object.
        inline virtual std::string getBindingName() const noexcept {
            return isCicm() ? std::to_string(reinterpret_cast<unsigned long>(getObject())) + std::string("camo") : std::string();}
        
        //! @brief Gets the position.
        inline std::array<int,2> getPosition() const noexcept {return std::array<int,2>({getX(), getY()});}
        
        //! @brief Gets the abscissa.
        inline int getX() const noexcept {return (bool(*this)) ? int(getObject()->te_xpix) : 0;}
        
        //! @brief Gets the ordinate.
        inline int getY() const noexcept {return (bool(*this)) ? int(getObject()->te_ypix) : 0;}
        
        //! @brief Gets the size.
        inline std::array<int,2> getSize() const noexcept {return std::array<int,2>({getWidth(), getHeight()});}
        
        //! @brief Gets the width.
        inline virtual int getWidth() const noexcept {return (bool(*this)) ? int(getObject()->te_width) : 0;}
        
        //! @brief Gets the height.
        inline virtual int getHeight() const noexcept {return 12;}
        
        //! @brief Gets the bounds.
        inline virtual std::array<int,4> getBounds() const noexcept {
            return std::array<int,4>({getX(), getY(), getWidth(), getHeight()});}
        
    protected:
        inline t_eclass* getClass() const noexcept {return (bool(*this)) ? (eobj_getclass(m_internal->object)) : nullptr;}
        inline t_object* getObject() const noexcept {return (bool(*this)) ? m_internal->object : nullptr;}
    };
}

#endif
