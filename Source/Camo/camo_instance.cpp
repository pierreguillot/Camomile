/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "camo_instance.hpp"
#include <cassert>
#include <cmath>

namespace camo
{
    xpd::symbol camomile::get_symbol_float()
    {
        static xpd::symbol x_sym("float");
        return x_sym;
    }
    
    xpd::symbol get_symbol_playing()
    {
        static xpd::symbol x_sym("playing");
        return x_sym;
    }
    
    xpd::symbol get_symbol_measure()
    {
        static xpd::symbol x_sym("measure");
        return x_sym;
    }
    
    // ================================================================================ //
    //                                      DEFAULT                                     //
    // ================================================================================ //
    
    
    camomile::camomile() : m_playing_list(2), m_measure_list(5)
    {
        
    }
    
    // ================================================================================ //
    //                                      INSTANCE                                    //
    // ================================================================================ //
    
    void camomile::receive(xpd::tie name, xpd::symbol selector, std::vector<xpd::atom> const& atoms)
    {
        if(!atoms.empty() && selector == get_symbol_float() && atoms[0].type() == xpd::atom::float_t)
        {
            for(size_t i = 0; i < m_parameters.size(); ++i)
            {
                if(m_parameters[i].receive_tie == name)
                {
                    set_parameter_value(i, static_cast<float>(atoms[i]), false);
                    return;
                }
            }
        }
    }
    
    void camomile::receive(xpd::console::post const& post)
    {
        xpd::console::history::add(std::move(post));
    }
    
    // ================================================================================ //
    //                                      PATCH                                       //
    // ================================================================================ //
    
    void camomile::load_patch(const std::string &name, const std::string &path)
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
        }
        m_patch = xpd::instance::load(name, path);
        if(static_cast<bool>(m_patch))
        {
            m_playhead_tie = xpd::tie(std::to_string(m_patch.unique_id()) + "-playhead");
        }
        else
        {
            send(xpd::console::post(xpd::console::error, std::string("camomile can't find the patch : ") + name));
        }
    }
    
    
    void camomile::close_patch()
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
            m_playhead_tie = xpd::tie();
        }
    }
    
    // ================================================================================ //
    //                                      PARAMETERS                                  //
    // ================================================================================ //
    
    void camomile::clear_parameters()
    {
        for(size_t i = 0; i < m_parameters.size(); ++i)
        {
            instance::unbind(m_parameters[i].send_tie);
        }
        m_parameters.clear();
    }
    
    void camomile::add_parameter(parameter const& param)
    {
        assert(!param.name.empty() && "the name of a camomile parameter can't be empty.");
        assert(static_cast<bool>(param.receive_tie) && "the receive tie of a camomile parameter can't be empty.");
        assert(static_cast<bool>(param.send_tie) && "the send tie of a camomile parameter can't be empty.");
        for(size_t i = 0; i < m_parameters.size(); ++i)
        {
            if(m_parameters[i].name == param.name ||
               m_parameters[i].receive_tie == param.receive_tie ||
               m_parameters[i].send_tie == param.send_tie)
            {
                throw "camomile receives a duplicated parameter.";
            }
        }
        m_parameters.push_back(param);
        instance::bind(param.send_tie);
    }
    
    float camomile::get_parameter_default_value(size_t const index, bool const normalized) const xpd_noexcept
    {
        return normalized ? m_parameters[index].defval : m_parameters[index].defval * (m_parameters[index].max - m_parameters[index].min) + m_parameters[index].min;
    }
    
    float camomile::get_parameter_value(size_t const index, bool const normalized) const xpd_noexcept
    {
        return normalized ? m_parameters[index].value : m_parameters[index].value * (m_parameters[index].max - m_parameters[index].min) + m_parameters[index].min;
    }
    
    void camomile::set_parameter_value(size_t const index, float val, bool const normalized)
    {
        if(!normalized)
        {
            val = (val - m_parameters[index].min) / (m_parameters[index].max - m_parameters[index].min);
        }
        if(m_parameters[index].nsteps > 1)
        {
            const float step = (1.f / float(m_parameters[index].nsteps - 1));
            val = std::round(val / step) * step;
        }
        m_parameters[index].value = val;
        instance::send(m_parameters[index].send_tie, get_symbol_float(), {get_parameter_value(index, false)});
    }
    
    
    // ================================================================================ //
    //                                      LISTENER                                    //
    // ================================================================================ //

    void camomile::add_listener(listener& l)
    {
        m_listeners.insert(&l);
    }
    
    void camomile::remove_listener(listener& l)
    {
        m_listeners.erase(&l);
    }
}

