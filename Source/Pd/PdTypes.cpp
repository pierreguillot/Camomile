/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdTypes.hpp"

extern "C"
{
#include "z_pd.h"
}

namespace pd
{
    Tie::Tie(std::string const& name) noexcept : ptr(z_pd_get_tie(name.c_str()))
    {
        ;
    }
    
    Tie::Tie(char const* name) noexcept : ptr(z_pd_get_tie(name))
    {
        
    }
    
    Tie& Tie::operator=(std::string const& name)
    {
        ptr = z_pd_get_tie(name.c_str());
        return *this;
    }
    
    Tie& Tie::operator=(char const* name)
    {
        ptr = z_pd_get_tie(name);
        return *this;
    }
    
    std::string Tie::getName() const
    {
        return z_pd_tie_get_name(reinterpret_cast<z_tie const *>(ptr));
    }
    
    
    Symbol::Symbol(std::string const& name) noexcept : ptr(z_pd_get_tie(name.c_str()))
    {
        ;
    }
    
    Symbol::Symbol(char const* name) noexcept : ptr(z_pd_get_tie(name))
    {
        
    }
    
    Symbol& Symbol::operator=(std::string const& name)
    {
        ptr = z_pd_get_tie(name.c_str());
        return *this;
    }
    
    Symbol& Symbol::operator=(char const* name)
    {
        ptr = z_pd_get_tie(name);
        return *this;
    }
    
    std::string Symbol::getName() const
    {
        return z_pd_tie_get_name(reinterpret_cast<z_tie const *>(ptr));
    }
}

