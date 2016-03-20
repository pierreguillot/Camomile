/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Pd.hpp"
#include "PdInstance.hpp"


extern "C"
{
#include "z_pd.h"
}

static std::vector<pd::MidiEvent>& getMidiOut()
{
    static std::vector<pd::MidiEvent> midiout;
    return midiout;
}

namespace pd
{
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    Pd::Pd() noexcept
    {
        static bool initialized = false;
        if(!initialized)
        {
            z_pd_init();
        }
        m_console.reserve(256);
        getMidiOut().reserve(1024);
    }
    
    Pd::~Pd() noexcept
    {
        z_pd_clear();
    }
    
    Pd& Pd::get() noexcept
    {
        static Pd pd;
        return pd;
    }
    
    std::string Pd::getPdVersion()
    {
        return std::to_string(z_pd_version_getmajor()) + "." +
        std::to_string(z_pd_version_getminor()) + "." +
        std::to_string(z_pd_version_getbug());
    }
    
    void Pd::addToSearchPath(std::string const& path) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        z_pd_searchpath_add(path.c_str());
    }
    
    void Pd::clearSearchPath() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        z_pd_searchpath_clear();
    }
    
    void Pd::clearConsole() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        int aki;
    }
    
    void Pd::postToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Post});
        pd.m_console_changed = true;
    }
    
    void Pd::logToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Log});
        pd.m_console_changed = true;
    }
    
    void Pd::errorToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Error});
        pd.m_console_changed = true;
    }
    
    std::vector<Post> Pd::getConsole(bool state) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console_changed = state;
        return pd.m_console;
    }
    
    bool Pd::hasConsoleChanged() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        return pd.m_console_changed;
    }
    
    void Pd::lock() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.lock();
    }
    
    void Pd::unlock() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.unlock();
    }
    
    Instance Pd::createInstance() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.lock();
        Instance instance(pdinstance_new());
        pd.m_mutex.unlock();
        return instance;
    }
    
    void Pd::free(Instance& instance)
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        pdinstance_free(reinterpret_cast<t_pdinstance *>(instance.m_ptr));
    }
    
    void Pd::send(BindingName const& name, float val) noexcept
    {
        t_symbol* sy = reinterpret_cast<t_symbol*>(name.ptr);
        if(sy && sy->s_thing)
        {
            pd_float((t_pd *)sy->s_thing, val);
        }
    }
    
    void Pd::sendNote(int channel, int pitch, int velocity)
    {
        z_pd_midisend_noteon(channel, pitch, velocity);
    }
    
    void Pd::sendControlChange(int channel, int controller, int value)
    {
        z_pd_midisend_controlchange(channel, controller, value);
    }
    
    void Pd::sendProgramChange(int channel, int value)
    {
        
    }
    
    void Pd::sendPitchBend(int channel, int value)
    {
        ;
    }
    
    void Pd::sendAfterTouch(int channel, int value)
    {
        ;
    }
    
    void Pd::sendPolyAfterTouch(int channel, int pitch, int value)
    {
        ;
    }
    
    void Pd::sendMidiByte(int port, int byte)
    {
        ;
    }
    
    void Pd::sendSysEx(int port, int byte)
    {
        ;
    }
    
    void Pd::sendSysRealtime(int port, int byte)
    {
        ;
    }
    
    void Pd::clearMidi()
    {
        getMidiOut().clear();
    }
    
    std::vector<MidiEvent>::const_iterator Pd::getMidiBegin()
    {
        return getMidiOut().cbegin();
    }
    
    std::vector<MidiEvent>::const_iterator Pd::getMidiEnd()
    {
        return getMidiOut().cend();
    }
}

