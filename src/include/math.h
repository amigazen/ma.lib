/*
 * math.h - Extended math library for ma.lib
 * 
 * Copyright (c) 2025 amigazen project
 * All rights reserved.
 * 
 * This header extends the standard math.h with C99 and POSIX.1 functions
 * not provided by SAS/C's scm.lib.
 */

#ifndef _MA_MATH_H
#define _MA_MATH_H

/* Include standard math.h first */
#ifdef __SASC
#include "sc:include/math.h"
#else
#error Wrong compiler (SAS/C required)
#endif

/* Ensure we have the basic math constants */
#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif
#ifndef M_LOG2E
#define M_LOG2E        1.4426950408889634074   /* log 2e */
#endif
#ifndef M_LOG10E
#define M_LOG10E       0.43429448190325182765  /* log 10e */
#endif
#ifndef M_LN2
#define M_LN2          0.69314718055994530942  /* log e2 */
#endif
#ifndef M_LN10
#define M_LN10         2.30258509299404568402  /* log e10 */
#endif
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif
#ifndef M_PI_2
#define M_PI_2         1.57079632679489661923  /* pi/2 */
#endif
#ifndef M_PI_4
#define M_PI_4         0.78539816339744830962  /* pi/4 */
#endif
#ifndef M_1_PI
#define M_1_PI         0.31830988618379067154  /* 1/pi */
#endif
#ifndef M_2_PI
#define M_2_PI         0.63661977236758134308  /* 2/pi */
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) */
#endif
#ifndef M_SQRT2
#define M_SQRT2        1.41421356237309504880  /* sqrt(2) */
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */
#endif

/* C99 Math constants */
#ifndef INFINITY
#define INFINITY       (1.0/0.0)
#endif

#ifndef NAN
#define NAN            (0.0/0.0)
#endif

/* C99 Classification macros */
#ifndef FP_NAN
#define FP_NAN         0
#define FP_INFINITE    1
#define FP_ZERO        2
#define FP_SUBNORMAL   3
#define FP_NORMAL      4
#endif

/* C99 Classification functions */
#ifndef isfinite
#define isfinite(x)    ((x) == (x) && (x) != (x) / 0.0)
#endif

#ifndef isnormal
#define isnormal(x)    (isfinite(x) && (x) != 0.0)
#endif

#ifndef signbit
#define signbit(x)     ((x) < 0.0)
#endif

/* C99 Comparison macros */
#ifndef isgreater
#define isgreater(x, y)        ((x) > (y))
#endif

#ifndef isgreaterequal
#define isgreaterequal(x, y)   ((x) >= (y))
#endif

#ifndef isless
#define isless(x, y)           ((x) < (y))
#endif

#ifndef islessequal
#define islessequal(x, y)      ((x) <= (y))
#endif

#ifndef islessgreater
#define islessgreater(x, y)    ((x) < (y) || (x) > (y))
#endif

#ifndef isunordered
#define isunordered(x, y)      ((x) != (x) || (y) != (y))
#endif

/* C99 Function declarations - Inverse Hyperbolic */
double acosh(double x);
double asinh(double x);
double atanh(double x);

/* C99 Function declarations - Advanced Exponential/Logarithmic */
double expm1(double x);
double log1p(double x);

/* C99 Function declarations - Rounding and Remainder */
double rint(double x);
double remainder(double x, double y);
double remquo(double x, double y, int *quo);

/* C99 Function declarations - Power and Root */
double cbrt(double x);
double hypot(double x, double y);

/* C99 Function declarations - Floating-Point Manipulation */
double copysign(double x, double y);
double nextafter(double x, double y);
double scalbn(double x, int n);
double scalb(double x, double n);
double logb(double x);
int ilogb(double x);
double significand(double x);

/* C99 Function declarations - Classification */
int finite(double x);
int isnan(double x);
int isinf(double x);
int fpclassify(double x);

/* POSIX.1 Function declarations - Error Functions */
double erf(double x);
double erfc(double x);

/* POSIX.1 Function declarations - Gamma Functions */
double tgamma(double x);
double lgamma(double x);
double gamma_r(double x, int *signgamp);
double lgamma_r(double x, int *signgamp);

/* POSIX.1 Function declarations - Bessel Functions */
double j0(double x);
double j1(double x);
double jn(int n, double x);
double y0(double x);
double y1(double x);
double yn(int n, double x);

/* IEEE 754 Function declarations - Min/Max */
double fmin(double x, double y);
double fmax(double x, double y);
double fdim(double x, double y);
double fma(double x, double y, double z);

/* IEEE 754 Function declarations - NaN */
double nan(const char *tagp);
float nanf(const char *tagp);
long double nanl(const char *tagp);

/* Float variants (f suffix) */
float acoshf(float x);
float asinhf(float x);
float atanhf(float x);
float expm1f(float x);
float log1pf(float x);
float rintf(float x);
float remainderf(float x, float y);
float remquof(float x, float y, int *quo);
float cbrtf(float x);
float hypotf(float x, float y);
float copysignf(float x, float y);
float nextafterf(float x, float y);
float scalbnf(float x, int n);
float scalbf(float x, float n);
float logbf(float x);
int ilogbf(float x);
float significandf(float x);
int finitef(float x);
int isnanf(float x);
int isinff(float x);
int fpclassifyf(float x);
float erff(float x);
float erfcf(float x);
float tgammaf(float x);
float lgammaf(float x);
float gamma_rf(float x, int *signgamp);
float lgamma_rf(float x, int *signgamp);
float j0f(float x);
float j1f(float x);
float jnf(int n, float x);
float y0f(float x);
float y1f(float x);
float ynf(int n, float x);
float fminf(float x, float y);
float fmaxf(float x, float y);
float fdimf(float x, float y);
float fmaf(float x, float y, float z);

/* Long double variants (l suffix) */
long double acoshl(long double x);
long double asinhl(long double x);
long double atanhl(long double x);
long double expm1l(long double x);
long double log1pl(long double x);
long double rintl(long double x);
long double remainderl(long double x, long double y);
long double remquol(long double x, long double y, int *quo);
long double cbrtl(long double x);
long double hypotl(long double x, long double y);
long double copysignl(long double x, long double y);
long double nextafterl(long double x, long double y);
long double scalbnl(long double x, int n);
long double scalbl(long double x, long double n);
long double logbl(long double x);
int ilogbl(long double x);
long double significandl(long double x);
int finitel(long double x);
int isnanl(long double x);
int isinfl(long double x);
int fpclassifyl(long double x);
long double erfl(long double x);
long double erfcl(long double x);
long double tgammal(long double x);
long double lgammal(long double x);
long double gamma_rl(long double x, int *signgamp);
long double lgamma_rl(long double x, int *signgamp);
long double j0l(long double x);
long double j1l(long double x);
long double jnl(int n, long double x);
long double y0l(long double x);
long double y1l(long double x);
long double ynl(int n, long double x);
long double fminl(long double x, long double y);
long double fmaxl(long double x, long double y);
long double fdiml(long double x, long double y);
long double fmal(long double x, long double y, long double z);

/* Include complex.h for complex number functions */
#include <complex.h>

/* Amiga math library integration */
#include <amiga/math.h>

#endif /* _MA_MATH_H */
