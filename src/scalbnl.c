/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_scalbn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * scalbnl (long double x, int n)
 * scalbnl(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 * Note: SAS/C maps long double to double, so delegate to scalbn()
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double scalbnl(long double x, int n)
{
    /* SAS/C maps long double to double, so delegate to scalbn() */
    return (long double)scalbn((double)x, n);
}

