// by schiavoni and porres 2017

#include "m_pd.h"
#include <stdio.h>

static t_class *median_class;

typedef struct _median {
   t_object x_obj;
   t_inlet *median;
   t_float samples;
   t_outlet *x_outlet;
} t_median;

// Constructor of the class
void * median_new(t_floatarg samples_arg) {
   t_median *x = (t_median *) pd_new(median_class);
   x->samples = (samples_arg < 1) ? 1 : samples_arg;
   x->x_outlet = outlet_new(&x->x_obj, &s_signal); // outlet
   floatinlet_new(&x->x_obj, &x->samples);
   return (void *) x;
}

void median_sort (t_float *a, int n) {
   if (n < 2)
      return;
   t_float p = a[n / 2];
   t_float *l = a;
   t_float *r = a + n - 1;
   while (l <= r) {
      while (*l < p)
         l++;
      while (*r > p)
         r--;
      if (l <= r) {
         t_float t = *l;
         *l++ = *r;
         *r-- = t;
      }
   }
   median_sort(a, r - a + 1);
   median_sort(l, a + n - l);
}


t_float median_calculate(t_float * array, int begin, int end){
   median_sort(array + begin, end - begin + 1);
   int qtd = end - begin + 1;
   t_float median = 0;
   median = (qtd%2 == 1)? 
         array[begin + ((qtd - 1)/2)] : 
         (array[begin + qtd / 2 - 1] + array[begin + qtd / 2])/2.0f;
   return median;
}

// Perform
static t_int * median_perform(t_int *w){
   t_median *x = (t_median *)(w[1]);
   t_int n = (int)(w[2]);
   t_float *in1 = (t_float *)(w[3]);
   t_float *out1 = (t_float *)(w[4]);

// will use a temp variable to not change the input values
   t_float temp[n];
   int i = 0;
   for(i = 0 ; i < n ; i++)
      temp[i] = in1[i];

   if(x->samples > n) x->samples = n;
   if(x->samples < 1) x->samples = 1;
   int begin = 0;
   int end = x->samples - 1;
   t_float median = 0;

   while(begin < n){
      median = median_calculate(temp, begin, end);
      i = 0;
      for(i = begin; i < end + 1; i++)
         out1[i] = median;
      begin += x->samples;
      end = (end + x->samples > n)? n - 1 : end + x->samples;
   }

   return (w + 5);
}

static void median_dsp(t_median *x, t_signal **sp){
   dsp_add(median_perform, 4, x, sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec);
}


void median_free(t_median *x)
{
   (void)x;
}

void median_tilde_setup(void) {
   median_class = class_new(gensym("median~"),
      (t_newmethod) median_new,
      (t_method) median_free,
      sizeof (t_median),
      0,
      A_DEFFLOAT,
      0);
   class_addmethod(median_class, nullfn, gensym("signal"), 0);
   class_addmethod(median_class, (t_method) median_dsp, gensym("dsp"), A_CANT, 0);
}
