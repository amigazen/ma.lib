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
 * cabs - complex absolute value (modulus)
 * 
 * Returns the absolute value (modulus) of a complex number.
 * cabs(z) = sqrt(creal(z)^2 + cimag(z)^2)
 * 
 * This wraps SAS/C's C++ abs() function.
 */

/****** ma.lib/cabs *****************************************************
* 
*   NAME	
* 	cabs -- Return absolute value of complex number. (V1.0)
*
*   SYNOPSIS
*	double result = cabs(complex_t z);
*	  D0		   D0
*	double cabs(complex_t z);
*
*   FUNCTION
*	Compute the absolute value (modulus) of a complex number z.
*	The absolute value is the distance from the origin in the complex
*	plane: sqrt(real^2 + imag^2).
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Absolute value of z, always non-negative. Returns NaN if
*	        either part of z is NaN, +Infinity if either part is
*	        infinite.
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0}; 
*	double abs = cabs(z);     
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	carg(), creal(), cimag(), complex.h
* 
******************************************************************************/

double cabs(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ abs() function
    return abs(cpp_z);
}