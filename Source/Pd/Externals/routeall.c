#include "m_pd.h"

static t_class *routeall_class;

typedef struct _routeall{
    t_object    x_obj;
    t_atom      *x_av;
    t_int       x_ac;
    t_int       x_bytes;
    t_outlet    **x_outs;
    t_outlet    *x_out_unmatch;
} t_routeall;

static void routeall_bang(t_routeall *x){
    t_int n;
    for(n = 0; n < x->x_ac; n++){
        if(x->x_av[n].a_type == A_SYMBOL){
            if(x->x_av[n].a_w.w_symbol == gensym("bang")){
                outlet_bang(x->x_outs[n]);
                return;
            }
        }
    }
    outlet_bang(x->x_out_unmatch);
}

static void routeall_symbol(t_routeall *x, t_symbol *s){
    t_int n;
    t_symbol *arg;
    for(n = 0; n < x->x_ac; n++){
        if(x->x_av[n].a_type == A_SYMBOL){
            arg = x->x_av[n].a_w.w_symbol;
            if(arg == gensym("symbol") || arg == s){
                outlet_symbol(x->x_outs[n], s);
                return;
            }
        }
    }
    outlet_symbol(x->x_out_unmatch, s);
}

static void routeall_list(t_routeall *x, t_symbol *s, int ac, t_atom *av){
    s = NULL;
    t_int n;
    t_symbol *arg;
    if(ac == 0){
        routeall_bang(x);
        return;
    }
    if(ac == 1 && av[0].a_type == A_SYMBOL){
        routeall_symbol(x, atom_getsymbol(av));
        return;
    }
    for(n = 0; n < x->x_ac; n++){
        if(x->x_av[n].a_type == A_SYMBOL){
            arg = x->x_av[n].a_w.w_symbol;
            if(arg == gensym("list") || arg == atom_getsymbol(av)){
                outlet_list(x->x_outs[n], gensym("list"), ac, av);
                return;
            }
        }
        else{
            if(x->x_av[n].a_w.w_float == atom_getfloat(av)){
                outlet_list(x->x_outs[n], gensym("list"), ac, av);
                return;
            }
        }
    }
    outlet_list(x->x_out_unmatch, gensym("list"), ac, av);
}

static void routeall_anything(t_routeall *x, t_symbol *s, int ac, t_atom *av){
    t_int n;
    for(n = 0; n < x->x_ac; n++){
        if(x->x_av[n].a_type == A_SYMBOL){
            if(x->x_av[n].a_w.w_symbol == s){
                outlet_anything(x->x_outs[n], s, ac, av);
                return;
            }
        }
    }
    outlet_anything(x->x_out_unmatch, s, ac, av);
}

static void *routeall_new(t_symbol *s, int argc, t_atom *argv){
    s = NULL;
    t_routeall *x = (t_routeall *)pd_new(routeall_class);
    t_outlet **outs;
    if(!argc){
        x->x_ac = 1;
        x->x_bytes = x->x_ac*sizeof(t_atom);
        x->x_av = (t_atom *)getbytes(x->x_bytes);
        SETFLOAT(x->x_av, 0);
    }
    else{
        x->x_ac = argc;
        x->x_bytes = x->x_ac*sizeof(t_atom);
        x->x_av = (t_atom *)getbytes(x->x_bytes);
        t_int n = 0;
        while(argc > 0){
            if(argv->a_type == A_FLOAT){
                t_float argval = atom_getfloatarg(0, argc, argv);
                SETFLOAT(x->x_av+n, argval);
            }
            else if(argv->a_type == A_SYMBOL){
                t_symbol *curarg = atom_getsymbolarg(0, argc, argv);
                SETSYMBOL(x->x_av+n, curarg);
            }
            n++;
            argv++;
            argc--;
        }
    }
    x->x_outs = (t_outlet **)getbytes(x->x_ac * sizeof(*outs));
    int i;
    for (i = 0; i < x->x_ac; i++)
        x->x_outs[i] = outlet_new(&x->x_obj, &s_anything);
    x->x_out_unmatch = outlet_new(&x->x_obj, &s_anything);
    return (x);
}

void routeall_setup(void){
    routeall_class = class_new(gensym("routeall"), (t_newmethod)routeall_new,
                                0, sizeof(t_routeall), 0, A_GIMME, 0);
    class_addbang(routeall_class, routeall_bang);
    class_addsymbol(routeall_class, routeall_symbol);
    class_addlist(routeall_class, routeall_list);
    class_addanything(routeall_class, routeall_anything);
}
