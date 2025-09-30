/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/w_jn.c and e_jn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double yn(int n, double x)
 * Bessel function of the second kind, order n
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
invsqrtpi=  5.64189583547756279280e-01, /* 0x3FE20DD7, 0x50429B6D */
two   =  2.00000000000000000000e+00, /* 0x40000000, 0x00000000 */
one   =  1.00000000000000000000e+00; /* 0x3FF00000, 0x00000000 */

static double zero  =  0.00000000000000000000e+00;

static double __ieee754_yn(int n, double x)
{
    int i,hx,ix,lx;
    int sign;
    double a, b, temp;

    hx = __HI(x);
    ix = 0x7fffffff&hx;
    lx = __LO(x);
    /* if Y(n,NaN) is NaN */
    if((ix|((unsigned)(lx|-lx))>>31)>0x7ff00000) return x+x;
    if((ix|lx)==0) return -one/zero;
    if(hx<0) return zero/zero;
    sign = 1;
    if(n<0){
        n = -n;
        sign = 1 - ((n&1)<<1);
    }
    if(n==0) return(y0(x));
    if(n==1) return(sign*y1(x));
    if(ix==0x7ff00000) return zero;
    if(ix>=0x52D00000) { /* x > 2**302 */
    /* (x >> n**2) 
     *	    Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Let s=sin(x), c=cos(x), 
     *		xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
     *
     *		   n	sin(xn)*sqt2	cos(xn)*sqt2
     *		----------------------------------
     *		   0	 s-c		 c+s
     *		   1	-s-c 		-c+s
     *		   2	-s+c		-c-s
     *		   3	 s+c		 c-s
     */
        switch(n&3) {
            case 0: temp =  sin(x)-cos(x); break;
            case 1: temp = -sin(x)-cos(x); break;
            case 2: temp = -sin(x)+cos(x); break;
            case 3: temp =  sin(x)+cos(x); break;
        }
        b = invsqrtpi*temp/sqrt(x);
    } else {
        a = y0(x);
        b = y1(x);
    /* quit if b is -inf */
        for(i=1;i<n&&(__HI(b) != 0xfff00000);i++){ 
            temp = b;
            b = ((double)(i+i)/x)*b - a;
            a = temp;
        }
    }
    if(sign>0) return b; else return -b;
}

double yn(int n, double x)
{
    return __ieee754_yn(n, x);
}

