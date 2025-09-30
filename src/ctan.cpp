/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    ctan
 *  Synopsis:    Complex tangent
 *  Arguments:   z - complex number
 *  Returns:     double_complex - tangent of z
 *  Description: ctan(z) = csin(z) / ccos(z)
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/ctan *****************************************************
* 
*   NAME	
* 	ctan -- Return complex tangent of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = ctan(complex_t z);
*	  D0		   D0
*	complex_t ctan(complex_t z);
*
*   FUNCTION
*	Compute the complex tangent of z. For z = a + bi, the complex tangent is:
*	ctan(z) = csin(z) / ccos(z)
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Complex tangent of z. Returns NaN+NaN*i if z is NaN,
*	        +Infinity+NaN*i if real part is +Infinity and imaginary
*	        part is finite, +0.0+0.0*i if real part is -Infinity.
* 
*   EXAMPLE
*	complex_t z = {M_PI/4, 0.0};
*	complex_t tan_z = ctan(z);   
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	csin(), ccos(), cexp(), complex.h
* 
******************************************************************************/

complex_t ctan(complex_t z)
{
    /* Use SAS/C C++ complex class for implementation */
    /* tan(z) = sin(z) / cos(z) */
    complex cpp_z(z.re, z.im);
    complex cpp_sin = sin(cpp_z);
    complex cpp_cos = cos(cpp_z);
    complex cpp_result = cpp_sin / cpp_cos;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
