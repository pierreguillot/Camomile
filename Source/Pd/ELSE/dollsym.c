// porres 2020

#include "m_pd.h"
#include "g_canvas.h"

static t_class *dollsym_class;

typedef struct _dollsym{
    t_object    x_obj;
    t_glist    *x_cv;
}t_dollsym;

static void dollsym_symbol(t_dollsym *x, t_symbol *s){
    outlet_symbol(x->x_obj.ob_outlet, canvas_realizedollar(x->x_cv, s));
}

static void *dollsym_new(t_floatarg f){
    t_dollsym *x = (t_dollsym *)pd_new(dollsym_class);
    int depth = f < 0 ? 0 : (int)f;
    x->x_cv = canvas_getrootfor(canvas_getcurrent());
    while(depth-- && x->x_cv->gl_owner)
        x->x_cv = canvas_getrootfor(x->x_cv->gl_owner);
    outlet_new(&x->x_obj, &s_);
    return(x);
}

void dollsym_setup(void){
    dollsym_class = class_new(gensym("dollsym"), (t_newmethod)dollsym_new,
        0, sizeof(t_dollsym), 0, A_DEFFLOAT, 0);
    class_addsymbol(dollsym_class, dollsym_symbol);
}
