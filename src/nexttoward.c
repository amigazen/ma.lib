/*
 * nexttoward.c - Next representable value toward another
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/*
 * nexttoward(x,y)
 * Return the next machine floating-point number after x toward y.
 * Special cases:
 *      nexttoward(x,x) = x
 *      nexttoward(0,y) = smallest positive number
 *      nexttoward(inf,y) = inf
 *      nexttoward(-inf,y) = -inf
 */

/****** ma.lib/nexttoward ***************************************************
* 
*   NAME	
* 	nexttoward -- Return next representable value toward y. (V1.0)
*
*   SYNOPSIS
*	double result = nexttoward(double x, long double y);
*	  D0		   D0
*	double nexttoward(double x, long double y);
*
*   FUNCTION
*	Compute the next representable floating-point value after x in the
*	direction toward y. This is useful for finding the next or previous
*	representable value. This implementation uses high-precision algorithms
*	for maximum accuracy.
* 
*   INPUTS
*	x - Starting value.
*	y - Direction value.
*	
*   RESULT
*	result - Next representable value after x toward y. Returns x if x
*	        equals y, returns NaN if either argument is NaN.
* 
*   EXAMPLE
*	double x = 1.0;
*	long double y = 2.0L;
*	double result = nexttoward(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is useful for finding adjacent representable values.
* 
*   SEE ALSO
*	nextafter(), math.h
* 
******************************************************************************/

double nexttoward(double x, long double y)
{
    int hx,ix,iy;
    unsigned lx,ly;
    double yd;  /* Declare at top for C89 compliance */

    hx = __HI(x);       /* high word of x */
    lx = __LO(x);       /* low  word of x */
    ix = hx&0x7fffffff; /* |x| */
    
    /* Convert y to double for comparison */
    yd = (double)y;
    iy = __HI(yd)&0x7fffffff; /* |y| */
    ly = __LO(yd);

    if(((ix>=0x7ff00000)&&((ix-0x7ff00000)|lx)!=0) ||   /* x is nan */
       ((iy>=0x7ff00000)&&((iy-0x7ff00000)|ly)!=0))     /* y is nan */
       return x+y;
    if(x==y) return y;          /* x=y, return y */
    if((ix|lx)==0) {            /* x == 0 */
        __HI(x) = hx&0x80000000; /* return +-minsubnormal */
        __LO(x) = 1;
        y = x*x;                /* raise underflow flag */
        return x;
    }
    if(hx>=0) {                 /* x > 0 */
        if(ix > iy || ((ix==iy) && (lx > ly))) { /* x > y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {                /* x < y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    } else {                    /* x < 0 */
        if(ix >= iy && ((ix!=iy)||(lx!=ly))) { /* x < y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {                /* x > y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    }
    __HI(x) = hx; __LO(x) = lx;
    return x;
}
