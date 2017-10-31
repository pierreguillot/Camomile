/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */


#include "xpd.h"
#include <cassert>
extern "C"
{
    #include <z_libpd.h>
}

/*
typedef struct l_instance
{
    t_pdinstance*       l_pd;
    size_t              l_blocksize;
    size_t              l_samplerate;
    size_t              l_ninputs;
    t_sample*           l_inputs;
    size_t              l_noutputs;
    t_sample*           l_outputs;
    char                l_name[MAXPDSTRING];
    char                l_folder[MAXPDSTRING];
    void*               l_patch;
    
    pthread_t           l_thd;
} t_libpd_instance;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static void* libpd_instance_dofree(t_libpd_instance* inst)
{
    pd_setinstance(inst->l_pd);
    if(inst->l_pd) {
        pdinstance_free(inst->l_pd); }
    return NULL;
}

static void libpd_instance_free(t_libpd_instance* inst)
{
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_dofree, inst) &&
           "thread creation error.");
    pthread_join(inst->l_thd, NULL);
    if(inst->l_inputs)
    {
        free(inst->l_inputs);
        inst->l_inputs = NULL;
        inst->l_ninputs = 0;
    }
    if(inst->l_outputs)
    {
        free(inst->l_outputs);
        inst->l_outputs = NULL;
        inst->l_noutputs = 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static void* libpd_instance_dodsp_start(t_libpd_instance* inst)
{
    pd_setinstance(inst->l_pd);
    libpd_start_message(1);
    libpd_add_float(1.f);
    libpd_finish_message("pd", "dsp");
    return NULL;
}

static void libpd_instance_dsp_start(t_libpd_instance* inst)
{
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_dodsp_start, inst) &&
           "libpd_instance_dsp_start thread creation error.");
    pthread_join(inst->l_thd, NULL);
}

static void* libpd_instance_dodsp_stop(t_libpd_instance* inst)
{
    pd_setinstance(inst->l_pd);
    libpd_start_message(1);
    libpd_add_float(0.f);
    libpd_finish_message("pd", "dsp");
    return NULL;
}

static void libpd_instance_dsp_stop(t_libpd_instance* inst)
{
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_dodsp_stop, inst) &&
           "libpd_instance_dsp_stop thread creation error.");
    pthread_join(inst->l_thd, NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static void* libpd_instance_doperform(t_libpd_instance* inst)
{
    size_t i;
    pd_setinstance(inst->l_pd);
    libpd_process_float((int)(inst->l_blocksize / (size_t)64), inst->l_inputs, inst->l_outputs);
    for(i = 0; i < inst->l_blocksize; ++i) {
        int result   = (int)inst->l_outputs[i];
        int expected = i%2 ? ((i-1)/2)%64 * -1 : (i/2)%64;
        assert(result == expected && "DSP results are wrong"); }
    return NULL;
}

static void libpd_instance_perform(t_libpd_instance* inst)
{
    assert(!pthread_create(&inst->l_thd, NULL, (void *)libpd_instance_doperform, inst) &&
           "libpd_instance_perform thread creation error.");
    pthread_join(inst->l_thd, NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

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
}

