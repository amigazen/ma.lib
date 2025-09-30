/*
 * roundl.c - Round to nearest integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double roundl(long double x)
{
    return (long double)round((double)x);
}
