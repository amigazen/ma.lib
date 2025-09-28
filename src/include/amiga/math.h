/*
 * amiga/math.h - AmigaOS math library integration for ma.lib
 * 
 * Copyright (c) 2025 amigazen project
 * All rights reserved.
 * 
 * This header provides integration with Amiga native math libraries
 * for optimal performance on Amiga hardware.
 */

#ifndef _AMIGA_MATH_H
#define _AMIGA_MATH_H

/* Include AmigaOS math library headers */
/* #include <libraries/mathffp.h> */
/* #include <libraries/mathieeesp.h> */
/* #include <libraries/mathieeedp.h> */
#include <libraries/mathlibrary.h>

#include <proto/mathffp.h>
#include <proto/mathieeesingbas.h>
#include <proto/mathieeedoubbas.h>
#include <proto/mathieeesingtrans.h>
#include <proto/mathieeedoubtrans.h>
#include <proto/mathtrans.h>

/* Include complex number types */
#include <complex.h>

/* Math library initialization/cleanup */
int amiga_math_init(void);
void amiga_math_cleanup(void);

/* Math library selection */
typedef enum {
    M99_MATH_FFP,      /* Fast Floating Point */
    M99_MATH_IEEE,     /* IEEE 754 */
    M99_MATH_TRANS,    /* Transcendental */
    M99_MATH_AUTO      /* Auto-detect best available */
} m99_math_type_t;

/* Set math library type */
void m99_set_math_type(m99_math_type_t type);
m99_math_type_t m99_get_math_type(void);

/* Check if specific math library is available */
int m99_has_ffp(void);
int m99_has_ieee(void);
int m99_has_trans(void);

/* Performance optimization flags */
#define M99_OPT_FPU        0x01    /* Use FPU when available */
#define M99_OPT_FFP        0x02    /* Use FFP for speed */
#define M99_OPT_IEEE       0x04    /* Use IEEE for precision */
#define M99_OPT_TRANS      0x08    /* Use transcendental lib */

/* Set optimization flags */
void m99_set_optimization(int flags);
int m99_get_optimization(void);

/* Error handling */
typedef enum {
    M99_ERR_NONE = 0,
    M99_ERR_LIB_OPEN,
    M99_ERR_LIB_CLOSE,
    M99_ERR_INVALID_ARG,
    M99_ERR_OVERFLOW,
    M99_ERR_UNDERFLOW,
    M99_ERR_DOMAIN,
    M99_ERR_RANGE
} m99_math_error_t;

/* Get last error */
m99_math_error_t m99_get_error(void);
const char *m99_get_error_string(m99_math_error_t error);

/* Clear error state */
void m99_clear_error(void);

/* Math function wrappers that use AmigaOS libraries */
double amiga_acos(double x);
double amiga_asin(double x);
double amiga_atan(double x);
double amiga_atan2(double y, double x);
double amiga_cos(double x);
double amiga_sin(double x);
double amiga_tan(double x);
double amiga_cosh(double x);
double amiga_sinh(double x);
double amiga_tanh(double x);
double amiga_exp(double x);
double amiga_log(double x);
double amiga_log10(double x);
double amiga_pow(double x, double y);
double amiga_sqrt(double x);
double amiga_ceil(double x);
double amiga_floor(double x);
double amiga_fabs(double x);
double amiga_fmod(double x, double y);

/* Transcendental functions */
double amiga_acosh(double x);
double amiga_asinh(double x);
double amiga_atanh(double x);
double amiga_cbrt(double x);
double amiga_hypot(double x, double y);
double amiga_erf(double x);
double amiga_erfc(double x);
double amiga_tgamma(double x);
double amiga_lgamma(double x);
double amiga_j0(double x);
double amiga_j1(double x);
double amiga_jn(int n, double x);
double amiga_y0(double x);
double amiga_y1(double x);
double amiga_yn(int n, double x);

/* Complex number functions using AmigaOS libraries */
/* Note: These functions are commented out as they use unsupported complex syntax */
/* Users should use the standard complex functions from complex.h instead */
/*
double amiga_cabs(complex_double z);
double amiga_carg(complex_double z);
double amiga_creal(complex_double z);
double amiga_cimag(complex_double z);
complex_double amiga_conj(complex_double z);
complex_double amiga_cexp(complex_double z);
complex_double amiga_clog(complex_double z);
complex_double amiga_cpow(complex_double z, complex_double c);
complex_double amiga_csqrt(complex_double z);
*/

#endif /* _AMIGA_MATH_H */
