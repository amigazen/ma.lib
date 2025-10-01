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

/****** ma.lib/carg **********************************************************
* 
*   NAME	
* 	carg -- Return complex argument (phase angle). (V1.0)
*
*   SYNOPSIS
*	double result = carg(complex_t z);
*	  D0		   D0
*	double carg(complex_t z);
*
*   FUNCTION
*	Compute the argument (phase angle) of a complex number. This returns
*	the angle in radians from the positive real axis to the vector
*	representing the complex number. This implementation uses SAS/C's
*	C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Argument of z in radians. Returns NaN if z is NaN,
*	        returns 0 if z is +0, returns π if z is -0.
* 
*   EXAMPLE
*	complex_t z = {1.0, 1.0};
*	double angle = carg(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	cabs(), creal(), cimag(), complex.h
* 
******************************************************************************/

double carg(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ arg() function
    return arg(cpp_z);
}