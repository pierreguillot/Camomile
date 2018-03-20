/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include <m_pd.h>
#include <m_imp.h>
#include <g_canvas.h>
#include "x_libpd_multi.h"


char const* libpd_get_object_class_name(void* ptr)
{
    return class_getname(pd_class((t_pd*)ptr));
}

void libpd_get_object_text(void* ptr, char** text, int* size)
{
    *text = NULL; *size = 0;
    binbuf_gettext(((t_text*)ptr)->te_binbuf, text, size);
}

void libpd_get_object_bounds(void* patch, void* ptr, int* x, int* y, int* w, int* h)
{
    t_canvas *cnv = (t_canvas*)patch;
    t_class const *c = pd_class((t_pd *)ptr);
    *x = 0; *y = 0; *w = 0; *h = 0;
    if(c->c_patchable && c->c_wb && c->c_wb->w_getrectfn)
    {
        c->c_wb->w_getrectfn((t_gobj *)ptr, cnv, x, y, w, h);
        *x -= 1;
        *y -= 1;
        *w -= *x;
        *h -= *y;
        while (cnv && cnv->gl_isgraph)
        {
            *x -= cnv->gl_xmargin;
            *y -= cnv->gl_ymargin;
            cnv = cnv->gl_owner;
        }
    }
}
