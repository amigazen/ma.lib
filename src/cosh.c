/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_cosh.c and w_cosh.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double cosh(double x)
 * Method : 
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double one = 1.0, half=0.5, huge = 1.0e300;

static double __ieee754_cosh(double x)
{	
    double t, w;
    int ix;
    unsigned lx;

    /* High word of |x|. */
    ix = __HI(x);
    ix &= 0x7fffffff;

    /* x is INF or NaN */
    if(ix>=0x7ff00000) return x*x;	

    /* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
    if(ix<0x3fd62e43) {
        t = expm1(fabs(x));
        w = one+t;
        if (ix<0x3c800000) return w;	/* cosh(tiny) = 1 */
        return one+(t*t)/(w+w);
    }

    /* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
    if (ix < 0x40360000) {
        t = exp(fabs(x));
        return half*t+half/t;
    }

    /* |x| in [22, log(maxdouble)] return half*exp(|x|) */
    if (ix < 0x40862E42)  return half*exp(fabs(x));

    /* |x| in [log(maxdouble), overflowthresold] */
    lx = *( (((*(unsigned*)&one)>>29)) + (unsigned*)&x);
    if (ix<0x408633CE || 
          (ix==0x408633ce)&&(lx<=(unsigned)0x8fb9f87d)) {
        w = exp(half*fabs(x));
        t = half*w;
        return t*w;
    }

    /* |x| > overflowthresold, cosh(x) overflow */
    return huge*huge;
}

double cosh(double x)
{
    return __ieee754_cosh(x);
}
