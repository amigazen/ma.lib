/*
 * llrint.c - Round to nearest long long integer
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <limits.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

/*
 * llrint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *      Using floating addition.
 * Exception:
 *      Inexact flag raised if x not equal to llrint(x).
 */

static const double huge = 1.0e300;

long_long_t llrint(double x)
{
    int i0,i1,j0;
    unsigned i,j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {
            if(huge+x>0.0) {        /* raise inexact if x != 0 */
                if(j0==-1) return x>0.0?long_to_long_long(1):long_to_long_long(-1);
                else return long_to_long_long(0);
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return long_to_long_long((long)x); /* x is integral */
            if(huge+x>0.0) {        /* raise inexact flag */
                if(i0>0) x += 0.5;
                else x -= 0.5;
                i0 = __HI(x);
                i1 = __LO(x);
                i0 &= (~i);
                i1 = 0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return long_to_long_long(0);   /* inf or NaN */
        else return long_to_long_long((long)x);              /* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return long_to_long_long((long)x);     /* x is integral */
        if(huge+x>0.0) {            /* raise inexact flag */
            if(i0>0) {
                if(j0==20) i0+=1;
                else {
                    j = i1+(1<<(52-j0));
                    if(j<i1) i0 +=1 ;       /* got a carry */
                    i1=j;
                }
            } else {
                if(j0==20) i0-=1;
                else {
                    j = i1 - (1<<(52-j0));
                    if(j>i1) i0 -=1;        /* got a borrow */
                    i1 = j;
                }
            }
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    
    /* Convert to long_long_t, checking for overflow */
    if (x > (double)LONG_MAX) return get_long_long_max();
    if (x < (double)LONG_MIN) return get_long_long_min();
    
    return long_to_long_long((long)x);
}
