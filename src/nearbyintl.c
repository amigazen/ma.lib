/*
 * nearbyintl.c - Round to nearest integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double nearbyintl(long double x)
{
    return (long double)nearbyint((double)x);
}
