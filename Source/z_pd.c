/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// This part of the code is greatly inspired by Pure Data and libPD, and sometimes
// directly copied. None of the authors of Pure Data and libPD is responsible for these
// experiments but you must be aware of their unintended contribution.

#include "z_pd.h"
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
#include "../ThirdParty/PureData/src/g_all_guis.h"


EXTERN void pd_init(void);

void bob_tilde_setup();
void bonk_tilde_setup();
void choice_setup();
void fiddle_tilde_setup();
void loop_tilde_setup();
void lrshift_tilde_setup();
void pique_setup();
void sigmund_tilde_setup();
void stdout_setup();

void sys_get_midi_apis(char *buf) {}
void sys_listmididevs(void) {}
void sys_get_midi_params(int *pnmidiindev, int *pmidiindev,int *pnmidioutdev, int *pmidioutdev) {}
void sys_open_midi(int nmidiindev, int *midiindev, int nmidioutdev, int *midioutdev, int enable) {}
void sys_close_midi() {}
void sys_reopen_midi(void) {}
void sys_initmidiqueue(void) {}
void sys_pollmidiqueue(void) {}
void sys_setmiditimediff(double inbuftime, double outbuftime) {}
void glob_midi_setapi(void *dummy, t_floatarg f) {}
void glob_midi_properties(t_pd *dummy, t_floatarg flongform) {}
void glob_midi_dialog(t_pd *dummy, t_symbol *s, int argc, t_atom *argv) {}
int sys_mididevnametonumber(int output, const char *name) { return 0; }
void sys_mididevnumbertoname(int output, int devno, char *name, int namesize) {}

static t_class *z_receiver_class;

typedef struct _receiver
{
    t_object            z_obj;
    struct _instance*   z_owner;
    t_symbol*           z_sym;
    z_hook_bang         z_m_bang;
    z_hook_float        z_m_float;
    z_hook_symbol       z_m_symbol;
    z_hook_gpointer     z_m_gpointer;
    z_hook_list         z_m_list;
    z_hook_anything     z_m_anything;
    struct _receiver* z_next;
} z_receiver;

static void receiver_bang(z_receiver *x)
{
    if(x->z_m_bang)
    {
        x->z_m_bang(x->z_owner, x->z_sym);
    }
}

static void receiver_float(z_receiver *x, t_float f)
{
    if(x->z_m_float)
    {
        x->z_m_float(x->z_owner, x->z_sym, f);
    }
}

static void receiver_symbol(z_receiver *x, t_symbol *s)
{
    if(x->z_m_symbol)
    {
        x->z_m_symbol(x->z_owner, x->z_sym, s);
    }
}

static void receiver_pointer(z_receiver *x, t_gpointer *gp)
{
    if(x->z_m_gpointer)
    {
        x->z_m_gpointer(x->z_owner, x->z_sym, gp);
    }
}

typedef struct _zinbuf
{
    int b_n;
    t_atom *b_vec;
}t_zinbuf;

static void receiver_list(z_receiver *x, t_symbol *s, int argc, t_atom *argv)
{
    int ugly;
    if(x->z_m_list)
    {
        t_zinbuf b;
        b.b_n = argc;
        b.b_vec = argv;
        x->z_m_list(x->z_owner, x->z_sym, (t_binbuf *)&b);
    }
}

static void receiver_anything(z_receiver *x, t_symbol *s, int argc, t_atom *argv)
{
    int ugly;
    if(x->z_m_anything)
    {
        t_zinbuf b;
        b.b_n = argc;
        b.b_vec = argv;
        x->z_m_anything(x->z_owner, x->z_sym, s, (t_binbuf *)&b);
    }
}

static void receiver_free(z_receiver *x)
{
    pd_unbind((t_pd *)x, x->z_sym);
}

void receiver_setup(void)
{
    t_class* c = class_new(gensym("z_receiver"),
                           (t_newmethod)NULL,
                           (t_method)receiver_free,
                           sizeof(z_receiver), CLASS_PD, A_DEFSYM, 0);
    if(c)
    {
        class_addbang(c, receiver_bang);
        class_addfloat(c, receiver_float);
        class_addsymbol(c, receiver_symbol);
        class_addpointer(c, receiver_pointer);
        class_addlist(c, receiver_list);
        class_addanything(c, receiver_anything);
    }
    z_receiver_class = c;
}





struct _internal
{
    t_pdinstance*           z_intance;
    t_sample*               z_inputs;
    t_sample*               z_outputs;
    int                     z_ninputs;
    int                     z_noutputs;
    int                     z_samplerate;
    z_hook_print            z_m_print;
    z_hook_noteon           z_m_noteon;
    z_hook_controlchange    z_m_controlchange;
    z_hook_programchange    z_m_programchange;
    z_hook_pitchbend        z_m_pitchbend;
    z_hook_aftertouch       z_m_aftertouch;
    z_hook_polyaftertouch   z_m_polyaftertouch;
    z_hook_byte             z_m_byte;
    z_receiver*             z_receiver_list;
};

static t_sample*        z_sample_ins        = NULL;
static t_sample*        z_sample_outs       = NULL;
static t_pdinstance*    z_first_instance    = NULL;
static z_instance*      z_current_instance  = NULL;
static t_symbol*        z_sym_pd            = NULL;
static t_symbol*        z_sym_dsp           = NULL;
static z_symbol*        z_sym_hsl           = NULL;
static z_symbol*        z_sym_vsl           = NULL;
static z_symbol*        z_sym_tgl           = NULL;
static z_symbol*        z_sym_nbx           = NULL;
static z_symbol*        z_sym_vradio        = NULL;
static z_symbol*        z_sym_hradio        = NULL;

static void z_pd_print(const char* s);

void z_pd_init()
{
    int devices = 0;
    int ioputs  = 2;
    static char initialized = 0;
    if(!initialized)
    {
        signal(SIGFPE, SIG_IGN);
        sys_printhook = NULL;
        sys_soundin = NULL;
        sys_soundout = NULL;
        sys_schedblocksize = DEFDACBLKSIZE;
        sys_externalschedlib = 0;
        sys_printtostderr = 0;
        sys_usestdpath = 0;
        sys_debuglevel = 1;
        sys_verbose = 4;
        sys_noloadbang = 0;
        sys_nogui = 1;
        sys_hipriority = 0;
        sys_nmidiin = 0;
        sys_nmidiout = 0;
        sys_init_fdpoll();
        pd_init();
        sys_set_audio_api(API_DUMMY);
        sys_searchpath = NULL;
        sys_set_audio_settings(1, &devices, 1, &ioputs, 1, &devices, 1, &ioputs, 44100, -1, 1, DEFDACBLKSIZE);
        sched_set_using_audio(SCHED_AUDIO_CALLBACK);
        sys_reopen_audio();
        z_sample_ins    = sys_soundin;
        z_sample_outs   = sys_soundout;
        z_first_instance= pd_this;
        sys_soundin         = NULL;
        sys_soundout        = NULL;
        z_current_instance  = NULL;
     
        z_sym_pd            = gensym("pd");
        z_sym_dsp           = gensym("dsp");
        z_sym_hsl           = gensym("hsl");
        z_sym_vsl           = gensym("vsl");
        z_sym_tgl           = gensym("tgl");
        z_sym_nbx           = gensym("nbx");
        z_sym_vradio        = gensym("vradio");
        z_sym_hradio        = gensym("hradio");
        
        bob_tilde_setup();
        bonk_tilde_setup();
        choice_setup();
        fiddle_tilde_setup();
        loop_tilde_setup();
        lrshift_tilde_setup();
        pique_setup();
        sigmund_tilde_setup();
        stdout_setup();
        receiver_setup();
        
        sys_printhook = (t_printhook)(z_pd_print);
        initialized = 1;
    }
    else
    {
        pd_error(NULL, "Pure Data is already initialized.");
    }
}

void z_pd_clear()
{
    if(z_sample_ins)
    {
        freebytes(z_sample_ins, (sys_inchannels ? sys_inchannels : 2) * (DEFDACBLKSIZE * sizeof(t_sample)));
    }
    if(z_sample_outs)
    {
        freebytes(z_sample_outs, (sys_outchannels ? sys_outchannels : 2) * (DEFDACBLKSIZE * sizeof(t_sample)));
    }
    if(z_first_instance)
    {
        pdinstance_free(z_first_instance);
    }
}




unsigned int z_pd_version_getmajor()
{
    return PD_MAJOR_VERSION;
}

unsigned int z_pd_version_getminor()
{
    return PD_MINOR_VERSION;
}

unsigned int z_pd_version_getbug()
{
    return PD_BUGFIX_VERSION;
}





void z_pd_searchpath_clear()
{
    namelist_free(sys_searchpath);
    sys_searchpath = NULL;
}

void z_pd_searchpath_add(const char* path)
{
    sys_searchpath = namelist_append(sys_searchpath, path, 0);
}




void z_pd_console_fatal(char const* message)
{
    verbose(-3, "%s", message);
}

void z_pd_console_error(char const* message)
{
    verbose(-2, "%s", message);
}

void z_pd_console_post(char const* message)
{
    verbose(-1, "%s", message);
}

void z_pd_console_log(char const* message)
{
    verbose(0, "%s", message);
}








static void z_pd_print(const char* s)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_print)
    {
        z_current_instance->z_internal_ptr->z_m_print(z_current_instance, s);
    }
#ifdef DEBUG
    printf("%s", s);
#endif
}


z_instance* z_pd_instance_new(size_t size,
                              z_hook_print mprint,
                              z_hook_noteon mnoteon,
                              z_hook_controlchange mcontrolchange,
                              z_hook_programchange mprogramchange,
                              z_hook_pitchbend mpitchbend,
                              z_hook_aftertouch maftertouch,
                              z_hook_polyaftertouch mpolyaftertouch,
                              z_hook_byte mbyte)
{
    z_instance* instance = NULL;
    z_internal* internal = (z_internal *)malloc(sizeof(z_internal));
    if(internal)
    {
        internal->z_inputs      = NULL;
        internal->z_outputs     = NULL;
        internal->z_samplerate  = 0;
        internal->z_ninputs     = 0;
        internal->z_noutputs    = 0;
        
        
        internal->z_m_print = mprint;
        internal->z_m_noteon = mnoteon;
        internal->z_m_controlchange = mcontrolchange;
        internal->z_m_programchange = mprogramchange;
        internal->z_m_pitchbend = mpitchbend;
        internal->z_m_aftertouch = maftertouch;
        internal->z_m_polyaftertouch = mpolyaftertouch;
        internal->z_m_byte = mbyte;
        
        internal->z_receiver_list = NULL;
        internal->z_intance = pdinstance_new();
        if(!internal->z_intance)
        {
            free(internal);
            return NULL;
        }
        instance = malloc(size);
        if(instance)
        {
            instance->z_internal_ptr = internal;
        }
    }
    return instance;
}

void z_pd_instance_free(z_instance* instance)
{
    z_receiver* next = NULL;
    if(z_current_instance == instance)
    {
        z_current_instance = NULL;
    }
    while(instance->z_internal_ptr->z_receiver_list)
    {
        next = instance->z_internal_ptr->z_receiver_list->z_next;
        pd_free((t_pd *)instance->z_internal_ptr->z_receiver_list);
        instance->z_internal_ptr->z_receiver_list = next;
    }
    pdinstance_free(instance->z_internal_ptr->z_intance);
    instance->z_internal_ptr->z_intance = NULL;
    free(instance->z_internal_ptr);
    instance->z_internal_ptr = NULL;
    free(instance);
}

void z_pd_instance_set(z_instance* instance)
{
    pd_setinstance(instance->z_internal_ptr->z_intance);
    sys_soundin     = instance->z_internal_ptr->z_inputs;
    sys_soundout    = instance->z_internal_ptr->z_outputs;
    sys_inchannels  = instance->z_internal_ptr->z_ninputs;
    sys_outchannels = instance->z_internal_ptr->z_noutputs;
    sys_dacsr       = instance->z_internal_ptr->z_samplerate;
    z_current_instance = instance;
}

static z_receiver* z_pd_instance_getreceiver(z_instance* instance, z_tie* tie)
{
    z_receiver* recv = instance->z_internal_ptr->z_receiver_list->z_next;
    while(recv)
    {
        if(recv->z_sym == tie)
        {
            return recv;
        }
        recv = recv->z_next;
    }
    return NULL;
}

void z_pd_instance_bind(z_instance* instance, z_tie* tie,
                                    z_hook_bang mbang,
                                    z_hook_float mfloat,
                                    z_hook_symbol msymbol,
                                    z_hook_gpointer mgpointer,
                                    z_hook_list mlist,
                                    z_hook_anything manything)
{
    z_receiver *x = z_pd_instance_getreceiver(instance, tie);
    if(x)
    {
        x->z_m_bang = mbang;
        x->z_m_float = mfloat;
        x->z_m_symbol = msymbol;
        x->z_m_gpointer = mgpointer;
        x->z_m_list = mlist;
        x->z_m_anything = manything;
    }
    else
    {
        x = (z_receiver *)pd_new(z_receiver_class);
        if(x)
        {
            x->z_sym = tie;
            x->z_owner = instance;
            x->z_m_bang = mbang;
            x->z_m_float = mfloat;
            x->z_m_symbol = msymbol;
            x->z_m_gpointer = mgpointer;
            x->z_m_list = mlist;
            x->z_m_anything = manything;
            x->z_next = instance->z_internal_ptr->z_receiver_list;
            instance->z_internal_ptr->z_receiver_list = x;
            pd_bind((t_pd *)x, x->z_sym);
        }
    }
}

void z_pd_instance_unbind(z_instance* instance, z_tie* tie)
{
    z_receiver *x = z_pd_instance_getreceiver(instance, tie);
    if(x)
    {
        pd_free((t_pd *)x);
    }
}

void z_pd_instance_dsp_prepare(z_instance* instance,
                               const int nins, const int nouts,
                               const int samplerate, const int nsamples)
{
    if(samplerate != instance->z_internal_ptr->z_samplerate ||
       nins != instance->z_internal_ptr->z_ninputs ||
       nouts != instance->z_internal_ptr->z_noutputs)
    {
        sys_setchsr(nins, nouts, samplerate);
        instance->z_internal_ptr->z_inputs      = sys_soundin;
        instance->z_internal_ptr->z_outputs     = sys_soundout;
        instance->z_internal_ptr->z_ninputs     = sys_inchannels;
        instance->z_internal_ptr->z_noutputs    = sys_outchannels;
        instance->z_internal_ptr->z_samplerate  = sys_getsr();
    }
    t_atom av;
    av.a_type = A_FLOAT;
    av.a_w.w_float = 1;
    pd_typedmess((t_pd *)z_sym_pd->s_thing, z_sym_dsp, 1, &av);
}

void z_pd_instance_dsp_perform(z_instance* instance, int nsamples,
                               const int nins, const z_sample** inputs,
                               const int nouts, z_sample** outputs)
{
    t_sample *ins = instance->z_internal_ptr->z_inputs;
    t_sample *outs = instance->z_internal_ptr->z_outputs;
    for(int i = 0; i < nsamples; i += DEFDACBLKSIZE)
    {
        for(int j = 0; j < nins; j++)
        {
            memcpy(ins+j*DEFDACBLKSIZE, inputs[j]+i, DEFDACBLKSIZE * sizeof(t_sample));
        }
        memset(outs, 0, DEFDACBLKSIZE * sizeof(t_sample) * nouts);
        sched_tick();
        for(int j = 0; j < nouts; j++)
        {
            memcpy(outputs[j]+i, outs+j*DEFDACBLKSIZE, DEFDACBLKSIZE * sizeof(t_sample));
        }
    }
}

void z_pd_instance_dsp_release(z_instance* instance)
{
    
}

int z_pd_instance_get_samplerate(z_instance* instance)
{
    return instance->z_internal_ptr->z_samplerate;
}







z_patch* z_pd_patch_new(const char* name, const char* path)
{
    t_canvas* cnv = NULL;
    if(name && path)
    {
        cnv = (t_canvas *)glob_evalfile(NULL, gensym(name), gensym(path));
        if(cnv)
        {
            cnv->gl_edit = 0;
        }
    }
    else if(name)
    {
        cnv = (t_canvas *)glob_evalfile(NULL, gensym(name), gensym(""));
        if(cnv)
        {
            cnv->gl_edit = 0;
        }
    }
    return cnv;
}

void z_pd_patch_free(z_patch* patch)
{
    canvas_free(patch);
}

const char* z_pd_patch_get_name(z_patch const* patch)
{
    return patch->gl_name->s_name;
}

const char* z_pd_patch_get_path(z_patch const* patch)
{
    return canvas_getdir((t_glist *)patch)->s_name;
}

int z_pd_patch_get_dollarzero(z_patch const* patch)
{
    int value = 0;
    t_canvas* current = canvas_getcurrent();
    canvas_setcurrent((t_glist *)patch);
    value = canvas_getdollarzero();
    canvas_setcurrent(current);
    return value;
}

int z_pd_patch_get_x(z_patch const* patch)
{
    return patch->gl_xmargin;
}

int z_pd_patch_get_y(z_patch const* patch)
{
    return patch->gl_ymargin;
}

int z_pd_patch_get_width(z_patch const* patch)
{
    return patch->gl_pixwidth;
}

int z_pd_patch_get_height(z_patch const* patch)
{
    return patch->gl_pixheight;
}

z_object* z_pd_patch_get_first_object(z_patch* patch)
{
    return (z_object *)patch->gl_list;
}

z_object* z_pd_patch_get_next_object(z_patch* patch, z_object* previous)
{
    return (z_object *)((t_gobj *)previous)->g_next;
}




static char z_pd_object_is_patchable(z_object const* object)
{
    return object->te_g.g_pd->c_patchable;
}

static struct _widgetbehavior* z_pd_object_get_widget(z_object const* object)
{
    return object->te_g.g_pd->c_wb;
}


z_symbol* z_pd_object_get_name(z_object const* object)
{
    return object->te_g.g_pd->c_name;
}

void z_pd_object_get_text(z_object const* object, int* size, char** text)
{
    binbuf_gettext(((t_text *)(object))->te_binbuf, text, size);
}

void z_pd_object_get_bounds(z_object const* object, z_patch const* patch, int* x, int* y, int* width, int* height)
{
    struct _widgetbehavior const* wb = z_pd_object_get_widget(object);
    if(z_pd_object_is_patchable(object) && wb && wb->w_getrectfn)
    {
        wb->w_getrectfn((t_gobj *)object, (t_canvas *)patch, x, y, width, height);
        *width  = *width - *x;
        *height = *height - *y;
        *x = *x - z_pd_patch_get_x(patch);
        *y = *y - z_pd_patch_get_y(patch);
    }
    else
    {
        *x = 0;
        *y = 0;
        *width = 0;
        *height = 0;
    }
}





z_symbol* z_pd_gui_get_label(z_gui const* gui)
{
    return gui->x_lab;
}

z_symbol* z_pd_gui_get_receive_symbol(z_gui const* gui)
{
    return gui->x_rcv;
}

z_symbol* z_pd_gui_get_send_symbol(z_gui const* gui)
{
    return gui->x_rcv;
}

float z_pd_gui_get_maximum_value(z_gui const* gui)
{
    if(gui->x_obj.te_g.g_pd->c_name == z_sym_hsl)
    {
        return ((t_hslider *)gui)->x_max;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vsl)
    {
        return ((t_vslider *)gui)->x_max;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_tgl)
    {
        return 1.f;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_nbx)
    {
        return ((t_my_numbox *)gui)->x_max;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vradio)
    {
        return ((t_hdial *)gui)->x_number - 1;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_hradio)
    {
        return ((t_vdial *)gui)->x_number - 1;
    }
    return 0.f;
}

float z_pd_gui_get_minimum_value(z_gui const* gui)
{
    if(gui->x_obj.te_g.g_pd->c_name == z_sym_hsl)
    {
        return ((t_hslider *)gui)->x_min;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vsl)
    {
        return ((t_vslider *)gui)->x_min;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_tgl)
    {
        return 0.f;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_nbx)
    {
        return ((t_my_numbox *)gui)->x_min;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vradio)
    {
        return 0.f;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_hradio)
    {
        return 0.f;
    }
    return 0.f;
}

int z_pd_gui_get_number_of_steps(z_gui const* gui)
{
    if(gui->x_obj.te_g.g_pd->c_name == z_sym_hsl)
    {
        return 0;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vsl)
    {
        return 0;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_tgl)
    {
        return 2;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_nbx)
    {
        return 0;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vradio)
    {
        return ((t_hdial *)gui)->x_number;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_hradio)
    {
        return ((t_vdial *)gui)->x_number;
    }
    return 0.f;
}

float z_pd_gui_get_value(z_gui const* gui)
{
    if(gui->x_obj.te_g.g_pd->c_name == z_sym_hsl)
    {
        return ((t_hslider *)gui)->x_val;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vsl)
    {
        return ((t_vslider *)gui)->x_val;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_tgl)
    {
        return ((t_toggle *)gui)->x_on;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_nbx)
    {
        return ((t_my_numbox *)gui)->x_val;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_vradio)
    {
        return ((t_hdial *)gui)->x_on;
    }
    else if(gui->x_obj.te_g.g_pd->c_name == z_sym_hradio)
    {
        return ((t_vdial *)gui)->x_on;
    }
    return 0.f;
}

void z_pd_gui_get_label_position(z_gui const* gui, z_patch const* patch, int* x, int* y)
{
    *x = ((t_object *)gui)->te_xpix - z_pd_patch_get_x(patch) + gui->x_ldx;
    *y = ((t_object *)gui)->te_ypix - z_pd_patch_get_y(patch) + gui->x_ldy;
}






z_tie* z_pd_get_tie(const char* name)
{
    return (z_tie *)gensym(name);
}

char const* z_pd_tie_get_name(z_tie const* tie)
{
    return tie->s_name;
}

z_symbol* z_pd_get_symbol(const char* symbol)
{
    return (z_symbol *)gensym(symbol);
}

char const* z_pd_symbol_get_name(z_symbol const* symbol)
{
    return symbol->s_name;
}

z_list* z_pd_get_list()
{
    return (z_list *)binbuf_new();
}

void z_pd_list_clear(z_list *list)
{
    binbuf_clear((t_binbuf *)list);
}

void z_pd_list_add_float(z_list *list, z_float value)
{
    t_atom av;
    av.a_type = A_FLOAT;
    av.a_w.w_float = value;
    binbuf_add((t_binbuf *)list, 1, &av);
}

void z_pd_list_add_symbol(z_list *list, z_symbol* symbol)
{
    t_atom av;
    av.a_type = A_SYMBOL;
    av.a_w.w_symbol = (t_symbol*)symbol;
    binbuf_add((t_binbuf *)list, 1, &av);
}

void z_pd_list_add_list(z_list *list, z_list *other)
{
    binbuf_addbinbuf((t_binbuf *)list, (t_binbuf *)other);
}







void z_pd_messagesend_bang(z_tie const* tie)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_bang((t_pd *)sym->s_thing);
    }
}

void z_pd_messagesend_float(z_tie const* tie, z_float value)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_float((t_pd *)sym->s_thing, value);
    }
}

void z_pd_messagesend_gpointer(z_tie const* tie, z_gpointer const* pointer)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_pointer((t_pd *)sym->s_thing, (t_gpointer *)pointer);
    }
}

void z_pd_messagesend_symbol(z_tie const* tie, z_symbol const* symbol)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_symbol((t_pd *)sym->s_thing, (t_symbol *)symbol);
    }
}

void z_pd_messagesend_list(z_tie const* tie, z_list const* list)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_list((t_pd *)sym->s_thing, &s_list,
                binbuf_getnatom((t_binbuf *)list), binbuf_getvec((t_binbuf *)list));
    }
}

void z_pd_messagesend_anything(z_tie const* tie, z_symbol const* symbol, z_list const* list)
{
    t_symbol const* sym = (t_symbol const *)tie;
    if(sym && sym->s_thing)
    {
        pd_typedmess((t_pd *)sym->s_thing, (t_symbol *)symbol,
                     binbuf_getnatom((t_binbuf *)list), binbuf_getvec((t_binbuf *)list));
    }
}








#define Z_PD_MIDI_CHECK_CHANNEL(channel) if (channel < 0 || channel > 16) return;
#define Z_PD_MIDI_CHECK_PORT(port) if (port < 0 || port > 0x0fff) return;
#define Z_PD_MIDI_CHECK_RANGE_7BIT(v) if (v < 0 || v > 0x7f) return;
#define Z_PD_MIDI_CHECK_RANGE_8BIT(v) if (v < 0 || v > 0xff) return;
#define Z_PD_MIDI_WRAP_PORT(channel) (channel >> 4)
#define Z_PD_MIDI_WRAP_CHANNEL(channel) (channel & 0x0f)

void z_pd_midisend_noteon(int channel, int pitch, int velocity)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    Z_PD_MIDI_CHECK_RANGE_7BIT(pitch)
    Z_PD_MIDI_CHECK_RANGE_8BIT(velocity)
    inmidi_noteon(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), pitch, velocity);
}

void z_pd_midisend_controlchange(int channel, int controller, int value)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    Z_PD_MIDI_CHECK_RANGE_7BIT(controller)
    Z_PD_MIDI_CHECK_RANGE_7BIT(value)
    inmidi_controlchange(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), controller, value);
}

void z_pd_midisend_programchange(int channel, int value)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    Z_PD_MIDI_CHECK_RANGE_7BIT(value)
    inmidi_programchange(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), value);
}

void z_pd_midisend_pitchbend(int channel, int value)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    if (value < -8192 || value > 8191) return;
    inmidi_pitchbend(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), value + 8192);
}

void z_pd_midisend_aftertouch(int channel, int value)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    Z_PD_MIDI_CHECK_RANGE_7BIT(value)
    inmidi_aftertouch(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), value);
}

void z_pd_midisend_polyaftertouch(int channel, int pitch, int value)
{
    Z_PD_MIDI_CHECK_CHANNEL(channel)
    Z_PD_MIDI_CHECK_RANGE_7BIT(pitch)
    Z_PD_MIDI_CHECK_RANGE_7BIT(value)
    inmidi_polyaftertouch(Z_PD_MIDI_WRAP_PORT(channel), Z_PD_MIDI_WRAP_CHANNEL(channel), pitch, value);
}

void z_pd_midisend_byte(int port, int byte)
{
    Z_PD_MIDI_CHECK_PORT(port)
    Z_PD_MIDI_CHECK_RANGE_8BIT(byte)
    inmidi_byte(port, byte);
}

void z_pd_midisend_sysex(int port, int byte)
{
    Z_PD_MIDI_CHECK_PORT(port)
    Z_PD_MIDI_CHECK_RANGE_7BIT(byte)
    inmidi_sysex(port, byte);
}

void z_pd_midisend_sysrealtimein(int port, int byte)
{
    Z_PD_MIDI_CHECK_PORT(port)
    Z_PD_MIDI_CHECK_RANGE_8BIT(byte)
    inmidi_realtimein(port, byte);
}

#undef Z_PD_MIDI_CHECK_CHANNEL
#undef Z_PD_MIDI_CHECK_PORT
#undef Z_PD_MIDI_CHECK_RANGE_7BIT
#undef Z_PD_MIDI_CHECK_RANGE_8BIT
#undef Z_PD_MIDI_WRAP_PORT
#undef Z_PD_MIDI_WRAP_CHANNEL


#define Z_PD_MIDI_CLIP(x, low, high) ((x > high) ? high : ((x < low) ? low : x))
#define Z_PD_MIDI_CLIP4BIT(x) Z_PD_MIDI_CLIP(x, 0, 0x0f)
#define Z_PD_MIDI_CLIP7BIT(x) Z_PD_MIDI_CLIP(x, 0, 0x7f)
#define Z_PD_MIDI_CLIP8BIT(x) Z_PD_MIDI_CLIP(x, 0, 0xff)
#define Z_PD_MIDI_CLIP12BIT(x) Z_PD_MIDI_CLIP(x, 0, 0x0fff)
#define Z_PD_MIDI_CLIP14BIT(x) Z_PD_MIDI_CLIP(x, 0, 0x3fff)
#define Z_PD_MIDI_CLIPCHANNEL(x) Z_PD_MIDI_CLIP(x, 0, 15)

void outmidi_noteon(int port, int channel, int pitch, int velo)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_noteon)
    {
        z_current_instance->z_internal_ptr->z_m_noteon(z_current_instance,
                                                       Z_PD_MIDI_CLIP12BIT(port),
                                                       Z_PD_MIDI_CLIPCHANNEL(channel),
                                                       Z_PD_MIDI_CLIP7BIT(pitch),
                                                       Z_PD_MIDI_CLIP7BIT(velo));
    }
}

void outmidi_controlchange(int port, int channel, int ctl, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_controlchange)
    {
        z_current_instance->z_internal_ptr->z_m_controlchange(z_current_instance,
                                                              Z_PD_MIDI_CLIP12BIT(port),
                                                              Z_PD_MIDI_CLIPCHANNEL(channel),
                                                              Z_PD_MIDI_CLIP7BIT(ctl),
                                                              Z_PD_MIDI_CLIP7BIT(value));
    }
}

void outmidi_programchange(int port, int channel, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_programchange)
    {
        z_current_instance->z_internal_ptr->z_m_programchange(z_current_instance,
                                                              Z_PD_MIDI_CLIP12BIT(port),
                                                              Z_PD_MIDI_CLIPCHANNEL(channel),
                                                              Z_PD_MIDI_CLIP7BIT(value));
    }
}

void outmidi_pitchbend(int port, int channel, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_pitchbend)
    {
        z_current_instance->z_internal_ptr->z_m_pitchbend(z_current_instance,
                                                          Z_PD_MIDI_CLIP12BIT(port),
                                                          Z_PD_MIDI_CLIPCHANNEL(channel),
                                                          Z_PD_MIDI_CLIP14BIT(value) - 8192);
    }
}

void outmidi_aftertouch(int port, int channel, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_aftertouch)
    {
        z_current_instance->z_internal_ptr->z_m_aftertouch(z_current_instance,
                                                           Z_PD_MIDI_CLIP12BIT(port),
                                                           Z_PD_MIDI_CLIPCHANNEL(channel),
                                                           Z_PD_MIDI_CLIP7BIT(value));
    }
}

void outmidi_polyaftertouch(int port, int channel, int pitch, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_polyaftertouch)
    {
        z_current_instance->z_internal_ptr->z_m_polyaftertouch(z_current_instance,
                                                               Z_PD_MIDI_CLIP12BIT(port),
                                                               Z_PD_MIDI_CLIPCHANNEL(channel),
                                                               Z_PD_MIDI_CLIP7BIT(pitch),
                                                               Z_PD_MIDI_CLIP7BIT(value));
    }
}

void outmidi_byte(int port, int value)
{
    if(z_current_instance && z_current_instance->z_internal_ptr->z_m_byte)
    {
        z_current_instance->z_internal_ptr->z_m_byte(z_current_instance,
                                                     Z_PD_MIDI_CLIP12BIT(port),
                                                     Z_PD_MIDI_CLIP8BIT(value));
    }
}

#undef Z_PD_MIDI_CLIP
#undef Z_PD_MIDI_CLIP4BIT
#undef Z_PD_MIDI_CLIP7BIT
#undef Z_PD_MIDI_CLIP8BIT
#undef Z_PD_MIDI_CLIP12BIT
#undef Z_PD_MIDI_CLIP14BIT
#undef Z_PD_MIDI_CLIPCHANNEL

