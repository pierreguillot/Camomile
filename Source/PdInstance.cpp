/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.hpp"
#include "Pd.hpp"

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
}

namespace pd
{
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    class Instance::Internal : public LeakDetector<Internal>
    {
    public:
        t_pdinstance*        instance;
        std::atomic<size_t>  counter;
        std::string          name;
        
        Internal(std::string const& _name);
        ~Internal();
    };
    
    Instance::Instance() noexcept : m_internal(nullptr)
    {
        
    }
    
    Instance::Internal::Internal(std::string const& _name) :
    instance(nullptr),
    counter(1),
    name(_name)
    {
        Pd::lock();
        instance = pdinstance_new();
        Pd::unlock();
    }
    
    Instance::Internal::~Internal()
    {
        Pd::lock();
        if(instance)
        {
            pdinstance_free(instance);
        }
        Pd::unlock();
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
        Pd::lock();
        pd_setinstance(m_internal->instance);
        t_atom av;
        av.a_type = A_FLOAT;
        av.a_w.w_float = 1;
        pd_typedmess((t_pd *)gensym("pd")->s_thing, gensym("dsp"), 1, &av);
        Pd::unlock();
    }

    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        Pd::lock();
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
        Pd::unlock();
    }
    
    void Instance::releaseDsp() noexcept
    {
        
    }
    
    void Instance::send(void* s, float val) const noexcept
    {
        t_symbol* sy = reinterpret_cast<t_symbol*>(s);
        if(sy && sy->s_thing)
        {
            pd_float((t_pd *)sy->s_thing, val);
        }
    }
    
    void Instance::lock() noexcept
    {
        Pd::lock();
        pd_setinstance(m_internal->instance);
    }
    
    void Instance::unlock()
    {
        Pd::unlock();
    }
    
    bool Instance::isValid() const noexcept
    {
        return bool(m_internal) && bool(m_internal->instance);
    }
    
    std::string Instance::getName() const noexcept
    {
        return bool(m_internal) ? m_internal->name : std::string();
    }
    
    void* Instance::createCanvas(std::string const& name, std::string const& path)
    {
        t_canvas* cnv = nullptr;
        Pd::lock();
        pd_setinstance(m_internal->instance);
        if(!name.empty() && !path.empty())
        {
            cnv = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
            cnv->gl_edit = 0;
        }
        else if(!name.empty())
        {
            cnv = reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym("")));
            cnv->gl_edit = 0;
        }
        Pd::unlock();
        return cnv;
    }
    
    void Instance::freeCanvas(void* cnv)
    {
        Pd::lock();
        pd_setinstance(m_internal->instance);
        canvas_free(reinterpret_cast<t_canvas*>(cnv));
        Pd::unlock();
    }
}



