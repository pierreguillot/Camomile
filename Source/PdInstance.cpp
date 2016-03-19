/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.hpp"
#include "PdPatch.hpp"
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
    
    Instance::Instance() noexcept :
    m_ptr(nullptr),
    m_count(nullptr),
    m_sample_rate(0ul),
    m_sample_ins(nullptr),
    m_sample_outs(nullptr)
    {
        
    }
    
    Instance::Instance(void* ptr) noexcept :
    m_ptr(ptr),
    m_count(new std::atomic<long>(1)),
    m_sample_rate(new std::atomic<long>(0)),
    m_sample_ins(nullptr),
    m_sample_outs(nullptr)
    {
        
    }
    
    Instance::Instance(Instance const& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count),
    m_sample_rate(other.m_sample_rate),
    m_sample_ins(other.m_sample_ins),
    m_sample_outs(other.m_sample_outs)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Instance::Instance(Instance&& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count),
    m_sample_rate(other.m_sample_rate),
    m_sample_ins(other.m_sample_ins),
    m_sample_outs(other.m_sample_outs)
    {
        other.m_ptr         = nullptr;
        other.m_count       = nullptr;
        other.m_sample_rate = nullptr;
        other.m_sample_ins  = nullptr;
        other.m_sample_outs = nullptr;
    }
    
    void Instance::release() noexcept
    {
        if(m_ptr && m_count && m_count->operator--() == 0)
        {
            releaseDsp();
            Pd::free(*this);
            delete m_count;
            delete m_sample_rate;
            m_ptr           = nullptr;
            m_count         = nullptr;
            m_sample_rate   = nullptr;
        }
    }
    
    Instance& Instance::operator=(Instance const& other) noexcept
    {
        release();
        if(other.m_ptr && other.m_count && other.m_count->operator++() > 0)
        {
            m_ptr           = other.m_ptr;
            m_count         = other.m_count;
            m_sample_rate   = other.m_sample_rate;
            m_sample_ins    = other.m_sample_ins;
            m_sample_outs   = other.m_sample_outs;
        }
        return *this;
    }
    
    Instance& Instance::operator=(Instance&& other) noexcept
    {
        std::swap(m_count, other.m_count);
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_sample_rate, other.m_sample_rate);
        std::swap(m_sample_ins, other.m_sample_ins);
        std::swap(m_sample_outs, other.m_sample_outs);
        return *this;
    }
    
    Instance::~Instance() noexcept
    {
        release();
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        lock();
        if(samplerate != m_sample_rate->load())
        {
            sys_setchsr(16, 16, samplerate);
            m_sample_ins    = sys_soundin;
            m_sample_outs   = sys_soundout;
            m_sample_rate->store(sys_getsr());
        }
        t_atom av;
        av.a_type = A_FLOAT;
        av.a_w.w_float = 1;
        pd_typedmess((t_pd *)gensym("pd")->s_thing, gensym("dsp"), 1, &av);
        unlock();
    }

    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        for(int i = 0; i < nsamples; i += DEFDACBLKSIZE)
        {
            for(int j = 0; j < nins; j++)
            {
                memcpy(reinterpret_cast<t_sample *>(m_sample_ins)+j*DEFDACBLKSIZE, inputs[j]+i, DEFDACBLKSIZE * sizeof(t_sample));
            }
            memset(reinterpret_cast<t_sample *>(m_sample_outs), 0, DEFDACBLKSIZE * sizeof(t_sample) * nouts);
            sched_tick();
            for(int j = 0; j < nouts; j++)
            {
                memcpy(outputs[j]+i, reinterpret_cast<t_sample *>(m_sample_outs)+j*DEFDACBLKSIZE, DEFDACBLKSIZE * sizeof(t_sample));
            }
        }
    }
    
    void Instance::releaseDsp() noexcept
    {
        
    }
    
    void Instance::send(BindingName const& name, float val) const noexcept
    {
        t_symbol* sy = reinterpret_cast<t_symbol*>(name.ptr);
        if(sy && sy->s_thing)
        {
            pd_float((t_pd *)sy->s_thing, val);
        }
    }
    
    void Instance::lock() noexcept
    {
        Pd::lock();
        pd_setinstance(reinterpret_cast<t_pdinstance *>(m_ptr));
        sys_soundin = reinterpret_cast<t_sample *>(m_sample_ins);
        sys_soundout= reinterpret_cast<t_sample *>(m_sample_outs);
        sys_dacsr   = m_sample_rate->load();
    }
    
    void Instance::unlock() noexcept
    {
        Pd::unlock();
    }
    
    bool Instance::isValid() const noexcept
    {
        return bool(m_ptr) && bool(m_count) && bool(m_count->load());
    }
    
    long Instance::getSampleRate() const noexcept
    {
        if(isValid())
        {
            return m_sample_rate->load();
        }
        return 0;
    }
    
    Patch Instance::createPatch(std::string const& name, std::string const& path)
    {
        Patch patch;
        t_canvas* cnv = nullptr;
        lock();
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
        if(cnv)
        {
            patch = Patch(*this, cnv, name, path);
        }
        unlock();
        return patch;
    }
    
    void Instance::freePatch(Patch &patch)
    {
        Pd::lock();
        pd_setinstance(reinterpret_cast<t_pdinstance *>(m_ptr));
        canvas_free(reinterpret_cast<t_canvas*>(patch.m_ptr));
        Pd::unlock();
    }
}



