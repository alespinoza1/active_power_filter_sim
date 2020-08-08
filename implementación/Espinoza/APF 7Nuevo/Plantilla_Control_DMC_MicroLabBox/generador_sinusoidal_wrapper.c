
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <parametros_gen.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void generador_sinusoidal_Outputs_wrapper(const real_T *in,
			real_T *y0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
Iref=in[0];
fref=in[1];
Tsl=in[2];
Ns=(int)1/(Tsl*fref);
y0[0]=Iref*sin(6.2831853*fref*t*Tsl);
y0[1]=Iref*sin(6.2831853*fref*t*Tsl+2.094395102393195);
y0[2]=Iref*sin(6.2831853*fref*t*Tsl+4.188790204786391);

if(t<Ns-1)
{
    t++;
}
else
{
    t=0;
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


