/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.h"
#include "PdPatch.h"
#include "PdMessenger.h"

extern "C"
{
    EXTERN  void pd_init(void);
}

namespace pd
{
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    int Instance::s_sample_rate;
    std::mutex Instance::s_mutex;
    std::string Instance::s_console;
    
    Instance::Internal::Internal(std::string const& _name) :
    instance(nullptr),
    counter(1),
    name(_name)
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        static int initialized = 0;
        if(!initialized)
        {
            signal(SIGFPE, SIG_IGN);
            sys_printhook = (t_printhook)print;
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
            s_sample_rate  = 0;
            initialized = 1;
            libpd_loadcream();
            
            int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
            outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
            indev[0] = outdev[0] = DEFAULTAUDIODEV;
            inch[0] = s_max_channels;
            outch[0] = s_max_channels;
            sys_set_audio_settings(1, indev, 1, inch,
                                   1, outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
            sched_set_using_audio(SCHED_AUDIO_CALLBACK);
            sys_reopen_audio();
            s_sample_rate = sys_getsr();
        }
        instance = pdinstance_new();
    }
    
    Instance::Internal::~Internal()
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        if(instance)
        {
            pdinstance_free(instance);
        }
    }
    
    Instance::Instance() noexcept : m_internal(nullptr)
    {
        
    }
    
    Instance::Instance(std::string const& name) noexcept : m_internal(new Internal(name))
    {
        
    }
    
    Instance::Instance(Instance const& other) noexcept : m_internal(other.m_internal)
    {
        if(m_internal)
        {
            ++m_internal->counter;
        }
    }
    
    Instance::Instance(Instance&& other) noexcept : m_internal(other.m_internal)
    {
        other.m_internal = nullptr;
    }
    
    Instance& Instance::operator=(Instance const& other) noexcept
    {
        if(other.m_internal)
        {
            other.m_internal->counter++;
            m_internal = other.m_internal;
        }
        else
        {
            m_internal = nullptr;
        }
        return *this;
    }
    
    Instance& Instance::operator=(Instance&& other) noexcept
    {
        std::swap(m_internal, other.m_internal);
        return *this;
    }
    
    Instance::~Instance() noexcept
    {
        if(m_internal && m_internal->counter)
        {
            if(!(--m_internal->counter))
            {
                releaseDsp();
                delete m_internal;
            }
        }
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        releaseDsp();
        lock();
        t_atom av;
        if(s_sample_rate != samplerate)
        {
            int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
            outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
            indev[0] = outdev[0] = DEFAULTAUDIODEV;
            inch[0] = s_max_channels;
            outch[0] = s_max_channels;
            sys_set_audio_settings(1, indev, 1, inch,
                                   1, outdev, 1, outch, samplerate, -1, 1, DEFDACBLKSIZE);
            sched_set_using_audio(SCHED_AUDIO_CALLBACK);
            sys_reopen_audio();
            s_sample_rate = sys_getsr();
        }
        
        atom_setfloat(&av, 1);
        pd_typedmess((t_pd *)gensym("pd")->s_thing, gensym("dsp"), 1, &av);
        unlock();
    }
    
    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        lock();
        for(int i = 0; i < nsamples; i += DEFDACBLKSIZE)
        {
            for(int j = 0; j < nins; j++)
            {
                memcpy(sys_soundin+j*DEFDACBLKSIZE, inputs[j]+i, DEFDACBLKSIZE * sizeof(t_sample));
            }
            memset(sys_soundout, 0, DEFDACBLKSIZE * sizeof(t_sample) * nouts);
            sched_tick();
            for(int j = 0; j < nouts; j++)
            {
                memcpy(outputs[j]+i, sys_soundout+j*DEFDACBLKSIZE, DEFDACBLKSIZE * sizeof(t_sample));
            }
        }
        unlock();
    }
    
    void Instance::releaseDsp() noexcept
    {
        ;
    }
    
    void Instance::trigger() const noexcept
    {
        lock();
        if(m_internal)
        {
            for(auto it : m_internal->messengers)
            {
                it->trigger();
            }
        }
        unlock();
    }
    
    void Instance::addMessenger(Messenger* messenger)
    {
        lock();
        if(m_internal)
        {
            m_internal->messengers.insert(messenger);
        }
        unlock();
    }
    
    void Instance::removeMessenger(Messenger* messenger)
    {
        lock();
        if(m_internal)
        {
            m_internal->messengers.erase(messenger);
        }
        unlock();
    }
    
    void Instance::addToSearchPath(std::string const& path) noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        sys_searchpath = namelist_append(sys_searchpath, path.c_str(), 0);
    }
    
    
    void Instance::clearSearchPath() noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        namelist_free(sys_searchpath);
        sys_searchpath = NULL;
    }
    
    void Instance::setConsole(std::string const& text) noexcept
    {
        s_console = text;
    }
    
    std::string Instance::getConsole() noexcept
    {
        if(s_console.size() > 1000)
        {
            s_console.erase(s_console.begin(), s_console.end()-1000);
        }
        return s_console;
    }
    
    void Instance::print(const char* s)
    {
        s_console.append(s);
        t_symbol* send = gensym("camo-console");
        if(send->s_thing)
        {
            pd_bang(send->s_thing);
        }
        std::cout << s;
    }
}



