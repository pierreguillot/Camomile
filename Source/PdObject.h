/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_OBJECT__
#define __CAMOMILE_PD_OBJECT__

#include "PdAtom.h"

namespace pd
{
    // ==================================================================================== //
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
    class Object
    {
        friend class Patch;
    protected:
        void* m_handle;
        Object(void* handle);
    public:
        
        //! @brief The destructor.
        inline virtual ~Object() noexcept {}
        
        //! @brief Checks if the object is CICM.
        inline virtual bool isCicm() const noexcept {return bool(eobj_iscicm(m_handle));}
        
        //! @brief Checks if the object is GUI.
        inline virtual bool isGui() const noexcept {return isCicm() && bool(eobj_isbox(m_handle));}
        
        //! @brief Checks if the object is DSP.
        inline virtual bool isDsp() const noexcept {return isCicm() && bool(eobj_isdsp(m_handle));}
        
        //! @brief Gets the class name of the object.
        inline virtual std::string getName() const noexcept {return std::string(eobj_getclassname(m_handle)->s_name);}
        
        //! @brief Gets the class name of the object.
        inline virtual std::string getBindingName() const noexcept {
            return std::to_string(reinterpret_cast<unsigned long>(m_handle)) + std::string("camo");}
        
        //! @brief Gets the position.
        inline std::array<int,2> getPosition() const noexcept {
            return std::array<int,2>({getX(), getY()});}
        
        //! @brief Gets the abscissa.
        inline int getX() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_xpix);}
        
        //! @brief Gets the ordinate.
        inline int getY() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_ypix);}
        
        //! @brief Gets the size.
        inline virtual std::array<int,2> getSize() const noexcept {
            return std::array<int,2>({getWidth(), getHeight()});}
        
        //! @brief Gets the width.
        inline virtual int getWidth() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_width);}
        
        //! @brief Gets the height.
        inline virtual int getHeight() const noexcept {return 0;}
        
        //! @brief Gets the bounds.
        inline virtual std::array<int,4> getBounds() const noexcept {
            return std::array<int,4>({getX(), getY(), getWidth(), getHeight()});}
        
    protected:
        
        inline t_eclass* getClass() const noexcept {return (bool(m_handle)) ? (eobj_getclass(m_handle)) : nullptr;}
        
        inline void* getHandle() const noexcept {return m_handle;}
    };
}

#endif
