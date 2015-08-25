/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_WRAPPER__
#define __CAMOMILE_PD_WRAPPER__

#include "PdMessenger.h"
#include "pdWidget.h"
#include "PdObject.h"
#include "PdGui.h"

namespace pd
{
    class Instance;
    class Patch;
    class Object;
    class Gui;
    class Messenger;
    class Listener;
    class TextEditor;
    
    typedef std::shared_ptr<Instance>       sInstance;
    typedef std::weak_ptr<Instance>         wInstance;
    typedef std::shared_ptr<const Instance> scInstance;
    typedef std::weak_ptr<const Instance>   wcInstance;
    
    typedef std::shared_ptr<Patch>          sPatch;
    typedef std::weak_ptr<Patch>            wPatch;
    typedef std::shared_ptr<const Patch>    scPatch;
    typedef std::weak_ptr<const Patch>      wcPatch;
    typedef std::shared_ptr<Object>         sObject;
    typedef std::weak_ptr<Object>           wObject;
    typedef std::shared_ptr<Gui>            sGui;
    typedef std::weak_ptr<Gui>              wGui;
    typedef std::shared_ptr<Messenger>      sMessenger;
    typedef std::weak_ptr<Messenger>        wMessenger;
    typedef std::shared_ptr<Messenger>      sListener;
    typedef std::weak_ptr<Messenger>        wListener;
    
    class Master
    {
        friend class Instance;
    private:
        static std::mutex   s_mutex;
        static int          s_sample_rate;
        static const int    s_max_channels = 16;
        
        static void print(const char* s);
        
        static t_canvas* openPatch(t_pdinstance* instance, std::string const& name, std::string const& path);
        
        static void closePatch(t_pdinstance* instance, const t_canvas* cnv);
        
        static void prepareDsp(t_pdinstance* instance,
                               const int samplerate,
                               int nsamples) noexcept;
        
        static void processDsp(t_pdinstance* instance,
                               int nsamples,
                               const int nins,
                               const float** inputs,
                               const int nouts,
                               float** output) noexcept;
    public:
        
        //! @brief Creates a new instance.
        static sInstance createInstance();
        
        //! @brief Close an instance.
        static void closeInstance(sInstance instance);
        
        //! @brief Adds a path to the search path.
        static void addToSearchPath(std::string const& path) noexcept;
        
        
        //! @brief Clears the search the search path.
        static void clearSearchPath() noexcept;
    };
    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    //! @brief
    //! @details 
    class Patch
    {
        friend class Instance;
    private:
        t_canvas*         m_cnv;
        const std::string m_name;
        const std::string m_path;
        std::vector<sObject> m_objects;
        
        Patch(t_canvas* cnv,
                std::string const& name,
                std::string const& path);
        
    public:
        ~Patch() noexcept {};
        
        //! @brief Gets the objects.
        std::vector<sObject> getObjects() const noexcept;
        
        //! @brief Gets the Guis.
        std::vector<sGui> getGuis() const noexcept;
        
        //! @brief Gets the camomile object.
        sGui getCamomile() const noexcept;
        
        //! @brief Gets the file's name.
        inline std::string getName() const {return m_name;}
        
        //! @brief Gets the file's path.
        inline std::string getPath() const {return m_path;}
    };
    
    
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The CPP wrapper for pd's instance.
    class Instance
    {
        friend class Master;
    private:
        t_pdinstance*                       m_instance;
        std::mutex                          m_mutex;
        std::set<sPatch>                    m_patcher;
        Instance(t_pdinstance* instance);
    public:
        
        ~Instance() noexcept;
        
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        
        inline void processDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            Master::processDsp(m_instance, nsamples, nins, inputs, nouts, outputs);
        }
        
        void releaseDsp() noexcept;
        
        sPatch openPatch(const std::string& name, const std::string& path);
        
        void closePatch(sPatch patch);
    };
}

#endif
