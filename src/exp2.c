/*
 * exp2.c - Base-2 exponential function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/*
 * exp2(x) = 2^x
 * 
 * Method:
 *   1. Argument Reduction: find k and f such that
 *      x = k*ln2 + f, with |f| <= 0.5*ln2
 *   2. Approximation of exp2(f) = 2^f.
 *   3. Return 2^k * exp2(f).
 */

static const double
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
huge   =  1.0e+300,
tiny   =  1.0e-300;

static const double
ln2_hi  =  6.93147180369123816490e-01,  /* 0x3fe62e42, 0xfee00000 */
ln2_lo  =  1.90821492927058770002e-10,  /* 0x3dea39ef, 0x35793c76 */
invln2 =  1.44269504088896338700e+00,  /* 0x3ff71547, 0x652b82fe */
P1     =  1.66666666666666019037e-01,  /* 0x3FC55555, 0x5555553E */
P2     = -2.77777777770155933842e-03,  /* 0xBF66C16C, 0x16BEBD93 */
P3     =  6.61375632143793436117e-05,  /* 0x3F11566A, 0xAF25DE2C */
P4     = -1.65339022054652515390e-06,  /* 0xBEBBBD41, 0xC5D26BF1 */
P5     =  4.13813679705723846039e-08;  /* 0x3E663769, 0x72BEA4D0 */

double exp2(double x)
{
    double y,hi=0,lo=0,c,t;
    int k,xsb;
    unsigned hx;

    hx = __HI(x);
    xsb = (hx>>31)&1;           /* sign bit of x */
    hx &= 0x7fffffff;           /* high word of |x| */

    /* filter out non-finite argument */
    if(hx >= 0x408ff000) {      /* if |x| >= 1024 */
        if(hx >= 0x7ff00000) {
            if(((hx&0xfffff)|__LO(x))!=0)
                return x+x;     /* NaN */
            else return (xsb==0)? x:0.0;    /* exp2(+-inf)={inf,0} */
        }
        if(x > 1024.0) return huge*huge; /* overflow */
        if(x < -1024.0) return tiny*tiny; /* underflow */
    }

    /* argument reduction */
    if(hx > 0x3fd00000) {       /* if |x| > 0.5 */
        if(hx < 0x3ff00000) {   /* and |x| < 1. */
            hi = x-ln2_hi;
            lo = ln2_lo;
            k = 1;
        } else {
            k  = (int)(invln2*x+((xsb==0)?0.5:-0.5));
            t  = k;
            hi = x - t*ln2_hi;  /* t*ln2_hi is exact here */
            lo = t*ln2_lo;
        }
        x  = hi - lo;
    } else if(hx < 0x3e300000)  {   /* when |x|<2**-28 */
        if(huge+x>0.0) return 1.0+x; /* trigger inexact */
    } else k = 0;

    /* x is now in primary range */
    t  = x*x;
    c  = x - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    if(k==0)        return 1.0-((x*c)/(c-2.0)-x);
    else            y = 1.0-((lo-(x*c)/(2.0-c))-hi);
    if(k >= -1021) {
        /* Reconstruct y with new exponent */
        int y_hi = __HI(y) + (k<<20);
        int y_lo = __LO(y);
        double result;
        __HI(result) = y_hi;
        __LO(result) = y_lo;
        return result;
    } else {
        /* Reconstruct y with new exponent and scale */
        int y_hi = __HI(y) + ((k+1000)<<20);
        int y_lo = __LO(y);
        double result;
        __HI(result) = y_hi;
        __LO(result) = y_lo;
        return result*twom54;
    }
}
