/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Pd.hpp"
#include "PdInstance.hpp"

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
EXTERN  void pd_init(void);
}

namespace pd
{
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    Pd::Pd() noexcept
    {
        signal(SIGFPE, SIG_IGN);
        sys_printhook = NULL;
        sys_soundin = NULL;
        sys_soundout = NULL;
        // are all these settings necessary?
        sys_schedblocksize = DEFDACBLKSIZE;
        sys_externalschedlib = 0;
        sys_printtostderr = 0;
        sys_usestdpath = 0;
        sys_debuglevel = 1;
        sys_verbose = 1;
        sys_noloadbang = 0;
        sys_nogui = 1;
        sys_hipriority = 0;
        sys_nmidiin = 0;
        sys_nmidiout = 0;
        sys_init_fdpoll();
#ifdef HAVE_SCHED_TICK_ARG
        sys_time = 0;
#endif
        pd_init();
        sys_set_audio_api(API_DUMMY);
        sys_searchpath = NULL;
        m_sample_rate  = 0;
        
        int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
        outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
        indev[0] = outdev[0] = DEFAULTAUDIODEV;
        inch[0] = m_max_channels;
        outch[0] = m_max_channels;
        sys_set_audio_settings(1, indev, 1, inch,
                               1, outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
        sched_set_using_audio(SCHED_AUDIO_CALLBACK);
        sys_reopen_audio();
        m_sample_rate = sys_getsr();
        m_console.clear();
        m_console.append("Camomile v0.0.2 for Pure Data 0.46.7\n");
        sys_printhook = reinterpret_cast<t_printhook>(print);
    }
    
    Pd& Pd::get() noexcept
    {
        static Pd pd;
        return pd;
    }
    
    void Pd::print(const char* s)
    {
        Pd& pd = Pd::get();
        pd.m_console.append(s);
        std::cout << s;
    }
    
    void Pd::addToSearchPath(std::string const& path) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        sys_searchpath = namelist_append(sys_searchpath, path.c_str(), 0);
    }
    
    void Pd::clearSearchPath() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        namelist_free(sys_searchpath);
        sys_searchpath = NULL;
    }
    
    void Pd::setConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        pd.m_console = text;
    }
    
    void Pd::addConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        pd.m_console += text;
    }
    
    std::string Pd::getConsole() noexcept
    {
        Pd& pd = Pd::get();
        if(pd.m_console.size() > 1000)
        {
            pd.m_console.erase(pd.m_console.begin(), pd.m_console.end()-1000);
        }
        return pd.m_console;
    }
    
    void Pd::setSampleRate(const int samplerate) noexcept
    {
        Pd& pd = Pd::get();
        if(pd.m_sample_rate != samplerate)
        {
            int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
            outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
            indev[0] = outdev[0] = DEFAULTAUDIODEV;
            inch[0] = pd.m_max_channels;
            outch[0] = pd.m_max_channels;
            sys_set_audio_settings(1, indev, 1, inch,
                                   1, outdev, 1, outch, samplerate, -1, 1, DEFDACBLKSIZE);
            sched_set_using_audio(SCHED_AUDIO_CALLBACK);
            sys_reopen_audio();
            pd.m_sample_rate = sys_getsr();
        }
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
        pd.m_mutex.unlock();
        Instance instance(pdinstance_new());
        Pd::unlock();
        return instance;
    }
}



