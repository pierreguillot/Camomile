/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_WRAPPER__
#define __CAMOMILE_PD_WRAPPER__

#include <string>
#include <array>
#include <vector>
#include <mutex>
#include <tuple>
#include <iostream>
#include <memory>

extern "C"
{
    
#include "m_pd.h"
#include "z_libpd.h"
#include "z_queued.h"
#include "z_print_util.h"
EXTERN  void pd_init(void);
}
#include "../ThirdParty/Cream/c.library.hpp"


namespace mpd
{
    class Instance;
    class Patcher;
    class Object;
    
    typedef std::shared_ptr<Object> sObject;
    typedef std::weak_ptr<Object> wObject;
    
    class Master
    {
    private:
        static std::mutex   s_mutex;
        static int          s_sample_rate;
        
        static void print(const char* s);
        
        //! @brief Initialize Pure Data.
        static void initialize() noexcept;
        
    public:
        
        //! @brief Creates a new instance.
        static t_pdinstance* createInstance() noexcept;
        
        //! @brief Adds a path to the search path.
        static void addToSearchPath(std::string const& path) noexcept
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            sys_searchpath = namelist_append(sys_searchpath, path.c_str(), 0);
        }
        
        
        //! @brief Clears the search the search path.
        static void clearSearchPath() noexcept
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            namelist_free(sys_searchpath);
            sys_searchpath = NULL;
        }
        
        static t_canvas* evalFile(std::string const& name,
                             std::string const& path) noexcept
        {
            if(!name.empty() && path.empty())
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                return reinterpret_cast<t_canvas*>(glob_evalfile(NULL, gensym(name.c_str()), gensym(path.c_str())));
            }
            return nullptr;
        }
        
        static void closePatch(const t_canvas* cnv)
        {
            std::lock_guard<std::mutex> guard(s_mutex);
            canvas_free(const_cast<t_canvas*>(cnv));
        }
    };
    
    
    
    // ==================================================================================== //
    //                                          OBJECT                                      //
    // ==================================================================================== //
    
    //! @brief The camomile counterpart of the t_ebox.
    //! @details This class is a wrapper for GUI object of the cicm wrapper.
    class Object
    {
    private:
        //! @brief The t_ebox pointer.
        void* m_handle;
        
    protected:
        
        inline t_eclass* getClass() const noexcept {
            return bool(m_handle) ? eobj_getclass(m_handle) : nullptr;}
    public:
        
        //! @brief The default constructor.
        inline Object() noexcept : m_handle(nullptr) {}
        
        //! @brief The attribute constructor.
        inline Object(void* handle) noexcept : m_handle(handle) {}
        
        //! @brief Gets the position.
        inline std::tuple<int,int> getPosition() const noexcept {
            return std::make_tuple(getX(), getY());}
        
        //! @brief Gets the abscissa.
        inline int getX() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_xpix);}
        
        //! @brief Gets the ordinate.
        inline int getY() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_ypix);}
        
        //! @brief Gets the size.
        inline virtual std::tuple<int,int> getSize() const noexcept {
            return std::make_tuple(getWidth(), getHeight());}
        
        //! @brief Gets the width.
        inline virtual int getWidth() const noexcept {
            return int(static_cast<t_ebox *>(m_handle)->b_rect.width);}
        
        //! @brief Gets the height.
        inline virtual int getHeight() const noexcept {
            return int(static_cast<t_ebox *>(m_handle)->b_rect.height);}
        
        //! @brief Gets the bounds.
        inline virtual std::tuple<int,int, int, int> getBounds() const noexcept {
            return std::make_tuple(getX(), getY(), getWidth(), getHeight());}
        
        //! @brief Gets the drawing parameters.
        //DrawParameters getDrawParameters() const noexcept;
        
    };
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    class Gui : public Object
    {
        t_ebox* m_handle;
        //! @brief The background color.
        std::array<float, 4> m_background_color;
        //! @brief The border color.
        std::array<float, 4> m_border_color;
        //! @brief The border size.
        int          m_border_size;
        //! @brief The corner roudness.
        int          m_corner_roundness;
    public:
        
        //! @brief The destructor.
        virtual ~Gui() {};
        
        //! @brief Gets if the GUI wants the mouse events.
        bool wantMouse() const noexcept;
        
        //! @brief Gets the GUI wants keyboard events.
        bool wantKeyboard() const noexcept;
        
        //! @brief Gets the width.
        inline int getWidth() const noexcept override {
            return int(m_handle->b_rect.width);}
        
        //! @brief Gets the height.
        inline int getHeight() const noexcept override {
            return int(m_handle->b_rect.height);}
        
        //! @brief Gets the bounds.
        inline std::tuple<int,int, int, int> getBounds() const noexcept override {
            return std::make_tuple(getX(), getY(), getWidth(), getHeight());}
        
        //! @brief Calls the mouse move method.
        void mouseMove(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse enter method.
        void mouseEnter(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse exist method.
        void mouseExit(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse down method.
        void mouseDown(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse drag method.
        void mouseDrag(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse up method.
        void mouseUp(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse double click method.
        void mouseDoubleClick(std::array<float, 2> const& pos, const long mod) noexcept;
        
        //! @brief Calls the mouse wheel method.
        void mouseWheelMove(std::array<float, 2> const& pos, const long mod, std::array<float, 2> const& delta) noexcept;
        
        //! @brief Gets the background color.
        inline std::array<float, 4> getBackgroundColor() const noexcept {return m_background_color;}
        
        //! @brief Gets the border color.
        inline std::array<float, 4> getBorderColor() const noexcept {return m_border_color;}
        
        //! @brief Gets the border size.
        inline int getBorderSize() const noexcept {return m_border_size;}
        
        //! @brief Gets the border size.
        inline int getCornerRoundness() const noexcept {return m_corner_roundness;}
        
        std::tuple<int, t_elayer*> paint() const noexcept;
    };
    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    //! @brief
    //! @details 
    class Patcher
    {
        friend class Instance;
    private:
        const std::string m_name;
        const std::string m_path;
        const t_canvas*   m_cnv;
    
        Patcher(std::string const& name,
                std::string const& path);
        
    public:
        ~Patcher() noexcept;
        
        //! @brief Gets the objects.
         std::vector<sObject> getObjects() const noexcept;
        
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
    private:
        t_pdinstance*       m_instance;
        std::mutex          m_mutex;
        std::vector<std::shared_ptr<Patcher>> m_patcher;
    public:

        inline Instance() noexcept :
        {
            m_instance = pdinstance_new();
        }

        inline ~Instance() noexcept
        {
            if(m_instance)
            {
                pdinstance_free(m_instance);
            }
        }
        
        inline void prepare(const int nins, const int nouts, const int samplerate) noexcept
        {
            if(m_instance)
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                pd_setinstance(m_instance);
                std::lock_guard<std::mutex> guard2(m_mutex);
                
                /*
                int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
                outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
                indev[0] = outdev[0] = DEFAULTAUDIODEV;
                inch[0] = inChans;
                outch[0] = outChans;
                sys_set_audio_settings(1, indev, 1, inch,
                                       1, outdev, 1, outch, sampleRate, -1, 1, DEFDACBLKSIZE);
                sched_set_using_audio(SCHED_AUDIO_CALLBACK);
                sys_reopen_audio();
                 */
            }
        }
        
        inline void process(int ticks, const float* inputs, float* outputs) noexcept
        {
            if(m_instance)
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                pd_setinstance(m_instance);
                std::lock_guard<std::mutex> guard2(m_mutex);
                libpd_process_float(ticks, inputs, outputs);
            }
        }
        
        inline void process(int ticks, const double* inputs, double* outputs) noexcept
        {
            if(m_instance)
            {
                std::lock_guard<std::mutex> guard(s_mutex);
                pd_setinstance(m_instance);
                std::lock_guard<std::mutex> guard2(m_mutex);
                libpd_process_double(ticks, inputs, outputs);
            }
        }
        
        inline void sendBang(t_symbol* dest) noexcept
        {
            if(dest->s_thing && m_instance)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_bang(dest->s_thing);
            }
        }
        
        inline void sendFloat(t_symbol* dest, float val)
        {
            if(dest->s_thing && m_instance)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_float(dest->s_thing, val);
            }
        }
        
        inline void sendSymbol(t_symbol* dest, t_symbol* sym)
        {
            if(dest->s_thing && m_instance)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_symbol(dest->s_thing, sym);
            }
        }
        
        inline void sendList(t_symbol* dest, t_symbol* sym, std::vector<t_atom> atoms)
        {
            if(dest->s_thing && m_instance)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_typedmess(dest->s_thing, sym, int(atoms.size()), atoms.data());
            }
        }
        
        std::shared_ptr<Patcher> openPatch(const std::string& patch, const std::string& path)
        {
            std::shared_ptr<Patcher> patcher;
            try
            {
                patcher = std::shared_ptr<Patcher>(new Patcher(patch.c_str(), path.c_str()));
            }
            catch (std::exception& e)
            {
                throw e;
            }
            m_patcher.push_back(patcher);
            return patcher;
        }
    };
}

#endif
