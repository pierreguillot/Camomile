/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "camo_processor.hpp"
#include <cassert>
#include <cmath>

namespace camo
{
    xpd::symbol processor::get_symbol_float()
    {
        static xpd::symbol x_sym("float");
        return x_sym;
    }
    
    xpd::symbol processor::get_symbol_list()
    {
        static xpd::symbol x_sym("list");
        return x_sym;
    }
    
    // ================================================================================ //
    //                                      DEFAULT                                     //
    // ================================================================================ //
    
    
    processor::processor() : m_playhead_list(14)
    {
        get_symbol_float();
        get_symbol_list();
    }
    
    // ================================================================================ //
    //                                      INSTANCE                                    //
    // ================================================================================ //
    
    void processor::receive(xpd::tie name, xpd::symbol selector, std::vector<xpd::atom> const& atoms)
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
    
    void processor::receive(xpd::console::post const& post)
    {
        xpd::console::history::add(std::move(post));
    }
    
    // ================================================================================ //
    //                                      PLAY HEAD                                   //
    // ================================================================================ //
    
    
    void processor::set_playhead_infos(PlayHeadInfos const& ph)
    {
        if(static_cast<bool>(m_playhead_tie))
        {
            m_playhead_list[0] = static_cast<float>(ph.bpm);
            m_playhead_list[1] = static_cast<float>(ph.timeSigNumerator);
            m_playhead_list[2] = static_cast<float>(ph.timeSigDenominator);
            m_playhead_list[3] = static_cast<float>(ph.timeInSamples);
            m_playhead_list[4] = static_cast<float>(ph.timeInSeconds);
            m_playhead_list[5] = static_cast<float>(ph.editOriginTime);
            m_playhead_list[6] = static_cast<float>(ph.ppqPosition);
            m_playhead_list[7] = static_cast<float>(ph.ppqPositionOfLastBarStart);
            m_playhead_list[8] = static_cast<float>(ph.frameRate);
            m_playhead_list[9] = static_cast<float>(ph.isPlaying);
            m_playhead_list[10] = static_cast<float>(ph.isRecording);
            m_playhead_list[11] = static_cast<float>(ph.ppqLoopStart);
            m_playhead_list[12] = static_cast<float>(ph.ppqLoopEnd);
            m_playhead_list[13] = static_cast<float>(ph.isLooping);
            xpd::instance::send(m_playhead_tie, get_symbol_list(), m_playhead_list);
        }
    }
    
    // ================================================================================ //
    //                                      PATCH                                       //
    // ================================================================================ //
    
    void processor::load_patch(const std::string &name, const std::string &path)
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
            send(xpd::console::post(xpd::console::error, std::string("processor can't find the patch : ") + name));
        }
    }
    
    
    void processor::close_patch()
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
    
    void processor::clear_parameters()
    {
        for(size_t i = 0; i < m_parameters.size(); ++i)
        {
            instance::unbind(m_parameters[i].send_tie);
        }
        m_parameters.clear();
    }
    
    void processor::add_parameter(parameter const& param)
    {
        assert(!param.name.empty() && "the name of a processor parameter can't be empty.");
        assert(static_cast<bool>(param.receive_tie) && "the receive tie of a processor parameter can't be empty.");
        assert(static_cast<bool>(param.send_tie) && "the send tie of a processor parameter can't be empty.");
        for(size_t i = 0; i < m_parameters.size(); ++i)
        {
            if(m_parameters[i].name == param.name ||
               m_parameters[i].receive_tie == param.receive_tie ||
               m_parameters[i].send_tie == param.send_tie)
            {
                throw "processor receives a duplicated parameter.";
            }
        }
        m_parameters.push_back(param);
        instance::bind(param.send_tie);
    }
    
    float processor::get_parameter_default_value(size_t const index, bool const normalized) const xpd_noexcept
    {
        return normalized ? m_parameters[index].defval : m_parameters[index].defval * (m_parameters[index].max - m_parameters[index].min) + m_parameters[index].min;
    }
    
    float processor::get_parameter_value(size_t const index, bool const normalized) const xpd_noexcept
    {
        return normalized ? m_parameters[index].value : m_parameters[index].value * (m_parameters[index].max - m_parameters[index].min) + m_parameters[index].min;
    }
    
    void processor::set_parameter_value(size_t const index, float val, bool const normalized)
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

    void processor::add_listener(listener& l)
    {
        m_listeners.insert(&l);
    }
    
    void processor::remove_listener(listener& l)
    {
        m_listeners.erase(&l);
    }
}

