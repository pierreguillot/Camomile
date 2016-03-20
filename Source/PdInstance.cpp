/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.hpp"
#include "PdPatch.hpp"

extern "C"
{
#include "z_pd.h"
}

namespace pd
{
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    Instance::Instance() noexcept :
    m_ptr(nullptr),
    m_count(nullptr)
    {
        
    }
    
    Instance::Instance(void* ptr) noexcept :
    m_ptr(ptr),
    m_count(new std::atomic<long>(1))
    {
        
    }
    
    Instance::Instance(Instance const& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Instance::Instance(Instance&& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count)
    {
        other.m_ptr         = nullptr;
        other.m_count       = nullptr;
    }
    
    void Instance::release() noexcept
    {
        if(m_ptr && m_count && m_count->operator--() == 0)
        {
            releaseDsp();
            Environment::free(*this);
            delete m_count;
            m_ptr           = nullptr;
            m_count         = nullptr;
        }
    }
    
    Instance& Instance::operator=(Instance const& other) noexcept
    {
        release();
        if(other.m_ptr && other.m_count && other.m_count->operator++() > 0)
        {
            m_ptr           = other.m_ptr;
            m_count         = other.m_count;
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
        release();
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        lock();
        z_pd_instance_dsp_prepare(reinterpret_cast<z_instance *>(m_ptr), nins, nouts, samplerate, nsamples);
        unlock();
    }

    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        z_pd_instance_dsp_perform(reinterpret_cast<z_instance *>(m_ptr), nsamples, nins, inputs, nouts, outputs);
    }
    
    void Instance::releaseDsp() noexcept
    {
        lock();
        z_pd_instance_dsp_release(reinterpret_cast<z_instance *>(m_ptr));
        unlock();
    }
    
    void Instance::lock() noexcept
    {
        Environment::lock();
        z_pd_instance_set(reinterpret_cast<z_instance *>(m_ptr));
    }
    
    void Instance::unlock() noexcept
    {
        Environment::unlock();
    }
    
    bool Instance::isValid() const noexcept
    {
        return bool(m_ptr) && bool(m_count) && bool(m_count->load());
    }
    
    long Instance::getSampleRate() const noexcept
    {
        return z_pd_instance_get_samplerate(reinterpret_cast<z_instance *>(m_ptr));
    }
    
    Patch Instance::createPatch(std::string const& name, std::string const& path)
    {
        Patch patch;
        lock();
        void* cnv = z_pd_patch_new(name.c_str(), path.c_str());
        if(cnv)
        {
            patch = Patch(*this, cnv, name, path);
        }
        unlock();
        return patch;
    }
    
    void Instance::freePatch(Patch &patch)
    {
        lock();
        z_pd_patch_free(reinterpret_cast<z_patch *>(patch.m_ptr));
        unlock();
    }
}



