/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_scalbn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * scalbnf (float x, int n)
 * scalbnf(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

static const float
two25   =  3.3554432000e+07, /* 0x4c000000 */
twom25  =  2.9802322388e-08, /* 0x33000000 */
huge   = 1.0e+30,
tiny   = 1.0e-30;

float scalbnf(float x, int n)
{
    int  k, hx;
    hx = __HI(x);
    k = (hx&0x7f800000)>>23;		/* extract exponent */
    if (k==0) {				/* 0 or subnormal x */
        if ((hx&0x7fffffff)==0) return x; /* +-0 */
        x *= two25; 
        hx = __HI(x);
        k = ((hx&0x7f800000)>>23) - 25; 
        if (n< -50000) return tiny*x; 	/*underflow*/
    }
    if (k==0xff) return x+x;		/* NaN or Inf */
    k = k+n; 
    if (k >  0xfe) return huge*copysignf(huge,x); /* overflow  */
    if (k > 0) 				/* normal result */
        {__HI(x) = (hx&0x807fffff)|(k<<23); return x;}
    if (k <= -25)
        if (n > 50000) 	/* in case integer overflow in n+k */
            return huge*copysignf(huge,x);	/*overflow*/
        else return tiny*copysignf(tiny,x); 	/*underflow*/
    k += 25;				/* subnormal result */
    __HI(x) = (hx&0x807fffff)|(k<<23);
    return x*twom25;
}
