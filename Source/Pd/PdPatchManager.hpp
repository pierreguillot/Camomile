/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_PATCH_MANAGER_HPP
#define Z_PD_PATCH_MANAGER_HPP

#include "PdObject.hpp"

namespace pd
{
    //! @brief A class that manages a patch to clean
    class PatchManager
    {
    public:
        PatchManager();
        virtual ~PatchManager();
        
        class Listener
        {
        public:
            inline constexpr Listener() {}
            inline virtual ~Listener() {}
            virtual void patchChanged() = 0;
        };
        
        void addListener(Listener* listener);
        void removeListener(Listener* listener);
        
        virtual void loadPatch(std::string const& name, std::string const& path) = 0;
        virtual void closePatch() = 0;
        inline const pd::Patch getPatch() const noexcept {return m_patch;}
        inline pd::Patch getPatch() noexcept {return m_patch;}
    protected:
        void notifyListeners();
        pd::Patch   m_patch;
    private:
        
        std::set<Listener*> m_listeners;
        std::mutex          m_mutex;
    };
}

#endif //Z_PD_PATCH_MANAGER_HPP
