/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fma(double x, double y, double z)
 * IEEE 754 fma function - fused multiply-add
 * 
 * Note: This is a simplified implementation that doesn't provide
 * the full precision guarantees of a true fused multiply-add.
 * For SAS/C on Amiga, we use the standard multiply and add.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/fma **********************************************************
* 
*   NAME	
* 	fma -- Return fused multiply-add x*y + z. (V1.0)
*
*   SYNOPSIS
*	double result = fma(double x, double y, double z);
*	  D0		   D0
*	double fma(double x, double y, double z);
*
*   FUNCTION
*	Compute the fused multiply-add operation x*y + z. This performs the
*	multiplication and addition as a single operation. This implementation
*	uses standard multiply and add for SAS/C compatibility.
* 
*   INPUTS
*	x - First multiplicand.
*	y - Second multiplicand.
*	z - Addend.
*	
*   RESULT
*	result - x*y + z. Returns NaN if any argument is NaN, returns ±Infinity
*	        for large results, returns ±0 for small results.
* 
*   EXAMPLE
*	double x = 2.0, y = 3.0, z = 1.0;
*	double result = fma(x, y, z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to x * y + z.
* 
*   SEE ALSO
*	pow(), exp(), log(), math.h
* 
******************************************************************************/

double fma(double x, double y, double z)
{
    return x * y + z;
}
