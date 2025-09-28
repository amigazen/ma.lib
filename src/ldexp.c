/*
 * m99 Math Library - ldexp function
 * 
 * C99/POSIX ldexp function for m99.lib
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * ldexp - combine floating-point value
 * 
 * Returns the quantity "value" * 2^"exp"
 * 
 * For IEEE format the double precision word format is:
 * WORD N   =>    SEEEEEEEEEEEMMMM 
 * WORD N+1 =>    MMMMMMMMMMMMMMMM 
 * WORD N+2 =>    MMMMMMMMMMMMMMMM 
 * WORD N+3 =>    MMMMMMMMMMMMMMMM
 * 
 * Where:          S  =>   Sign bit 
 *                 E  =>   Exponent 
 *                 X  =>   Ignored (set to 0)
 *                 M  =>   Mantissa bit
 */
#define MANT_MASK 0x800FFFFF    /* Mantissa extraction mask     */
#define EXP_MASK 0x7FF00000     /* Mask for exponent            */
#define EXP_SHIFTS 20           /* Shifts to get into LSB's     */
#define EXP_BIAS 1023           /* Exponent bias                */

union dtol {
    double dval;
    int ival[2];
};

double ldexp(double value, int exp)
{
    union dtol number;
    int *iptr, cexp;

    if (value == 0.0) {
        return 0.0;
    } else {
        number.dval = value;
        iptr = &number.ival[0];
        cexp = (((*iptr) & EXP_MASK) >> EXP_SHIFTS) - EXP_BIAS;
        *iptr &= ~EXP_MASK;
        exp += EXP_BIAS;
        *iptr |= ((exp + cexp) << EXP_SHIFTS) & EXP_MASK;
        return number.dval;
    }
}
