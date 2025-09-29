/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * 
 * isinf(x) returns 1 if x is infinity, else 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

int isinf(double x)
{
    int hx, lx;
    hx = __HI(x);
    lx = __LO(x);
    hx &= 0x7fffffff;        /* mask off sign bit */
    hx |= (unsigned)(lx|(-lx))>>31;  /* set lx|=0 if lx==0, else lx|=1 */
    hx = 0x7ff00000 - hx;    /* now hx is 0 if x is infinite */
    return ((unsigned)(hx))>>31;
}
