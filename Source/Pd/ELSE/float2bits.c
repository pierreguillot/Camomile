// matt barber and porres (2017)

#include "m_pd.h"
#include <stdlib.h>

#ifndef HAVE_ALLOCA     /* can work without alloca() but we never need it */
#define HAVE_ALLOCA 1
#endif
#define TEXT_NGETBYTE 100 /* bigger that this we use alloc, not alloca */
#if HAVE_ALLOCA
#define ATOMS_ALLOCA(x, n) ((x) = (t_atom *)((n) < TEXT_NGETBYTE ?  \
        alloca((n) * sizeof(t_atom)) : getbytes((n) * sizeof(t_atom))))
#define ATOMS_FREEA(x, n) ( \
    ((n) < TEXT_NGETBYTE || (freebytes((x), (n) * sizeof(t_atom)), 0)))
#else
#define ATOMS_ALLOCA(x, n) ((x) = (t_atom *)getbytes((n) * sizeof(t_atom)))
#define ATOMS_FREEA(x, n) (freebytes((x), (n) * sizeof(t_atom)))
#endif

typedef struct _float2bits{
    t_object x_obj;
    t_float x_f;
    t_outlet *x_out1;
    t_outlet *x_out2;
    t_outlet *x_out3;
} t_float2bits;

union u_float2bits{
	float uf;
	uint32_t ui;
};

static t_class *float2bits_class;

static void float2bits_split(t_float2bits *x){
    unsigned int mask = 0x80000000, i;
    union u_float2bits ufb;
    t_atom *outv;
    ATOMS_ALLOCA(outv, 32); // no need for alloca ???
    ufb.uf = x->x_f;
    for(i = 0; i < 32; i++, mask >>= 1)
        SETFLOAT(&outv[i], (ufb.ui & mask) != 0);
    outlet_anything(x->x_obj.ob_outlet, gensym("mantissa"), 23, outv+9);
    outlet_anything(x->x_obj.ob_outlet, gensym("exponent"), 8, outv+1);
    outlet_anything(x->x_obj.ob_outlet, gensym("sign"), 1, outv);
    ATOMS_FREEA(outv, 32);
}

static void float2bits_bang(t_float2bits *x){
	unsigned int mask = 0x80000000, i;
	union u_float2bits ufb;
	t_atom *outv;
	ATOMS_ALLOCA(outv, 32); // no need for alloca
	ufb.uf = x->x_f;
	for(i = 0; i < 32; i++, mask >>= 1)
		SETFLOAT(&outv[i], (ufb.ui & mask) != 0);
    outlet_anything(x->x_obj.ob_outlet, gensym("list"), 32, outv);
	ATOMS_FREEA(outv, 32);
}

static void float2bits_set(t_float2bits *x, t_float f){
    x->x_f = f;
}

static void float2bits_float(t_float2bits *x, t_float f){
	x->x_f = f;
	float2bits_bang(x);
}

static void *float2bits_new(t_floatarg f){
    t_float2bits *x = (t_float2bits *)pd_new(float2bits_class);
    // CHECKME large values (???)
    //x->x_value = sinhf(f); // ???
    x->x_f = f;
    floatinlet_new((t_object *)x, &x->x_f);
    outlet_new(&x->x_obj, &s_anything);
    return(x);
}

void float2bits_setup(void){
    float2bits_class = class_new(gensym("float2bits"),
			   (t_newmethod)float2bits_new, 0,
			   sizeof(t_float2bits), 0, A_DEFFLOAT, 0);
    class_addmethod(float2bits_class, (t_method)float2bits_split, gensym("split"), 0);
    class_addmethod(float2bits_class, (t_method)float2bits_set, gensym("set"), A_DEFFLOAT, 0);
    class_addbang(float2bits_class, float2bits_bang);
    class_addfloat(float2bits_class, float2bits_float);
}
