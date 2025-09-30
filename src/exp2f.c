/*
 * exp2f.c - Base-2 exponential function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float exp2f(float x)
{
    return (float)exp2((double)x);
}
