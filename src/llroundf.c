/*
 * llroundf.c - Round to nearest long long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

long_long_t llroundf(float x)
{
    return llround((double)x);
}
