/*
 * ma.lib Math Library - frexp function
 * 
 * C99/POSIX frexp function for ma.lib
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _WITH_SCLIB

#include <stdio.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * frexp - split floating-point value
 * 
 * Returns the significand of a double "value" as a double quantity,
 * "x", of magnitude less than 1 and stores an integer "n", indirectly
 * through "eptr", such that "value" = "x" * 2^"n"
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
#define EXP_BIAS 1022           /* Exponent bias                */

union dtol {
    double dval;
    int ival[2];
};

double frexp(double value, int *eptr)
{
    union dtol number;
    int *iptr, exp;

    if (value == 0.0) {
        *eptr = 0;
        return 0.0;
    } else {
        number.dval = value;
        iptr = &number.ival[0];
        *eptr = (((*iptr) & EXP_MASK) >> EXP_SHIFTS) - EXP_BIAS;
        *iptr &= ~EXP_MASK;
        exp = EXP_BIAS;
        *iptr |= (exp << EXP_SHIFTS) & EXP_MASK;
        return number.dval;
    }
}

#endif /* _WITH_SCLIB */

