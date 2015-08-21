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
#include <set>
#include <map>
#include <mutex>
#include <tuple>
#include <iostream>
#include <memory>

#include "../ThirdParty/Cream/c.library.hpp"

// Mieux gérer les layers

namespace pd
{
    class Instance;
    class Patch;
    class Object;
    class Gui;
    class Messenger;
    class Listener;
    
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
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
    class Object
    {
        friend class Patch;
    protected:
        //! @brief The t_ebox pointer.
        void* m_handle;

        //! @brief The constructor.
        Object(void* handle);
    public:
            
        //! @brief The destructor.
        inline virtual ~Object() noexcept {}
        
        //! @brief Checks if the object is CICM.
        inline virtual bool isCicm() const noexcept {return bool(eobj_iscicm(m_handle));}
        
        //! @brief Checks if the object is GUI.
        inline virtual bool isGui() const noexcept {return isCicm() && bool(eobj_isbox(m_handle));}
        
        //! @brief Checks if the object is DSP.
        inline virtual bool isDsp() const noexcept {return isCicm() && bool(eobj_isdsp(m_handle));}
        
        //! @brief Gets the class name of the object.
        inline virtual std::string getName() const noexcept {return std::string(eobj_getclassname(m_handle)->s_name);}
        
        //! @brief Gets the class name of the object.
        inline virtual std::string getBindingName() const noexcept {
            return std::to_string(reinterpret_cast<unsigned long>(m_handle)) + std::string("camo");}
        
        //! @brief Gets the position.
        inline std::array<int,2> getPosition() const noexcept {
            return std::array<int,2>({getX(), getY()});}
        
        //! @brief Gets the abscissa.
        inline int getX() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_xpix);}
        
        //! @brief Gets the ordinate.
        inline int getY() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_ypix);}
        
        //! @brief Gets the size.
        inline virtual std::array<int,2> getSize() const noexcept {
            return std::array<int,2>({getWidth(), getHeight()});}
        
        //! @brief Gets the width.
        inline virtual int getWidth() const noexcept {
            return int(static_cast<t_object *>(m_handle)->te_width);}
        
        //! @brief Gets the height.
        inline virtual int getHeight() const noexcept {return 0;}
        
        //! @brief Gets the bounds.
        inline virtual std::array<int,4> getBounds() const noexcept {
            return std::array<int,4>({getX(), getY(), getWidth(), getHeight()});}
        
    protected:
        
        inline t_eclass* getClass() const noexcept {return (bool(m_handle)) ? (eobj_getclass(m_handle)) : nullptr;}
            
        inline void* getHandle() const noexcept {return m_handle;}
    };
    
    // ==================================================================================== //
    //                                       PATH                                           //
    // ==================================================================================== //
    
    class Gobj
    {
    private:
        t_egobj* obj;
    public:
        
        enum Type
        {
            Invalid = 0,
            Path    = 1,
            Rect    = 2,
            Arc     = 3,
            Oval    = 4,
            Text    = 5
        };
        
        enum Justification
        {
            Left                            = 1,
            Right                           = 2,
            HorizontallyCentred             = 4,
            Top                             = 8,
            Bottom                          = 16,
            VerticallyCentred               = 32,
            horizontallyJustified           = 64,
            Centred                         = 36,
            CentredLeft                     = 33,
            CentredRight                    = 34,
            CentredTop                      = 12,
            CentredBottom                   = 20,
            TopLeft                         = 9,
            TopRight                        = 10,
            BottomLeft                      = 17,
            BottomRight                     = 18
        };
        
        inline constexpr Gobj() noexcept : obj(nullptr) {}
        inline constexpr Gobj(t_egobj* obj) noexcept : obj(obj) {}
        inline Type type() const noexcept {return Type(obj->e_type);}
        inline bool filled() const noexcept {return bool(obj->e_filled);}
        inline int witdh() const noexcept {return int(obj->e_width);}
        inline std::string text() const noexcept {return std::string(obj->e_text->s_name);}
        inline Justification justification() const noexcept {return Justification(obj->e_justify);}
        inline float fontSize() const noexcept {return obj->e_font.c_size;}
        inline bool wrapText() const noexcept {return false;}
        inline std::vector<t_pt> points() const noexcept {
            return std::vector<t_pt>(obj->e_points, obj->e_points+obj->e_npoints);}
        inline std::array<float, 4> color() const noexcept {
            return std::array<float, 4>({obj->e_color.red, obj->e_color.green, obj->e_color.blue, obj->e_color.alpha});
        }
    };
    
    // ==================================================================================== //
    //                                      LAYER                                           //
    // ==================================================================================== //
    
    class Layer
    {
    private:
        t_elayer* layer;
    public:
        
        enum State
        {
            Open    =  0,
            Closed  = -1,
            Invalid = -2,
            Todraw  = -3
        };
        
        inline constexpr Layer() noexcept : layer(nullptr) {}
        inline constexpr Layer(t_elayer* _layer) : layer(_layer) {}
        inline Layer& operator=(t_elayer* _layer) noexcept {layer = _layer; return *this;}
        inline State state() const noexcept {return (layer) ? (State(layer->e_state)) : Invalid;}
        inline size_t size() const noexcept {return size_t(layer->e_number_objects);}
        inline bool empty() const noexcept {return bool(layer->e_number_objects);}
        inline Gobj operator[](size_t index) const noexcept {return Gobj(layer->e_objects+index);}
        inline void close() noexcept {layer->e_state = Closed;}
    };
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    class Gui : public Object
    {
        friend class Patch;
    private:
        //! @brief The background color.
        std::array<float, 4> m_background_color;
        //! @brief The border color.
        std::array<float, 4> m_border_color;
        //! @brief The border size.
        int          m_border_size;
        //! @brief The corner roudness.
        int          m_corner_roundness;
        
        //! @brief The Contructor.
        Gui(void* handle);
    public:
            
        //! @brief The destructor.
        inline virtual ~Gui() {};
        
        //! @brief Gets the preset name.
        bool hasPresetName() const noexcept;
        
        //! @brief Gets the preset name.
        std::string getPresetName() const noexcept;
        
        //! @brief Gets if the GUI wants the mouse events.
        bool wantMouse() const noexcept;
        
        //! @brief Gets the GUI wants keyboard events.
        bool wantKeyboard() const noexcept;
        
        //! @brief Gets the width.
        inline int getWidth() const noexcept override {
            return int(static_cast<t_ebox *>(getHandle())->b_rect.width);}
        
        //! @brief Gets the height.
        inline int getHeight() const noexcept override {
            return int(static_cast<t_ebox *>(getHandle())->b_rect.height);}
        
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
        
        //! @brief Calls the key method.
        void keyPressed(const char key, const long mod) noexcept;
        
        //! @brief Calls the key filter method.
        void keyFilter(const char key, const long mod) noexcept;
        
        //! @brief Gets the background color.
        inline std::array<float, 4> getBackgroundColor() const noexcept {return m_background_color;}
        
        //! @brief Gets the border color.
        inline std::array<float, 4> getBorderColor() const noexcept {return m_border_color;}
        
        //! @brief Gets the border size.
        inline int getBorderSize() const noexcept {return m_border_size;}
        
        //! @brief Gets the border size.
        inline int getCornerRoundness() const noexcept {return m_corner_roundness;}
        
        //! @brief Calls the paint method and return a set of object to paint.
        std::vector<Layer> paint() const noexcept;
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
        std::map<std::string, sMessenger>   m_messengers;
        
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
        
        inline void send(t_symbol* dest) noexcept
        {
            if(dest->s_thing)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_bang(dest->s_thing);
            }
        }
        
        inline void send(t_symbol* dest, float val)
        {
            if(dest->s_thing)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_float(dest->s_thing, val);
            }
        }
        
        inline void send(t_symbol* dest, t_symbol* sym)
        {
            if(dest->s_thing)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_symbol(dest->s_thing, sym);
            }
        }
        
        inline void send(t_symbol* dest, t_symbol* sym, std::vector<t_atom> atoms)
        {
            if(dest->s_thing)
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                pd_typedmess(dest->s_thing, sym, int(atoms.size()), atoms.data());
            }
        }
        
        sPatch openPatch(const std::string& name, const std::string& path);
        
        void closePatch(sPatch patch);
    };
    
    // ==================================================================================== //
    //                                      MESSENGER                                       //
    // ==================================================================================== //
    
    class Messenger
    {
    private:        
        void*                       m_internal;
        std::string                 m_symbol;
        std::set<pd::Listener*>     m_listeners;
        mutable std::mutex          m_mutex;
        std::vector<pd::Listener*>  getListeners() const noexcept;
        
    public:
        Messenger(std::string const& name);
        ~Messenger();
        void addListener(pd::Listener* listener);
        void removeListener(pd::Listener* listener);
        
        void receiveBang();
        void receiveFloat(float num);
        void receiveSymbol(t_symbol* s);
        void receiveList(std::vector<const t_atom *> atoms);
        void receiveAnything(t_symbol* s, std::vector<const t_atom *> atoms);
        
    };
    
    // ==================================================================================== //
    //                                      MESSENGER                                       //
    // ==================================================================================== //
    
    class Listener
    {
    public:
        virtual ~Listener() {};
        virtual void receive(const std::string& dest) {}
        virtual void receive(const std::string& dest, float num) {}
        virtual void receive(const std::string& dest, t_symbol* s) {}
        virtual void receive(const std::string& dest, std::vector<const t_atom *> atoms) {}
        virtual void receive(const std::string& dest, t_symbol* s, std::vector<const t_atom *> atoms) {}
    };
}

#endif
