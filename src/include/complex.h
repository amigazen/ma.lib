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
extern "C" {
#endif

/*========================================================================*
 *                    C99 COMPLEX NUMBER TYPES
 *========================================================================*/

/* 
 * C99 complex number types - SAS/C compatible implementation
 * These map to SAS/C's C++ complex class internally
 */

/* Define the actual complex number structures for C89 compatibility */
typedef struct { double re, im; } complex_double;
typedef struct { float re, im; } complex_float;
typedef struct { long double re, im; } complex_long_double;

/* C99 complex number type definitions */
typedef complex_double double_complex;
typedef complex_float float_complex;
typedef complex_long_double long_double_complex;


/* C99 complex number macros */
#ifndef I
#define I              {0.0, 1.0}
#endif

/* Complex number literals for struct-based types */
#define CMPLXF(real, imag)  ((struct complex_float){real, imag})
#define CMPLX(real, imag)   ((struct complex_double){real, imag})
#define CMPLXL(real, imag)  ((struct complex_long_double){real, imag})

/* Helper macros for struct-based complex numbers */
#define creal(z) ((z).re)
#define cimag(z) ((z).im)

/* C99-compatible complex number creation functions */
/* Note: These are implemented as macros for C89 compatibility */
#define cpack(r, i) ((complex_double){(r), (i)})
#define cpackf(r, i) ((complex_float){(r), (i)})
#define cpackl(r, i) ((complex_long_double){(r), (i)})

/*========================================================================*
 *                    C99 COMPLEX NUMBER FUNCTIONS
 *========================================================================*/

/* Basic Operations */
double cabs(double_complex z);
double carg(double_complex z);
double_complex conj(double_complex z);

/* Trigonometric Functions */
double_complex cacos(double_complex z);
double_complex casin(double_complex z);
double_complex catan(double_complex z);
double_complex ccos(double_complex z);
double_complex csin(double_complex z);
double_complex ctan(double_complex z);

/* Hyperbolic Functions */
double_complex cacosh(double_complex z);
double_complex casinh(double_complex z);
double_complex catanh(double_complex z);
double_complex ccosh(double_complex z);
double_complex csinh(double_complex z);
double_complex ctanh(double_complex z);

/* Exponential and Logarithmic Functions */
double_complex cexp(double_complex z);
#ifndef __cplusplus
double_complex clog(double_complex z);
#else
/* In C++, clog conflicts with iostream, so we use a different name */
double_complex clog_c99(double_complex z);
#define clog clog_c99
#endif
double_complex cpow(double_complex z, double_complex w);
double_complex csqrt(double_complex z);

/* Utility Functions */
double cmod(double_complex z);
double_complex cneg(double_complex z);
double_complex cscale(double_complex z, double scale);

/* Projection and Classification */
double_complex cproj(double_complex z);

/* Float variants */
float cabsf(float_complex z);
float cargf(float_complex z);
float_complex conjf(float_complex z);
float_complex cacosf(float_complex z);
float_complex casinf(float_complex z);
float_complex catanf(float_complex z);
float_complex ccosf(float_complex z);
float_complex csinf(float_complex z);
float_complex ctanf(float_complex z);
float_complex cacoshf(float_complex z);
float_complex casinhf(float_complex z);
float_complex catanhf(float_complex z);
float_complex ccoshf(float_complex z);
float_complex csinhf(float_complex z);
float_complex ctanhf(float_complex z);
float_complex cexpf(float_complex z);
float_complex clogf(float_complex z);
float_complex cpowf(float_complex z, float_complex w);
float_complex csqrtf(float_complex z);
float_complex cprojf(float_complex z);

/* Long double variants */
long double cabsl(long_double_complex z);
long double cargl(long_double_complex z);
long_double_complex conjl(long_double_complex z);
long_double_complex cacosl(long_double_complex z);
long_double_complex casinl(long_double_complex z);
long_double_complex catanl(long_double_complex z);
long_double_complex ccosl(long_double_complex z);
long_double_complex csinl(long_double_complex z);
long_double_complex ctanl(long_double_complex z);
long_double_complex cacoshl(long_double_complex z);
long_double_complex casinhl(long_double_complex z);
long_double_complex catanhl(long_double_complex z);
long_double_complex ccoshl(long_double_complex z);
long_double_complex csinhl(long_double_complex z);
long_double_complex ctanhl(long_double_complex z);
long_double_complex cexpl(long_double_complex z);
long_double_complex clogl(long_double_complex z);
long_double_complex cpowl(long_double_complex z, long_double_complex w);
long_double_complex csqrtl(long_double_complex z);
long_double_complex cprojl(long_double_complex z);

#ifdef __cplusplus
    }
#endif

#endif /* _COMPLEX_H */