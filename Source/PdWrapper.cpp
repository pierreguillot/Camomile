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
    
    sInstance Master::createInstance()
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        
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
        
        sInstance instance;
        try
        {
            instance = std::shared_ptr<Instance>(new Instance(pdinstance_new()));
        }
        catch(std::exception& e)
        {
            throw e;
        }
        return instance;
    }
    
    void Master::closeInstance(sInstance instance)
    {
        if(instance)
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            pdinstance_free(instance->m_instance);
        }
    }
    
    t_canvas* Master::openPatch(std::string const& name, std::string const& path)
    {
        if(!name.empty() && !path.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            return reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
        }
        else if(!name.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            return reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym("")));
        }
        return nullptr;
    }
    
    void Master::closePatch(const t_canvas* cnv)
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        canvas_free(const_cast<t_canvas*>(cnv));
    }
    
    void Master::print(const char* s)
    {
        std::cout << s << "\n";
    }
    
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    Instance::Instance(t_pdinstance* instance) : m_instance(instance)
    {
        if(!m_instance)
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "Can't allocate instance !";}
            };
            throw Error();
        }
    }
    
    sPatcher Instance::openPatcher(const std::string& name, const std::string& path)
    {
        std::shared_ptr<Patcher> patcher;
        t_canvas* cnv = Master::openPatch(name.c_str(), path.c_str());
        try
        {
            patcher = std::shared_ptr<Patcher>(new Patcher(cnv, name, path));
        }
        catch(std::exception& e)
        {
            throw e;
        }
        std::lock_guard<std::mutex> guard(m_mutex);
        m_patcher.insert(patcher);
        return patcher;
    }
    
    void Instance::closePatcher(sPatcher patch)
    {
        if(patch)
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if(m_patcher.erase(patch))
            {
                Master::closePatch(patch->m_cnv);
            }
        }
    }
    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patcher::Patcher(t_canvas* cnv,
                     std::string const& name,
                     std::string const& path) :
    m_cnv(cnv),
    m_name(name),
    m_path(path)
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
        else
        {
            for(t_gobj *y = m_cnv->gl_list; y; y = y->g_next)
            {
                Object* obj = new Object(y);
                if(obj && obj->isGui())
                {
                    m_objects.insert(std::shared_ptr<Gui>(new Gui(y)));
                }
                else
                {
                    m_objects.insert(std::shared_ptr<Object>(obj));
                }
            }
        }
    }
    
    std::vector<sObject> Patcher::getObjects() const noexcept
    {
        return std::vector<sObject>(m_objects.begin(), m_objects.end());
    }
    
    // ==================================================================================== //
    //                                          OBJECT                                      //
    // ==================================================================================== //
    
    Object::Object(void* handle) : m_handle(handle)
    {
        if(!handle)
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "The object isn't valid !";}
            };
        }
    }
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    Gui::Gui(void* handle) : Object(handle)
    {
        t_eclass* c = getClass();
        if(!c || !eobj_iscicm(getHandle()) || !eobj_isbox(getHandle()))
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "The object isn't a GUI !";}
            };
        }
        else if(c && c->c_widget.w_getdrawparameters)
        {
            t_edrawparams params;
            c->c_widget.w_getdrawparameters(getHandle(), NULL, &params);
            m_background_color = {params.d_boxfillcolor.red,
                params.d_boxfillcolor.green,
                params.d_boxfillcolor.blue,
                params.d_boxfillcolor.alpha};
            m_border_color = {params.d_bordercolor.red,
                params.d_bordercolor.green,
                params.d_bordercolor.blue,
                params.d_bordercolor.alpha};
            m_border_size = params.d_borderthickness;
            m_corner_roundness = params.d_cornersize;
        }
    }
    
    bool Gui::wantMouse() const noexcept
    {
        t_eclass* c = getClass();
        return c && !(static_cast<t_ebox *>(getHandle())->b_flags & EBOX_IGNORELOCKCLICK) &&
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
            c->c_widget.w_mousemove(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseenter)
        {
            c->c_widget.w_mouseenter(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseExit(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseleave)
        {
            c->c_widget.w_mouseleave(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDown(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedown)
        {
            c->c_widget.w_mousedown(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousedrag)
        {
            c->c_widget.w_mousedrag(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseUp(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mouseup)
        {
            c->c_widget.w_mouseup(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_dblclick)
        {
            c->c_widget.w_dblclick(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod);
        }
    }
    
    void Gui::mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_mousewheel)
        {
            c->c_widget.w_mousewheel(getHandle(), NULL, t_pt({pos[0], pos[1]}), (long)mod, delta[0], delta[1]);
        }
    }
}



