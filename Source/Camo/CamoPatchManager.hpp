/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_PATCH_MANAGER_INCLUDE_HPP
#define CAMO_PATCH_MANAGER_INCLUDE_HPP

#include <string>
#include <cstdlib>
#include "../ThirdParty/zpd/xpd/xpd.hpp"

// ==================================================================================== //
//                                  CAMOMILE PARAMETER                                  //
// ==================================================================================== //

namespace camo
{
    class PatchManager
    {
        virtual ~PatchManager() {}
        void load(std::string const& name, std::string const& path);
        void close();
        inline xpd::patch const get() const noexcept {return m_patch;}
        
        class Listener
        {
        public:
            virtual ~Listener() noexcept {}
            virtual void patchChanged() = 0;
        };
        
    private:
        xpd::patch m_patch;
    };
}


#endif // CAMO_PATCH_MANAGER_INCLUDE_HPP
