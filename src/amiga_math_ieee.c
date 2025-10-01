/*
 * amiga_math_ieee.c - AmigaOS IEEE math library integration
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file provides integration with AmigaOS IEEE math libraries
 * using the same pattern as amiga-gcc-2.95.3-math-main.
 */

#ifndef _AMIGA_MATH_IEEE_C
#define _AMIGA_MATH_IEEE_C

#include <exec/exec.h>
#include <libraries/mathieeedoubbas.h>
#include <libraries/mathieeedoubtrans.h>
#include <amiga/math.h>

/****** ma.lib/amiga_ieee_add **********************************************
* 
*   NAME	
* 	amiga_ieee_add -- Return IEEE double precision addition. (V1.0)
*
*   SYNOPSIS
*	double result = amiga_ieee_add(double x, double y);
*	  D0		   D0
*	double amiga_ieee_add(double x, double y);
*
*   FUNCTION
*	Add two IEEE double precision numbers using Amiga's mathieeedoubbas
*	library. This provides access to the Amiga's native IEEE math
*	functions for maximum compatibility.
* 
*   INPUTS
*	x - First value (double).
*	y - Second value (double).
*	
*   RESULT
*	result - x + y using IEEE library.
* 
*   EXAMPLE
*	double x = 3.14, y = 2.86;
*	double result = amiga_ieee_add(x, y);  
*
*   NOTES
*	This function is Amiga-specific and requires mathieeedoubbas.library.
*	Uses inline assembly for direct library calls.
* 
*   SEE ALSO
*	amiga_ieee_sub(), amiga_ieee_mul(), mathieeedoubbas.library
* 
******************************************************************************/

double amiga_ieee_add(double x, double y)
{
    register double result asm("d0");
    
    asm("move.l 16(sp),d0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; movea.l %1,a6; jsr -66(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_sub - IEEE double precision subtraction
 */
double amiga_ieee_sub(double x, double y)
{
    register double result asm("d0");
    
    asm("move.l 16(sp),d0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; movea.l %1,a6; jsr -72(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_mul - IEEE double precision multiplication
 */
double amiga_ieee_mul(double x, double y)
{
    register double result asm("d0");
    
    asm("move.l 16(sp),d0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; movea.l %1,a6; jsr -78(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_div - IEEE double precision division
 */
double amiga_ieee_div(double x, double y)
{
    register double result asm("d0");
    
    asm("move.l 16(sp),d0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; movea.l %1,a6; jsr -84(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_cmp - IEEE double precision comparison
 */
long amiga_ieee_cmp(double x, double y)
{
    register long result asm("d0");
    
    asm("move.l 16(sp),d0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; movea.l %1,a6; jsr -42(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_neg - IEEE double precision negation
 */
double amiga_ieee_neg(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %2,a6; jsr -60(a6);" :
        "=r"(result) : "m"(x), "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_fabs - IEEE double precision absolute value
 */
double amiga_ieee_fabs(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -54(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_ceil - IEEE double precision ceiling
 */
double amiga_ieee_ceil(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -96(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_floor - IEEE double precision floor
 */
double amiga_ieee_floor(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -90(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_fix - IEEE double to long conversion
 */
long amiga_ieee_fix(double x)
{
    register long result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -30(a6);" :
        "=r"(result) : "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_float - Long to IEEE double conversion
 */
double amiga_ieee_float(long x)
{
    register double result asm("d0");
    
    asm("move.l %1,d0; movea.l %2,a6; jsr -36(a6);" :
        "=r"(result) : "m"(x), "m"(MathIeeeDoubBasBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/* IEEE Transcendental Functions */

/*
 * amiga_ieee_sin - IEEE double precision sine
 */
double amiga_ieee_sin(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -36(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_cos - IEEE double precision cosine
 */
double amiga_ieee_cos(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -42(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_tan - IEEE double precision tangent
 */
double amiga_ieee_tan(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -48(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_asin - IEEE double precision arcsine
 */
double amiga_ieee_asin(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -114(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_acos - IEEE double precision arccosine
 */
double amiga_ieee_acos(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -120(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_atan - IEEE double precision arctangent
 */
double amiga_ieee_atan(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -30(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_sinh - IEEE double precision hyperbolic sine
 */
double amiga_ieee_sinh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -60(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_cosh - IEEE double precision hyperbolic cosine
 */
double amiga_ieee_cosh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -66(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_tanh - IEEE double precision hyperbolic tangent
 */
double amiga_ieee_tanh(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -72(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_exp - IEEE double precision exponential
 */
double amiga_ieee_exp(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -78(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_log - IEEE double precision natural logarithm
 */
double amiga_ieee_log(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -84(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_log10 - IEEE double precision base-10 logarithm
 */
double amiga_ieee_log10(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -126(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_sqrt - IEEE double precision square root
 */
double amiga_ieee_sqrt(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -96(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_pow - IEEE double precision power
 */
double amiga_ieee_pow(double x, double y)
{
    register double result asm("d0");
    
    asm("movea.l 16(sp),a0; move.l 20(sp),d1; move.l 24(sp),d2; move.l 28(sp),d3; "
        "movea.l %1,a6; jsr -90(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "d2", "d3", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

/*
 * amiga_ieee_sincos - IEEE double precision combined sine/cosine
 */
double amiga_ieee_sincos(double *cos_result, double x)
{
    register double result asm("d0");
    
    asm("movea.l 8(sp),a0; move.l 12(sp),d0; move.l 16(sp),d1; movea.l %1,a6; jsr -54(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}

#endif /* __AMIGA__ */
