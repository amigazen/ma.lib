/*
 * log2.c - Base-2 logarithm function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/*
 * log2(x) = log(x) / log(2)
 * 
 * Simple implementation using log(x) / log(2)
 */

double log2(double x)
{
    /* Handle special cases first */
    if (x <= 0.0) {
        errno = EDOM;
        if (x == 0.0) {
            return -INFINITY;
        } else {
            return NAN;  /* log2 of negative number */
        }
    }
    
    /* Use log(x) / log(2) */
    return log(x) / M_LN2;
}