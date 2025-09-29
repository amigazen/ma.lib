/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ldexp.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double ldexp(double value, int exp)
 * Returns value * 2^exp
 */

#include <math.h>
#include "include/internal/m99_math.h"

double ldexp(double value, int exp)
{
    if(!finite(value)||value==0.0) return value;
    value = scalbn(value,exp);
    if(!finite(value)||value==0.0) {
        /* Set errno to ERANGE if available */
        /* errno = ERANGE; */
    }
    return value;
}