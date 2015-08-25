/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_MASTER__
#define __CAMOMILE_PD_MASTER__

#include "PdAtom.h"

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The CPP wrapper for pd's instance.
    class Instance
    {
        friend class patch;
    private:
        struct Internal
        {
            t_pdinstance*       instance;
            std::mutex          mutex;
            std::set<Patch>     patcher;
            std::atomic<size_t> counter;
        };
        Internal*   m_internal;
    public:
        
        Instance();
        Instance(Instance const& other) : m_internal(other.m_internal) {m_internal->counter++;}
        ~Instance() noexcept;
        Instance& operator=(Instance const& other) {m_internal = other.m_internal; m_internal->counter++; return *this;}
        
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        void processDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept;
        void releaseDsp() noexcept;
        
        Patch openPatch(const std::string& name, const std::string& path);
        void  closePatch(Patch patch);
        
        static void addToSearchPath(std::string const& path) noexcept;
        static void clearSearchPath() noexcept;
        
    private:
        static std::mutex                   s_mutex;
        static int                          s_sample_rate;
        static const int                    s_max_channels = 16;
        static void print(const char* s) {std::cout << s << "\n";}
    };

}

#endif
