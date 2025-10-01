/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_nextafter.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * nextafterf(float x, float y)
 * return the next machine floating-point number of x in the
 * direction toward y.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

/****** ma.lib/nextafterf ****************************************************
* 
*   NAME	
* 	nextafterf -- Next representable float toward another. (V1.0)
*
*   SYNOPSIS
*	float result = nextafterf(float x, float y);
*	  D0		   D0
*	float nextafterf(float x, float y);
*
*   FUNCTION
*	Return the next representable float value after x in the
*	direction toward y. This is useful for implementing floating-point
*	algorithms that need to step through representable values.
*	This implementation uses high-precision algorithms from fdlibm.
* 
*   INPUTS
*	x - Starting float value.
*	y - Target float value (direction).
*	
*   RESULT
*	result - Next representable float value toward y.
* 
*   EXAMPLE
*	float x = 1.0f;
*	float y = 2.0f;
*	float result = nextafterf(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses direct bit manipulation for optimal performance.
* 
*   SEE ALSO
*	nextafter(), nexttowardf(), math.h
* 
******************************************************************************/

float nextafterf(float x, float y)
{
    int hx, hy, ix, iy;

    hx = __HI(x);		/* high word of x */
    hy = __HI(y);		/* high word of y */
    ix = hx&0x7fffffff;		/* |x| */
    iy = hy&0x7fffffff;		/* |y| */

    if(((ix>=0x7f800000)&&(ix!=0x7f800000)) ||   /* x is nan */ 
       ((iy>=0x7f800000)&&(iy!=0x7f800000)))     /* y is nan */ 
       return x+y;				
    if(x==y) return x;		/* x=y, return x */
    if(ix==0) {			/* x == 0 */
        __HI(x) = hy&0x80000000;	/* return +-minsubnormal */
        y = x*x;
        if(y==x) return y; else return x;	/* raise underflow flag */
    } 
    if(hx>=0) {			/* x > 0 */
        if(hx>hy) {		/* x > y, x -= ulp */
            hx -= 1;
        } else {		/* x < y, x += ulp */
            hx += 1;
        }
    } else {			/* x < 0 */
        if(hy>=0||hx>hy){	/* x < y, x -= ulp */
            hx -= 1;
        } else {		/* x > y, x += ulp */
            hx += 1;
        }
    }
    hy = hx&0x7f800000;
    if(hy>=0x7f800000) return x+x;	/* overflow  */
    if(hy<0x00800000) {		/* underflow */
        y = x*x;
        if(y!=x) {		/* raise underflow flag */
            __HI(y) = hx;
            return y;
        }
    }
    __HI(x) = hx;
    return x;
}


