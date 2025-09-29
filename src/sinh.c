/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_sinh.c and w_sinh.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double sinh(double x)
 * Method : 
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double one = 1.0, shuge = 1.0e307;

static double __ieee754_sinh(double x)
{	
    double t, w, h;
    int ix, jx;
    unsigned lx;

    /* High word of |x|. */
    jx = __HI(x);
    ix = jx&0x7fffffff;

    /* x is INF or NaN */
    if(ix>=0x7ff00000) return x+x;	

    h = 0.5;
    if (jx<0) h = -h;
    /* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
    if (ix < 0x40360000) {		/* |x|<22 */
        if (ix<0x3e300000) 		/* |x|<2**-28 */
            if(shuge+x>one) return x;/* sinh(tiny) = tiny with inexact */
        t = expm1(fabs(x));
        if(ix<0x3ff00000) return h*(2.0*t-t*t/(t+one));
        return h*(t+t/(t+one));
    }

    /* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
    if (ix < 0x40862E42)  return h*exp(fabs(x));

    /* |x| in [log(maxdouble), overflowthresold] */
    lx = *( (((*(unsigned*)&one)>>29)) + (unsigned*)&x);
    if (ix<0x408633CE || (ix==0x408633ce)&&(lx<=(unsigned)0x8fb9f87d)) {
        w = exp(0.5*fabs(x));
        t = h*w;
        return t*w;
    }

    /* |x| > overflowthresold, sinh(x) overflow */
    return x*shuge;
}

double sinh(double x)
{
    return __ieee754_sinh(x);
}
