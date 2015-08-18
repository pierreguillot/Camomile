/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdWrapper.h"

namespace mpd
{
    // ==================================================================================== //
    //                                          MASTER                                      //
    // ==================================================================================== //
    
    int Master::s_sample_rate;
    std::mutex Master::s_mutex;
    
    void Master::initialize() noexcept
    {
        static int initialized = 0;
        if(!initialized)
        {
            //std::lock_guard<std::mutex> guard(s_mutex);
            signal(SIGFPE, SIG_IGN);
            sys_printhook = (t_printhook)print;
            sys_soundin = NULL;
            sys_soundout = NULL;
            // are all these settings necessary?
            sys_schedblocksize = DEFDACBLKSIZE;
            sys_externalschedlib = 0;
            sys_printtostderr = 0;
            sys_usestdpath = 0;
            sys_debuglevel = 0;
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
            s_sample_rate  = 44100;
            initialized = 1;
            libpd_loadcream();
        }
    }
    
    t_pdinstance* Master::createInstance() noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        initialize();
        return pdinstance_new();
    }
    
    void Master::print(const char* s)
    {
        std::cout << s << "\n";
    }
    
    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patcher::Patcher(std::string const& name,
                     std::string const& path) :
    m_name(name),
    m_path(path),
    m_cnv(Master::evalFile(name, path))
    {
        if(!m_cnv)
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "Can't allocate patcher !";}
            };
            throw Error();
        }
    }
    
    Patcher::~Patcher() noexcept
    {
        if(m_cnv)
        {
            Master::closePatch(m_cnv);
        }
    }
    
    std::vector<sObject> Patcher::getObjects() const noexcept
    {
        std::vector<sObject> objects;
        for(t_gobj *y = m_cnv->gl_list; y; y = y->g_next)
        {
            objects.push_back(std::make_shared<Object>(y));
        }
        return objects;
    }
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    bool Gui::wantMouse() const noexcept
    {
        t_eclass* c = getClass();
        return c && !(m_handle->b_flags & EBOX_IGNORELOCKCLICK) &&
        (c->c_widget.w_mousedown ||
         c->c_widget.w_mousedrag ||
         c->c_widget.w_mouseenter ||
         c->c_widget.w_mouseleave ||
         c->c_widget.w_mousemove ||
         c->c_widget.w_mouseup ||
         c->c_widget.w_mousewheel ||
         c->c_widget.w_dblclick);
    }
    
    bool Gui::wantKeyboard() const noexcept
    {
        t_eclass* c = getClass();
        return c && (c->c_widget.w_key || c->c_widget.w_keyfilter);
    }
    
    void Gui::mouseMove(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousemove)
        {
            c->c_widget.w_mousemove(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseenter)
        {
            c->c_widget.w_mouseenter(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseExit(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseleave)
        {
            c->c_widget.w_mouseleave(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDown(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedown)
        {
            c->c_widget.w_mousedown(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedrag)
        {
            c->c_widget.w_mousedrag(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseUp(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseup)
        {
            c->c_widget.w_mouseup(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_dblclick)
        {
            c->c_widget.w_dblclick(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousewheel)
        {
            c->c_widget.w_mousewheel(m_handle, NULL, t_pt({pos[0], pos[1]}), (long)mod, delta[0], delta[1]);
        }
    }
}



