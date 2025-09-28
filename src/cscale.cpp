/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *	Function	ComScale
 *	Programmer	N.d'Alterio (adapted)
 *	Date		31/10/94
 *
 *  Synopsis:	This function scales a complex number by a real factor.
 *
 *  Arguments:	COMPLEX z	-	complex number to scale
 *              double scale	-	scaling factor
 *
 *  Returns:	COMPLEX		-	scaled complex number
 *
 *  Variables:	result		-	the scaled complex number
 *      	z		-	input complex number
 *              scale		-	scaling factor
 *
 */

#include "include/internal/complex_internal.h"

COMPLEX ComScale(COMPLEX z, double scale)
{
    COMPLEX result;

    /*
     *  Scale both real and imaginary parts.
     */
    result.Real = z.Real * scale;
    result.Imag = z.Imag * scale;

    /*
     *  Return the result.
     */
    return result;

}   /* end function ComScale */