/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cimag
 *  Synopsis:    Get the imaginary part of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - imaginary part
 *  Description: cimag(z) = imag(z)
 */

#include "complex.h"

/****** ma.lib/cimag ***********************************************************
* 
*   NAME	
* 	cimag -- Return imaginary part of complex number. (V1.0)
*
*   SYNOPSIS
*	double result = cimag(complex_t z);
*	  D0		   D0
*	double cimag(complex_t z);
*
*   FUNCTION
*	Extract the imaginary part of a complex number. This function returns
*	the imaginary component of the complex number z. This is equivalent
*	to accessing the .im field of the complex_t structure.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Imaginary part of z. Returns z.im.
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	double imag_part = cimag(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to z.im.
* 
*   SEE ALSO
*	creal(), complex.h
* 
******************************************************************************/

double cimag(complex_t z)
{
    return z.im;
}
