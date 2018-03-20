/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef __X_LIBPD_EXTRA_UTILS_H__
#define __X_LIBPD_EXTRA_UTILS_H__

#ifdef __cplusplus
extern "C"
{
#endif
    
#include <z_libpd.h>

    char const* libpd_get_object_class_name(void* ptr);
    void libpd_get_object_text(void* ptr, char** text, int* size);
    void libpd_get_object_bounds(void* patch, void* ptr, int* x, int* y, int* w, int* h);
    
#ifdef __cplusplus
}
#endif

#endif
