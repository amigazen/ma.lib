/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *	Function	ComNeg
 *	Programmer	N.d'Alterio (adapted)
 *	Date		31/10/94
 *
 *  Synopsis:	This function negates a complex number and returns the result.
 *
 *  Arguments:	COMPLEX z	-	complex number to negate
 *
 *  Returns:	COMPLEX		-	negated complex number
 *
 *  Variables:	result		-	the negated complex number
 *      	z		-	input complex number
 *
 */

#include "include/internal/complex_internal.h"

complex_double ComNeg(complex_double z)
{
    complex_double result;

    /*
     *  Negate both real and imaginary parts.
     */
    result.re = -z.re;
    result.im = -z.im;

    /*
     *  Return the result.
     */
    return result;

}   /* end function ComNeg */