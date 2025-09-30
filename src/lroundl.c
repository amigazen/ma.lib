/*
 * lroundl.c - Round to nearest long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long lroundl(long double x)
{
    return lround((double)x);
}
