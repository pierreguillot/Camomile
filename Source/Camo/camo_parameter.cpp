/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "camo_parameter.hpp"
#include <exception>

namespace camo
{
    xpd::symbol exchanger::s_float;
    
    // ==================================================================================== //
    //                                      EXCHANGER                                       //
    // ==================================================================================== //
    
    exchanger::exchanger()
    {
        s_float = std::string("float");
    }
    
    exchanger::~exchanger()
    {
        
    }
    
    void exchanger::add_parameter(std::string const& name, std::string const& label,
                                           float value, float defval, float min, float max, size_t nsteps,
                                           xpd::tie receive_tie, xpd::tie send_tie)
    {
        for(size_t i = 0; i < m_parameters.size(); ++i)
        {
            if(m_parameters[i].name == name
               || m_parameters[i].receive_tie == receive_tie
               || m_parameters[i].send_tie == send_tie)
            {
                throw "parameter duplicated.";
            }
        }
        m_parameters.push_back({name, label, value, defval, min, max, nsteps, receive_tie, send_tie});
    }
    
    bool exchanger::evaluate(xpd::tie name, xpd::symbol selector, std::vector<xpd::atom> const& atoms) xpd_noexcept
    {
        if(selector == s_float && !atoms.empty() && atoms[0].type() == xpd::atom::float_t)
        {
            for(size_t i = 0; i < m_parameters.size(); ++i)
            {
                if(m_parameters[i].receive_tie == name)
                {
                    m_parameters[i].set(static_cast<float>(atoms[i]), false);
                    return true;
                }
            }
        }
        return false;
    }
    
}

