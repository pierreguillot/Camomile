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
    
    Instance::Instance() noexcept : m_ptr(nullptr), m_count(nullptr)
    {
        
    }
    
    Instance::Instance(void* ptr) noexcept : m_ptr(ptr), m_count(new std::atomic<size_t>(1))
    {
        
    }
    
    Instance::Instance(Instance const& other) noexcept : m_ptr(other.m_ptr), m_count(other.m_count)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Instance::Instance(Instance&& other) noexcept : m_ptr(other.m_ptr), m_count(other.m_count)
    {
        other.m_ptr     = nullptr;
        other.m_count   = nullptr;
    }
    
    Instance& Instance::operator=(Instance const& other) noexcept
    {
        if(m_ptr && m_count && --(*m_count) == 0)
        {
            Pd::lock();
            releaseDsp();
            delete m_count;
            pdinstance_free(reinterpret_cast<t_pdinstance *>(m_ptr));
            Pd::unlock();
            
            m_ptr   = nullptr;
            m_count =nullptr;
        }
        if(other.m_ptr && other.m_count)
        {
            ++(*m_count);
            m_ptr   = other.m_ptr;
            m_count = other.m_count;
        }
        return *this;
    }
    
    Instance& Instance::operator=(Instance&& other) noexcept
    {
        std::swap(m_count, other.m_count);
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    
    Instance::~Instance() noexcept
    {
        if(m_ptr && m_count && --(*m_count) == 0)
        {
            Pd::lock();
            releaseDsp();
            delete m_count;
            pdinstance_free(reinterpret_cast<t_pdinstance *>(m_ptr));
            Pd::unlock();
            
            m_ptr   = nullptr;
            m_count =nullptr;
        }
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        t_atom av;
        av.a_type = A_FLOAT;
        av.a_w.w_float = 1;
        pd_typedmess((t_pd *)gensym("pd")->s_thing, gensym("dsp"), 1, &av);
    }

    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
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
        pd_setinstance(reinterpret_cast<t_pdinstance *>(m_ptr));
    }
    
    void Instance::unlock()
    {
        Pd::unlock();
    }
    
    bool Instance::isValid() const noexcept
    {
        return bool(m_ptr) && bool(m_count);
    }
    
    Patch Instance::createPatch(std::string const& name, std::string const& path)
    {
        Patch patch;
        t_canvas* cnv = nullptr;
        Pd::lock();
        pd_setinstance(reinterpret_cast<t_pdinstance *>(m_ptr));
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
        Pd::unlock();
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



