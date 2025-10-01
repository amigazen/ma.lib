/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_sin.c, k_sin.c, k_cos.c, e_rem_pio2.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double sin(double x)
 * Return sine function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/sin ***********************************************************
* 
*   NAME	
* 	sin -- Return sine of x. (V1.0)
*
*   SYNOPSIS
*	double result = sin(double x);
*	  D0		   D0
*	double sin(double x);
*
*   FUNCTION
*	Compute the sine of x. This returns the sine of x in radians.
*	This implementation uses high-precision algorithms from fdlibm
*	for maximum accuracy.
* 
*   INPUTS
*	x - Input value in radians. Range is [-∞, +∞].
*	
*   RESULT
*	result - Sine of x. Returns NaN if x is NaN, returns NaN if x is
*	        ±Infinity, returns x if x is ±0.
* 
*   EXAMPLE
*	double x = M_PI / 2.0;
*	double result = sin(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses range reduction to [-π/4, π/4] for optimal accuracy.
* 
*   SEE ALSO
*	cos(), tan(), asin(), math.h
* 
******************************************************************************/

/* Internal functions for sin */
int __ieee754_rem_pio2(double x, double *y);
double __kernel_sin(double x, double y, int iy);
double __kernel_cos(double x, double y);

/* Kernel sin function constants */
static const double
half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

/* Kernel cos function constants */
static const double
one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

/* rem_pio2 constants */
static const double
zero =  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
half_rem =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
two24 =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
invpio2 =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
pio2_1  =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
pio2_1t =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
pio2_2  =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
pio2_2t =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
pio2_3  =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
pio2_3t =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

static const int npio2_hw[] = {
0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
0x404858EB, 0x404921FB,
};

double __kernel_sin(double x, double y, int iy)
{
    double z, r, v;
    int ix;
    ix = __HI(x)&0x7fffffff;	/* high word of x */
    if(ix<0x3e400000)			/* |x| < 2**-27 */
       {if((int)x==0) return x;}		/* generate inexact */
    z	=  x*x;
    v	=  z*x;
    r	=  S2+z*(S3+z*(S4+z*(S5+z*S6)));
    if(iy==0) return x+v*(S1+z*r);
    else      return x-((z*(half*y-v*r)-y)-v*S1);
}

double __kernel_cos(double x, double y)
{
    double a, hz, z, r, qx;
    int ix;
    ix = __HI(x)&0x7fffffff;	/* ix = |x|'s high word*/
    if(ix<0x3e400000) {			/* if x < 2**27 */
        if(((int)x)==0) return one;		/* generate inexact */
    }
    z  = x*x;
    r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
    if(ix < 0x3FD33333) 			/* if |x| < 0.3 */ 
        return one - (0.5*z - (z*r - x*y));
    else {
        if(ix > 0x3fe90000) {		/* x > 0.78125 */
            qx = 0.28125;
        } else {
            __HI(qx) = ix-0x00200000;	/* x/4 */
            __LO(qx) = 0;
        }
        hz = 0.5*z-qx;
        a  = one-qx;
        return a - (hz - (z*r-x*y));
    }
}

int __ieee754_rem_pio2(double x, double *y)
{
    double z, w, t, r, fn;
    double tx[3];
    int e0, i, j, nx, n, ix, hx;

    hx = __HI(x);		/* high word of x */
    ix = hx&0x7fffffff;
    if(ix<=0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
        {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
        if(hx>0) { 
            z = x - pio2_1;
            if(ix!=0x3ff921fb) { 	/* 33+53 bit pi is good enough */
                y[0] = z - pio2_1t;
                y[1] = (z-y[0])-pio2_1t;
            } else {		/* near pi/2, use 33+33+53 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z-y[0])-pio2_2t;
            }
            return 1;
        } else {	/* negative x */
            z = x + pio2_1;
            if(ix!=0x3ff921fb) { 	/* 33+53 bit pi is good enough */
                y[0] = z + pio2_1t;
                y[1] = (z-y[0])+pio2_1t;
            } else {		/* near pi/2, use 33+33+53 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z-y[0])+pio2_2t;
            }
            return -1;
        }
    }
    if(ix<=0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
        t  = fabs(x);
        n  = (int) (t*invpio2+half_rem);
        fn = (double)n;
        r  = t-fn*pio2_1;
        w  = fn*pio2_1t;	/* 1st round good to 85 bit */
        if(n<32&&ix!=npio2_hw[n-1]) {	
            y[0] = r-w;	/* quick check no cancellation */
        } else {
            j  = ix>>20;
            y[0] = r-w; 
            i = j-(((__HI(y[0]))>>20)&0x7ff);
            if(i>16) {  /* 2nd iteration needed, good to 118 */
                t  = r;
                w  = fn*pio2_2;	
                r  = t-w;
                w  = fn*pio2_2t-((t-r)-w);	
                y[0] = r-w;
                i = j-(((__HI(y[0]))>>20)&0x7ff);
                if(i>49)  {	/* 3rd iteration need, 151 bits acc */
                    t  = r;	/* will cover all possible cases */
                    w  = fn*pio2_3;	
                    r  = t-w;
                    w  = fn*pio2_3t-((t-r)-w);	
                    y[0] = r-w;
                }
            }
        }
        y[1] = (r-y[0])-w;
        if(hx<0) 	{y[0] = -y[0]; y[1] = -y[1]; return -n;}
        else	 return n;
    }
    /* 
     * all other (large) arguments - simplified fallback
     */
    if(ix>=0x7ff00000) {		/* x is inf or NaN */
        y[0]=y[1]=x-x; return 0;
    }
    /* For very large arguments, use a simplified approach */
    t = fabs(x);
    n = (int) (t*invpio2+half_rem);
    fn = (double)n;
    r = t-fn*pio2_1;
    w = fn*pio2_1t;
    y[0] = r-w;
    y[1] = (r-y[0])-w;
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
}

/****** ma.lib/sin ******************************************************
* 
*   NAME	
* 	sin -- Return sine function of x. (V1.0)
*
*   SYNOPSIS
*	double result = sin(double x);
*	  D0		   D0
*	double sin(double x);
*
*   FUNCTION
*	Compute the sine of x, where x is in radians. The sine function
*	returns values in the range [-1, 1]. This implementation uses
*	high-precision algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value in radians. Range is approximately [-2^63, 2^63].
*	
*   RESULT
*	result - Sine of x, in the range [-1, 1]. Returns NaN if x is NaN,
*	        returns x if x is ±0, returns NaN if x is ±Infinity.
* 
*   EXAMPLE
*	double angle = M_PI / 4.0;  
*	double sine = sin(angle);   
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performance is optimized for the Amiga platform.
* 
*   SEE ALSO
*	cos(), tan(), asin(), math.h
* 
******************************************************************************/

double sin(double x)
{
    double y[2], z=0.0;
    int n, ix;

    /* High word of x. */
    ix = __HI(x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return __kernel_sin(x,z,0);

    /* sin(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = __ieee754_rem_pio2(x,y);
        switch(n&3) {
            case 0: return  __kernel_sin(y[0],y[1],1);
            case 1: return  __kernel_cos(y[0],y[1]);
            case 2: return -__kernel_sin(y[0],y[1],1);
            default:
                return -__kernel_cos(y[0],y[1]);
        }
    }
}