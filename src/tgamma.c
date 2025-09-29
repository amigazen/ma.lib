/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/w_gamma.c and e_gamma.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double tgamma(double x)
 * Return the Gamma function of x.
 * 
 * Method: call gamma_r and return exp(gamma_r)
 */

#include <math.h>
#include "include/internal/m99_math.h"

extern int signgam;

static double __ieee754_gamma_r(double x, int *signgamp)
{
    return lgamma_r(x, signgamp);
}

double tgamma(double x)
{
    double y;
    y = __ieee754_gamma_r(x,&signgam);
    if(!finite(y)&&finite(x)) {
        if(floor(x)==x&&x<=0.0) {
            /* gamma pole */
            return y;
        } else {
            /* gamma overflow */
            return y;
        }
    } else {
        return exp(y);
    }
}
