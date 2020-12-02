// porres 2020

#include <math.h>
#include "m_pd.h"
#include "magic.h" // needed???????
#include "buffer.h"
#include <stdlib.h>

#define HALF_PI (M_PI * 0.5)

#define ONE_SIXTH 0.16666666666666666666667f
#define SHARED_FLT_MAX  1E+36
#define tabplayer_MINITIME 0.023 //minumum ms for xfade. 1/44.1 rounded up
// note, loop starts fading in at stms, starts fading out at endms

typedef struct _tabplayer{
    t_object    x_obj;
    t_buffer   *x_buffer;
    t_glist    *x_glist;
    int         x_hasfeeders; //if there's a signal coming in the main inlet
    float     x_sr; //pd's sample rate in ms
    float     x_array_sr_khz; //array's sample rate in ms
    double      x_sr_ratio; //sample rate ratio (array/pd)
    float     x_fadems; // xfade in ms (also known as interptime)
    float     x_stms; //start position in ms
    float     x_endms; //end pos in ms
    unsigned long long x_npts; //array size in samples
    unsigned long long x_start; //start position in samp
    unsigned long long x_stxsamp; //end of xfade ramp from start in samp
    unsigned long long x_end; //end pos in samp
    unsigned long long x_endxsamp; //end of xfade ramp from end in ms
    unsigned long long x_rangesamp; //length of loop in samples
    unsigned long long x_fadesamp; //length of fade in samples
    double      x_rate; //rate of playback
    double      x_phase; //phase for float playback mode
    int         x_loop; //if loop or not
    int         x_playing; //if playing
    int         x_playnew; //if started playing this particular block
    int         x_rfirst; //if this is the first time ramping up (for linterp mode)
    int         x_numchans;
    t_float    *x_ivec; // input vector
    t_float   **x_ovecs; //output vectors
    t_outlet    *x_donelet;
}t_play;

static t_class *tabplayer_class;

static void tabplayer_ms2samp(t_play *x){ // get index from ms
    t_float a_sr = x->x_array_sr_khz; // array's sample rate
    t_float stms = x->x_stms, endms = x->x_endms;
    unsigned long long npts = x->x_npts; //length of array in samples
    unsigned long long start = (unsigned long long)(stms * a_sr);
    unsigned long long end = x->x_end = (endms >= SHARED_FLT_MAX/a_sr ?
                                         SHARED_INT_MAX :
                                         (int)(endms * a_sr));
    x->x_start = start = start > npts ? npts : start < 0 ? 0 : start;
    x->x_end = end = end > npts ? npts : end < 0 ? 0 : end;
    if(x->x_start > x->x_end){
//        post("x->x_start (%llu) / x->x_end (%llu)", x->x_start, x->x_end);
        unsigned long long temp = x->x_start;
        x->x_start = x->x_end ;
        x->x_end = temp;
//        post("x->x_start (%llu) / x->x_end (%llu)", x->x_start, x->x_end);
    }
    unsigned long long rangesamp = x->x_rangesamp = x->x_end - x->x_start;
    unsigned long long fadesamp = (unsigned long long)(x->x_fadems * a_sr);
    //boundschecking
    if(fadesamp > rangesamp / 2)
        fadesamp = rangesamp / 2;
    else if(fadesamp < 0)
        fadesamp = 0;
    unsigned long long stxsamp, endxsamp;
    // if (isneg), end pts of loop come before the loop end points in the buffer,
    //if pos, come after
    stxsamp = x->x_start;
    endxsamp = x->x_end;
    if(stxsamp < 0)
        stxsamp = 0;
    if(endxsamp < 0)
        endxsamp = 0;
    x->x_stxsamp = stxsamp;
    x->x_endxsamp = endxsamp;
    x->x_fadesamp = fadesamp;
}

static void tabplayer_set(t_play *x, t_symbol *s){
    buffer_setarray(x->x_buffer, s);
    x->x_npts = x->x_buffer->c_npts;
    x->x_sr_ratio = x->x_array_sr_khz/x->x_sr;
}

/*static void tabplayer_arraysr(t_play *x, t_floatarg f){
    //sample rate of array in samp/sec
    if(f <= 1)
        f = 1;
    x->x_array_sr_khz = f * 0.001;
    x->x_sr_ratio = x->x_array_sr_khz/x->x_sr;
    tabplayer_ms2samp(x);
}*/

static void tabplayer_fade(t_play *x, t_floatarg f){
    x->x_fadems = f < 0 ? 0 : f;
    tabplayer_ms2samp(x);
}

static void tabplayer_range(t_play *x, t_floatarg f1, t_floatarg f2){
    x->x_stms = f1 < 0 ? 0 : f1;
    x->x_endms = f2;
    tabplayer_ms2samp(x);
}

static void tabplayer_reset(t_play *x){
    x->x_start = 0;
    x->x_end = x->x_npts;
}

static void tabplayer_speed(t_play *x, t_floatarg f){
    x->x_rate = f / 100;
}

static void tabplayer_start(t_play *x, t_floatarg f){
    x->x_stms = f < 0 ? 0 : f;
    tabplayer_ms2samp(x);
}

static void tabplayer_end(t_play *x, t_floatarg f){
    x->x_endms = f < 0 ? 0 : f;
    tabplayer_ms2samp(x);
}

static void tabplayer_bang(t_play *x){
    x->x_playing = x->x_playnew = 1; // start playing
}

static void tabplayer_play(t_play *x, t_symbol *s, int ac, t_atom *av){
    s = NULL;
    if(ac){ // args: start (ms) / end (ms), rate
/*        t_float stms = x->x_stms;
        t_float endms = x->x_endms;
        t_float rate = x->x_rate;*/
        float stms = 0;
        float endms = SHARED_FLT_MAX;
        float rate = 1;
        int argnum = 0;
        while(ac){
            if(av->a_type == A_FLOAT){
                switch(argnum){
                    case 0:
                        stms = atom_getfloatarg(0, ac, av);
                        if(stms < 0)
                            stms = 0;
                        break;
                    case 1:
                        endms = atom_getfloatarg(0, ac, av);
                        if(endms < 0)
                            endms = 0;
                        break;
                    case 2:
                        rate = atom_getfloatarg(0, ac, av) * 0.01;
                        break;
                    default:
                        break;
                };
                argnum++;
            };
            ac--, av++;
        };
        x->x_stms = stms;
        x->x_endms = endms;
        x->x_rate = rate;
        tabplayer_ms2samp(x); // calculate sample equivalents
    }
    tabplayer_bang(x);
}

static void tabplayer_stop(t_play *x){
    if(x->x_playing){
        x->x_playing = x->x_playnew = 0;
        outlet_bang(x->x_donelet);
    };
}

static void tabplayer_float(t_play *x, t_floatarg f){
    f > 0 ? x->x_playing = x->x_playnew = 1 : tabplayer_stop(x);
}

static void tabplayer_pause(t_play *x){
    x->x_playing = 0;
}

static void tabplayer_resume(t_play *x){
    x->x_playing = 1;
}

static void tabplayer_loop(t_play *x, t_floatarg f){
    x->x_loop = f > 0 ? 1 : 0;
}

static double tabplayer_interp(t_play *x, int chidx, double phase){
    int ndx;
    double out;
    t_word **vectable = x->x_buffer->c_vectors;
    int npts = x->x_npts;
    int maxindex = npts - 3;
    if(phase < 0 || phase > maxindex)
        phase = 0;  // CHECKED: a value 0, not ndx 0
    ndx = (int)phase;
    float f,  a,  b,  c,  d, cmb;
    if(ndx < 1)
        ndx = 1, f = 0;
    else if(ndx > maxindex)
        ndx = maxindex, f = 1;
    else f = phase - ndx;
    t_word *vp = vectable[chidx];
    if(vp){
        vp += ndx;
        a = vp[-1].w_float;
        b = vp[0].w_float;
        c = vp[1].w_float;
        d = vp[2].w_float;
        cmb = c-b;
        // lagrange
        out = b + f*(cmb - ONE_SIXTH*(1. - f)*((d - a - 3.0f*cmb)*f + (d + 2.0f*a - 3.0f*b)));
        double fade = -1;
        if(phase < (x->x_start + x->x_fadesamp)){
            fade = (phase - x->x_start) / x->x_fadesamp;
            out *= sin(fade*HALF_PI);
        }
        else if(phase > (x->x_end - x->x_fadesamp)){
            fade = (phase - (x->x_end - x->x_fadesamp)) / x->x_fadesamp;
            out *= cos(fade*HALF_PI);
        }
    }
    else
        out = 0;
    return(out);
}

static t_int *tabplayer_perform(t_int *w){
    t_play *x = (t_play *)(w[1]);
    t_buffer *buffer = x->x_buffer;
    int n = (int)(w[2]);
    int ch = x->x_numchans, chidx, i;
    if(buffer->c_playable){
        if(x->x_hasfeeders){ // signal input present, indexing into array
            t_float *xin = x->x_ivec;
            for(i = 0; i < n; i++){
                float phase = *xin++;
                for(chidx = 0; chidx < ch; chidx++){
                    t_float *out = *(x->x_ovecs+chidx);
                    out[i] = tabplayer_interp(x, chidx, phase);
                };
            };
        }
        else{ // no signal input present, auto playback mode
            if(x->x_playing){
                double output;
                double gain;
                unsigned long long npts = x->x_npts;
                unsigned long long start = x->x_start;
                unsigned long long end = x->x_end;
                int isneg = x->x_rate < 0;
                int loop = x->x_loop;
                unsigned long long rangesamp = x->x_rangesamp;
                int ramping = 0; //if we're ramping
                if(x->x_playnew){ // if starting to play this block
                    x->x_phase = isneg ? (double)end : (double)start;
                    if(loop) // 1st ramp can't have the end of the loop fading out
                        x->x_rfirst = 1;
                    x->x_playnew = 0;
                };
                for(i = 0; i < n; i++){
                    double phase = x->x_phase;
                    double fadephase, fadegain;
                    if(isneg){ // play backwards
                        if(phase < start){
                            if(loop){ // restart
                                phase = (double)(end - start) - phase;
                                outlet_bang(x->x_donelet);
                            }
                            else{ // done playing
                                if(x->x_playing)
                                    outlet_bang(x->x_donelet);
                                x->x_playing = 0;
                            };
                        }
                        if(loop){  // check loop conditions
                            // if in the xfade period, calculate gain of fading in loop
                            if(phase > x->x_stxsamp && phase <= start){
                                gain = (double)(start - phase)/(double)x->x_fadesamp;
                                ramping = 1;
                                if(x->x_rfirst == 0){ // if not the first ramp, need the fade out ramp
                                    fadephase = phase - (double)rangesamp;
                                    fadegain = 1.-gain;
                                    // boundschecking
                                    if(fadephase < 0)
                                        fadephase = 0;
                                    else if(fadephase >= start)
                                        fadephase = (double)start;
                                    if(fadegain < 0)
                                        fadegain = 0.;
                                };
                            }
                            else if(x->x_rfirst) // if we just finished the first ramp, flag it
                                x->x_rfirst = 0;
                        };
                    }
                    else{ // forwards
                        //boundschecking for phase
                        if(phase > end){
                            if(loop){ // loop
                                phase = (double)start + phase - (double)end;
                                outlet_bang(x->x_donelet);
                            }
                            else{ //we're done
                                if(x->x_playing)
                                    outlet_bang(x->x_donelet);
                                x->x_playing = 0;
                            };
                        }
                        else if(phase < start)
                            phase = (double)start;
                        if(loop){ // check loop conditions
                            //if in the xfade period, calculate gain of fading in loop
                            if(phase < x->x_stxsamp && phase >= start){
                                gain = (double)(phase-start)/(double)x->x_fadesamp;
                                ramping = 1;
                                if(x->x_rfirst == 0){
                                    //if not the first ramp, need the fade out ramp
                                    fadephase = phase + (double)rangesamp;
                                    fadegain = 1.-gain;
                                    //boundschecking
                                    if(fadephase >= npts)
                                        fadephase = npts - 1;
                                    else if(fadephase <= start)
                                        fadephase = (double)start;
                                    if(fadegain < 0)
                                        fadegain = 0.;
                                };
                            }
                            else if(x->x_rfirst) // if we just finished the first ramp, flag it
                                x->x_rfirst = 0;
                        };
                    };
                    // reading output vals (for both forwards and backwards)
                    int rfirst = x->x_rfirst;
                    for(chidx = 0; chidx < ch; chidx++){
                        t_float *out = *(x->x_ovecs+chidx);
                        if(x->x_playing){
                            output = tabplayer_interp(x, chidx, phase);
                            if(ramping){
                                output *= gain;
                                if(!rfirst){ // if not the first ramp, need the fading out ramp
                                    double out2 = tabplayer_interp(x, chidx, fadephase);
                                    out2 *= fadegain;
                                    output += out2;
                                };
                            };
                        }
                        else
                            output = 0.;
                        out[i] = output;
                    };
                    x->x_phase = phase + x->x_sr_ratio*x->x_rate; // increment for both forwards/backwards
                };
            }
            else //not playing, just output zeros
                goto nullstate;
        };
    }
    else{
        nullstate:
            for(chidx = 0; chidx < ch; chidx++){
                t_float *out = *(x->x_ovecs+chidx);
                int nblock = n;
                while(nblock--)
                    *out++ = 0;
            };
    };
    return(w+3);
}

/*
static t_int *tabplayer_perform(t_int *w){
    t_play *x = (t_play *)(w[1]);
    t_buffer *buffer = x->x_buffer;
    int n = (int)(w[2]);
    int ch = x->x_numchans, chidx, i;
    if(buffer->c_playable){
        if(x->x_playing){
            int start = x->x_start;
            int end = x->x_end;
            int isneg = x->x_rate < 0;
            if(x->x_playnew){ // if starting to play on this block
                x->x_phase = isneg ? (double)end : (double)start;
                x->x_playnew = 0;
            };
            for(i = 0; i < n; i++){
                for(chidx = 0; chidx < ch; chidx++){
                    t_float *out = *(x->x_ovecs+chidx);
                    out[i] = tabplayer_interp(x, chidx, (double)x->x_phase);
                };
                x->x_phase += x->x_rate;
                if(x->x_phase < x->x_start || x->x_phase > x->x_end){
                    if(x->x_loop)
                        x->x_phase = isneg ? (double)end : (double)start;
                    else
                        x->x_playing = 0;
                }
            };
        }
        else //not playing, just output zeros
            goto nullstate;
    }
    else{
        nullstate:
        for(i = 0; i < n; i++){
            for(chidx = 0; chidx < ch; chidx++){
                t_float *out = *(x->x_ovecs+chidx);
                out[i] = 0;
            };
        }
    };
    return(w+3);
}
*/

static void tabplayer_dsp(t_play *x, t_signal **sp){
    buffer_checkdsp(x->x_buffer);
    unsigned long long npts = x->x_buffer->c_npts;
    x->x_hasfeeders = magic_inlet_connection((t_object *)x, x->x_glist, 0, &s_signal);
    t_float pdksr= sp[0]->s_sr * 0.001;
    x->x_sr = pdksr;
    x->x_sr_ratio = (double)(x->x_array_sr_khz/x->x_sr);
    if(npts != x->x_npts){
        x->x_npts = npts;
        tabplayer_ms2samp(x); // recalculate sample equivalents
    };
    int i, n = sp[0]->s_n;
    t_signal **sigp = sp;
    x->x_ivec = (*sigp++)->s_vec;
    for (i = 0; i < x->x_numchans; i++) //input vectors first
        *(x->x_ovecs+i) = (*sigp++)->s_vec;
    dsp_add(tabplayer_perform, 2, x, n);
}

static void *tabplayer_free(t_play *x){
    buffer_free(x->x_buffer);
    freebytes(x->x_ovecs, x->x_numchans * sizeof(*x->x_ovecs));
    outlet_free(x->x_donelet);
    return (void *)x;
}

static void *tabplayer_new(t_symbol * s, int ac, t_atom *av){
    t_symbol *arrname = NULL;
    t_float channels = 1;
    t_float fade = 0;
    int loop = 0;
    int nameset = 0;
    while(ac){
        if(av->a_type == A_SYMBOL){ // if name not passed so far, count arg as array name
            if(!nameset){
                arrname = atom_getsymbolarg(0, ac, av);
                ac--, av++;
                nameset = 1;
            }
            else{ // flag
                s = atom_getsymbolarg(0, ac, av);
                if(s == gensym("-loop")){
                    loop = 1;
                    ac--, av++;
                }
                else if(s == gensym("-fade") && ac > 2){
                    float f = atom_getfloatarg(0, ac, av);
                    fade = f < 0 ? 0 : f;
                    ac-=2, av+=2;
                }
                else
                    goto errstate;
            }
        }
        else{
            if(nameset){
                channels = atom_getfloatarg(0, ac, av);
                ac--, av++;
            }
            else
                goto errstate;
        }
    };
    // one auxiliary signal:  position input
    int chn_n = (int)channels > 64 ? 64 : (int)channels;
    t_play *x = (t_play *)pd_new(tabplayer_class);
    x->x_glist = canvas_getcurrent();
    x->x_hasfeeders = 0;
    x->x_sr = (float)sys_getsr() * 0.001;
    x->x_array_sr_khz = x->x_sr; // set sample rate of array as pd's sample rate for now
    x->x_buffer = buffer_init((t_class *)x, arrname, chn_n, 0);
    if(x->x_buffer){
        int ch = x->x_buffer->c_numchans;
        x->x_npts = x->x_buffer->c_npts;
        x->x_numchans = ch;
        x->x_ovecs = getbytes(x->x_numchans * sizeof(*x->x_ovecs));
        while(ch--)
            outlet_new((t_object *)x, &s_signal);
        x->x_donelet = outlet_new(&x->x_obj, &s_bang);
        x->x_playing = 0;
        x->x_playnew = 0;
        x->x_loop = loop;
        x->x_fadems = fade;
        //defaults for start, end, and duration
        x->x_stms = 0;
        x->x_endms = SHARED_FLT_MAX;
        x->x_rate = 1;
        tabplayer_ms2samp(x);
    }
    return(x);
    errstate:
        pd_error(x, "[tabplayer~]: improper args");
        return(NULL);
}

void tabplayer_tilde_setup(void){
    tabplayer_class = class_new(gensym("tabplayer~"), (t_newmethod)tabplayer_new, (t_method)tabplayer_free,
        sizeof(t_play), 0, A_GIMME, 0);
    class_domainsignalin(tabplayer_class, -1);
    class_addbang(tabplayer_class, tabplayer_bang);
    class_addfloat(tabplayer_class, tabplayer_float);
    class_addmethod(tabplayer_class, (t_method)tabplayer_dsp, gensym("dsp"), A_CANT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_set, gensym("set"), A_SYMBOL, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_play, gensym("play"), A_GIMME, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_stop, gensym("stop"), 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_pause, gensym("pause"), 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_resume, gensym("resume"), 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_reset, gensym("reset"), 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_start, gensym("start"), A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_end, gensym("end"), A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_range, gensym("range"), A_FLOAT, A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_speed, gensym("speed"), A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_loop, gensym("loop"), A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_fade, gensym("fade"), A_FLOAT, 0);
/*    class_addmethod(tabplayer_class, (t_method)tabplayer_mode, gensym("mode"), A_FLOAT, 0);
    class_addmethod(tabplayer_class, (t_method)tabplayer_arraysr, gensym("arraysr"), A_FLOAT, 0); */
}
