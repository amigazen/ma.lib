/*
 * amiga_math_ffp.c - Amiga FFP math library integration
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file provides integration with Amiga mathffp.library
 */

#ifndef _AMIGA_MATH_FFP_C
#define _AMIGA_MATH_FFP_C

#include <exec/exec.h>
#include <libraries/mathffp.h>
#include <amiga/math.h>

/****** ma.lib/amiga_ffp_sin ***********************************************
* 
*   NAME	
* 	amiga_ffp_sin -- Return sine using Amiga FFP library. (V1.0)
*
*   SYNOPSIS
*	double result = amiga_ffp_sin(double x);
*	  D0		   D0
*	double amiga_ffp_sin(double x);
*
*   FUNCTION
*	Compute the sine of x using Amiga's mathffp.library. This provides
*	access to the Amiga's native FFP (Fast Floating Point) math
*	functions for maximum compatibility.
* 
*   INPUTS
*	x - Input value in radians (double).
*	
*   RESULT
*	result - Sine of x using FFP library.
* 
*   EXAMPLE
*	double x = M_PI / 2.0;
*	double result = amiga_ffp_sin(x);  
*
*   NOTES
*	This function is Amiga-specific and requires mathffp.library.
*	Uses inline assembly for direct library calls.
* 
*   SEE ALSO
*	amiga_ffp_cos(), amiga_ffp_tan(), mathffp.library
* 
******************************************************************************/

double amiga_ffp_sin(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -36(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_cos - FFP cosine function
 */
double amiga_ffp_cos(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -42(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_tan - FFP tangent function
 */
double amiga_ffp_tan(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -48(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_asin - FFP arcsine function
 */
double amiga_ffp_asin(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -114(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_acos - FFP arccosine function
 */
double amiga_ffp_acos(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -120(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_atan - FFP arctangent function
 */
double amiga_ffp_atan(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -30(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_sinh - FFP hyperbolic sine function
 */
double amiga_ffp_sinh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -60(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_cosh - FFP hyperbolic cosine function
 */
double amiga_ffp_cosh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -66(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_tanh - FFP hyperbolic tangent function
 */
double amiga_ffp_tanh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -72(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_exp - FFP exponential function
 */
double amiga_ffp_exp(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -78(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_log - FFP natural logarithm function
 */
double amiga_ffp_log(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -84(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_log10 - FFP base-10 logarithm function
 */
double amiga_ffp_log10(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -126(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_sqrt - FFP square root function
 */
double amiga_ffp_sqrt(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -96(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_pow - FFP power function
 */
double amiga_ffp_pow(double x, double y)
{
    register double result asm("d0");
    
    asm("movea.l 16(sp),a0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; "
        "movea.l %1,a6; jsr -90(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ffp_sincos - FFP combined sine/cosine function
 */
double amiga_ffp_sincos(double *cos_result, double x)
{
    register double result asm("d0");
    
    asm("movea.l 8(sp),a0; move.l 12(sp),d0; move.l 16(sp),d1; movea.l %1,a6; jsr -54(a6);" :
        "=r"(result) : "m"(MathFFPBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

#endif /* _AMIGA_MATH_FFP_C */
