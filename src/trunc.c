/*
 * trunc.c - Truncate toward zero
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/*
 * trunc(x)
 * Return x rounded toward 0 to integral value
 * Method:
 *      Bit twiddling.
 * Exception:
 *      Inexact flag raised if x not equal to trunc(x).
 */

static const double huge = 1.0e300;

double trunc(double x)
{
    int i0,i1,j0;
    unsigned i,j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {  /* raise inexact if x != 0 */
            if(huge+x>0.0) {        /* |x|<huge, return 0*sign(x) */
                i0 &= 0x80000000U;
                i1 = 0;
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {        /* raise inexact flag */
                i0 &= (~i); i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;   /* inf or NaN */
        else return x;              /* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x;     /* x is integral */
        if(huge+x>0.0) {            /* raise inexact flag */
            i1 &= (~i);
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    return x;
}
