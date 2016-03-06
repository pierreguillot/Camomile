/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_PATCH__
#define __CAMOMILE_PD_PATCH__

#include "PdObject.hpp"

namespace pd
{
    class Instance;
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
        bool isValid() const noexcept;
        
        //! @brief Gets the Instance that owns the Path.
        Instance getInstance() const noexcept;
        
        //! @brief Gets the file's name.
        std::string getName() const;
        
        //! @brief Gets the file's path.
        std::string getPath() const;
        
        //! @brief Gets the Path size.
        std::array<float, 2> getSize() const noexcept;
        
        //! @brief Gets the Slider objects from the patch.
        std::vector<Slider> getSliders() const noexcept;
        
        //! @brief Gets the Slider objects from the patch.
        void* getPtr() const noexcept;
        
    private:
        class Internal;
        Internal* m_internal;
    };
}

#endif
