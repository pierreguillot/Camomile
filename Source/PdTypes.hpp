/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_TYPES_HPP
#define Z_PD_TYPES_HPP

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
    class Smuggler;
    
    // ==================================================================================== //
    //                                      TIE                                             //
    // ==================================================================================== //
    //! @brief A tie is used as a connection between the interface and Pure Data.
    //! @details The wrapper for z_tie struct.
    class Tie
    {
    public:
        Tie(std::string const& name) noexcept ;
        Tie(char const* name) noexcept ;
        inline constexpr Tie() : ptr(nullptr) {}
        inline constexpr Tie(Tie const& other) : ptr(other.ptr) {}
        inline Tie& operator=(Tie const& other) {ptr = other.ptr; return *this;}
        Tie& operator=(std::string const& name);
        Tie& operator=(char const* name);
        inline constexpr bool operator!=(Tie const& other)const noexcept {return other.ptr != ptr;}
        inline constexpr bool operator==(Tie const& other) const noexcept {return other.ptr == ptr;}
        std::string getName() const;
    
    private:
        void* ptr;
        friend class Smuggler;
        inline constexpr void const* get() const noexcept{return ptr;}
        inline constexpr Tie(void *_ptr) : ptr(_ptr) {}
    };
    
    
    // ==================================================================================== //
    //                                      SYMBOL                                          //
    // ==================================================================================== //
    //! @brief A symbol is used as for fast comparaison of string with Pure Data.
    //! @details The wrapper for z_symbol struct.
    class Symbol
    {
    public:
        Symbol(std::string const& name) noexcept ;
        Symbol(char const* name) noexcept ;
        inline constexpr Symbol() : ptr(nullptr) {}
        inline constexpr Symbol(Symbol const& other) : ptr(other.ptr) {}
        inline Symbol& operator=(Symbol const& other) {ptr = other.ptr; return *this;}
        Symbol& operator=(std::string const& name);
        Symbol& operator=(char const* name);
        inline constexpr bool operator!=(Symbol const& other)const noexcept {return other.ptr != ptr;}
        inline constexpr bool operator==(Symbol const& other) const noexcept{return other.ptr == ptr;}
        std::string getName() const;
        
    private:
        void* ptr;
        friend class Smuggler;
        inline constexpr void const* get() const noexcept{return ptr;}
        inline constexpr Symbol(void *_ptr) : ptr(_ptr) {}
    };
    
    
    // ==================================================================================== //
    //                                      GPOINTER                                        //
    // ==================================================================================== //
    //! @brief A gpointer.
    //! @details The wrapper for z_gpointer struct.
    class Gpointer
    {
    public:
        inline constexpr Gpointer() : ptr(nullptr) {}
        inline constexpr Gpointer(Gpointer const& other) : ptr(other.ptr) {}
        inline Gpointer& operator=(Gpointer const& other) {ptr = other.ptr; return *this;}
        inline bool operator!=(Gpointer const& other)const noexcept {return other.ptr != ptr;}
        inline bool operator==(Gpointer const& other) const noexcept{return other.ptr == ptr;}
        
    private:
        void* ptr;
        friend class Smuggler;
        inline constexpr void const* get() const noexcept{return ptr;}
        inline constexpr Gpointer(void *_ptr) : ptr(_ptr) {}
    };
    
    // ==================================================================================== //
    //                                      LIST                                          //
    // ==================================================================================== //
    //! @brief A list.
    //! @details The wrapper for z_list struct.
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
    
    
    //! @brief The smuggler is optimized for internal use.
    //! @details The class doesn't break the efficiency of creation of some type, but you
    //! should use it if and only if you know what you do.
    class Smuggler
    {
    public:
        ~Smuggler() noexcept {}
    protected:
        inline static constexpr void const* getTie(Tie const& tie) noexcept {return tie.ptr;}
        inline static constexpr Tie createTie(void *ptr) noexcept {return Tie(ptr);}
        inline static constexpr void const* getSymbol(Symbol const& symbol) noexcept {return symbol.ptr;}
        inline static constexpr Symbol createSymbol(void *ptr) noexcept {return Symbol(ptr);}
        inline static constexpr void const* getGpointer(Gpointer const& gpointer) noexcept {return gpointer.ptr;}
        inline static constexpr Gpointer createGpointer(void *ptr) noexcept {return Gpointer(ptr);}
    };
}

#endif // Z_PD_TYPES_HPP
