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

/****** ma.lib/cscale ********************************************************
* 
*   NAME	
* 	cscale -- Return complex number scaled by real factor. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cscale(complex_t z, double scale);
*	  D0		   D0
*	complex_t cscale(complex_t z, double scale);
*
*   FUNCTION
*	Scale a complex number by a real factor. This multiplies both
*	the real and imaginary parts of the complex number by the
*	scaling factor.
* 
*   INPUTS
*	z - Complex number to scale.
*	scale - Scaling factor (real number).
*	
*   RESULT
*	result - Scaled complex number. Returns (scale * z.re, scale * z.im).
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	double scale = 2.0;
*	complex_t result = cscale(z, scale);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to cmul(z, {scale, 0.0}).
* 
*   SEE ALSO
*	cmul(), cneg(), complex.h
* 
******************************************************************************/

complex_t cscale(complex_t z, double scale)
{
    complex_t result;

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