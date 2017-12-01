/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include <m_pd.h>
#include <string.h>
#include <assert.h>
#include <s_stuff.h>
#include "x_libpd_multi.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

// For declare object multi instance support

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
    t_binbuf *b = binbuf_new();
    
    glob_setfilename(0, gensym("_float_template"), gensym("."));
    binbuf_text(b, garray_floattemplatefile, strlen(garray_floattemplatefile));
    binbuf_eval(b, &pd_canvasmaker, 0, 0);
    vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
    
    glob_setfilename(0, gensym("_float_array_template"), gensym("."));
    binbuf_text(b, garray_arraytemplatefile, strlen(garray_arraytemplatefile));
    binbuf_eval(b, &pd_canvasmaker, 0, 0);
    vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
    
    glob_setfilename(0, &s_, &s_);
    binbuf_free(b);
}

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
    t_binbuf *b = binbuf_new();
    
    glob_setfilename(0, gensym("_text_template"), gensym("."));
    binbuf_text(b, text_templatefile, strlen(text_templatefile));
    binbuf_eval(b, &pd_canvasmaker, 0, 0);
    vmess(s__X.s_thing, gensym("pop"), (char *)"i", 0);
    
    glob_setfilename(0, &s_, &s_);
    binbuf_free(b);
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void libpd_instance_init(void)
{
    garray_init();
    text_template_init();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static t_class *libpd_multi_receiver_class;

typedef struct _libpd_multi_receiver
{
    t_object    x_obj;
    t_symbol*   x_sym;
    void*       x_ptr;
    
    t_libpd_multi_banghook      x_hook_bang;
    t_libpd_multi_floathook     x_hook_float;
    t_libpd_multi_symbolhook    x_hook_symbol;
    t_libpd_multi_listhook      x_hook_list;
    t_libpd_multi_messagehook   x_hook_message;
} t_libpd_multi_receiver;

static void libpd_multi_receiver_bang(t_libpd_multi_receiver *x)
{
    if(x->x_hook_bang)
        x->x_hook_bang(x->x_ptr, x->x_sym->s_name);
}

static void libpd_multi_receiver_float(t_libpd_multi_receiver *x, t_float f)
{
    if(x->x_hook_float)
        x->x_hook_float(x->x_ptr, x->x_sym->s_name, f);
}

static void libpd_multi_receiver_symbol(t_libpd_multi_receiver *x, t_symbol *s)
{
    if(x->x_hook_symbol)
        x->x_hook_symbol(x->x_ptr, x->x_sym->s_name, s->s_name);
}

static void libpd_multi_receiver_list(t_libpd_multi_receiver *x, t_symbol *s, int argc, t_atom *argv)
{
    if(x->x_hook_list)
        x->x_hook_list(x->x_ptr, x->x_sym->s_name, argc, argv);
}

static void libpd_multi_receiver_anything(t_libpd_multi_receiver *x, t_symbol *s, int argc, t_atom *argv)
{
    if(x->x_hook_message)
        x->x_hook_message(x->x_ptr, x->x_sym->s_name, s->s_name, argc, argv);
}

static void libpd_multi_receiver_free(t_libpd_multi_receiver *x)
{
    pd_unbind(&x->x_obj.ob_pd, x->x_sym);
}

static void libpd_multi_receiver_setup(void)
{
    sys_lock();
    libpd_multi_receiver_class = class_new(gensym("libpd_multi_receiver"), (t_newmethod)NULL, (t_method)libpd_multi_receiver_free,
                                           sizeof(t_libpd_multi_receiver), CLASS_DEFAULT, A_NULL, 0);
    class_addbang(libpd_multi_receiver_class, libpd_multi_receiver_bang);
    class_addfloat(libpd_multi_receiver_class,libpd_multi_receiver_float);
    class_addsymbol(libpd_multi_receiver_class, libpd_multi_receiver_symbol);
    class_addlist(libpd_multi_receiver_class, libpd_multi_receiver_list);
    class_addanything(libpd_multi_receiver_class, libpd_multi_receiver_anything);
    sys_unlock();
}

void* libpd_multi_receiver_new(void* ptr, char const *s,
                               t_libpd_multi_banghook hook_bang,
                               t_libpd_multi_floathook hook_float,
                               t_libpd_multi_symbolhook hook_symbol,
                               t_libpd_multi_listhook hook_list,
                               t_libpd_multi_messagehook hook_message)
{
    
    t_libpd_multi_receiver *x = (t_libpd_multi_receiver *)pd_new(libpd_multi_receiver_class);
    if(x)
    {
        sys_lock();
        x->x_sym = gensym(s);
        sys_unlock();
        pd_bind(&x->x_obj.ob_pd, x->x_sym);
        x->x_ptr = ptr;
        x->x_hook_bang = hook_bang;
        x->x_hook_float = hook_float;
        x->x_hook_symbol = hook_symbol;
        x->x_hook_list = hook_list;
        x->x_hook_message = hook_message;
    }
    return x;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static t_class *libpd_multi_midi_class;

typedef struct _libpd_multi_midi
{
    t_object    x_obj;
    void*       x_ptr;
    
    t_libpd_multi_noteonhook            x_hook_noteon;
    t_libpd_multi_controlchangehook     x_hook_controlchange;
    t_libpd_multi_programchangehook     x_hook_programchange;
    t_libpd_multi_pitchbendhook         x_hook_pitchbend;
    t_libpd_multi_aftertouchhook        x_hook_aftertouch;
    t_libpd_multi_polyaftertouchhook    x_hook_polyaftertouch;
    t_libpd_multi_midibytehook          x_hook_midibyte;
} t_libpd_multi_midi;

static void libpd_multi_noteon(int channel, int pitch, int velocity)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_noteon)
    {
        x->x_hook_noteon(x->x_ptr, channel, pitch, velocity);
    }
}

static void libpd_multi_controlchange(int channel, int controller, int value)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_controlchange)
    {
        x->x_hook_controlchange(x->x_ptr, channel, controller, value);
    }
}

static void libpd_multi_programchange(int channel, int value)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_programchange)
    {
        x->x_hook_programchange(x->x_ptr, channel, value);
    }
}

static void libpd_multi_pitchbend(int channel, int value)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_pitchbend)
    {
        x->x_hook_pitchbend(x->x_ptr, channel, value);
    }
}

static void libpd_multi_aftertouch(int channel, int value)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_aftertouch)
    {
        x->x_hook_aftertouch(x->x_ptr, channel, value);
    }
}

static void libpd_multi_polyaftertouch(int channel, int pitch, int value)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_polyaftertouch)
    {
        x->x_hook_polyaftertouch(x->x_ptr, channel, pitch, value);
    }
}

static void libpd_multi_midibyte(int port, int byte)
{
    t_libpd_multi_midi* x = (t_libpd_multi_midi*)gensym("#libpd_multi_midi")->s_thing;
    if(x && x->x_hook_midibyte)
    {
        x->x_hook_midibyte(x->x_ptr, port, byte);
    }
}

static void libpd_multi_midi_free(t_libpd_multi_midi *x)
{
    pd_unbind(&x->x_obj.ob_pd, gensym("#libpd_multi_midi"));
}

static void libpd_multi_midi_setup(void)
{
    sys_lock();
    libpd_multi_midi_class = class_new(gensym("libpd_multi_midi"), (t_newmethod)NULL, (t_method)libpd_multi_midi_free,
                                       sizeof(t_libpd_multi_midi), CLASS_DEFAULT, A_NULL, 0);
    sys_unlock();
}

void* libpd_multi_midi_new(void* ptr,
                           t_libpd_multi_noteonhook hook_noteon,
                           t_libpd_multi_controlchangehook hook_controlchange,
                           t_libpd_multi_programchangehook hook_programchange,
                           t_libpd_multi_pitchbendhook hook_pitchbend,
                           t_libpd_multi_aftertouchhook hook_aftertouch,
                           t_libpd_multi_polyaftertouchhook hook_polyaftertouch,
                           t_libpd_multi_midibytehook hook_midibyte)
{
    
    t_libpd_multi_midi *x = (t_libpd_multi_midi *)pd_new(libpd_multi_midi_class);
    if(x)
    {
        sys_lock();
        t_symbol* s = gensym("#libpd_multi_midi");
        sys_unlock();
        pd_bind(&x->x_obj.ob_pd, s);
        x->x_ptr = ptr;
        x->x_hook_noteon        = hook_noteon;
        x->x_hook_controlchange = hook_controlchange;
        x->x_hook_programchange = hook_programchange;
        x->x_hook_pitchbend     = hook_pitchbend;
        x->x_hook_aftertouch    = hook_aftertouch;
        x->x_hook_polyaftertouch= hook_polyaftertouch;
        x->x_hook_midibyte      = hook_midibyte;
    }
    return x;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static t_class *libpd_multi_print_class;

typedef struct _libpd_multi_print
{
    t_object    x_obj;
    void*       x_ptr;
    t_libpd_multi_printhook x_hook;
} t_libpd_multi_print;

static void libpd_multi_print(const char* message)
{
    t_libpd_multi_print* x = (t_libpd_multi_print*)gensym("#libpd_multi_print")->s_thing;
    if(x && x->x_hook)
    {
        x->x_hook(x->x_ptr, message);
    }
}

static void libpd_multi_print_setup(void)
{
    sys_lock();
    libpd_multi_print_class = class_new(gensym("libpd_multi_print"), (t_newmethod)NULL, (t_method)NULL,
                                       sizeof(t_libpd_multi_print), CLASS_DEFAULT, A_NULL, 0);
    sys_unlock();
}

void* libpd_multi_print_new(void* ptr, t_libpd_multi_printhook hook_print)
{
    
    t_libpd_multi_print *x = (t_libpd_multi_print *)pd_new(libpd_multi_print_class);
    if(x)
    {
        sys_lock();
        t_symbol* s = gensym("#libpd_multi_print");
        sys_unlock();
        pd_bind(&x->x_obj.ob_pd, s); 
        x->x_ptr = ptr;
        x->x_hook = hook_print;
    }
    return x;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void libpd_multi_init(void)
{
    static int initialized = 0;
    if(!initialized)
    {
        libpd_set_noteonhook(libpd_multi_noteon);
        libpd_set_controlchangehook(libpd_multi_controlchange);
        libpd_set_programchangehook(libpd_multi_programchange);
        libpd_set_pitchbendhook(libpd_multi_pitchbend);
        libpd_set_aftertouchhook(libpd_multi_aftertouch);
        libpd_set_polyaftertouchhook(libpd_multi_polyaftertouch);
        libpd_set_midibytehook(libpd_multi_midibyte);
        libpd_set_printhook(libpd_multi_print);
        
        assert(PDINSTANCE && "PDINSTANCE undefined");
        assert(PDTHREADS && "PDTHREADS undefined");
        libpd_init();
        sys_debuglevel = 1;
        sys_verbose = 1;
        libpd_multi_receiver_setup();
        libpd_multi_midi_setup();
        libpd_multi_print_setup();
        
        initialized = 1;
    }
}


