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
    class Instance;
    class Patch;
    class Object;
    class Gui;
    class Parameter;
    
    // ==================================================================================== //
    //                                      ATOM                                            //
    // ==================================================================================== //
    
    //! @brief The container for typed messages.
    //! @details The Atom is a wrapper for the pd's native t_atom.
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
        //! @brief The default constructor.
        //! @details Creates an Undefined Atom.
        inline Atom() noexcept : m_type(Undefined) {}
        
        //! @brief The float constructor.
        //! @details Creates an Float Atom.
        inline Atom(float f) noexcept : m_symbol(), m_float(f), m_type(Float) {}
        
        //! @brief The string constructor.
        //! @details Creates an Symbol Atom.
        inline Atom(std::string const& s) noexcept : m_symbol(s), m_float(), m_type(Symbol) {}
        
        //! @brief The copy constructor.
        //! @details Copies the content of another Atom.
        inline Atom(Atom const& other) noexcept : m_symbol(other.m_symbol), m_float(other.m_float), m_type(other.m_type) {}
        
        //! @brief The move constructor.
        //! @details Copies the content of another Atom.
        inline Atom(Atom&& other) noexcept : m_symbol(), m_float(other.m_float), m_type(other.m_type)
        {m_symbol.swap(other.m_symbol);}
        
        //! @brief The string move constructor.
        //! @details Creates an Symbol Atom.
        inline Atom(std::string&& s) noexcept : m_symbol(), m_float(), m_type(Symbol) {m_symbol.swap(s);}
        
        //! @brief The float copy operator.
        //! @details Initializes the Atom with a float.
        inline Atom& operator=(float f) noexcept {m_float = f; m_type = Float; return *this;}
        
        //! @brief The string copy operator.
        //! @details Initializes the Atom with a string.
        inline Atom& operator=(std::string const& s) noexcept {m_symbol = s; m_type = Symbol; return *this;}
        
        //! @brief The copy operator.
        //! @details Initializes the Atom with a another.
        inline Atom& operator=(Atom const& other) noexcept {
            m_symbol = other.m_symbol; m_float = other.m_float; m_type = other.m_type; return *this;}
        
        //! @brief The string move operator.
        //! @details Initializes the Atom with a string.
        inline Atom& operator=(std::string&& s) noexcept {m_symbol.swap(s); m_type = Symbol; return *this;}
        
        //! @brief The move operator.
        //! @details Initializes the Atom with a another.
        inline Atom& operator=(Atom&& other) noexcept {
            m_symbol.swap(other.m_symbol); m_float = other.m_float; m_type = other.m_type; return *this;}
        
        //! @brief The float operator.
        //! @details Returns the float content of the Atom.
        inline operator float() const noexcept {return m_float;}
        
        //! @brief The string operator.
        //! @details Returns the string content of the Atom.
        inline operator std::string() const noexcept {return m_symbol;}
        
        //! @brief The float comparaison.
        //! @details Returns true if the Atom is typed Float and if the float values are equals.
        inline bool operator==(const float f) const noexcept {return isFloat() && m_float == f;}
        
        //! @brief The float comparaison.
        //! @details Returns true if the Atom is not typed Float or if the float values are not equals.
        inline bool operator!=(const float f) const noexcept {return !isFloat() || m_float != f;}
        
        //! @brief The string comparaison.
        //! @details Returns true if the Atom is typed Symbol and if the string values are equals.
        inline bool operator==(std::string const& s) const noexcept {return isSymbol() && m_symbol == s;}
        
        //! @brief The string comparaison.
        //! @details Returns true if the Atom is not typed Symbol or if the string values are not equals.
        inline bool operator!=(std::string const& s) const noexcept {return !isSymbol() || m_symbol != s;}
        
        //! @brief The Atom comparaison.
        //! @details Returns true if the Atoms are typed similar and if their values are equals.
        inline bool operator==(Atom const& other) const noexcept {
            return m_type == other.m_type && (isFloat()) ? (m_float == other.m_float) : (m_symbol == other.m_symbol);}
        
        //! @brief The Atom comparaison.
        //! @details Returns true if the Atoms are not typed similar or if their values are not equals.
        inline bool operator!=(Atom const& other) const noexcept {
            return m_type != other.m_type || (isFloat()) ? (m_float != other.m_float) : (m_symbol != other.m_symbol);}
        
        //! @brief Gets if the Atom is Undefined.
        inline bool isUndefined() const noexcept {return m_type == Undefined;}
        
        //! @brief Gets if the Atom is Float.
        inline bool isFloat() const noexcept {return m_type == Float;}
        
        //! @brief Gets if the Atom is Symbol.
        inline bool isSymbol() const noexcept {return m_type == Symbol;}
    };
}

#endif
