/*
 * scalblnf.c - Scale by long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float scalblnf(float x, long n)
{
    return (float)scalbln((double)x, n);
}
