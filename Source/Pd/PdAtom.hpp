/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

namespace pd
{
    // ==================================================================================== //
    //                                      ATOM                                            //
    // ==================================================================================== //
    
    class Atom
    {
    public:
        inline Atom() : type(FLOAT), value(0), symbol() {}
        inline Atom(const float val) : type(FLOAT), value(val), symbol() {}
        inline Atom(const std::string& sym) : type(SYMBOL), value(0), symbol(sym) {}
        inline Atom(const char* sym) : type(SYMBOL), value(0), symbol(sym) {}
        
        inline bool isFloat() const noexcept { return type == FLOAT; }
        inline bool isSymbol() const noexcept { return type == SYMBOL; }
        inline float getFloat() const noexcept { return value; }
        inline std::string const& getSymbol() const noexcept { return symbol; }
        
        inline bool operator==(Atom const& other) const noexcept
        {
            if(type == SYMBOL) { return other.type == SYMBOL && symbol == other.symbol; }
            else { return other.type == FLOAT && value == other.value; }
        }
    private:
        enum Type
        {
            FLOAT,
            SYMBOL
        };
        Type        type = FLOAT;
        float       value = 0;
        std::string symbol;
    };
}
