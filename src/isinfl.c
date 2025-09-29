/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * isinfl(x) returns 1 if x is infinity, else 0
 * Note: SAS/C maps long double to double, so delegate to isinf()
 */

#include <math.h>
#include "include/internal/m99_math.h"

int isinfl(long double x)
{
    /* SAS/C maps long double to double, so delegate to isinf() */
    return isinf((double)x);
}
