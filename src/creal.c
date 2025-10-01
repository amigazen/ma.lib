/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    creal
 *  Synopsis:    Get the real part of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - real part
 *  Description: creal(z) = real(z)
 */

#include "complex.h"

/****** ma.lib/creal ***********************************************************
* 
*   NAME	
* 	creal -- Return real part of complex number. (V1.0)
*
*   SYNOPSIS
*	double result = creal(complex_t z);
*	  D0		   D0
*	double creal(complex_t z);
*
*   FUNCTION
*	Extract the real part of a complex number. This function returns
*	the real component of the complex number z. This is equivalent
*	to accessing the .re field of the complex_t structure.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Real part of z. Returns z.re.
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	double real_part = creal(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to z.re.
* 
*   SEE ALSO
*	cimag(), complex.h
* 
******************************************************************************/

double creal(complex_t z)
{
    return z.re;
}
