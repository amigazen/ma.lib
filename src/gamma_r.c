/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_gamma_r.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * gamma_r(x, signgamp) - Reentrant gamma function
 * Return the logarithm of the Gamma function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Forward declaration */
double lgamma_r(double x, int *signgamp);

double gamma_r(double x, int *signgamp)
{
    return lgamma_r(x, signgamp);
}
