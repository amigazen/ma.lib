/*
 * Internal Complex Number Operations for SAS/C C++ Implementation
 * 
 * This header contains internal complex number operations and includes
 * SAS/C's C++ complex class support. It should only be included in
 * .cpp files that implement the C99 complex API.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _INTERNAL_COMPLEX_H
#define _INTERNAL_COMPLEX_H

/* Prevent iostream from being included - we don't need it for math library */
#define __IOSTREAM_H

/* Provide minimal iostream declarations needed by complex class */
#ifdef __cplusplus
class ostream;
class istream;
#endif

/* Define SAS/C specific macros needed for complex class */
#define _INLINE_FUNC(x) x

/* Include math.h for standard math functions */
#include <math.h>

/* Include our math constants header */
#include "m99_math.h"

/* Include SAS/C's C++ complex class support */
#ifdef __cplusplus
#include "cxxinclude:complex.h"
#else
#error This header should only be included in C++ files
#endif

/* Include the public complex.h for type definitions after C++ complex class */
#include <complex.h>

/*========================================================================*
 *                    INTERNAL COMPLEX IMPLEMENTATION TYPES
 *========================================================================*/

/* 
 * We use the same types as the public API but with internal naming
 * for clarity in implementation files
 */
typedef double_complex complex_double_t;
typedef float_complex complex_float_t;
typedef long_double_complex complex_long_double_t;

/*========================================================================*
 *                    INTERNAL COMPLEX IMPLEMENTATION FUNCTIONS
 *========================================================================*/

/* 
 * These are the internal implementation functions that wrap
 * SAS/C's C++ complex class. They are used by the public API
 * functions in the .cpp files.
 */

/* Basic Operations - Internal */
double cabs_internal(complex_double_t z);
double carg_internal(complex_double_t z);
complex_double_t conj_internal(complex_double_t z);

/* Arithmetic Operations - Internal */
complex_double_t cadd_internal(complex_double_t a, complex_double_t b);
complex_double_t csub_internal(complex_double_t a, complex_double_t b);
complex_double_t cmul_internal(complex_double_t a, complex_double_t b);
complex_double_t cdiv_internal(complex_double_t a, complex_double_t b);

/* Trigonometric Functions - Internal */
complex_double_t cacos_internal(complex_double_t z);
complex_double_t casin_internal(complex_double_t z);
complex_double_t catan_internal(complex_double_t z);
complex_double_t ccos_internal(complex_double_t z);
complex_double_t csin_internal(complex_double_t z);
complex_double_t ctan_internal(complex_double_t z);

/* Hyperbolic Functions - Internal */
complex_double_t cacosh_internal(complex_double_t z);
complex_double_t casinh_internal(complex_double_t z);
complex_double_t catanh_internal(complex_double_t z);
complex_double_t ccosh_internal(complex_double_t z);
complex_double_t csinh_internal(complex_double_t z);
complex_double_t ctanh_internal(complex_double_t z);

/* Exponential and Logarithmic Functions - Internal */
complex_double_t cexp_internal(complex_double_t z);
complex_double_t clog_internal(complex_double_t z);
complex_double_t cpow_internal(complex_double_t z, complex_double_t w);
complex_double_t csqrt_internal(complex_double_t z);

/* Projection and Classification - Internal */
complex_double_t cproj_internal(complex_double_t z);

/*========================================================================*
 *                    LEGACY COMPLEX SUPPORT (Nicolas d'Alterio)
 *========================================================================*/

/* Original Complex library structure from Nicolas d'Alterio */
struct Complex {
    double Real;
    double Imag;
};

typedef struct Complex COMPLEX;

/* Legacy internal complex utility functions */
COMPLEX ComNeg(COMPLEX z);
COMPLEX ComScale(COMPLEX z, double scale);

#endif /* _INTERNAL_COMPLEX_H */