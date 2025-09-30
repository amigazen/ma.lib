/*
 * truncf.c - Truncate toward zero (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float truncf(float x)
{
    return (float)trunc((double)x);
}
