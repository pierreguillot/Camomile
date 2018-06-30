/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include <m_pd.h>
#include <m_imp.h>
#include <g_canvas.h>
#include <g_all_guis.h>
#include "x_libpd_multi.h"

// False GARRAY
typedef struct _fake_garray
{
    t_gobj x_gobj;
    t_scalar *x_scalar;
    t_glist *x_glist;
    t_symbol *x_name;
    t_symbol *x_realname;
    char x_usedindsp;
    char x_saveit;
    char x_listviewing;
    char x_hidename;
} t_fake_garray;

void* libpd_create_canvas(const char* name, const char* path)
{
    t_canvas* cnv = (t_canvas *)libpd_openfile(name, path);
    if(cnv)
    {
        canvas_vis(cnv, 1.f);
    }
    return cnv;
}

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
    t_canvas *cnv = (t_canvas*)glist_getcanvas(patch);
    *x = 0; *y = 0; *w = 0; *h = 0;
    gobj_getrect((t_gobj *)ptr, cnv, x, y, w, h);
    *x -= 1;
    *y -= 1;
    *w -= *x;
    *h -= *y;
}

t_fake_garray* libpd_array_get_byname(char const* name)
{
    return (t_fake_garray *)pd_findbyclass(gensym((char *)name), garray_class);
}

char const* libpd_array_get_name(void* ptr)
{
    return ((t_fake_garray*)ptr)->x_realname->s_name;
}

void libpd_array_get_scale(char const* name, float* min, float* max)
{
    t_canvas const *cnv;
    t_fake_garray const *array = libpd_array_get_byname(name);
    if(array)
    {
        cnv = ((t_fake_garray*)array)->x_glist;
        if(cnv)
        {
            *min = cnv->gl_y2;
            *max = cnv->gl_y1;
            return;
        }
    }
    *min = -1;
    *max = 1;
}

int libpd_array_get_style(char const* name)
{
    t_fake_garray const *array = libpd_array_get_byname(name);
    if(array && array->x_scalar)
    {
        t_scalar *scalar = array->x_scalar;
        t_template *scalartplte = template_findbyname(scalar->sc_template);
        if(scalartplte)
        {
            return (int)template_getfloat(scalartplte, gensym("style"), scalar->sc_vec, 0);
        }
    }
    return 0;
}




static unsigned int convert_from_iem_color(int const color)
{
    unsigned int const c = (unsigned int)(color << 8 | 0xFF);
    return ((0xFF << 24) | ((c >> 24) << 16) | ((c >> 16) << 8) | (c >> 8));
}

unsigned int libpd_iemgui_get_background_color(void* ptr)
{
    return convert_from_iem_color(((t_iemgui*)ptr)->x_bcol);
}

unsigned int libpd_iemgui_get_foreground_color(void* ptr)
{
    return convert_from_iem_color(((t_iemgui*)ptr)->x_fcol);
}

float libpd_get_canvas_font_height(t_canvas* cnv)
{
    const int fontsize = glist_getfont(cnv);
    if(fontsize == 8)
    {
        return 9.68f;
    }
    else if(fontsize == 10)
    {
        return 11.6f;
    }
    else if(fontsize == 12)
    {
        return 13.55f;
    }
    else if(fontsize == 16)
    {
        return 19.35f;
    }
    else if(fontsize == 24)
    {
        return 26.79f;
    }
    else if(fontsize == 36)
    {
        return 41.91f;
    }
    return glist_fontheight(cnv);
}

