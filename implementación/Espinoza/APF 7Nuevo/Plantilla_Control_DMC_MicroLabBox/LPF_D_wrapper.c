
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
#include <parametrosLPF.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 4
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
void LPF_D_Outputs_wrapper(const real_T *u0,
			real_T *y0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
Tk = u0[3];
Vas_N = (1-Tk*497.359197)*Vas_Nant + (Tk*497.359197)*Vas_ant;
Vbs_N = (1-Tk*497.359197)*Vbs_Nant + (Tk*497.359197)*Vbs_ant;
Vcs_N = (1-Tk*497.359197)*Vcs_Nant + (Tk*497.359197)*Vcs_ant;

//Se actualizan las variables
    Vas_Nant = Vas_N;
    Vas_ant = u0[0];
    Vbs_Nant = Vbs_N;
    Vbs_ant = u0[1];
    Vcs_Nant = Vcs_N;
    Vcs_ant = u0[2];
    
y0[0] = Vas_N;
y0[1] = Vbs_N;
y0[2] = Vcs_N;

/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


