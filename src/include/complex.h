/*
 * C99 Complex Number Support for SAS/C
 * 
 * This header provides C99-compliant complex number support by wrapping
 * SAS/C's existing C++ complex class implementation.
 * 
 * Uses SAS/C's class complex for implementation while providing
 * standard C99 complex API for maximum compatibility.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _COMPLEX_H
#define _COMPLEX_H

#ifdef __cplusplus
    #include <complex.h>  // Use SAS/C's C++ complex class
    extern "C" {
#endif

/*========================================================================*
 *                    C99 COMPLEX NUMBER TYPES
 *========================================================================*/

/* 
 * C99 complex number types - SAS/C compatible implementation
 * These are standard C99 types that work with SAS/C's C++ complex class
 */
typedef double complex double complex;
typedef float complex float complex;
typedef long double complex long double complex;

/* C99 complex number macros */
#ifndef I
#define I              {0.0, 1.0}
#endif

/* Helper macros for struct-based complex numbers */
#define creal(z) ((z).real)
#define cimag(z) ((z).imag)

/*========================================================================*
 *                    C99 COMPLEX NUMBER FUNCTIONS
 *========================================================================*/

/* Basic Operations */
double cabs(double complex z);
double carg(double complex z);
double complex conj(double complex z);

/* Arithmetic Operations (utility functions) */
double complex cadd(double complex a, double complex b);
double complex csub(double complex a, double complex b);
double complex cmul(double complex a, double complex b);
double complex cdiv(double complex a, double complex b);

/* Trigonometric Functions */
double complex cacos(double complex z);
double complex casin(double complex z);
double complex catan(double complex z);
double complex ccos(double complex z);
double complex csin(double complex z);
double complex ctan(double complex z);

/* Hyperbolic Functions */
double complex cacosh(double complex z);
double complex casinh(double complex z);
double complex catanh(double complex z);
double complex ccosh(double complex z);
double complex csinh(double complex z);
double complex ctanh(double complex z);

/* Exponential and Logarithmic Functions */
double complex cexp(double complex z);
double complex clog(double complex z);
double complex clog10(double complex z);
double complex cpow(double complex z, double complex w);
double complex csqrt(double complex z);

/* Projection and Classification */
double complex cproj(double complex z);

/* Float variants */
float cabsf(float complex z);
float cargf(float complex z);
float complex conjf(float complex z);

/* Long double variants */
long double cabsl(long double complex z);
long double cargl(long double complex z);
long double complex conjl(long double complex z);

#ifdef __cplusplus
    }
#endif

#endif /* _COMPLEX_H */