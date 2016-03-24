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
#include <cmath>

namespace pd
{
    class Smuggler;
    class List;
    
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
        inline constexpr operator bool() const noexcept {return bool(ptr);}
        std::string getName() const;
    
    private:
        void* ptr;
        friend class Smuggler;
        friend class List;
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
        inline constexpr operator bool() const noexcept {return bool(ptr);}
        std::string getName() const;
        
    private:
        void* ptr;
        friend class Smuggler;
        friend class List;
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
        friend class List;
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
        enum class Type
        {
            Nothing,
            Float,
            Symbol,
            Gpointer
        };
        List();
        List(size_t size);
        List(List const& other);
        List(List&& other);
        ~List();
        List& operator=(List const& other);
        List& operator=(List&& other);
        void resize(size_t size);
        size_t getSize() const noexcept;
        Type getType(size_t index) const;
        float getFloat(size_t index) const;
        Symbol getSymbol(size_t index) const;
        Gpointer getGpointer(size_t index) const;
        void setFloat(size_t index, float value);
        void setSymbol(size_t index, Symbol& symbol);
        void setGpointer(size_t index, Gpointer& pointer);
    private:
        void* ptr;
        friend class Smuggler;
        inline void const* get() const noexcept{return ptr;}
        inline List(void *_ptr) : ptr(_ptr) {}
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
        
        inline static constexpr void const* getList(List const& list) noexcept {return list.ptr;}
        inline static List createList(void *ptr) noexcept {return List(ptr);}
    };
}

#endif // Z_PD_TYPES_HPP
