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

complex_t cneg(complex_t z)
{
    complex_t result;

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