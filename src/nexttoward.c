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
