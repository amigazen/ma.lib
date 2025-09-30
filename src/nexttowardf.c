/*
 * nexttowardf.c - Next representable value toward another (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float nexttowardf(float x, long double y)
{
    return (float)nexttoward((double)x, y);
}
