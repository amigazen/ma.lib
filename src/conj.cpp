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
#include "include/internal/complex_internal.h"

/****** ma.lib/conj **********************************************************
* 
*   NAME	
* 	conj -- Return complex conjugate. (V1.0)
*
*   SYNOPSIS
*	complex_t result = conj(complex_t z);
*	  D0		   D0
*	complex_t conj(complex_t z);
*
*   FUNCTION
*	Compute the complex conjugate of z. This returns a complex number
*	with the same real part but negated imaginary part. This
*	implementation uses SAS/C's C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex conjugate of z. Returns (z.re, -z.im).
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	complex_t result = conj(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	creal(), cimag(), cabs(), complex.h
* 
******************************************************************************/

complex_t conj(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ conj() function
    complex cpp_result = conj(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}