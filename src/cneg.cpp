/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cneg
 *  Synopsis:    Negate a complex number
 *  Arguments:   z - complex number to negate
 *  Returns:     double_complex - negated complex number
 *  Description: cneg(z) = -z = (-real(z), -imag(z))
 */

#include "include/internal/complex_internal.h"

double_complex cneg(double_complex z)
{
    double_complex result;

    /*
     *  Negate both real and imaginary parts
     */
    result.re = -z.re;
    result.im = -z.im;

    /*
     *  Return the result
     */
    return result;
}