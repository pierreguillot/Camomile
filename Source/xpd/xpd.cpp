/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */


#include "xpd.h"
#include <cassert>
#include <algorithm>

extern "C"
{
    #include <z_libpd.h>
    #include <m_pd.h>
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    // For declare object multi instance support
    
    static t_pd *garray_arraytemplatecanvas;  /* written at setup w/ global lock */
    static const char garray_arraytemplatefile[] = "\
    canvas 0 0 458 153 10;\n\
    #X obj 43 31 struct float-array array z float float style\n\
    float linewidth float color;\n\
    #X obj 43 70 plot z color linewidth 0 0 1 style;\n\
    ";
    static const char garray_floattemplatefile[] = "\
    canvas 0 0 458 153 10;\n\
    #X obj 39 26 struct float float y;\n\
    ";
    
    /* create invisible, built-in canvases to supply templates for floats
     and float-arrays. */
    
    static void garray_init(void)
    {
        t_binbuf *b;
        if (garray_arraytemplatecanvas)
            return;
        b = binbuf_new();
        
        glob_setfilename(0, gensym("_float_template"), gensym("."));
        binbuf_text(b, garray_floattemplatefile, strlen(garray_floattemplatefile));
        binbuf_eval(b, &pd_canvasmaker, 0, 0);
        vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
        
        glob_setfilename(0, gensym("_float_array_template"), gensym("."));
        binbuf_text(b, garray_arraytemplatefile, strlen(garray_arraytemplatefile));
        binbuf_eval(b, &pd_canvasmaker, 0, 0);
        garray_arraytemplatecanvas = s__X.s_thing;
        vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
        
        glob_setfilename(0, &s_, &s_);
        binbuf_free(b);
    }
    
    static t_pd *text_templatecanvas;
    static char text_templatefile[] = "\
    canvas 0 0 458 153 10;\n\
    #X obj 43 31 struct text float x float y text t;\n\
    ";
    
    /* create invisible, built-in canvas to supply template containing one text
     field named 't'.  I don't know how to make this not break
     pre-0.45 patches using templates named 'text'... perhaps this is a minor
     enough incompatibility that I'll just get away with it. */
    
    static void text_template_init(void)
    {
        t_binbuf *b;
        if (text_templatecanvas)
            return;
        b = binbuf_new();
        
        glob_setfilename(0, gensym("_text_template"), gensym("."));
        binbuf_text(b, text_templatefile, strlen(text_templatefile));
        binbuf_eval(b, &pd_canvasmaker, 0, 0);
        vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
        
        glob_setfilename(0, &s_, &s_);
        binbuf_free(b);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    static t_class *libpd_multirec_class;
    
    typedef struct pd::instance::_libpd_multirec
    {
    public:
        t_object        x_obj;
        t_symbol*       x_sym;
        std::string     x_recv;
        pd::instance*  x_instance;
        
        static void libpd_multirec_bang(struct pd::instance::_libpd_multirec *x)
        {
            std::vector<Atom> vec;
            std::lock_guard<std::mutex> lock(x->x_instance->m_messages_mutex);
            x->x_instance->m_messages.push({x->x_recv, std::string("bang"), vec});
        }
        
        static void libpd_multirec_float(struct pd::instance::_libpd_multirec *x, t_float f) {
            std::vector<Atom> vec(1, f);
            std::lock_guard<std::mutex> lock(x->x_instance->m_messages_mutex);
            x->x_instance->m_messages.push({x->x_recv, std::string("float"), vec});
        }
        
        static void libpd_multirec_symbol(struct pd::instance::_libpd_multirec *x, t_symbol *s) {
            std::vector<Atom> vec(1, std::string(s->s_name));
            std::lock_guard<std::mutex> lock(x->x_instance->m_messages_mutex);
            x->x_instance->m_messages.push({x->x_recv, std::string("symbol"), vec});
        }
        
        static void libpd_multirec_list(struct pd::instance::_libpd_multirec *x, t_symbol *s, int argc, t_atom *argv) {
            std::vector<Atom> vec;
            for(int i = 0; i < argc; ++i)
            {
                if(argv[i].a_type == A_FLOAT)
                    vec.push_back(Atom(atom_getfloat(argv+i)));
                else if(argv[i].a_type == A_SYMBOL)
                    vec.push_back(Atom(std::string(atom_getsymbol(argv+i)->s_name)));
                else
                    vec.push_back(Atom());
            }
            std::lock_guard<std::mutex> lock(x->x_instance->m_messages_mutex);
            x->x_instance->m_messages.push({x->x_recv, std::string("list"), vec});
        }
        
        static void libpd_multirec_anything(struct pd::instance::_libpd_multirec *x, t_symbol *s, int argc, t_atom *argv) {
            std::vector<Atom> vec;
            std::string const sel(s->s_name);
            for(int i = 0; i < argc; ++i)
            {
                if(argv[i].a_type == A_FLOAT)
                    vec.push_back(Atom(atom_getfloat(argv+i)));
                else if(argv[i].a_type == A_SYMBOL)
                    vec.push_back(Atom(std::string(atom_getsymbol(argv+i)->s_name)));
                else
                    vec.push_back(Atom());
            }
            std::lock_guard<std::mutex> lock(x->x_instance->m_messages_mutex);
            x->x_instance->m_messages.push({x->x_recv, sel, vec});
        }
        
    } t_libpd_multirec;
    
    static void libpdmultireceive_free(t_libpd_multirec *x) {
        pd_unbind(&x->x_obj.ob_pd, x->x_sym);
    }
    
    static void *libpd_multirec_new(t_symbol *s, pd::instance* instance) {
        t_libpd_multirec *x = NULL;
        sys_lock();
        x = (t_libpd_multirec *)pd_new(libpd_multirec_class);
        if(x)
        {
            x->x_sym = s;
            x->x_recv = std::string(s->s_name);
            x->x_instance = instance;
            pd_bind(&x->x_obj.ob_pd, s);
        }
        sys_unlock();
        return x;
    }
    
    static void libpd_multirec_setup(void) {
        sys_lock();
        libpd_multirec_class = class_new(gensym("libpd_multireceive"), (t_newmethod)NULL, (t_method)libpdmultireceive_free,
                                         sizeof(t_libpd_multirec), CLASS_DEFAULT, A_DEFSYM, 0);
        class_addbang(libpd_multirec_class, t_libpd_multirec::libpd_multirec_bang);
        class_addfloat(libpd_multirec_class,t_libpd_multirec::libpd_multirec_float);
        class_addsymbol(libpd_multirec_class, t_libpd_multirec::libpd_multirec_symbol);
        //class_addpointer(libpd_multirec_class, libpd_multirec_pointer);
        class_addlist(libpd_multirec_class, t_libpd_multirec::libpd_multirec_list);
        class_addanything(libpd_multirec_class, t_libpd_multirec::libpd_multirec_anything);
        sys_unlock();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    static void libpd_multi_midisend(const char* receiver, const char* msg, int argc, t_atom* argv)
    {
        // Avoid thread concurrency. If this function is called, it must be in the right thread.
        t_symbol *sym = gensym(receiver);
        if(sym->s_thing)
        {
            pd_typedmess(sym->s_thing, gensym(msg), argc, argv);
        }
    }
    
    static void libpd_multi_noteon(int channel, int pitch, int velocity)
    {
        t_atom av[3];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)pitch);
        SETFLOAT(av+2, (float)velocity);
        libpd_multi_midisend("camomile", "#noteout", 3, av);
    }
    
    static void libpd_multi_controlchange(int channel, int controller, int value)
    {
        t_atom av[3];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)controller);
        SETFLOAT(av+2, (float)value);
        libpd_multi_midisend("camomile", "#controlchange", 3, av);
    }
    
    static void libpd_multi_programchange(int channel, int value)
    {
        t_atom av[2];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)value);
        libpd_multi_midisend("camomile", "#programchange", 2, av);
    }
    
    static void libpd_multi_pitchbend(int channel, int value)
    {
        t_atom av[2];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)value);
        libpd_multi_midisend("camomile", "#pitchbend", 2, av);
    }
    
    static void libpd_multi_aftertouch(int channel, int value)
    {
        t_atom av[2];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)value);
        libpd_multi_midisend("camomile", "#aftertouch", 2, av);
    }
    
    static void libpd_multi_polyaftertouch(int channel, int pitch, int value)
    {
        t_atom av[3];
        SETFLOAT(av, (float)channel);
        SETFLOAT(av+1, (float)pitch);
        SETFLOAT(av+2, (float)value);
        libpd_multi_midisend("camomile", "#polyaftertouch", 3, av);
    }
}

namespace pd
{
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    instance::instance()
    {
        static int initialized = 0;
        if(!initialized)
        {
            assert(PDINSTANCE && "PDINSTANCE undefined");
            assert(PDTHREADS && "PDTHREADS undefined");
            libpd_init();
            libpd_multirec_setup();
            initialized = 1;
            
            libpd_set_noteonhook(libpd_multi_noteon);
            libpd_set_controlchangehook(libpd_multi_controlchange);
            libpd_set_programchangehook(libpd_multi_programchange);
            libpd_set_pitchbendhook(libpd_multi_pitchbend);
            libpd_set_aftertouchhook(libpd_multi_aftertouch);
            libpd_set_polyaftertouchhook(libpd_multi_polyaftertouch);
        }
        
        m_instance = libpd_new_instance();
        garray_init();
        text_template_init();
    }
    
    instance::~instance()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_free_instance(static_cast<t_pdinstance *>(m_instance));
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void instance::prepareDSP(const int nins, const int nouts, const int blksize, const double samplerate)
    {
        m_inputs.resize(blksize * nins);
        m_outputs.resize(blksize * nouts);
        
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_init_audio((int)nins, (int)nouts, (int)samplerate);
        libpd_start_message(1);
        libpd_add_float(1.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void instance::releaseDSP()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_start_message(1);
        libpd_add_float(0.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void instance::performDSP(const int blksize,
                           const int nins, float const** inputs,
                           const int nouts, float** outputs)
    {
        for(int i = 0; i < nins; ++i)
        {
            for(int j = 0; j < blksize; ++j)
            {
                m_inputs[j*nins+i] = inputs[i][j];
            }
        }
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_process_float(blksize / 64, m_inputs.data(), m_outputs.data());
        for(int i = 0; i < nouts; ++i)
        {
            for(int j = 0; j < blksize; ++j)
            {
                outputs[i][j] = m_outputs[j*nouts+i];
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void instance::sendNoteOn(const int channel, const int pitch, const int velocity) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_noteon(channel, pitch, velocity);
    }
    
    void instance::sendControlChange(const int channel, const int controller, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_controlchange(channel, controller, value);
    }
    
    void instance::sendProgramChange(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_programchange(channel, value);
    }
    
    void instance::sendPitchBend(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_pitchbend(channel, value);
    }
    
    void instance::sendAfterTouch(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_aftertouch(channel, value);
    }
    
    void instance::sendPolyAfterTouch(const int channel, const int pitch, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_polyaftertouch(channel, pitch, value);
    }
    
    void instance::sendSysEx(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_sysex(port, byte);
    }
    
    void instance::sendSysRealTime(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_sysrealtime(port, byte);
    }
    
    void instance::sendMidiByte(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_midibyte(port, byte);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void instance::sendBang(std::string const& receiver) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_bang(receiver.c_str());
    }
    
    void instance::sendFloat(std::string const& receiver, float const value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_float(receiver.c_str(), value);
    }
    
    void instance::sendSymbol(std::string const& receiver, std::string const& symbol) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_symbol(receiver.c_str(), symbol.c_str());
    }
    
    void instance::sendList(std::string const& receiver, const std::vector<Atom>& list) const
    {
        t_atom* argv = (t_atom *)getbytes(sizeof(t_atom) * list.size());
        if(argv)
        {
            libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
            for(size_t i = 0; i < list.size(); ++i)
            {
                if(list[i].isFloat())
                    libpd_set_float(argv+i, list[i].getFloat());
                else
                    libpd_set_symbol(argv+i, list[i].getSymbol().c_str());
            }
            libpd_list(receiver.c_str(), (int)list.size(), argv);
            freebytes(argv, sizeof(t_atom) * list.size());
        }
    }
    
    void instance::sendMessage(std::string const& receiver, const std::string& msg, const std::vector<Atom>& list) const
    {
        t_atom* argv = (t_atom *)getbytes(sizeof(t_atom) * list.size());
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        for(size_t i = 0; i < list.size(); ++i)
        {
            if(list[i].isFloat())
                libpd_set_float(argv+i, list[i].getFloat());
            else
                libpd_set_symbol(argv+i, list[i].getSymbol().c_str());
        }
        libpd_message(receiver.c_str(), msg.c_str(), (int)list.size(), argv);
        freebytes(argv, sizeof(t_atom) * list.size());
    }
    
    void instance::processReceive()
    {
        std::lock_guard<std::mutex> lock(m_messages_mutex);
        while (!m_messages.empty())
        {
            message const& mess = m_messages.front();
            if(mess.selector == std::string("bang"))
            {
                receiveBang(mess.destination);
            }
            else if(mess.selector == std::string("float"))
            {
                receiveFloat(mess.destination, mess.list[0].getFloat());
            }
            else if(mess.selector == std::string("symbol"))
            {
                receiveSymbol(mess.destination, mess.list[0].getSymbol());
            }
            else if(mess.selector == std::string("list"))
            {
                receiveList(mess.destination, mess.list);
            }
            else
            {
                receiveMessage(mess.destination, mess.selector, mess.list);
            }
            m_messages.pop();
        }
        
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void instance::bind(std::string const& symbol)
    {
        t_symbol *s;
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        sys_lock();
        s = gensym(symbol.c_str());
        sys_unlock();
        m_receivers.push_back(libpd_multirec_new(s, this));
    }
    
    void instance::unbind(std::string const& symbol)
    {
        for(size_t i = 0; i < m_receivers.size(); ++i)
        {
            std::string name = static_cast<t_libpd_multirec *>(m_receivers[i])->x_sym->s_name;
            if(name == symbol)
            {
                sys_lock();
                pd_free((t_pd *)m_receivers[i]);
                sys_unlock();
                m_receivers.erase(m_receivers.begin()+i);
                return;
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void instance::open(std::string const& path, std::string const& name)
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        m_patch = libpd_openfile(name.c_str(), path.c_str());
    }
    
    void instance::close()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_closefile(m_patch);
    }
}

