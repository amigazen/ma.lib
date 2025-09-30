/*
 * lroundf.c - Round to nearest long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long lroundf(float x)
{
    return lround((double)x);
}
