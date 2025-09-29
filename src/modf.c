/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_modf.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * modf(double x, double *iptr) 
 * return fraction part of x, and return x's integral part in *iptr.
 * Method: Bit twiddling.
 * Exception: No exception.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)
#define __HIp(x) *(int*)&x
#define __LOp(x) *(1+(int*)&x)

static const double one = 1.0;

double modf(double x, double *iptr)
{
    int i0, i1, j0;
    unsigned i;
    i0 =  __HI(x);		/* high x */
    i1 =  __LO(x);		/* low  x */
    j0 = ((i0>>20)&0x7ff)-0x3ff;	/* exponent of x */
    if(j0<20) {			/* integer part in high x */
        if(j0<0) {			/* |x|<1 */
            __HIp(iptr) = i0&0x80000000;
            __LOp(iptr) = 0;		/* *iptr = +-0 */
            return x;
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) {		/* x is integral */
                *iptr = x;
                __HI(x) &= 0x80000000;
                __LO(x)  = 0;	/* return +-0 */
                return x;
            } else {
                __HIp(iptr) = i0&(~i);
                __LOp(iptr) = 0;
                return x - *iptr;
            }
        }
    } else if (j0>51) {		/* no fraction part */
        *iptr = x*one;
        __HI(x) &= 0x80000000;
        __LO(x)  = 0;	/* return +-0 */
        return x;
    } else {			/* fraction part in low x */
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) { 		/* x is integral */
            *iptr = x;
            __HI(x) &= 0x80000000;
            __LO(x)  = 0;	/* return +-0 */
            return x;
        } else {
            __HIp(iptr) = i0;
            __LOp(iptr) = i1&(~i);
            return x - *iptr;
        }
    }
}
