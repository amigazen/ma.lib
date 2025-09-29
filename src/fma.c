/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fma(double x, double y, double z)
 * IEEE 754 fma function - fused multiply-add
 * 
 * Note: This is a simplified implementation that doesn't provide
 * the full precision guarantees of a true fused multiply-add.
 * For SAS/C on Amiga, we use the standard multiply and add.
 */

#include <math.h>
#include "include/internal/m99_math.h"

double fma(double x, double y, double z)
{
    return x * y + z;
}
