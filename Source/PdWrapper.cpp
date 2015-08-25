/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdWrapper.h"
#include <iomanip>

extern "C"
{
EXTERN  void pd_init(void);
}

namespace pd
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
    
    t_canvas* Master::openPatch(t_pdinstance* instance, std::string const& name, std::string const& path)
    {
        if(!name.empty() && !path.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            pd_setinstance(instance);
            return reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
        }
        else if(!name.empty())
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            pd_setinstance(instance);
            return reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym("")));
        }
        return nullptr;
    }
    
    void Master::closePatch(t_pdinstance* instance, const t_canvas* cnv)
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        pd_setinstance(instance);
        canvas_free(const_cast<t_canvas*>(cnv));
    }
    
    void Master::addToSearchPath(std::string const& path) noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        sys_searchpath = namelist_append(sys_searchpath, path.c_str(), 0);
    }
    
    
    void Master::clearSearchPath() noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        namelist_free(sys_searchpath);
        sys_searchpath = NULL;
    }
    
    void Master::prepareDsp(t_pdinstance* instance,
                            const int samplerate,
                            int nsamples) noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        pd_setinstance(instance);
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
    
    void Master::processDsp(t_pdinstance* instance,
                            int nsamples,
                            const int nins,
                            const float** inputs,
                            const int nouts,
                            float** outputs) noexcept
    {
        std::lock_guard<std::mutex> guard(s_mutex);
        pd_setinstance(instance);
        
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

    void Master::print(const char* s)
    {
        std::cout << s << "\n";
    }
    
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    Instance::Instance(t_pdinstance* instance) :
    m_instance(instance)
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
    
    Instance::~Instance() noexcept
    {
        releaseDsp();
        std::lock_guard<std::mutex> guard(m_mutex);
        m_patcher.clear();
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        releaseDsp();
        std::lock_guard<std::mutex> guard(m_mutex);
        Master::prepareDsp(m_instance, samplerate, nsamples);
    }
    
    void Instance::releaseDsp() noexcept
    {
        ;
    }
    
    sPatch Instance::openPatch(const std::string& name, const std::string& path)
    {
        std::shared_ptr<Patch> patcher;
        std::lock_guard<std::mutex> guard(m_mutex);
        t_canvas* cnv = Master::openPatch(m_instance, name.c_str(), path.c_str());
        try
        {
            patcher = std::shared_ptr<Patch>(new Patch(cnv, name, path));
        }
        catch(std::exception& e)
        {
            throw e;
        }
        m_patcher.insert(patcher);
        return patcher;
    }
    
    void Instance::closePatch(sPatch patch)
    {
        if(patch)
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if(m_patcher.erase(patch))
            {
                Master::closePatch(m_instance, patch->m_cnv);
            }
        }
    }
    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Patch(t_canvas* cnv,
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
                    m_objects.push_back(std::shared_ptr<Gui>(new Gui(y)));
                }
                else
                {
                    m_objects.push_back(std::shared_ptr<Object>(obj));
                }
            }
        }
    }
    
    std::vector<sObject> Patch::getObjects() const noexcept
    {
        return m_objects;
    }
    
    std::vector<sGui> Patch::getGuis() const noexcept
    {
        std::vector<sGui> guis;
        for(auto it : m_objects)
        {
            if(it->isGui())
            {
                sGui gui = std::dynamic_pointer_cast<Gui>(it);
                if(gui)
                {
                    guis.push_back(gui);
                }
            }
        }
        return guis;
    }
    
    sGui Patch::getCamomile() const noexcept
    {
        auto it = std::find_if(m_objects.begin(), m_objects.end(), [] (sObject const& obj)
                               {
                                   return obj->getName() == "c.camomile";
                               });
        if(it != m_objects.end())
        {
            return std::dynamic_pointer_cast<Gui>(*it);
        }
        else
        {
            return nullptr;
        }
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
    
    bool Gui::hasPresetName() const noexcept
    {
        return is_valid_symbol(static_cast<t_ebox *>(getHandle())->b_preset_id);
    }
    
    std::string Gui::getPresetName() const noexcept
    {
        if(hasPresetName())
        {
            t_ebox* box = static_cast<t_ebox *>(getHandle());
            return std::string(box->b_preset_id->s_name);
        }
        return std::string();
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
    
    bool Gui::hasTextEditor() const noexcept
    {
        t_eclass* c = getClass();
        return c && (c->c_widget.w_texteditor_keyfilter || c->c_widget.w_texteditor_keypress);
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
    
    void Gui::textEditorKeyPress(TextEditor& editor, char ch) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_texteditor_keypress)
        {
            c->c_widget.w_texteditor_keypress(getHandle(), editor.m_editor, (int)ch);
        }
    }
    
    void Gui::textEditorKeyFilter(TextEditor& editor, int filter) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_texteditor_keyfilter)
        {
            c->c_widget.w_texteditor_keyfilter(getHandle(), editor.m_editor, (ekey_flags)filter);
        }
    }
    
    void Gui::keyPressed(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_key)
        {
            c->c_widget.w_key(getHandle(), NULL, key, mod);
        }
    }
    
    void Gui::keyFilter(const char key, const long mod) noexcept
    {
        t_eclass* c = getClass();
        if(c && c->c_widget.w_keyfilter)
        {
            c->c_widget.w_keyfilter(getHandle(), NULL, key, mod);
        }
    }
    
    std::vector<Layer> Gui::paint() const noexcept
    {
        t_eclass* c = getClass();
        std::vector<Layer> objs;
        t_ebox* x = ((t_ebox *)getHandle());
        if(c && c->c_widget.w_paint && x->b_ready_to_draw)
        {
            if(x->b_layers)
            {
                for(int i = 0; i < x->b_number_of_layers; i++)
                {
                    x->b_layers[i].e_state = EGRAPHICS_INVALID;
                }
            }
            c->c_widget.w_paint(m_handle, NULL);
            objs.resize(x->b_number_of_layers);
            for(size_t i = 0; i < objs.size(); i++)
            {
                objs[i] = ((t_ebox *)(m_handle))->b_layers+i;
            }
        }
        
        return objs;
    }
}



