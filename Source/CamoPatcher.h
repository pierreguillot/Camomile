/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__PATCHER__
#define __CAMOMILE__PATCHER__

#include "CamoWrapper.h"

namespace camo
{
    /*
    //! @brief The camomille counterpart of the pd::Patch.
    //! @details This class is a wrapper for the pd::Patch that owns a camomile object.
    class Patcher
    {
    private:
        //! @brief The camomile object.
        Object    m_camomile;
        //! @brief The pd::Patch
        pd::Patch m_patch;
    public:
        
        //! @brief The default constructor.
        Patcher() noexcept;
        
        //! @brief The attribute copy constructor.
        Patcher(pd::Patch const& other) noexcept;
        
        //! @brief The copy constructor.
        Patcher(Patcher const& other) noexcept;
        
        //! @brief The attribute copy operator.
        void operator=(pd::Patch const& other) noexcept;
        
        //! @brief The copy operator.
        void operator=(Patcher const& other) noexcept;
        
        //! @brief The bool operator.
        inline operator bool() const noexcept {return m_patch.isValid() && bool(m_camomile);}
        
        //! @brief The pd::Patch operator.
        inline operator pd::Patch() const noexcept {return m_patch;}
        
        //! @brief The pd::Patch operator.
        inline operator pd::Patch&() noexcept {return m_patch;}
        
        //! @brief Gets if the path is open.
        inline bool isOpen() const noexcept {return m_patch.isValid();}
        
        //! @brief Gets the camomile controller.
        inline Object getCamomile() const noexcept {return m_camomile;};
        
        //! @brief Gets objects.
        std::vector<Object> getObjects() const noexcept;
        
        //! @brief Gets the file's name.
        inline std::string getFileName() const {return m_patch.filename();}
        
        //! @brief Gets the file's path.
        inline std::string getFilePath() const {return m_patch.path();}
        
        //! @brief Gets binding name
        inline std::string getName() const {return m_patch.dollarZeroStr() + "-camomile";}
        
    };*/
}

#endif
