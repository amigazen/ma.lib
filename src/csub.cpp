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

/****** ma.lib/csub ***********************************************************
* 
*   NAME	
* 	csub -- Subtract two complex numbers. (V1.0)
*
*   SYNOPSIS
*	complex_t result = csub(complex_t a, complex_t b);
*	  D0		   D0
*	complex_t csub(complex_t a, complex_t b);
*
*   FUNCTION
*	Subtract two complex numbers. This computes a - b where a and b
*	are complex numbers. This implementation uses SAS/C's C++ complex
*	class for maximum accuracy.
* 
*   INPUTS
*	a - First complex number (minuend).
*	b - Second complex number (subtrahend).
*	
*   RESULT
*	result - Complex number a - b. Returns {a.re - b.re, a.im - b.im}.
* 
*   EXAMPLE
*	complex_t a = {3.0, 4.0};
*	complex_t b = {1.0, 2.0};
*	complex_t result = csub(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	cadd(), cmul(), cdiv(), complex.h
* 
******************************************************************************/

complex_t csub(complex_t a, complex_t b)
{
    // Convert to SAS/C C++ complex class
    complex cpp_a(a.re, a.im);
    complex cpp_b(b.re, b.im);
    
    // Use SAS/C's C++ operator-
    complex cpp_result = cpp_a - cpp_b;
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}