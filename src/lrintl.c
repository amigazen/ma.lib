/*
 * lrintl.c - Round to nearest long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long lrintl(long double x)
{
    return lrint((double)x);
}
