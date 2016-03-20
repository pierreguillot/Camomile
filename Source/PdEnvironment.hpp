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
    class Environment;
    
    // ==================================================================================== //
    //                                      TIE                                             //
    // ==================================================================================== //
    //! @brief A tie.
    //! @details The wrapper for z_tie struct.
    class Tie
    {
    public:
        inline constexpr Tie(void *_ptr) : ptr(_ptr) {}
        inline constexpr Tie() : ptr(nullptr) {}
        inline constexpr Tie(Tie const& other) : ptr(other.ptr) {}
        inline Tie& operator=(Tie const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(Tie const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(Tie const& other) const noexcept{return other.ptr == ptr;}
        inline void const* get() const noexcept{return ptr;}
    private:
        void* ptr;
    };
    
    // ==================================================================================== //
    //                                      SYMBOL                                          //
    // ==================================================================================== //
    //! @brief A symbol.
    //! @details The wrapper for z_symbol struct.
    class Symbol
    {
    public:
        inline constexpr Symbol(void *_ptr) : ptr(_ptr) {}
        inline constexpr Symbol() : ptr(nullptr) {}
        inline constexpr Symbol(Symbol const& other) : ptr(other.ptr) {}
        inline Symbol& operator=(Symbol const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(Symbol const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(Symbol const& other) const noexcept{return other.ptr == ptr;}
        inline void const* get() const noexcept{return ptr;}
    private:
        void* ptr;
    };
    
    // ==================================================================================== //
    //                                      SYMBOL                                          //
    // ==================================================================================== //
    //! @brief A gpointer.
    //! @details The wrapper for z_gpointer struct.
    class Gpointer
    {
    public:
        inline constexpr Gpointer(void *_ptr) : ptr(_ptr) {}
        inline constexpr Gpointer() : ptr(nullptr) {}
        inline constexpr Gpointer(Gpointer const& other) : ptr(other.ptr) {}
        inline Gpointer& operator=(Gpointer const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(Gpointer const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(Gpointer const& other) const noexcept{return other.ptr == ptr;}
        inline void const* get() const noexcept{return ptr;}
    private:
        void* ptr;
    };
    
    // ==================================================================================== //
    //                                      LIST                                          //
    // ==================================================================================== //
    //! @brief A gpointer.
    //! @details The wrapper for z_gpointer struct.
    class List
    {
    public:
        inline constexpr List(void *_ptr) : ptr(_ptr) {}
        inline constexpr List() : ptr(nullptr) {}
        inline constexpr List(List const& other) : ptr(other.ptr) {}
        inline List& operator=(List const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(List const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(List const& other) const noexcept{return other.ptr == ptr;}
        inline void const* get() const noexcept{return ptr;}
    private:
        void* ptr;
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
        
        //! @brief Creates a new Tie object.
        static Tie createTie(std::string const& name) noexcept;
        
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
