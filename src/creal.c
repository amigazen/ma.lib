/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    creal
 *  Synopsis:    Get the real part of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - real part
 *  Description: creal(z) = real(z)
 */

#include "complex.h"

double creal(complex_t z)
{
    return z.re;
}
