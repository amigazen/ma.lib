/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cproj
 *  Synopsis:    Complex projection onto Riemann sphere
 *  Arguments:   z - complex number
 *  Returns:     double_complex - projection of z
 *  Description: cproj(z) = z if z is finite, otherwise (INFINITY, copysign(0.0, cimag(z)))
 */

#include "include/internal/complex_internal.h"

complex_t cproj(complex_t z)
{
    /* Check if z is finite */
    if (isfinite(z.re) && isfinite(z.im)) {
        return z;
    }
    
    /* For infinite values, project to infinity on the real axis */
    complex_t result;
    result.re = INFINITY;
    result.im = copysign(0.0, z.im);
    
    return result;
}
