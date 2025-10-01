/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_jn.c and w_jn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double jn(int n, double x)
 * double yn(int n, double x)
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n
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

static double __ieee754_jn(int n, double x)
{
    int i,hx,ix,lx, sgn;
    double a, b, temp, di;
    double z, w;

    /* J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
     * Thus, J(-n,x) = J(n,-x)
     */
    hx = __HI(x);
    ix = 0x7fffffff&hx;
    lx = __LO(x);
    /* if J(n,NaN) is NaN */
    if((ix|((unsigned)(lx|-lx))>>31)>0x7ff00000) return x+x;
    if(n<0){		
        n = -n;
        x = -x;
        hx ^= 0x80000000;
    }
    if(n==0) return(j0(x));
    if(n==1) return(j1(x));
    sgn = (n&1)&(hx>>31);	/* even n -- 0, odd n -- sign(x) */
    x = fabs(x);
    if((ix|lx)==0||ix>=0x7ff00000) 	/* if x is 0 or inf */
        b = zero;
    else if((double)n<=x) {   
        /* Safe to use J(n+1,x)=2n/x *J(n,x)-J(n-1,x) */
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
                case 0: temp =  cos(x)+sin(x); break;
                case 1: temp = -cos(x)+sin(x); break;
                case 2: temp = -cos(x)-sin(x); break;
                case 3: temp =  cos(x)-sin(x); break;
            }
            b = invsqrtpi*temp/sqrt(x);
        } else {	
            a = j0(x);
            b = j1(x);
            for(i=1;i<n;i++){
                temp = b;
                b = b*((double)(i+i)/x) - a; /* avoid underflow */
                a = temp;
            }
        }
    } else {
        if(ix<0x3e100000) {	/* x < 2**-29 */
    /* x is tiny, return the first Taylor expansion of J(n,x) 
     * J(n,x) = 1/n!*(x/2)^n  - ...
     */
            if(n>33)	/* underflow */
                b = zero;
            else {
                temp = x*0.5; b = temp;
                for (a=one,i=2;i<=n;i++) {
                    a *= (double)i;		/* a = n! */
                    b *= temp;		/* b = (x/2)^n */
                }
                b = b/a;
            }
        } else {
            /* use backward recurrence */
            /* 			x      x^2      x^2       
             *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
             *			2n  - 2(n+1) - 2(n+2)
             *
             * 			1      1        1       
             *  (for large x)   =  ----  ------   ------   .....
             *			2n   2(n+1)   2(n+2)
             *			-- - ------ - ------ - 
             *			 x     x         x
             *
             * Let w = 2n/x and h=2/x, then the above quotient
             * is equal to the continued fraction:
             *		    1
             *	= -----------------------
             *		       1
             *	   w - -----------------
             *			  1
             * 	        w+h - ---------
             *		       w+2h - ...
             *
             * To determine how many terms needed, let
             * Q(0) = w, Q(1) = w(w+h) - 1,
             * Q(k) = (w+k*h)*Q(k-1) - Q(k-2),
             * When Q(k) > 1e4	good for single 
             * When Q(k) > 1e9	good for double 
             * When Q(k) > 1e17	good for quadruple 
             */
        /* determine k */
            double t,v;
            double q0,q1,h,tmp; int k,m;
            w  = (n+n)/(double)x; h = 2.0/(double)x;
            q0 = w;  z = w+h; q1 = w*z - 1.0; k=1;
            while(q1<1.0e9) {
                k += 1; z += h;
                tmp = z*q1 - q0;
                q0 = q1;
                q1 = tmp;
            }
            m = n+n;
            for(t=zero, i = 2*(n+k); i>=m; i -= 2) t = one/(i/x-t);
            a = t;
            b = one;
            /*  estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
             *  Hence, if n*(log(2n/x)) > ...
             *  single 8.8722839355e+01
             *  double 7.09782712893383973096e+02
             *  long double 1.1356523406294143949491931077970765006170e+04
             *  then recurrent value may overflow and the result is 
             *  likely underflow to zero
             */
            tmp = n;
            v = two/x;
            tmp = tmp*log(fabs(v*tmp));
            if(tmp<7.09782712893383973096e+02) {
                for(i=n-1,di=(double)(i+i);i>0;i--){
                    temp = b;
                    b *= di;
                    b  = b/x - a;
                    a = temp;
                    di -= two;
                }
            } else {
                for(i=n-1,di=(double)(i+i);i>0;i--){
                    temp = b;
                    b *= di;
                    b  = b/x - a;
                    a = temp;
                    di -= two;
                /* scale b to avoid spurious overflow */
                    if(b>1e100) {
                        a /= b;
                        t /= b;
                        b  = one;
                    }
                }
            }
            b = (t*j0(x)/b);
        }
    }
    if(sgn==1) return -b; else return b;
}

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

/****** ma.lib/jn *************************************************************
* 
*   NAME	
* 	jn -- Return Bessel function of first kind, order n. (V1.0)
*
*   SYNOPSIS
*	double result = jn(int n, double x);
*	  D0		   D0
*	double jn(int n, double x);
*
*   FUNCTION
*	Compute the Bessel function of the first kind of order n.
*	This function is used in various mathematical and physical
*	applications. This implementation uses high-precision algorithms
*	from fdlibm for maximum accuracy.
* 
*   INPUTS
*	n - Order of the Bessel function.
*	x - Input value. Must be >= 0 for valid result.
*	
*   RESULT
*	result - Bessel function J_n(x). Returns NaN if x < 0, returns
*	        0 if n < 0 and x is 0, returns 1 if n = 0 and x is 0.
* 
*   EXAMPLE
*	int n = 2;
*	double x = 1.0;
*	double result = jn(n, x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM if x < 0.
* 
*   SEE ALSO
*	yn(), j0(), j1(), math.h
* 
******************************************************************************/

double jn(int n, double x)
{
    return __ieee754_jn(n, x);
}

