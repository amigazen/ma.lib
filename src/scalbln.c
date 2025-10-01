/*
 * scalbln.c - Scale by long integer
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <limits.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/*
 * scalbln(x, n) = x * 2^n
 * 
 * Method:
 *     1. If n is in range, use scalbn.
 *     2. Otherwise, handle overflow/underflow.
 */

static const double
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
huge   =  1.0e+300,
tiny   =  1.0e-300;

/****** ma.lib/scalbln ******************************************************
* 
*   NAME	
* 	scalbln -- Return x * 2^n. (V1.0)
*
*   SYNOPSIS
*	double result = scalbln(double x, long n);
*	  D0		   D0
*	double scalbln(double x, long n);
*
*   FUNCTION
*	Compute x * 2^n. This scales x by a power of 2. This implementation
*	uses high-precision algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value.
*	n - Exponent value.
*	
*   RESULT
*	result - x * 2^n. Returns NaN if x is NaN, returns ±Infinity for
*	        large results, returns ±0 for small results.
* 
*   EXAMPLE
*	double x = 3.0;
*	long n = 2;
*	double result = scalbln(x, n);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to scalbn(x, n) when n is in range.
* 
*   SEE ALSO
*	scalbn(), scalb(), ldexp(), math.h
* 
******************************************************************************/

double scalbln(double x, long n)
{
    int k,hx,lx;
    hx = __HI(x);
    lx = __LO(x);
    k = (hx&0x7ff00000)>>20;        /* extract exponent */
    if (k==0) {                      /* 0 or subnormal x */
        if ((lx|(hx&0x7fffffff))==0) return x; /* +-0 */
        x *= two54;
        hx = __HI(x);
        k = ((hx&0x7ff00000)>>20) - 54;
        if (n< -50000) return tiny*x;  /*underflow*/
    }
    if (k==0x7ff) return x+x;        /* NaN or Inf */
    k = k+n;
    if (n> 50000 || k >  0x7fe)
        return huge*copysign(huge,x); /* overflow  */
    if (k > 0) {                         /* normal result */
        /* Reconstruct x with new exponent */
        int x_hi = (hx&0x800fffff)|(k<<20);
        int x_lo = __LO(x);
        double result;
        __HI(result) = x_hi;
        __LO(result) = x_lo;
        return result;
    }
    if (k <= -54) {
        if (n > 50000)    /* in case integer overflow in n+k */
            return huge*copysign(huge,x);    /*overflow*/
        else return tiny*copysign(tiny,x);   /*underflow*/
    }
    k += 54;                        /* subnormal result */
    /* Reconstruct x with new exponent and scale */
    {
        int x_hi = (hx&0x800fffff)|(k<<20);
        int x_lo = __LO(x);
        double result;
        __HI(result) = x_hi;
        __LO(result) = x_lo;
        return result*twom54;
    }
}
