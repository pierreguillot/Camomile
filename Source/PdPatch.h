/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_PATCHER__
#define __CAMOMILE_PD_PATCHER__

#include "PdInstance.h"

namespace pd
{
    class Object;
    class Gui;
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    class Patch
    {
    private:
        struct Internal
        {
            Instance            instance;
            t_canvas*           canvas;
            std::atomic<size_t> counter;
            const std::string   name;
            const std::string   path;
        };
        Internal* m_internal;
        
    public:
        Patch();
        Patch(Patch const& other) : m_internal(other.m_internal) {m_internal->counter++;}
        Patch(Instance const& instance, std::string const& name, std::string const& path);
        ~Patch();
        
        //! @brief Gets the instance.
        inline Instance getInstance() const noexcept {return m_internal->instance;};
        
        //! @brief Gets the objects.
        std::vector<Object> getObjects() const noexcept;
        
        //! @brief Gets the Guis.
        std::vector<Gui> getGuis() const noexcept;
        
        //! @brief Gets the camomile object.
        Gui getCamomile() const noexcept;
        
        //! @brief Gets the file's name.
        inline std::string getName() const {return m_internal->name;}
        
        //! @brief Gets the file's path.
        inline std::string getPath() const {return m_internal->path;}
    };
}

#endif
