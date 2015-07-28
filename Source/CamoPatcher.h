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
    //! @brief The camomille counterpart of the pd::Patch.
    //! @details This class is a wrapper for the pd::Patch that owns a camomile object.
    class Patcher : public pd::Patch
    {
    private:
        //! @brief The camomile object.
        Object m_camomile;
    public:
        
        Patcher() noexcept {};
        Patcher(const std::string& filename, const std::string& path) {};
        Patcher(void* handle, int dollarZero, const std::string& filename, const std::string& path) {};
        Patcher(pd::Patch const& other) {};
        Patcher(Patcher const& other) {};
        void operator=(Patch const& from) {};
        void operator=(Patcher const& from) {};
        
        bool isPlugin() const noexcept {return true;};
    };
}

#endif
