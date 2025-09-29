/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cscale
 *  Synopsis:    Scale a complex number by a real factor
 *  Arguments:   z - complex number to scale
 *               scale - scaling factor
 *  Returns:     double_complex - scaled complex number
 *  Description: cscale(z, scale) = (scale * real(z), scale * imag(z))
 */

#include "include/internal/complex_internal.h"

double_complex cscale(double_complex z, double scale)
{
    double_complex result;

    /*
     *  Scale both real and imaginary parts
     */
    result.re = z.re * scale;
    result.im = z.im * scale;

    /*
     *  Return the result
     */
    return result;
}