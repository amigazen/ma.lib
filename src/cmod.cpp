/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cmod
 *  Synopsis:    Calculate the modulus (absolute value) of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - the modulus
 *  Description: cmod(z) = sqrt(real(z)^2 + imag(z)^2)
 *               This is equivalent to cabs(z) but provided for completeness
 */

#include <math.h>
#include "include/internal/complex_internal.h"

double cmod(double_complex z)
{
    double mod;

    /*
     *  Calculate the modulus using the C99 complex number structure
     */
    mod = sqrt(z.re * z.re + z.im * z.im);

    /*
     *  Return the answer
     */
    return mod;
}

/*========================================================================*
                                   END
 *========================================================================*/
