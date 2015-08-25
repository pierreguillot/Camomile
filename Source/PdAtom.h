/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_TYPES__
#define __CAMOMILE_PD_TYPES__

#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <mutex>
#include <tuple>
#include <iostream>
#include <memory>

#include "../ThirdParty/Cream/c.library.hpp"

namespace pd
{
    // ==================================================================================== //
    //                                      ATOM                                            //
    // ==================================================================================== //
    
    class Atom
    {
    private:
        enum Type
        {
            Undefined = 0,
            Float     = 1,
            Symbol    = 2
        };
        std::string m_symbol;
        float       m_float;
        Type        m_type;
    public:
        
        inline Atom() noexcept : m_type(Undefined) {}
        inline Atom(Atom const& other) noexcept : m_symbol(other.m_symbol), m_float(other.m_float), m_type(other.m_type) {}
        inline Atom(float f) noexcept : m_symbol(), m_float(f), m_type(Float) {}
        inline Atom(std::string const& s) noexcept : m_symbol(s), m_float(), m_type(Symbol) {}
        inline Atom(Atom&& other) noexcept : m_symbol(), m_float(other.m_float), m_type(other.m_type) {m_symbol.swap(other.m_symbol);}
        inline Atom(std::string&& s) noexcept : m_symbol(), m_float(), m_type(Symbol) {m_symbol.swap(s);}
        
        inline Atom& operator=(Atom const& other) noexcept {m_symbol = other.m_symbol; m_float = other.m_float; m_type = other.m_type; return *this;}
        inline Atom& operator=(float f) noexcept {m_float = f; m_type = Float; return *this;}
        inline Atom& operator=(std::string const& s) noexcept {m_symbol = s; m_type = Symbol; return *this;}
        inline Atom& operator=(Atom&& other) noexcept {m_symbol.swap(other.m_symbol); m_float = other.m_float; m_type = other.m_type; return *this;}
        inline Atom& operator=(std::string&& s) noexcept {m_symbol.swap(s); m_type = Symbol; return *this;}
        
        inline operator std::string() const noexcept {return m_symbol;}
        inline operator float() const noexcept {return m_float;}
        
        inline bool operator==(std::string const& s) const noexcept {return isSymbol() && m_symbol == s;}
        inline bool operator==(float f) const noexcept {return isFloat() && m_float == f;}
        inline bool operator==(Atom const& other) const noexcept {
            return m_type == other.m_type && (isFloat()) ? (m_float == other.m_float) : (m_symbol == other.m_symbol);}
        
        inline bool isUndefined() const noexcept {return m_type == Undefined;}
        inline bool isFloat() const noexcept {return m_type == Float;}
        inline bool isSymbol() const noexcept {return m_type == Symbol;}
    };
}

#endif
