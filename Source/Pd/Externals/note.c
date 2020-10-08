// based on our work in cyclone's comment

#include <string.h>
#include <ctype.h>
#include "m_pd.h"
#include "g_canvas.h"

#define note_LMARGIN     1
#define note_RMARGIN     1
#define note_TMARGIN     2
#define note_BMARGIN     2
#define note_MINWIDTH    8
#define note_HANDLEWIDTH 8
#define note_OUTBUFSIZE  1000
#define note_NUMCOLORS   3

typedef struct _note{
    t_object        x_obj;
    t_glist        *x_glist;
    t_canvas       *x_canvas;
    t_symbol       *x_bindsym;
    char            x_tag[32];
    char            x_texttag[32];
    char            x_outlinetag[32];
    t_clock        *x_transclock;
    t_binbuf       *x_binbuf;
    char           *x_textbuf;
    int             x_textbufsize;
    int             x_pixwidth;
    int             x_bbset;
    int             x_bbpending;
    int             x_x1;
    int             x_y1;
    int             x_x2;
    int             x_y2;
    int             x_newx2;
    int             x_dragon;
    int             x_fontsize;    // requested size
    t_symbol       *x_fontfamily;  // requested family
    int             x_fontprops;   // 0: reg, 1: bold, 2: italic, 3: bolditalic (unused)
    t_symbol       *x_encoding;    // requested encoding (unused)
    unsigned char   x_red;
    unsigned char   x_green;
    unsigned char   x_blue;
    char            x_color[8];
    int             x_selstart;
    int             x_selend;
    int             x_active;
    int             x_ready;
    t_symbol       *x_receive_sym;
    int             x_rcv_set;
    int             x_flag;
    t_symbol       *x_rcv_unexpanded;
}t_note;

static t_class *note_class;
static t_class *notesink_class;

static t_pd *notesink = 0;

static void note_receive(t_note *x, t_symbol *s){
    t_symbol *rcv = canvas_realizedollar(x->x_glist, x->x_rcv_unexpanded = s);
    if(rcv == gensym("empty"))
        rcv = &s_;
    if(rcv != &s_){
        if(rcv != x->x_receive_sym){
            canvas_dirty(x->x_glist, 1);
            if(x->x_receive_sym != &s_)
                pd_unbind(&x->x_obj.ob_pd, x->x_receive_sym);
            pd_bind(&x->x_obj.ob_pd, x->x_receive_sym = rcv);
        }
    }
    else{
        canvas_dirty(x->x_glist, 1);
        if(x->x_receive_sym != &s_)
            pd_unbind(&x->x_obj.ob_pd, x->x_receive_sym);
        x->x_receive_sym = rcv;
    }
}

static void note_set_receive(t_note *x, t_symbol *s){
    x->x_rcv_set = 1;
    note_receive(x, s);
}

static void note_draw(t_note *x){
    char buf[note_OUTBUFSIZE], *outbuf, *outp;
    unsigned long cv = (unsigned long)x->x_canvas;
    int reqsize = x->x_textbufsize + 250;  // FIXME estimation
    if(reqsize > note_OUTBUFSIZE){ // <= seems unnecessary (porres)
        if(!(outbuf = getbytes(reqsize)))
            return;
    }
    outp = outbuf = buf;
    sprintf(outp, "note_draw %s .x%lx.c %s %s %f %f %s -%d %s %s {%.*s} %d\n",
            x->x_bindsym->s_name, cv, x->x_texttag, x->x_tag,
            (float)(text_xpix((t_text *)x, x->x_glist) + note_LMARGIN),
            (float)(text_ypix((t_text *)x, x->x_glist) + note_TMARGIN),
            x->x_fontfamily->s_name, x->x_fontsize,
            (glist_isselected(x->x_glist, &x->x_glist->gl_gobj) ? "blue" : x->x_color),
            "\"\"", // encoding <= remove!!!
            x->x_textbufsize, x->x_textbuf, x->x_pixwidth);
    x->x_bbpending = 1;
    sys_gui(outbuf);
    if(outbuf != buf) freebytes(outbuf, reqsize);
}

static void note_update(t_note *x){
    char buf[note_OUTBUFSIZE], *outbuf, *outp;
    unsigned long cv = (unsigned long)x->x_canvas;
    int reqsize = x->x_textbufsize + 250;  // FIXME estimation
    if (reqsize > note_OUTBUFSIZE){ // <= seems unnecessary (porres)
        if(!(outbuf = getbytes(reqsize)))
            return;
    }
    outp = outbuf = buf;
    sprintf(outp, "note_update .x%lx.c %s %s {%.*s} %d\n", cv,
            x->x_texttag, (x->x_encoding ? x->x_encoding->s_name : "\"\""),
            x->x_textbufsize, x->x_textbuf, x->x_pixwidth);
    outp += strlen(outp);
    if(x->x_active){
        if(x->x_selend > x->x_selstart){
            sprintf(outp, ".x%lx.c select from %s %d\n", cv, x->x_texttag, x->x_selstart);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c select to %s %d\n", cv, x->x_texttag, x->x_selend);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c focus {}\n", cv);
        }
        else{
            sprintf(outp, ".x%lx.c select clear\n", cv);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c icursor %s %d\n", cv, x->x_texttag, x->x_selstart);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c focus %s\n", cv, x->x_texttag);
        }
        outp += strlen(outp);
    }
    sprintf(outp, "note_bbox %s .x%lx.c %s\n",
            x->x_bindsym->s_name, cv, x->x_texttag);
    x->x_bbpending = 1;
    sys_gui(outbuf);
    if (outbuf != buf) freebytes(outbuf, reqsize);
}

static void note_validate(t_note *x, t_glist *glist){
    if(!x->x_ready){
        if(x->x_textbuf)
            freebytes(x->x_textbuf, x->x_textbufsize);
        binbuf_gettext(x->x_binbuf, &x->x_textbuf, &x->x_textbufsize);
        x->x_ready = 1;
    }
    if(glist){
        if(glist != x->x_glist){
            post("bug [note]: note_getcanvas");
            x->x_glist = glist;
        }
        x->x_canvas = glist_getcanvas(glist);
    }
}

static void note_grabbedkey(void *z, t_floatarg f){
    z = NULL;
    f = 0;
}

static void note_dograb(t_note *x){
    /* LATER investigate the grabbing feature.
     Here we use it just to prevent backspace from erasing entire text.
     This has to be done also when we are already active, because
     after being clicked at we have lost our previous grab. */
    glist_grab(x->x_glist, (t_gobj *)x, 0, note_grabbedkey, 0, 0);
}

static void note__bboxhook(t_note *x, t_symbol *bindsym,
    t_floatarg x1, t_floatarg y1, t_floatarg x2, t_floatarg y2){
    bindsym = NULL;
    x->x_x1 = x1;
    x->x_y1 = y1;
    x->x_x2 = x2;
    x->x_y2 = y2;
    x->x_bbset = 1;
    x->x_bbpending = 0;
}

static void note__clickhook(t_note *x, t_symbol *s, int ac, t_atom *av){
    t_symbol *dummy = s;
    dummy = NULL;
    int xx, yy, ndx;
    if(ac == 8 && av->a_type == A_SYMBOL
       && av[1].a_type == A_FLOAT && av[2].a_type == A_FLOAT
       && av[3].a_type == A_FLOAT
       && av[4].a_type == A_FLOAT && av[5].a_type == A_FLOAT
       && av[6].a_type == A_FLOAT && av[7].a_type == A_FLOAT){
        xx = (int)av[1].a_w.w_float;
        yy = (int)av[2].a_w.w_float;
        ndx = (int)av[3].a_w.w_float;
        note__bboxhook(x, av->a_w.w_symbol,
                          av[4].a_w.w_float, av[5].a_w.w_float,
                          av[6].a_w.w_float, av[7].a_w.w_float);
    }
    else{
        post("bug [note]: note__clickhook");
        return;
    }
    if(x->x_glist->gl_edit){
        if(x->x_active){
            if(ndx >= 0 && ndx < x->x_textbufsize){
                // set selection, LATER shift-click and drag
                x->x_selstart = x->x_selend = ndx;
                note_dograb(x);
                note_update(x);
            }
        }
        else if(xx > x->x_x2 - note_HANDLEWIDTH){ // start resizing
            char buf[note_OUTBUFSIZE], *outp = buf;
            unsigned long cv = (unsigned long)x->x_canvas;
            sprintf(outp, ".x%lx.c bind %s <ButtonRelease> \
                    {pdsend {%s _release %s}}\n", cv, x->x_texttag,
                    x->x_bindsym->s_name, x->x_bindsym->s_name);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c bind %s <Motion> \
                    {pdsend {%s _motion %s %%x %%y}}\n", cv, x->x_texttag,
                    x->x_bindsym->s_name, x->x_bindsym->s_name);
            outp += strlen(outp);
            sprintf(outp, ".x%lx.c create rectangle %d %d %d %d -outline blue \
                    -tags {%s %s}\n",
                    cv, x->x_x1, x->x_y1, x->x_x2, x->x_y2,
                    x->x_outlinetag, x->x_tag);
            sys_gui(buf);
            x->x_newx2 = x->x_x2;
            x->x_dragon = 1;
        }
    }
}

static void note__releasehook(t_note *x, t_symbol *bindsym){
    bindsym = NULL;
    unsigned long cv = (unsigned long)x->x_canvas;
    sys_vgui(".x%lx.c bind %s <ButtonRelease> {}\n", cv, x->x_texttag);
    sys_vgui(".x%lx.c bind %s <Motion> {}\n", cv, x->x_texttag);
    sys_vgui(".x%lx.c delete %s\n", cv, x->x_outlinetag);
    x->x_dragon = 0;
    if(x->x_newx2 != x->x_x2){
        x->x_pixwidth = x->x_newx2 - x->x_x1;
        x->x_x2 = x->x_newx2;
        note_update(x);
    }
}

static void note__motionhook(t_note *x, t_symbol *bindsym, t_floatarg xx, t_floatarg yy){
    bindsym = NULL;
    yy = 0;
    unsigned long cv = (unsigned long)x->x_canvas;
    if(xx > x->x_x1 + note_MINWIDTH)
        sys_vgui(".x%lx.c coords %s %d %d %d %d\n", cv, x->x_outlinetag,
            x->x_x1, x->x_y1, x->x_newx2 = xx, x->x_y2);
}

static void notesink__bboxhook(t_pd *x, t_symbol *bindsym,
t_floatarg x1, t_floatarg y1, t_floatarg x2, t_floatarg y2){
    x1 = x2 = y1 = y2 = 0;
    if(bindsym->s_thing == x){
        pd_unbind(x, bindsym);  // if note gone, unbind
    }
}

static void notesink_anything(t_pd *x, t_symbol *s, int ac, t_atom *av){
    // nop (just avoid Pd warnings)
    x = NULL;
    s = NULL;
    ac = (int)av;
}

static void note_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2){
    t_note *x = (t_note *)z;
    int width,  height;
    float x1, y1, x2, y2;
    note_validate(x, glist);
    if((width = x->x_pixwidth) < 1) // FIXME estimation
        width = x->x_fontsize * x->x_textbufsize;
    width += note_LMARGIN + note_RMARGIN;
    // FIXME estimation
    height = x->x_fontsize + note_TMARGIN + note_BMARGIN;
    x1 = text_xpix((t_text *)x, glist);
    y1 = text_ypix((t_text *)x, glist) + 1;  // LATER revisit
    x2 = x1 + width;
    y2 = y1 + height - 2;  // LATER revisit
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}

static void note_displace(t_gobj *z, t_glist *glist, int dx, int dy){
    t_note *x = (t_note *)z;
    if(!x->x_active && !x->x_dragon){  // LATER rethink
        t_text *t = (t_text *)z;
        note_validate(x, glist);
        t->te_xpix += dx;
        t->te_ypix += dy;
        if(x->x_bbset){
            x->x_x1 += dx;
            x->x_y1 += dy;
            x->x_x2 += dx;
            x->x_y2 += dy;
        }
        if(glist_isvisible(glist)){
            t_canvas *cv = glist_getcanvas(glist);
            sys_vgui(".x%lx.c move %s %d %d\n", x->x_canvas, x->x_tag, dx, dy);
            canvas_fixlinesfor(cv, t);
        }
    }
}

static void note_activate(t_gobj *z, t_glist *glist, int state){
    t_note *x = (t_note *)z;
    note_validate(x, glist);
    if(state){
        note_dograb(x);
        if (x->x_active)
            return;
        sys_vgui(".x%lx.c focus %s\n", x->x_canvas, x->x_texttag);
        x->x_selstart = 0;
        x->x_selend = x->x_textbufsize;
        x->x_active = 1;
        pd_bind((t_pd *)x, gensym("#key"));
        pd_bind((t_pd *)x, gensym("#keyname"));
    }
    else{
        if (!x->x_active)
            return;
        pd_unbind((t_pd *)x, gensym("#key"));
        pd_unbind((t_pd *)x, gensym("#keyname"));
        sys_vgui("selection clear .x%lx.c\n", x->x_canvas);
        sys_vgui(".x%lx.c focus {}\n", x->x_canvas);
        x->x_active = 0;
    }
    note_update(x);
}

static void note_select(t_gobj *z, t_glist *glist, int state){
    t_note *x = (t_note *)z;
    note_validate(x, glist);
    if(!state && x->x_active) note_activate(z, glist, 0);
    sys_vgui(".x%lx.c itemconfigure %s -fill %s\n", x->x_canvas,
        x->x_texttag, (state ? "blue" : x->x_color));
    /* A regular rtext should now set 'canvas_editing' variable to its canvas,
     but we do not do that, because we get the keys through a global binding
     to "#key" (and because 'canvas_editing' is not exported). */
}

static void note_delete(t_gobj *z, t_glist *glist){
    canvas_deletelinesfor(glist, (t_text *)z);
}

static void note_vis(t_gobj *z, t_glist *glist, int vis){
    t_note *x = (t_note *)z;
    note_validate(x, glist);
    if(vis) note_draw(x);
    else sys_vgui(".x%lx.c delete %s\n", x->x_canvas, x->x_tag);
}
 
static void note_save(t_gobj *z, t_binbuf *b){
    t_note *x = (t_note *)z;
    t_binbuf *bb = x->x_obj.te_binbuf;
    if(!x->x_rcv_set){ // no receive set, search arguments
        int n_args = binbuf_getnatom(bb); // number of arguments
        if(n_args > 0){ // we have arguments, let's search them
            char buf[80];
            if(x->x_flag){ // search for receive name in flag
                for(int i = 0;  i < n_args; i++){
                    atom_string(binbuf_getvec(bb) + i, buf, 80);
                    if(!strcmp(buf, "-receive")){
                        i++;
                        atom_string(binbuf_getvec(bb) + i, buf, 80);
                        x->x_rcv_unexpanded = gensym(buf);
                        break;
                    }
                }
            }
            else{ // search receive argument
                int arg_n = 4; // receive argument number
                if(n_args >= arg_n){ // we have it, get it
                    atom_string(binbuf_getvec(bb) + arg_n, buf, 80);
                    x->x_rcv_unexpanded = gensym(buf);
                }
            }
        }
        if(x->x_rcv_unexpanded == &s_) // if nothing found, set to "empty"
            x->x_rcv_unexpanded = gensym("empty");
    }
    binbuf_addv(b, "ssiisiissiiii",
                gensym("#X"),
                gensym("obj"),
                (int)x->x_obj.te_xpix,
                (int)x->x_obj.te_ypix,
                atom_getsymbol(binbuf_getvec(bb)),
                x->x_pixwidth,
                x->x_fontsize,
                x->x_fontfamily,
                x->x_rcv_unexpanded,
                x->x_fontprops,
                (int)x->x_red,
                (int)x->x_green,
                (int)x->x_blue);
    binbuf_addbinbuf(b, x->x_binbuf); // the actual note
    binbuf_addv(b, ";");
}

static t_widgetbehavior note_widgetbehavior ={
    note_getrect,
    note_displace,
    note_select,
    note_activate,
    note_delete,
    note_vis,
    0,
};

// this fires if a transform request was sent to a symbol we are bound to
static void note_transtick(t_note *x){
    glist_delete(x->x_glist, (t_gobj *)x);
}

// what follows is basically the original code of rtext_key()
static void note_float(t_note *x, t_float f){
    if(x->x_active){
        int keynum = (int)f;
        if(keynum){
            int i, newsize, ndel;
            int n = keynum;
            if (n == '\r') n = '\n';
            if (n == '\b'){
                if ((!x->x_selstart) && (x->x_selend == x->x_textbufsize)){
                    goto donefloat;
                }
                else if (x->x_selstart && (x->x_selstart == x->x_selend))
                    x->x_selstart--;
            }
            ndel = x->x_selend - x->x_selstart;
            for (i = x->x_selend; i < x->x_textbufsize; i++)
                x->x_textbuf[i- ndel] = x->x_textbuf[i];
            newsize = x->x_textbufsize - ndel;
            x->x_textbuf = resizebytes(x->x_textbuf, x->x_textbufsize, newsize);
            x->x_textbufsize = newsize;
            if(n == '\n' || !iscntrl(n)){
                newsize = x->x_textbufsize+1;
                x->x_textbuf = resizebytes(x->x_textbuf, x->x_textbufsize, newsize);
                for(i = x->x_textbufsize; i > x->x_selstart; i--)
                    x->x_textbuf[i] = x->x_textbuf[i-1];
                x->x_textbuf[x->x_selstart] = n;
                x->x_textbufsize = newsize;
                x->x_selstart = x->x_selstart + 1;
            }
            x->x_selend = x->x_selstart;
            x->x_glist->gl_editor->e_textdirty = 1;
            binbuf_text(x->x_binbuf, x->x_textbuf, x->x_textbufsize);
            note_update(x);
        }
    }
    else post("bug [note]: note_float");
donefloat:;
}

static void note_list(t_note *x, t_symbol *s, int ac, t_atom *av){
    t_symbol *dummy = s;
    dummy = NULL;
    if (!x->x_active)
        post("bug [note]: note_list");
    else if(ac > 1 && av->a_type == A_FLOAT && (int)av->a_w.w_float && av[1].a_type == A_SYMBOL){
        t_symbol *keysym = av[1].a_w.w_symbol;
        if (!strcmp(keysym->s_name, "Right")){
            if (x->x_selend == x->x_selstart &&
                x->x_selstart < x->x_textbufsize)
                x->x_selend = x->x_selstart = x->x_selstart + 1;
            else
                x->x_selstart = x->x_selend;
        }
        else if (!strcmp(keysym->s_name, "Left")){
            if (x->x_selend == x->x_selstart && x->x_selstart > 0)
                x->x_selend = x->x_selstart = x->x_selstart - 1;
            else
                x->x_selend = x->x_selstart;
        }
        // this should be improved...  life's too short
        else if (!strcmp(keysym->s_name, "Up")){
            if (x->x_selstart)
                x->x_selstart--;
            while (x->x_selstart > 0 && x->x_textbuf[x->x_selstart] != '\n')
                x->x_selstart--;
            x->x_selend = x->x_selstart;
        }
        else if (!strcmp(keysym->s_name, "Down")){
            while (x->x_selend < x->x_textbufsize &&
                   x->x_textbuf[x->x_selend] != '\n')
                x->x_selend++;
            if (x->x_selend < x->x_textbufsize)
                x->x_selend++;
            x->x_selstart = x->x_selend;
        }
        else goto donelist;
        note_update(x);
    }
donelist:;
}

static void note_free(t_note *x){
    if (x->x_active){
        pd_unbind((t_pd *)x, gensym("#key"));
        pd_unbind((t_pd *)x, gensym("#keyname"));
    }
    if(x->x_receive_sym != &s_)
        pd_unbind(&x->x_obj.ob_pd, x->x_receive_sym);
    if (x->x_transclock) clock_free(x->x_transclock);
    if(x->x_bindsym){
        pd_unbind((t_pd *)x, x->x_bindsym);
        if(!x->x_bbpending)
            pd_unbind(notesink, x->x_bindsym);
    }
    if(x->x_binbuf && !x->x_ready) binbuf_free(x->x_binbuf);
    if(x->x_textbuf) freebytes(x->x_textbuf, x->x_textbufsize);
}

static void note_set(t_note *x, t_symbol *s, int argc, t_atom * argv){
    t_symbol *dummy = s;
    dummy = NULL;
    if(argc){
        binbuf_clear(x->x_binbuf);
        binbuf_restore(x->x_binbuf, argc, argv);
        binbuf_gettext(x->x_binbuf, &x->x_textbuf, &x->x_textbufsize);
        sys_vgui(".x%lx.c delete %s\n", x->x_canvas, x->x_tag);
        canvas_dirty(x->x_glist, 1);
        note_draw(x);
    }
}

static void note_rgb(t_note *x, t_floatarg r, t_floatarg g, t_floatarg b){
    x->x_red = (unsigned char)r;
    x->x_green = (unsigned char)g;
    x->x_blue = (unsigned char)b;
    sprintf(x->x_color, "#%2.2x%2.2x%2.2x", x->x_red, x->x_green, x->x_blue);
    note_update(x);
    sys_vgui(".x%lx.c delete %s\n", x->x_canvas, x->x_tag);
    canvas_dirty(x->x_glist, 1);
    note_draw(x);
}

static void note_name(t_note *x, t_symbol *name){
    x->x_fontfamily = name;
    note_update(x);
    sys_vgui(".x%lx.c delete %s\n", x->x_canvas, x->x_tag);
    canvas_dirty(x->x_glist, 1);
    note_draw(x);
}

static void note_size(t_note *x, t_floatarg f){
    x->x_fontsize = (int)f < 5 ? 5 : (int)f;
    note_update(x);
    sys_vgui(".x%lx.c delete %s\n", x->x_canvas, x->x_tag);
    canvas_dirty(x->x_glist, 1);
    note_draw(x);
}

static void note_flag_parser(t_note *x, int argc, t_atom * argv){
    t_atom* comlist = t_getbytes(argc * sizeof(*comlist));
    int i, comlen = 0; //eventual length of note list comlist
    for(i = 0; i < argc; i++){
        if(argv[i].a_type == A_FLOAT){
            SETFLOAT(&comlist[comlen], argv[i].a_w.w_float);
            comlen++;
        }
        else if(argv[i].a_type == A_SYMBOL){
            t_symbol * cursym = argv[i].a_w.w_symbol;
            if(!strcmp(cursym->s_name, "-size")){
                i++;
                if((argc-i) > 0){
                    if(argv[i].a_type == A_FLOAT){
                        int fontsize = (int)argv[i].a_w.w_float;
                        x->x_fontsize = fontsize;
                    }
                    else i--;
                };
            }
            else if(!strcmp(cursym->s_name, "-name")){
                i++;
                if((argc-i) > 0){
                    if(argv[i].a_type == A_SYMBOL) x->x_fontfamily = argv[i].a_w.w_symbol;
                    else i--;
                };
            }
            else if(!strcmp(cursym->s_name, "-receive")){
                x->x_flag = 1;
                i++;
                if((argc-i) > 0){
                    if(argv[i].a_type == A_SYMBOL)
                        pd_bind(&x->x_obj.ob_pd, x->x_receive_sym = atom_getsymbolarg(i, argc, argv));
                    else i--;
                };
            }
            else if(!strcmp(cursym->s_name, "-rgb")){
                i++;
                if((argc-i) > 0){
                    if(argv[i].a_type == A_FLOAT){
                        int rgb = (unsigned char)argv[i].a_w.w_float;
                        x->x_red = rgb;
                        sprintf(x->x_color, "#%2.2x%2.2x%2.2x", x->x_red, x->x_green, x->x_blue);
                    }
                    else i--;
                };
                if((argc-i) > 0){
                    if(argv[i].a_type == A_FLOAT){
                        i++;
                        int rgb = (unsigned char)argv[i].a_w.w_float;
                        x->x_green = rgb;
                        sprintf(x->x_color, "#%2.2x%2.2x%2.2x", x->x_red, x->x_green, x->x_blue);
                    }
                    else i--;
                };
                if((argc-i) > 0){
                    if(argv[i].a_type == A_FLOAT){
                        i++;
                        int rgb = (unsigned char)argv[i].a_w.w_float;
                        x->x_blue = rgb;
                        sprintf(x->x_color, "#%2.2x%2.2x%2.2x", x->x_red, x->x_green, x->x_blue);
                    }
                    else i--;
                };
            }
            else if(!strcmp(cursym->s_name, "-note")){
                i++;
                if((argc-i) > 0){
                    if(argv[i].a_type == A_SYMBOL){
                        SETSYMBOL(&comlist[comlen], argv[i].a_w.w_symbol);
                        comlen++;
                    }
                    else i--;
                };
            }
            else{ // treat it as a part of comlist
                SETSYMBOL(&comlist[comlen], cursym);
                comlen++;
            };
        };
    };
    if(comlen) //set the note with comlist
        binbuf_restore(x->x_binbuf, comlen, comlist);
    else{
        SETSYMBOL(&comlist[0], gensym("note"));
        binbuf_restore(x->x_binbuf, 1, comlist);
    };
    t_freebytes(comlist, argc * sizeof(*comlist));
}

static void *note_new(t_symbol *s, int ac, t_atom *av){
    t_note *x = (t_note *)pd_new(note_class);
    t_symbol *dummy = s;
    dummy = NULL;
    t_text *t = (t_text *)x;
    t->te_type = T_TEXT;
    x->x_glist = (t_glist*) canvas_getcurrent();
    sprintf(x->x_tag, "all%lx", (unsigned long)x);
    sprintf(x->x_texttag, "t%lx", (unsigned long)x);
    sprintf(x->x_outlinetag, "h%lx", (unsigned long)x);
    x->x_encoding = x->x_fontfamily = 0;
    x->x_canvas = 0;
    x->x_textbuf = 0;
    x->x_rcv_set = x->x_flag = 0;
    x->x_pixwidth = x->x_fontsize = x->x_fontprops = x->x_bbpending = 0;
    x->x_red = x->x_green = x->x_blue = x->x_textbufsize = 0;
    x->x_bbset = x->x_ready = x->x_dragon = 0;
    x->x_receive_sym = x->x_rcv_unexpanded = &s_;
    x->x_transclock = clock_new(x, (t_method)note_transtick);
    char buf[32];
    sprintf(buf, "note%lx", (unsigned long)x);
    x->x_bindsym = gensym(buf);
    pd_bind((t_pd *)x, x->x_bindsym);
    if(!notesink)
        notesink = pd_new(notesink_class);
    pd_bind(notesink, x->x_bindsym);
////////////////////////////////// GET ARGS ///////////////////////////////////////////
    if(ac && av->a_type == A_FLOAT){ // 1ST Width
        x->x_pixwidth = (int)av->a_w.w_float;
        ac--; av++;
        if(ac && av->a_type == A_FLOAT){ // 2ND Size
            x->x_fontsize = (int)av->a_w.w_float;
            ac--; av++;
            if(ac && av->a_type == A_SYMBOL){ // 3RD type
                x->x_fontfamily = av->a_w.w_symbol;
                ac--; av++;
                if(ac && av->a_type == A_SYMBOL){ // 4TH RECEIVE
                    if(av->a_w.w_symbol != gensym("empty")){
                        pd_bind(&x->x_obj.ob_pd, x->x_receive_sym = av->a_w.w_symbol);
                        ac--; av++;
                    }
                    else
                        ac--; av++;
                    if (ac && av->a_type == A_FLOAT){
                        x->x_fontprops = (int)av->a_w.w_float;
                        ac--; av++;
                        if (ac && av->a_type == A_FLOAT){
                            x->x_red = (unsigned char)av->a_w.w_float;
                            ac--; av++;
                            if(ac && av->a_type == A_FLOAT){
                                x->x_green = (unsigned char)av->a_w.w_float;
                                ac--; av++;
                                if(ac && av->a_type == A_FLOAT){
                                    x->x_blue = (unsigned char)av->a_w.w_float;
                                    ac--; av++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(x->x_fontsize < 1) x->x_fontsize = glist_getfont(x->x_glist);
    if(!x->x_fontfamily) x->x_fontfamily = gensym("helvetica");
    sprintf(x->x_color, "#%2.2x%2.2x%2.2x", x->x_red, x->x_green, x->x_blue);
    x->x_binbuf = binbuf_new();
    if(ac) note_flag_parser(x, ac, av);
    else{
        t_atom at;
        SETSYMBOL(&at, gensym("note"));
        binbuf_restore(x->x_binbuf, 1, &at);
    }
    return(x);
}

void note_setup(void){
    note_class = class_new(gensym("note"), (t_newmethod)note_new, (t_method)note_free,
        sizeof(t_note), CLASS_DEFAULT, A_GIMME, 0);
    class_addfloat(note_class, note_float);
    class_addlist(note_class, note_list);
    class_addmethod(note_class, (t_method)note_rgb,
        gensym("rgb"), A_FLOAT, A_FLOAT, A_FLOAT, 0);
    class_addmethod(note_class, (t_method)note_name,
        gensym("name"), A_SYMBOL, 0);
    class_addmethod(note_class, (t_method)note_set_receive,
        gensym("receive"), A_SYMBOL, 0);
    class_addmethod(note_class, (t_method)note_size,
        gensym("size"), A_FLOAT, 0);
    class_addmethod(note_class, (t_method)note_set,
        gensym("set"), A_GIMME, 0);
    class_addmethod(note_class, (t_method)note__bboxhook,
        gensym("_bbox"), A_SYMBOL, A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, 0);
    class_addmethod(note_class, (t_method)note__clickhook,
        gensym("_click"), A_GIMME, 0);
    class_addmethod(note_class, (t_method)note__releasehook,
        gensym("_release"), A_SYMBOL, 0);
    class_addmethod(note_class, (t_method)note__motionhook,
        gensym("_motion"), A_SYMBOL, A_FLOAT, A_FLOAT, 0);
    class_setwidget(note_class, &note_widgetbehavior);
    class_setsavefn(note_class, note_save);
    notesink_class = class_new(gensym("_notesink"), 0, 0,
        sizeof(t_pd), CLASS_PD, 0);
    class_addanything(notesink_class, notesink_anything);
    class_addmethod(notesink_class, (t_method)notesink__bboxhook,
        gensym("_bbox"), A_SYMBOL, A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, 0);
    
    sys_gui("proc note_bbox {target cvname tag} {\n\
            pdsend \"$target _bbox $target [$cvname bbox $tag]\"}\n");
    // LATER think about window vs canvas coords
    sys_gui("proc note_click {target cvname x y tag} {\n\
            pdsend \"$target _click $target [$cvname canvasx $x] [$cvname canvasy $y]\
            [$cvname index $tag @$x,$y] [$cvname bbox $tag]\"}\n");
    /* LATER think how to conditionally (FORKY_VERSION >= 38)
     replace puts with pdtk_post */
    sys_gui("proc note_entext {enc tt} {\n\
            if {$enc == \"\"} {concat $tt} else {\n\
            set rr [catch {encoding convertfrom $enc $tt} tt1]\n\
            if {$rr == 0} {concat $tt1} else {\n\
            puts stderr [concat tcl/tk error: $tt1]\n\
            concat $tt}}}\n");
    sys_gui("proc note_draw {tgt cv tag1 tag2 x y fnm fsz clr enc tt wd} {\n\
            set tt1 [note_entext $enc $tt]\n\
            if {$wd > 0} {\n\
            $cv create text $x $y -text $tt1 -tags [list $tag1 $tag2] \
            -font [list $fnm $fsz] -fill $clr -width $wd -anchor nw} else {\n\
            $cv create text $x $y -text $tt1 -tags [list $tag1 $tag2] \
            -font [list $fnm $fsz] -fill $clr -anchor nw}\n\
            note_bbox $tgt $cv $tag1\n\
            $cv bind $tag1 <Button> [list note_click $tgt %W %x %y $tag1]}\n");
    sys_gui("proc note_update {cv tag enc tt wd} {\n\
            set tt1 [note_entext $enc $tt]\n\
            if {$wd > 0} {$cv itemconfig $tag -text $tt1 -width $wd} else {\n\
            $cv itemconfig $tag -text $tt1}}\n");
}
