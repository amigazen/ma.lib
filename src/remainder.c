/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_remainder.c and w_remainder.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * remainder(x,p)
 * Return: returns x REM p = x - [x/p]*p as if in infinite 
 * precise arithmetic, where [x/p] is the (infinite bit) 
 * integer nearest x/p (in half way case choose the even one).
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double zero = 0.0;

/* Internal IEEE 754 remainder function */
static double __ieee754_remainder(double x, double p)
{
    int hx, hp;
    unsigned sx, lx, lp;
    double p_half;

    hx = __HI(x);		/* high word of x */
    lx = __LO(x);		/* low  word of x */
    hp = __HI(p);		/* high word of p */
    lp = __LO(p);		/* low  word of p */
    sx = hx&0x80000000;
    hp &= 0x7fffffff;
    hx &= 0x7fffffff;

    /* purge off exception values */
    if((hp|lp)==0) return (x*p)/(x*p); 	/* p = 0 */
    if((hx>=0x7ff00000)||			/* x not finite */
      ((hp>=0x7ff00000)&&			/* p is NaN */
      (((hp-0x7ff00000)|lp)!=0)))
        return (x*p)/(x*p);

    if (hp<=0x7fdfffff) x = fmod(x,p+p);	/* now x < 2p */
    if (((hx-hp)|(lx-lp))==0) return zero*x;
    x  = fabs(x);
    p  = fabs(p);
    if (hp<0x00200000) {
        if(x+x>p) {
            x-=p;
            if(x+x>=p) x -= p;
        }
    } else {
        p_half = 0.5*p;
        if(x>p_half) {
            x-=p;
            if(x>=p_half) x -= p;
        }
    }
    __HI(x) ^= sx;
    return x;
}

/* Public remainder function */
double remainder(double x, double y)
{
    double z;
    z = __ieee754_remainder(x,y);
    if(isnan(y)) return z;
    if(y==0.0) {
        /* remainder(x,0) - return NaN */
        return NAN;
    } else {
        return z;
    }
}

