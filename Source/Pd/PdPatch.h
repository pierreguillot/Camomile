/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "PdInstance.h"

namespace pd
{
    class Gui;
    class Object;
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    class Patch
    {
    public:
        Patch() noexcept;
        Patch(Patch const& other) noexcept;
        Patch& operator=(Patch const& other) noexcept;
        ~Patch() noexcept;
        
        int getDollarZero();
        bool isGraph() const noexcept;
        std::array<int, 4> getBounds() const noexcept;
        std::vector<Gui> getGuis() const noexcept;
    private:
        Patch(void* ptr, Instance* instance) noexcept;
        void*  m_ptr;
        Instance* m_instance;
        friend class Instance;
        friend class Object;
        friend class Gui;
    };
}
