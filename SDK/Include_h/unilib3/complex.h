/*
 * POSIX Complex Number Support for SAS/C
 * 
 * This header provides POSIX-compliant complex number support by wrapping
 * SAS/C's existing C++ complex class implementation.
 * 
 * Uses SAS/C's class complex for implementation while providing
 * standard POSIX complex API for maximum compatibility.
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
 *                    POSIX COMPLEX NUMBER TYPES
 *========================================================================*/

/* 
 * POSIX complex number types - SAS/C compatible implementation
 * These map to SAS/C's C++ complex class internally
 */

/* Define the actual complex number structures for C89 compatibility */
typedef struct { double re, im; } complex_double;
typedef struct { float re, im; } complex_float;
typedef struct { long double re, im; } complex_long_double;

/* POSIX-compliant complex number type definitions */
/* Following Solaris/POSIX conventions */
typedef complex_double complex_t;
typedef complex_float float_complex_t;
typedef complex_long_double long_double_complex_t;

/* C99-compatible aliases for backward compatibility */
typedef complex_double double_complex;
typedef complex_float float_complex;
typedef complex_long_double long_double_complex;

/* POSIX-compatible type aliases */
/* Note: We can't use "double complex" syntax in C89, so we provide macros instead */
#define double_complex_t complex_double
#define float_complex_t complex_float
#define long_double_complex_t complex_long_double


/* POSIX complex number macros */
#ifndef _Complex_I
#define _Complex_I     {0.0, 1.0}
#endif

#ifndef I
#define I              _Complex_I
#endif

/* Note: We can't define 'complex' macro as it conflicts with C++ class complex */

/* Complex number literals for struct-based types */
#define CMPLXF(real, imag)  ((struct complex_float){real, imag})
#define CMPLX(real, imag)   ((struct complex_double){real, imag})
#define CMPLXL(real, imag)  ((struct complex_long_double){real, imag})

/* Helper macros for struct-based complex numbers */
/* Note: creal and cimag are implemented as functions, not macros */

/* C99-compatible complex number creation functions */
/* Note: These are implemented as macros for C89 compatibility */
#define cpack(r, i) ((complex_double){(r), (i)})
#define cpackf(r, i) ((complex_float){(r), (i)})
#define cpackl(r, i) ((complex_long_double){(r), (i)})

/*========================================================================*
 *                    POSIX COMPLEX NUMBER FUNCTIONS
 *========================================================================*/

/* Basic Operations */
double cabs(complex_t z);
double carg(complex_t z);
double creal(complex_t z);
double cimag(complex_t z);
complex_t conj(complex_t z);

/* Trigonometric Functions */
complex_t cacos(complex_t z);
complex_t casin(complex_t z);
complex_t catan(complex_t z);
complex_t ccos(complex_t z);
complex_t csin(complex_t z);
complex_t ctan(complex_t z);

/* Hyperbolic Functions */
complex_t cacosh(complex_t z);
complex_t casinh(complex_t z);
complex_t catanh(complex_t z);
complex_t ccosh(complex_t z);
complex_t csinh(complex_t z);
complex_t ctanh(complex_t z);

/* Exponential and Logarithmic Functions */
complex_t cexp(complex_t z);
#ifndef __cplusplus
complex_t clog(complex_t z);
#else
/* In C++, clog conflicts with iostream, so we use a different name */
complex_t clog_c99(complex_t z);
#define clog clog_c99
#endif
complex_t cpow(complex_t z, complex_t w);
complex_t csqrt(complex_t z);

/* Utility Functions */
double cmod(complex_t z);
complex_t cneg(complex_t z);
complex_t cscale(complex_t z, double scale);

/* Projection and Classification */
complex_t cproj(complex_t z);

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