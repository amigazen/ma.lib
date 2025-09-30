/*
 * C99 complex number functions - C wrapper around SAS/C C++ complex class
 * 
 * This file provides C99-compliant complex number functions that wrap
 * SAS/C's existing C++ complex class implementation.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <complex.h>
#include <math.h>
#include "include/internal/complex_internal.h"

/*
 * clog - complex natural logarithm
 * 
 * Returns the complex natural logarithm of z.
 * clog(z) = ln(z)
 * 
 * This wraps SAS/C's C++ log() function.
 */

/****** ma.lib/clog *****************************************************
* 
*   NAME	
* 	clog -- Return complex natural logarithm of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = clog(complex_t z);
*	  D0		   D0
*	complex_t clog(complex_t z);
*
*   FUNCTION
*	Compute the complex natural logarithm of z. For z = a + bi, the complex
*	logarithm is: clog(z) = log(|z|) + i*arg(z)
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Complex logarithm of z. Returns -Infinity+NaN*i if z is 0,
*	        +Infinity+NaN*i if z is +Infinity, NaN+NaN*i if z is NaN.
* 
*   EXAMPLE
*	complex_t z = {M_E, 0.0};  
*	complex_t log_z = clog(z);  
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance. Uses clog_c99 internally to avoid
*	conflicts with iostream.
* 
*   SEE ALSO
*	cexp(), cpow(), cabs(), carg(), complex.h
* 
******************************************************************************/

/* Internal implementation function to avoid clog conflict */
complex_t clog_c99(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ log() function
    complex cpp_result = log(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}

/* Provide clog as a macro to avoid iostream conflict */
#define clog clog_c99
