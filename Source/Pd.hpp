/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD__
#define __CAMOMILE_PD__

#include "PdGui.hpp"

namespace pd
{
    class Instance;
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    //! @brief Pure Data.
    //! @details The wrapper for Pure Data environment.
    class Pd
    {
    public:
        //! @brief Gets the current version of the program.
        static std::string getVersion() {return std::string("0.0.3");}
        
        //! @brief Adds a path the global search path.
        static std::string getPdVersion();
        
        //! @brief Adds a path the global search path.
        static void addToSearchPath(std::string const& path) noexcept;
        
        //! @brief Clears all the paths of the global search path.
        static void clearSearchPath() noexcept;
        
        //! @brief Sets the text of the console.
        static void clearConsole() noexcept;
        
        //! @brief Sets the text of the console.
        static void setConsole(std::string const& text) noexcept;
        
        //! @brief Sets the text of the console.
        static void addConsole(std::string const& text) noexcept;
        
        //! @brief Retrieves the text of the console.
        static std::string getConsole() noexcept;
        
        //! @brief Creates a new Instance object.
        static Instance createInstance() noexcept;
        
    private:
        
        //! @brief The Pure Data contructor.
        Pd() noexcept;
        
        //! @brief The Pure Data destructor.
        ~Pd() noexcept {}
        
        //! @brief Gets the singleton of Pure Data.
        static Pd& get() noexcept;
        
        //! @brief Locks Pure Data.
        static void lock() noexcept;
        
        //! @brief Unlocks Pure Data.
        static void unlock() noexcept;
        
        //! @brief Sets the global sample rate.
        static void setSampleRate(const int samplerate) noexcept;
        
        std::mutex                  m_mutex;
        int                         m_sample_rate;
        const int                   m_max_channels = 16;
        std::string                 m_console;
        static void print(const char* s);
        
        friend class Instance;
    };
}

#endif
