/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_ENVIRONMENT_HPP
#define Z_PD_ENVIRONMENT_HPP

#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <mutex>
#include <tuple>
#include <iostream>
#include <memory>
#include <cassert>
#include <atomic>
#include <cstring>

namespace pd
{
    class Instance;
    
    // ==================================================================================== //
    //                                      ENVIRONMENT                                     //
    // ==================================================================================== //
    //! @brief A tie.
    //! @details The wrapper for z_tie struct.
    class Tie
    {
    public:
        inline constexpr Tie() : ptr(nullptr) {}
        inline constexpr Tie(Tie const& other) : ptr(other.ptr) {}
        inline Tie& operator=(Tie const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(Tie const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(Tie const& other) const noexcept{return other.ptr == ptr;}
    private:
        inline constexpr Tie(void *_ptr) : ptr(_ptr) {}
        void* ptr;
        friend class Environment;
    };
    
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
        
        //! @brief Creates a new Instance object.
        static Instance createInstance() noexcept;
        
        //! @brief Creates a new Tie object.
        static Tie createTie(std::string const& name) noexcept;
        
        //! @brief Sends a float to Pure Data.
        //! @details You should locks the Instance to ensure thread safety.
        static void send(Tie const& name, float val) noexcept;
        
        static void sendNote(int channel, int pitch, int velocity);
        
        static void sendControlChange(int channel, int controller, int value);
        
        static void sendProgramChange(int channel, int value);
        
        static void sendPitchBend(int channel, int value);
        
        static void sendAfterTouch(int channel, int value);
        
        static void sendPolyAfterTouch(int channel, int pitch, int value);
        
        static void sendMidiByte(int port, int byte);
        
        static void sendSysEx(int port, int byte);
        
        static void sendSysRealtime(int port, int byte);
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
        
        // For Instance
        
        //! @brief Releases an Instance.
        static void free(Instance& instance);
        
        
        std::mutex   m_mutex;
        friend class Instance;
    };
}

#endif // Z_PD_ENVIRONMENT_HPP
