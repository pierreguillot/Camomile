/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// This part of the code is greatly inspired by Pure Data and libPD, and sometimes
// directly copied. None of the authors of Pure Data and libPD is responsible for these
// experiments but you must be aware of their unintended contribution.

#ifndef z_pd_h
#define z_pd_h

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#ifdef _WIN32
#ifdef PD_INTERNAL
#define Z_PD_EXTERN __declspec(dllexport) extern
#else
#define Z_PD_EXTERN __declspec(dllimport) extern
#endif
#else
#define Z_PD_EXTERN extern
#endif

#if defined(_MSC_VER) && !defined(_LANGUAGE_C_PLUS_PLUS) && !defined(__cplusplus)
#define Z_PD_EXTERN_STRUCT extern struct
#else
#define Z_PD_EXTERN_STRUCT struct
#endif

Z_PD_EXTERN_STRUCT _symbol;
Z_PD_EXTERN_STRUCT _symbol;
Z_PD_EXTERN_STRUCT _binbuf;
Z_PD_EXTERN_STRUCT _internal;
Z_PD_EXTERN_STRUCT _gpointer;
Z_PD_EXTERN_STRUCT _glist;
Z_PD_EXTERN_STRUCT _text;
Z_PD_EXTERN_STRUCT _iemgui;

typedef float z_sample;
typedef float z_float;
typedef struct _symbol      z_tie;
typedef struct _symbol      z_symbol;
typedef struct _binbuf      z_list;
typedef struct _internal    z_internal;
typedef struct _gpointer    z_gpointer;
typedef struct _glist       z_patch;
typedef struct _text        z_object;
typedef struct _iemgui      z_gui;

typedef struct _instance
{
    z_internal* z_internal_ptr;
}z_instance;

typedef void (*z_hook_print)(struct _instance* instance, const char *s);
typedef void (*z_hook_noteon)(struct _instance* instance, int port, int channel, int pitch, int velocity);
typedef void (*z_hook_controlchange)(struct _instance* instance, int port, int channel, int control, int value);
typedef void (*z_hook_programchange)(struct _instance* instance, int port, int channel, int value);
typedef void (*z_hook_pitchbend)(struct _instance* instance, int port, int channel, int value);
typedef void (*z_hook_aftertouch)(struct _instance* instance, int port, int channel, int value);
typedef void (*z_hook_polyaftertouch)(struct _instance* instance, int port, int channel, int pitch, int value);
typedef void (*z_hook_byte)(struct _instance* instance, int port, int value);

typedef void (*z_hook_bang)(struct _instance* instance, z_tie* tie);
typedef void (*z_hook_float)(struct _instance* instance, z_tie* tie, z_float f);
typedef void (*z_hook_symbol)(struct _instance* instance, z_tie* tie, z_symbol* s);
typedef void (*z_hook_gpointer)(struct _instance* instance, z_tie* tie, z_gpointer *gp);
typedef void (*z_hook_list)(struct _instance* instance, z_tie* tie, z_list *list);
typedef void (*z_hook_anything)(struct _instance* instance, z_tie* tie, z_symbol *s, z_list *list);


//! @brief Initializes the Pure Data environment.
//! @details The method should be called only one time at the initialization, before
//! everything else.
Z_PD_EXTERN void z_pd_init();

//! @brief Clears the Pure Data environment.
//! @details The method should be called only one time when the Pure Data environment will
//! never be called again.
Z_PD_EXTERN void z_pd_clear();






//! @brief Retrieves the major version of Pure Data.
Z_PD_EXTERN unsigned int z_pd_version_getmajor();

//! @brief Retrieves the minor version of Pure Data.
Z_PD_EXTERN unsigned int z_pd_version_getminor();

//! @brief Retrieves the bug version of Pure Data.
Z_PD_EXTERN unsigned int z_pd_version_getbug();






//! @brief Clears the search path of Pure Data.
Z_PD_EXTERN void z_pd_searchpath_clear();

//! @brief Adds a path to the search path of Pure Data.
Z_PD_EXTERN void z_pd_searchpath_add(const char* path);






//! @brief Sends a normal post to the console Pure Data.
Z_PD_EXTERN void z_pd_console_post(char const* message);

//! @brief Sends a log post to the console Pure Data.
Z_PD_EXTERN void z_pd_console_log(char const* message);

//! @brief Sends an error to the console Pure Data.
Z_PD_EXTERN void z_pd_console_error(char const* message);

//! @brief Sends a fatal error to the console Pure Data.
Z_PD_EXTERN void z_pd_console_fatal(char const* message);






//! @brief Creates a new instance.
Z_PD_EXTERN z_instance* z_pd_instance_new(size_t size,
                                          z_hook_print mprint,
                                          z_hook_noteon mnoteon,
                                          z_hook_controlchange mcontrolchange,
                                          z_hook_programchange mprogramchange,
                                          z_hook_pitchbend mpitchbend,
                                          z_hook_aftertouch maftertouch,
                                          z_hook_polyaftertouch mpolyaftertouch,
                                          z_hook_byte mbyte);

//! @brief Deletes an instance.
Z_PD_EXTERN void z_pd_instance_free(z_instance* instance);

//! @brief Sets the current instance.
Z_PD_EXTERN void z_pd_instance_set(z_instance* instance);

//! @brief Binds an instance to a tie.
Z_PD_EXTERN void z_pd_instance_bind(z_instance* instance, z_tie* tie,
                                    z_hook_bang mbang,
                                    z_hook_float mfloat,
                                    z_hook_symbol msymbol,
                                    z_hook_gpointer mgpointer,
                                    z_hook_list mlist,
                                    z_hook_anything manything);

//! @brief Unbinds an instance to a tie.
Z_PD_EXTERN void z_pd_instance_unbind(z_instance* instance, z_tie* tie);

//! @brief Prepares the DSP for an instance.
Z_PD_EXTERN void z_pd_instance_dsp_prepare(z_instance* instance,
                                           const int nins, const int nouts,
                                           const int samplerate, const int nsamples);

//! @brief Performs the DSP for an instance.
Z_PD_EXTERN void z_pd_instance_dsp_perform(z_instance* instance, int nsamples,
                                           const int nins, const z_sample** inputs,
                                           const int nouts, z_sample** outputs);

//! @brief Releases the DSP for an instance.
Z_PD_EXTERN void z_pd_instance_dsp_release(z_instance* instance);

//! @brief Gets the sample rate of an instance.
Z_PD_EXTERN int z_pd_instance_get_samplerate(z_instance* instance);








//! @brief Creates a new patch.
Z_PD_EXTERN z_patch* z_pd_patch_new(const char* name, const char* path);

//! @brief Frees a patch.
Z_PD_EXTERN void z_pd_patch_free(z_patch* patch);

//! @brief Gets the name of a patch.
Z_PD_EXTERN const char* z_pd_patch_get_name(z_patch const* patch);

//! @brief Gets the path of a patch.
Z_PD_EXTERN const char* z_pd_patch_get_path(z_patch const* patch);

//! @brief Gets the x margin of a patch.
Z_PD_EXTERN int z_pd_patch_get_x(z_patch const* patch);

//! @brief Gets the x margin of a patch.
Z_PD_EXTERN int z_pd_patch_get_y(z_patch const* patch);

//! @brief Gets the width of a patch.
Z_PD_EXTERN int z_pd_patch_get_width(z_patch const* patch);

//! @brief Gets the height of a patch.
Z_PD_EXTERN int z_pd_patch_get_height(z_patch const* patch);

//! @brief Gets the first object of a patch.
Z_PD_EXTERN z_object* z_pd_patch_get_first_object(z_patch* patch);

//! @brief Gets the next object of a patch.
Z_PD_EXTERN z_object* z_pd_patch_get_next_object(z_patch* patch, z_object* previous);




//! @brief Gets the name of an object.
Z_PD_EXTERN z_symbol* z_pd_object_get_name(z_object const* object);

//! @brief Gets the name of an object.
Z_PD_EXTERN void z_pd_object_get_text(z_object const* object, int* size, char** text);

//! @brief Gets the bounds of an object.
Z_PD_EXTERN void z_pd_object_get_bounds(z_object const* object, z_patch const* patch,
                                        int* x, int* y, int* width, int* height);








//! @brief Gets the label of a gui.
Z_PD_EXTERN z_symbol* z_pd_gui_get_label(z_gui const* gui);

//! @brief Gets the receive symbol of a gui.
Z_PD_EXTERN z_symbol* z_pd_gui_get_receive_symbol(z_gui const* gui);

//! @brief Gets the send symbol of a gui.
Z_PD_EXTERN z_symbol* z_pd_gui_get_send_symbol(z_gui const* gui);

//! @brief Gets the maximum value of a gui.
Z_PD_EXTERN float z_pd_gui_get_maximum_value(z_gui const* gui);

//! @brief Gets the maximum value of a gui.
Z_PD_EXTERN float z_pd_gui_get_minimum_value(z_gui const* gui);

//! @brief Gets the number of steps of a gui.
Z_PD_EXTERN int z_pd_gui_get_number_of_steps(z_gui const* gui);

//! @brief Gets the number of steps of a gui.
Z_PD_EXTERN float z_pd_gui_get_value(z_gui const* gui);

//! @brief Gets the bounds of a gui.
Z_PD_EXTERN void z_pd_gui_get_label_position(z_gui const* gui, z_patch const* patch, int* x, int* y);






//! @brief Retrieves an opaque tie that can be understood by Pure Data.
Z_PD_EXTERN z_tie* z_pd_get_tie(const char* name);

//! @brief Retrieves an opaque symbol that can be understood by Pure Data.
Z_PD_EXTERN char const* z_pd_tie_get_name(z_tie const* tie);

//! @brief Retrieves an opaque symbol that can be understood by Pure Data.
Z_PD_EXTERN z_symbol* z_pd_get_symbol(const char* symbol);

//! @brief Retrieves an opaque symbol that can be understood by Pure Data.
Z_PD_EXTERN char const* z_pd_symbol_get_name(z_symbol const* symbol);

//! @brief Retrieves an opaque list that can be understood by Pure Data.
Z_PD_EXTERN z_list* z_pd_get_list();

//! @brief Clears a list.
Z_PD_EXTERN void z_pd_list_clear(z_list *list);

//! @brief Adds a float to a list.
Z_PD_EXTERN void z_pd_list_add_float(z_list *list, z_float value);

//! @brief Adds a symbol to a list.
Z_PD_EXTERN void z_pd_list_add_symbol(z_list *list, z_symbol* symbol);

//! @brief Adds a list to a list.
Z_PD_EXTERN void z_pd_list_add_list(z_list *list, z_list *other);







//! @brief Sends a bang to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_bang(z_tie const* tie);

//! @brief Sends a float to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_float(z_tie const* tie, z_float value);

//! @brief Sends a gpointer to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_gpointer(z_tie const* tie, z_gpointer const* pointer);

//! @brief Sends a symbol to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_symbol(z_tie const* tie, z_symbol const* symbol);

//! @brief Sends a list to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_list(z_tie const* tie, z_list const* list);

//! @brief Sends a anything to Pure Data.
Z_PD_EXTERN void z_pd_messagesend_anything(z_tie const* tie, z_symbol const* symbol, z_list const* list);







//! @brief Sends a midi note on event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_noteon(int channel, int pitch, int velocity);

//! @brief Sends a midi control change event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_controlchange(int channel, int controller, int value);

//! @brief Sends a midi program change event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_programchange(int channel, int value);

//! @brief Sends a midi pitch bend event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_pitchbend(int channel, int value);

//! @brief Sends a midi after touch event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_aftertouch(int channel, int value);

//! @brief Sends a midi poly after touch event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_polyaftertouch(int channel, int pitch, int value);

//! @brief Sends a midi byte event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_byte(int port, int byte);

//! @brief Sends a midi sys ex event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_sysex(int port, int byte);

//! @brief Sends a midi real time in event to Pure Data.
Z_PD_EXTERN void z_pd_midisend_sysrealtimein(int port, int byte);


#undef Z_PD_EXTERN
#undef Z_PD_EXTERN_STRUCT

#endif /* z_pd_h */
