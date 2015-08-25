/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.h"
#include "PdPatch.h"

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
    
    Instance::Instance()
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
            sys_debuglevel = 4;
            sys_verbose = 0;
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
        m_internal = new Internal();
        m_internal->instance = pdinstance_new();
        m_internal->counter  = 1;
        if(!m_internal->instance)
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "Can't allocate instance !";}
            };
            throw Error();
        }
    }
    
    Instance::~Instance() noexcept
    {
        std::lock_guard<std::mutex> guard(m_internal->mutex);
        if(!(--m_internal->counter))
        {
            releaseDsp();
            m_internal->patcher.clear();
            if(m_internal->instance)
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                pdinstance_free(m_internal->instance);
            }
        }
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        releaseDsp();
        std::lock_guard<std::mutex> guard(m_internal->mutex);
        std::lock_guard<std::mutex> guard2(s_mutex);
        pd_setinstance(m_internal->instance);
        t_atom av;
        atom_setfloat(&av, 0);
        pd_typedmess((t_pd *)gensym("pd")->s_thing, gensym("dsp"), 1, &av);
        
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
    }
    
    void Instance::processDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        std::lock_guard<std::mutex> guard(m_internal->mutex);
        std::lock_guard<std::mutex> guard2(s_mutex);
        pd_setinstance(m_internal->instance);
        
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
    }
    
    void Instance::releaseDsp() noexcept
    {
        ;
    }
    
    Patch Instance::openPatch(const std::string& name, const std::string& path)
    {
        /*
        std::lock_guard<std::mutex> guard(m_internal->mutex);
        t_canvas* cnv = NULL;
        if(!name.empty() && !path.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            pd_setinstance(m_internal->instance);
            cnv = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
        }
        else if(!name.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            pd_setinstance(m_internal->instance);
            cnv = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym("")));
        }
        try
        {
            patcher = std::shared_ptr<Patch>(new Patch(cnv, name, path));
        }
        catch(std::exception& e)
        {
            throw e;
        }
        m_internal->patcher.insert(patcher);
        return patcher;
         */
    }
    
    void Instance::closePatch(Patch patch)
    {
        /*
        if(patch)
        {
            std::lock_guard<std::mutex> guard(m_internal->mutex);
            if(m_internal->patcher.erase(patch))
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                pd_setinstance(m_internal->instance);
                canvas_free(const_cast<t_canvas*>(patch->m_cnv));
            }
        }
         */
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
    
    
}



