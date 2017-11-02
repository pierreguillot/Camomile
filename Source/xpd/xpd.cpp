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
        vmess(s__X.s_thing, gensym("pop"), "i", 0);
        
        glob_setfilename(0, gensym("_float_array_template"), gensym("."));
        binbuf_text(b, garray_arraytemplatefile, strlen(garray_arraytemplatefile));
        binbuf_eval(b, &pd_canvasmaker, 0, 0);
        garray_arraytemplatecanvas = s__X.s_thing;
        vmess(s__X.s_thing, gensym("pop"), "i", 0);
        
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
        vmess(s__X.s_thing, gensym("pop"), "i", 0);
        
        glob_setfilename(0, &s_, &s_);
        binbuf_free(b);
    }
}

namespace xpd
{
    void environment::initialize() noexcept
    {
        static int initialized = 0;
        if(!initialized)
        {
            assert(PDINSTANCE && "PDINSTANCE undefined");
            assert(PDTHREADS && "PDTHREADS undefined");
            libpd_init();
            initialized = 1;
        }
    }
    
    void environment::clear() noexcept
    {
        ;
    }
    
    // ==================================================================================== //
    //                                      INSTANCE                                        //
    // ==================================================================================== //
    
    instance::instance()
    {
        m_ptr = pdinstance_new();
        garray_init();
        text_template_init();
    }
    
    instance::~instance()
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        pdinstance_free(static_cast<t_pdinstance *>(m_ptr));
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void instance::prepare(const int nins, const int nouts, const int blksize, const double samplerate)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        m_inputs.resize(blksize * nins);
        m_outputs.resize(blksize * nouts);
        libpd_init_audio((int)nins, (int)nouts, (int)samplerate);
        libpd_start_message(1);
        libpd_add_float(1.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void instance::release()
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_start_message(1);
        libpd_add_float(0.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void instance::perform(const int blksize,
                           const int nins, float const** inputs,
                           const int nouts, float** outputs)
    {
        for(int i = 0; i < nins; ++i) {
            for(int j = 0; j < blksize; ++j) {
                m_inputs[j*nins+i] = inputs[i][j];
            }
        }
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_process_float(blksize / 64, m_inputs.data(), m_outputs.data());
        for(int i = 0; i < nouts; ++i) {
            for(int j = 0; j < blksize; ++j) {
                outputs[i][j] = m_outputs[j*nouts+i];
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void instance::sendNoteOn(const int channel, const int pitch, const int velocity)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        garray_init();
        text_template_init();
        libpd_noteon(channel, pitch, velocity);
    }
    
    void instance::sendControlChange(const int channel, const int controller, const int value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_controlchange(channel, controller, value);
    }
    
    void instance::sendProgramChange(const int channel, const int value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_programchange(channel, value);
    }
    
    void instance::sendPitchBend(const int channel, const int value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_pitchbend(channel, value);
    }
    
    void instance::sendAfterTouch(const int channel, const int value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_aftertouch(channel, value);
    }
    
    void instance::sendPolyAfterTouch(const int channel, const int pitch, const int value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_polyaftertouch(channel, pitch, value);
    }
    
    void instance::sendSysEx(const int port, const int byte)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_sysex(port, byte);
    }
    
    void instance::sendSysRealTime(const int port, const int byte)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_sysrealtime(port, byte);
    }
    
    void instance::sendMidiByte(const int port, const int byte)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_midibyte(port, byte);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void instance::sendBang(std::string const& receiver)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_bang(receiver.c_str());
    }
    
    void instance::sendFloat(std::string const& receiver, float const value)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_float(receiver.c_str(), value);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void instance::open(std::string const& path, std::string const& name)
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        m_patch = libpd_openfile(name.c_str(), path.c_str());
    }
    
    void instance::close()
    {
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
        libpd_closefile(m_patch);
    }
}

