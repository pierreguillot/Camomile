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
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    //! @brief The manager for Object objects.
    //! @details The Patch is a wrapper for the pd's native t_canvas.
    //! @details With the default constructor, the Patch won't be initialized. A valid
    //! @details Patch should be created with a Instance and a name. The Patch has some kind
    //! @details of smart pointer behavior so when no Patch uses a t_canvas anymore the
    //! @details t_canvas is deleted.
    class Patch
    {
    private:
        struct Internal : public LeakDetector<Internal>
        {
            Instance            instance;
            t_canvas*           canvas;
            std::atomic<size_t> counter;
            const std::string   name;
            const std::string   path;
        
            Internal(Instance const& _instance, std::string const& _name, std::string const& _path);
            ~Internal();
        };
        Internal* m_internal;
        
    public:
        
        //! @brief The constructor for an empty Patch.
        //! @details Creates an Patch that can be used as an empty reference inside
        //! @details another class.
        Patch() noexcept;
        
        //! @brief The constructor for a new Patch.
        //! @details Creates a new valid Patch.
        Patch(Instance const& instance, std::string const& name, std::string const& path) noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of a Patch and increments his counter.
        Patch(Patch const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of a Patch without incrementing his counter. The
        //! @details other Patch will be useless.
        Patch(Patch&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Patch and increments his counter.
        Patch& operator=(Patch const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Patch without incrementing his counter. The other
        //! @details Patch will be destroyed if needed.
        Patch& operator=(Patch&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Patch will be destroyed if no other copy exists.
        ~Patch() noexcept;
        
        //! @brief Gets if the Patch is valid.
        inline operator bool() const noexcept {
            return bool(m_internal) && bool(m_internal->canvas);};
        
        //! @brief Gets the Instance that owns the Path.
        inline Instance getInstance() const noexcept {
            return bool(m_internal) ? m_internal->instance : Instance();};
        
        //! @brief Gets the objects.
        std::vector<Object> getObjects() const noexcept;
        
        //! @brief Gets the Guis.
        std::vector<Gui> getGuis() const noexcept;
        
        //! @brief Gets the camomile object.
        Gui getCamomile() const noexcept;
        
        //! @brief Gets the file's name.
        inline std::string getName() const {return bool(m_internal) ? m_internal->name : std::string();}
        
        //! @brief Gets the file's path.
        inline std::string getPath() const {return bool(m_internal) ? m_internal->path : std::string();}
    };
}

#endif
