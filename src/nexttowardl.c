/*
 * nexttowardl.c - Next representable value toward another (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double nexttowardl(long double x, long double y)
{
    return (long double)nexttoward((double)x, (double)y);
}
