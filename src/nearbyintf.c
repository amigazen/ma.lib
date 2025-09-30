/*
 * nearbyintf.c - Round to nearest integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float nearbyintf(float x)
{
    return (float)nearbyint((double)x);
}
