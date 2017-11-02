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
}

/*
static void* libpd_instance_doclose(t_libpd_instance* inst)
{
    pd_setinstance(inst->l_pd);
    assert(inst->l_patch && "patch not loaded so can't be closed");
    libpd_closefile(inst->l_patch);
    return NULL;
}

static void libpd_instance_close(t_libpd_instance* inst)
{
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_doclose, inst) &&
           "libpd_instance_close thread creation error.");
    pthread_join(inst->l_thd, NULL);
    inst->l_patch = NULL;
}

static void* libpd_instance_doopen(t_libpd_instance* inst)
{
    pd_setinstance(inst->l_pd);
    assert((inst->l_patch = libpd_openfile(inst->l_name, inst->l_folder)) &&
           "patch can't be loaded");
    return NULL;
}

static void libpd_instance_open(t_libpd_instance* inst, const char *name, const char *folder)
{
    if(inst->l_patch) {
        libpd_instance_close(inst); }
    strncpy(inst->l_name, name, MAXPDSTRING);
    strncpy(inst->l_folder, folder, MAXPDSTRING);
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_doopen, inst) &&
           "libpd_instance_open thread creation error.");
    pthread_join(inst->l_thd, NULL);
}

static void* multi_instance_run(t_libpd_instance* inst)
{
    size_t i;
    libpd_instance_init(inst, 256, 44100, 2, 2);
    libpd_instance_open(inst, LIBPD_TEST_PATCH_NAME, test_path);
    libpd_instance_dsp_start(inst);
    for(i = 0; i < LIBPD_TEST_NLOOPS; ++i) {
        libpd_instance_perform(inst); }
    libpd_instance_dsp_stop(inst);
    libpd_instance_close(inst);
    
    libpd_instance_free(inst);
    return NULL;
}
*/


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
        pd_setinstance(static_cast<t_pdinstance *>(m_ptr));
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

