/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double nan(const char *tagp)
 * float nanf(const char *tagp)
 * long double nanl(const char *tagp)
 * IEEE 754 nan functions
 */

#include <math.h>
#include "include/internal/m99_math.h"

double nan(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return NAN;
}

float nanf(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return (float)NAN;
}

long double nanl(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return (long double)NAN;
}
