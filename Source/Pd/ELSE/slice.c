
#include "m_pd.h"
#include "math.h"

typedef struct _slice{
    t_object    x_obj;
    float       x_n;
    int         x_rev;
    t_outlet   *x_out1;
    t_outlet   *x_out2;
}t_slice;

static t_class *slice_class;

static void slice_rev(t_slice *x, t_floatarg f){
    x->x_rev = (int)(f != 0);
}

static void slice_list(t_slice *x, t_symbol *s, int ac, t_atom *av){
    int n = x->x_n < 0 ? 0 : (int)x->x_n;
    if(!x->x_rev){
        if(n == 0)
            outlet_anything(x->x_out2, s, ac, av);
        else if(n >= ac)
            outlet_anything(x->x_out1, s, ac, av);
        else{
            outlet_anything(x->x_out2, s, ac-n, av+n);
            outlet_anything(x->x_out1, s, n, av);
        }
    }
    else{
        if(n == 0)
            outlet_anything(x->x_out1, s, ac, av);
        else if(n >= ac)
            outlet_anything(x->x_out2, s, ac, av);
        else{
            outlet_anything(x->x_out2, s, n, av+(ac-n));
            outlet_anything(x->x_out1, s, ac-n, av);
        }
    }
}

static void *slice_new(t_symbol *s, int ac, t_atom *av){
    t_slice *x = (t_slice *)pd_new(slice_class);
    t_symbol *dummy = s;
    dummy = NULL;
    x->x_rev = 0;
    x->x_n = 0;
/////////////////////////////////////////////////////////////////////////////////////
    if(ac){
        while(ac > 0){
            if(av->a_type == A_FLOAT){
                x->x_n = atom_getfloatarg(0, ac, av);
                ac--;
                av++;
            }
            else if(av->a_type == A_SYMBOL){
                t_symbol *curarg = atom_getsymbolarg(0, ac, av);
                if(curarg == gensym("-rev")){
                    x->x_rev = 1;
                    ac--;
                    av++;
                }
                else
                    goto errstate;
            }
        };
    }
/////////////////////////////////////////////////////////////////////////////////////
    floatinlet_new(&x->x_obj, &x->x_n);
    x->x_out1  = outlet_new(&x->x_obj, &s_list);
    x->x_out2  = outlet_new(&x->x_obj, &s_list);
    return(x);
    errstate:
        pd_error(x, "[slice]: improper args");
        return NULL;
}

void slice_setup(void){
    slice_class = class_new(gensym("slice"), (t_newmethod)slice_new,
        0, sizeof(t_slice), 0, A_GIMME, 0);
    class_addlist(slice_class, slice_list);
    class_addmethod(slice_class, (t_method)slice_rev, gensym("rev"), A_FLOAT, 0);
}

