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

/****** ma.lib/cproj **********************************************************
* 
*   NAME	
* 	cproj -- Return complex projection onto Riemann sphere. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cproj(complex_t z);
*	  D0		   D0
*	complex_t cproj(complex_t z);
*
*   FUNCTION
*	Project complex number onto the Riemann sphere. For finite z,
*	returns z unchanged. For infinite z, projects to infinity on
*	the real axis with sign of imaginary part preserved.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Projection of z. Returns z if finite, returns
*	        (INFINITY, copysign(0.0, cimag(z))) if infinite.
* 
*   EXAMPLE
*	complex_t z = {INFINITY, 1.0};
*	complex_t result = cproj(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Used for complex arithmetic with infinity handling.
* 
*   SEE ALSO
*	cabs(), carg(), complex.h
* 
******************************************************************************/

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
