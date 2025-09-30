/*
 * scalblnl.c - Scale by long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double scalblnl(long double x, long n)
{
    return (long double)scalbln((double)x, n);
}
