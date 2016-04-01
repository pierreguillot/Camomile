/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_PATCH_HPP
#define Z_PD_PATCH_HPP

#include "PdInstance.hpp"

namespace pd
{
    class Gui;
    class Object;
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    //! @brief The Pure Data patch.
    //! @details The Instance is a wrapper for the Pure Data's native patch.
    //! With the default constructor, the Patch won't be initialized. A valid
    //! Patch should be created via an Instance. The Patch has some kind of smart
    //! pointer behavior so when an Patch object is no more useful the object is deleted.
    class Patch
    {
    public:
        
        //! @brief The constructor for a new Patch.
        //! @details Creates a new valid Patch.
        Patch(Instance& instance, std::string const& name, std::string const& path) noexcept;
        
        //! @brief The constructor for an empty Patch.
        //! @details Creates an Patch that can be used as an empty reference inside
        //! another class.
        Patch() noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of a Patch and increments his counter.
        Patch(Patch const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of a Patch without incrementing his counter. The
        //! other Patch will be useless.
        Patch(Patch&& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Patch and increments his counter.
        Patch& operator=(Patch const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Patch without incrementing his counter. The other
        //! Patch will be destroyed if needed.
        Patch& operator=(Patch&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Patch will be destroyed if no other copy exists.
        ~Patch() noexcept;
        
        //! @brief Gets if the Patch is valid.
        bool isValid() const noexcept;
        
        //! @brief Gets the Instance that owns the Patch.
        Instance getInstance() const noexcept;
        
        //! @brief Gets the file's name.
        std::string getName() const;
        
        //! @brief Gets the file's path.
        std::string getPath() const;
        
        //! @brief Gets the dollar zero of the Patch.
        int getDollarZero();
        
        //! @brief Gets the Patch position.
        std::array<int, 2> getPosition() const noexcept;
        
        //! @brief Gets the Patch size.
        std::array<int, 2> getSize() const noexcept;
        
        //! @brief Gets the Gui objects from the patch.
        std::vector<Gui> getGuis() const noexcept;
        
        //! @brief Gets the Comment objects from the patch.
        std::vector<Object> getComments() const noexcept;
    private:
        void release() noexcept;
        void*                   m_ptr;
        std::atomic<size_t>*    m_count;
        Instance                m_instance;
        
        friend class Object;
    };
}

#endif // Z_PD_PATCH_HPP
