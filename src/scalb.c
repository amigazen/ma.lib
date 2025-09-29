/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_scalb.c and w_scalb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double scalb(double x, double fn)
 * wrapper scalb(double x, double fn) is provide for
 * passing various standard test suite. One 
 * should use scalbn() instead.
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

static double __ieee754_scalb(double x, double fn)
{
    if (isnan(x)||isnan(fn)) return x*fn;
    if (!finite(fn)) {
        if(fn>0.0) return x*fn;
        else       return x/(-fn);
    }
    if (rint(fn)!=fn) return (fn-fn)/(fn-fn);
    if ( fn > 65000.0) return scalbn(x, 65000);
    if (-fn > 65000.0) return scalbn(x,-65000);
    return scalbn(x,(int)fn);
}

double scalb(double x, double fn)
{
    double z;
    z = __ieee754_scalb(x,fn);
    if(!(finite(z)||isnan(z))&&finite(x)) {
        /* scalb overflow */
        return z;
    }
    if(z==0.0&&z!=x) {
        /* scalb underflow */
        return z;
    } 
    if(!finite(fn)) errno = ERANGE;
    return z;
}
