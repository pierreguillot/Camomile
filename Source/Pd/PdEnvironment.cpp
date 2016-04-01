/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdEnvironment.hpp"
#include "PdInstance.hpp"

extern "C"
{
#include "z_pd.h"
}

namespace pd
{
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    Environment::Environment() noexcept
    {
        static bool initialized = false;
        if(!initialized)
        {
            z_pd_init();
        }
    }
    
    Environment::~Environment() noexcept
    {
        z_pd_clear();
    }
    
    Environment& Environment::get() noexcept
    {
        static Environment pd;
        return pd;
    }
    
    std::string Environment::getPdVersion()
    {
        return std::to_string(z_pd_version_getmajor()) + "." +
        std::to_string(z_pd_version_getminor()) + "." +
        std::to_string(z_pd_version_getbug());
    }
    
    void Environment::addToSearchPath(std::string const& path) noexcept
    {
        std::lock_guard<std::mutex> guard(Environment::get().m_mutex);
        z_pd_searchpath_add(path.c_str());
    }
    
    void Environment::clearSearchPath() noexcept
    {
        std::lock_guard<std::mutex> guard(Environment::get().m_mutex);
        z_pd_searchpath_clear();
    }
    
    void Environment::lock() noexcept
    {
        Environment::get().m_mutex.lock();
    }
    
    void Environment::unlock() noexcept
    {
        Environment::get().m_mutex.unlock();
    }
}

