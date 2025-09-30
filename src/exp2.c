/*
 * exp2.c - Base-2 exponential function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/*
 * exp2(x) = 2^x
 * 
 * Simple implementation using exp(x * ln(2))
 */

double exp2(double x)
{
    /* Handle special cases */
    if (x == 0.0) return 1.0;
    if (x == 1.0) return 2.0;
    if (x == 2.0) return 4.0;
    
    /* Use exp(x * ln(2)) */
    return exp(x * M_LN2);
}
