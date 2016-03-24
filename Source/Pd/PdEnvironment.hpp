/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_ENVIRONMENT_HPP
#define Z_PD_ENVIRONMENT_HPP

#include "PdTypes.hpp"

namespace pd
{
    // ==================================================================================== //
    //                                      ENVIRONMENT                                     //
    // ==================================================================================== //
    
    //! @brief Pure Data.
    //! @details The wrapper for Pure Data environment.
    class Environment
    {
    public:        
        //! @brief Adds a path the global search path.
        static std::string getPdVersion();
        
        //! @brief Adds a path the global search path.
        static void addToSearchPath(std::string const& path) noexcept;
        
        //! @brief Clears all the paths of the global search path.
        static void clearSearchPath() noexcept;
        
    private:
        
        //! @brief The Pure Data contructor.
        Environment() noexcept;
        
        //! @brief The Pure Data destructor.
        ~Environment() noexcept;
        
        //! @brief Gets the singleton of Pure Data.
        static Environment& get() noexcept;
        
        //! @brief Locks Pure Data.
        static void lock() noexcept;
        
        //! @brief Unlocks Pure Data.
        static void unlock() noexcept;
        
        std::mutex   m_mutex;
        friend class Instance;
    };
}

#endif // Z_PD_ENVIRONMENT_HPP
