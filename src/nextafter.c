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
 * nextafter(x,y)
 * return the next machine floating-point number of x in the
 * direction toward y.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/nextafter ****************************************************
* 
*   NAME	
* 	nextafter -- Return next representable value toward y. (V1.0)
*
*   SYNOPSIS
*	double result = nextafter(double x, double y);
*	  D0		   D0
*	double nextafter(double x, double y);
*
*   FUNCTION
*	Compute the next representable floating-point value after x in the
*	direction toward y. This is useful for finding the next or previous
*	representable value. This implementation uses high-precision algorithms
*	from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Starting value.
*	y - Direction value.
*	
*   RESULT
*	result - Next representable value after x toward y. Returns y if x
*	        equals y, returns NaN if either argument is NaN.
* 
*   EXAMPLE
*	double x = 1.0, y = 2.0;
*	double result = nextafter(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is useful for finding adjacent representable values.
* 
*   SEE ALSO
*	nexttoward(), math.h
* 
******************************************************************************/

double nextafter(double x, double y)
{
    int hx, hy, ix, iy;
    unsigned lx, ly;

    hx = __HI(x);		/* high word of x */
    lx = __LO(x);		/* low  word of x */
    hy = __HI(y);		/* high word of y */
    ly = __LO(y);		/* low  word of y */
    ix = hx&0x7fffffff;		/* |x| */
    iy = hy&0x7fffffff;		/* |y| */

    if(((ix>=0x7ff00000)&&((ix-0x7ff00000)|lx)!=0) ||   /* x is nan */ 
       ((iy>=0x7ff00000)&&((iy-0x7ff00000)|ly)!=0))     /* y is nan */ 
       return x+y;				
    if(x==y) return x;		/* x=y, return x */
    if((ix|lx)==0) {		/* x == 0 */
        __HI(x) = hy&0x80000000;	/* return +-minsubnormal */
        __LO(x) = 1;
        y = x*x;
        if(y==x) return y; else return x;	/* raise underflow flag */
    } 
    if(hx>=0) {			/* x > 0 */
        if(hx>hy||((hx==hy)&&(lx>ly))) {	/* x > y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {		/* x < y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    } else {			/* x < 0 */
        if(hy>=0||hx>hy||((hx==hy)&&(lx>ly))){/* x < y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {		/* x > y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    }
    hy = hx&0x7ff00000;
    if(hy>=0x7ff00000) return x+x;	/* overflow  */
    if(hy<0x00100000) {		/* underflow */
        y = x*x;
        if(y!=x) {		/* raise underflow flag */
            __HI(y) = hx; __LO(y) = lx;
            return y;
        }
    }
    __HI(x) = hx; __LO(x) = lx;
    return x;
}

