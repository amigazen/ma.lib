/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cimag
 *  Synopsis:    Get the imaginary part of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - imaginary part
 *  Description: cimag(z) = imag(z)
 */

#include "complex.h"

double cimag(complex_t z)
{
    return z.im;
}
