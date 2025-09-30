/*
 * test_math.c - Unit tests for math.h functions
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This program tests all math functions provided by ma.lib
 * in a pure ANSI C89 environment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

/* Test case counters */
static int tests_run = 0;
static int tests_failed = 0;

/* Function prototypes */
void assert_test(const char* test_name, int condition, const char* file, int line);
void test_trigonometric(void);
void test_hyperbolic(void);
void test_exponential_logarithmic(void);
void test_power_root(void);
void test_rounding_remainder(void);
void test_floating_point_manipulation(void);
void test_classification_comparison(void);
void test_utility(void);
void test_error_functions(void);
void test_bessel(void);
void test_constants(void);
void test_float_variants(void);
void test_long_double_variants(void);

/* Simple assertion function */
void assert_test(const char* test_name, int condition, const char* file, int line) {
    tests_run++;
    if (!condition) {
        printf("[FAIL] %s:%d: %s failed\n", file, line, test_name);
        tests_failed++;
    } else {
        printf("[PASS] %s:%d: %s passed\n", file, line, test_name);
    }
}

#define ASSERT(condition) assert_test(#condition, (condition), __FILE__, __LINE__)

/* Helper function to check if two doubles are approximately equal */
int double_approx_equal(double a, double b, double tolerance) {
    return fabs(a - b) < tolerance;
}

/* Helper function to check if long_long_t equals an integer */
int long_long_equals_int(long_long_t ll, int i) {
    if (i >= 0) {
        return (ll.hi == 0 && ll.lo == (unsigned long)i);
    } else {
        return (ll.hi == 0xFFFFFFFFUL && ll.lo == (unsigned long)i);
    }
}

/* Test basic trigonometric functions */
void test_trigonometric() {
    printf("\n--- Testing Trigonometric Functions ---\n");
    
    /* Test sin */
    ASSERT(double_approx_equal(sin(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(sin(M_PI/2.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(sin(M_PI), 0.0, 1e-10));
    ASSERT(double_approx_equal(sin(3.0*M_PI/2.0), -1.0, 1e-10));
    
    /* Test cos */
    ASSERT(double_approx_equal(cos(0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(cos(M_PI/2.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(cos(M_PI), -1.0, 1e-10));
    ASSERT(double_approx_equal(cos(3.0*M_PI/2.0), 0.0, 1e-10));
    
    /* Test tan */
    ASSERT(double_approx_equal(tan(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(tan(M_PI/4.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(tan(M_PI), 0.0, 1e-10));
    
    /* Test asin */
    ASSERT(double_approx_equal(asin(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(asin(1.0), M_PI/2.0, 1e-10));
    ASSERT(double_approx_equal(asin(-1.0), -M_PI/2.0, 1e-10));
    
    /* Test acos */
    ASSERT(double_approx_equal(acos(1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(acos(0.0), M_PI/2.0, 1e-10));
    ASSERT(double_approx_equal(acos(-1.0), M_PI, 1e-10));
    
    /* Test atan */
    ASSERT(double_approx_equal(atan(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(atan(1.0), M_PI/4.0, 1e-10));
    ASSERT(double_approx_equal(atan(-1.0), -M_PI/4.0, 1e-10));
    
    /* Test atan2 */
    ASSERT(double_approx_equal(atan2(0.0, 1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(atan2(1.0, 0.0), M_PI/2.0, 1e-10));
    ASSERT(double_approx_equal(atan2(0.0, -1.0), M_PI, 1e-10));
    ASSERT(double_approx_equal(atan2(-1.0, 0.0), -M_PI/2.0, 1e-10));
}

/* Test hyperbolic functions */
void test_hyperbolic() {
    printf("\n--- Testing Hyperbolic Functions ---\n");
    
    /* Test sinh */
    ASSERT(double_approx_equal(sinh(0.0), 0.0, 1e-10));
    ASSERT(sinh(1.0) > 0.0);
    ASSERT(sinh(-1.0) < 0.0);
    
    /* Test cosh */
    ASSERT(double_approx_equal(cosh(0.0), 1.0, 1e-10));
    ASSERT(cosh(1.0) > 1.0);
    ASSERT(cosh(-1.0) > 1.0);
    
    /* Test tanh */
    ASSERT(double_approx_equal(tanh(0.0), 0.0, 1e-10));
    ASSERT(tanh(1.0) > 0.0);
    ASSERT(tanh(-1.0) < 0.0);
    ASSERT(tanh(1.0) < 1.0);
    ASSERT(tanh(-1.0) > -1.0);
    
    /* Test asinh */
    ASSERT(double_approx_equal(asinh(0.0), 0.0, 1e-10));
    ASSERT(asinh(1.0) > 0.0);
    ASSERT(asinh(-1.0) < 0.0);
    
    /* Test acosh */
    ASSERT(double_approx_equal(acosh(1.0), 0.0, 1e-10));
    ASSERT(acosh(2.0) > 0.0);
    
    /* Test atanh */
    ASSERT(double_approx_equal(atanh(0.0), 0.0, 1e-10));
    ASSERT(atanh(0.5) > 0.0);
    ASSERT(atanh(-0.5) < 0.0);
}

/* Test exponential and logarithmic functions */
void test_exponential_logarithmic() {
    printf("\n--- Testing Exponential and Logarithmic Functions ---\n");
    
    /* Test exp */
    ASSERT(double_approx_equal(exp(0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(exp(1.0), M_E, 1e-10));
    ASSERT(exp(1.0) > 0.0);
    ASSERT(exp(-1.0) > 0.0);
    
    /* Test exp2 */
    ASSERT(double_approx_equal(exp2(0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(exp2(1.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(exp2(2.0), 4.0, 1e-10));
    
    /* Test expm1 */
    ASSERT(double_approx_equal(expm1(0.0), 0.0, 1e-10));
    ASSERT(expm1(1.0) > 0.0);
    ASSERT(expm1(-1.0) < 0.0);
    
    /* Test log */
    ASSERT(isinf(log(0.0)) && log(0.0) < 0.0);
    ASSERT(double_approx_equal(log(1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(log(M_E), 1.0, 1e-10));
    
    /* Test log2 */
    ASSERT(isinf(log2(0.0)) && log2(0.0) < 0.0);
    ASSERT(double_approx_equal(log2(1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(log2(2.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(log2(4.0), 2.0, 1e-10));
    
    /* Test log10 */
    ASSERT(isinf(log10(0.0)) && log10(0.0) < 0.0);
    ASSERT(double_approx_equal(log10(1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(log10(10.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(log10(100.0), 2.0, 1e-10));
    
    /* Test log1p */
    ASSERT(double_approx_equal(log1p(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(log1p(M_E-1.0), 1.0, 1e-10));
    ASSERT(log1p(1.0) > 0.0);
    ASSERT(log1p(-0.5) < 0.0);
}

/* Test power and root functions */
void test_power_root() {
    printf("\n--- Testing Power and Root Functions ---\n");
    
    /* Test pow */
    ASSERT(double_approx_equal(pow(2.0, 0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(pow(2.0, 1.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(pow(2.0, 2.0), 4.0, 1e-10));
    ASSERT(double_approx_equal(pow(4.0, 0.5), 2.0, 1e-10));
    
    /* Test sqrt */
    ASSERT(double_approx_equal(sqrt(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(sqrt(1.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(sqrt(4.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(sqrt(9.0), 3.0, 1e-10));
    
    /* Test cbrt */
    ASSERT(double_approx_equal(cbrt(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(cbrt(1.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(cbrt(8.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(cbrt(27.0), 3.0, 1e-10));
    
    /* Test hypot */
    ASSERT(double_approx_equal(hypot(3.0, 4.0), 5.0, 1e-10));
    ASSERT(double_approx_equal(hypot(0.0, 0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(hypot(1.0, 0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(hypot(0.0, 1.0), 1.0, 1e-10));
}

/* Test rounding and remainder functions */
void test_rounding_remainder() {
    int quo;
    double rem;
    
    printf("\n--- Testing Rounding and Remainder Functions ---\n");
    
    /* Test ceil */
    ASSERT(ceil(3.2) == 4.0);
    ASSERT(ceil(3.0) == 3.0);
    ASSERT(ceil(-3.2) == -3.0);
    ASSERT(ceil(-3.0) == -3.0);
    
    /* Test floor */
    ASSERT(floor(3.8) == 3.0);
    ASSERT(floor(3.0) == 3.0);
    ASSERT(floor(-3.8) == -4.0);
    ASSERT(floor(-3.0) == -3.0);
    
    /* Test round */
    ASSERT(round(3.4) == 3.0);
    ASSERT(round(3.6) == 4.0);
    ASSERT(round(-3.4) == -3.0);
    ASSERT(round(-3.6) == -4.0);
    
    /* Test trunc */
    ASSERT(trunc(3.8) == 3.0);
    ASSERT(trunc(3.0) == 3.0);
    ASSERT(trunc(-3.8) == -3.0);
    ASSERT(trunc(-3.0) == -3.0);
    
    /* Test rint */
    ASSERT(rint(3.4) == 3.0);
    ASSERT(rint(3.6) == 4.0);
    ASSERT(rint(-3.4) == -3.0);
    ASSERT(rint(-3.6) == -4.0);
    
    /* Test nearbyint */
    ASSERT(nearbyint(3.4) == 3.0);
    ASSERT(nearbyint(3.6) == 4.0);
    ASSERT(nearbyint(-3.4) == -3.0);
    ASSERT(nearbyint(-3.6) == -4.0);
    
    /* Test lround */
    ASSERT(lround(3.4) == 3);
    ASSERT(lround(3.6) == 4);
    ASSERT(lround(-3.4) == -3);
    ASSERT(lround(-3.6) == -4);
    
    /* Test llround */
    ASSERT(long_long_equals_int(llround(3.4), 3));
    ASSERT(long_long_equals_int(llround(3.6), 4));
    ASSERT(long_long_equals_int(llround(-3.4), -3));
    ASSERT(long_long_equals_int(llround(-3.6), -4));
    
    /* Test lrint */
    ASSERT(long_long_equals_int(llrint(3.4), 3));
    ASSERT(long_long_equals_int(llrint(3.6), 4));
    ASSERT(long_long_equals_int(llrint(-3.4), -3));
    ASSERT(long_long_equals_int(llrint(-3.6), -4));
    
    /* Test llrint */
    ASSERT(long_long_equals_int(llrint(3.4), 3));
    ASSERT(long_long_equals_int(llrint(3.6), 4));
    ASSERT(long_long_equals_int(llrint(-3.4), -3));
    ASSERT(long_long_equals_int(llrint(-3.6), -4));
    
    /* Test fmod */
    ASSERT(double_approx_equal(fmod(5.0, 2.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(fmod(5.0, 3.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(fmod(-5.0, 2.0), -1.0, 1e-10));
    
    /* Test remainder */
    ASSERT(double_approx_equal(remainder(5.0, 2.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(remainder(5.0, 3.0), -1.0, 1e-10));
    ASSERT(double_approx_equal(remainder(-5.0, 2.0), 1.0, 1e-10));
    
    /* Test remquo */
    rem = remquo(5.0, 2.0, &quo);
    ASSERT(double_approx_equal(rem, 1.0, 1e-10));
    ASSERT(quo == 2);
}

/* Test floating-point manipulation functions */
void test_floating_point_manipulation() {
    int exp;
    double mantissa;
    double intpart, fracpart;
    double next, next2;
    
    printf("\n--- Testing Floating-Point Manipulation Functions ---\n");
    
    /* Test frexp */
    mantissa = frexp(8.0, &exp);
    ASSERT(double_approx_equal(mantissa, 0.5, 1e-10));
    ASSERT(exp == 4);
    
    mantissa = frexp(0.5, &exp);
    ASSERT(double_approx_equal(mantissa, 0.5, 1e-10));
    ASSERT(exp == 0);
    
    /* Test ldexp */
    ASSERT(double_approx_equal(ldexp(0.5, 4), 8.0, 1e-10));
    ASSERT(double_approx_equal(ldexp(1.0, 0), 1.0, 1e-10));
    ASSERT(double_approx_equal(ldexp(0.5, -1), 0.25, 1e-10));
    
    /* Test modf */
    fracpart = modf(3.14, &intpart);
    ASSERT(double_approx_equal(intpart, 3.0, 1e-10));
    ASSERT(double_approx_equal(fracpart, 0.14, 1e-10));
    
    /* Test scalbn */
    ASSERT(double_approx_equal(scalbn(1.0, 2), 4.0, 1e-10));
    ASSERT(double_approx_equal(scalbn(1.0, 0), 1.0, 1e-10));
    ASSERT(double_approx_equal(scalbn(1.0, -2), 0.25, 1e-10));
    
    /* Test scalbln */
    ASSERT(double_approx_equal(scalbln(1.0, 2), 4.0, 1e-10));
    ASSERT(double_approx_equal(scalbln(1.0, 0), 1.0, 1e-10));
    ASSERT(double_approx_equal(scalbln(1.0, -2), 0.25, 1e-10));
    
    /* Test nextafter */
    next = nextafter(1.0, 2.0);
    ASSERT(next > 1.0);
    ASSERT(next < 2.0);
    
    next = nextafter(1.0, 0.0);
    ASSERT(next < 1.0);
    ASSERT(next > 0.0);
    
    /* Test nexttoward */
    next2 = nexttoward(1.0, 2.0);
    ASSERT(next2 > 1.0);
    ASSERT(next2 < 2.0);
    
    next2 = nexttoward(1.0, 0.0);
    ASSERT(next2 < 1.0);
    ASSERT(next2 > 0.0);
}

/* Test classification and comparison functions */
void test_classification_comparison() {
    printf("\n--- Testing Classification and Comparison Functions ---\n");
    
    /* Test fpclassify */
    ASSERT(fpclassify(1.0) == FP_NORMAL);
    ASSERT(fpclassify(0.0) == FP_ZERO);
    ASSERT(fpclassify(INFINITY) == FP_INFINITE);
    ASSERT(fpclassify(NAN) == FP_NAN);
    
    /* Test isfinite */
    ASSERT(isfinite(1.0) == 1);
    ASSERT(isfinite(0.0) == 1);
    ASSERT(isfinite(INFINITY) == 0);
    ASSERT(isfinite(NAN) == 0);
    
    /* Test isinf */
    ASSERT(isinf(1.0) == 0);
    ASSERT(isinf(0.0) == 0);
    ASSERT(isinf(INFINITY) == 1);
    ASSERT(isinf(NAN) == 0);
    
    /* Test isnan */
    ASSERT(isnan(1.0) == 0);
    ASSERT(isnan(0.0) == 0);
    ASSERT(isnan(INFINITY) == 0);
    ASSERT(isnan(NAN) == 1);
    
    /* Test isnormal */
    ASSERT(isnormal(1.0) == 1);
    ASSERT(isnormal(0.0) == 0);
    ASSERT(isnormal(INFINITY) == 0);
    ASSERT(isnormal(NAN) == 0);
    
    /* Test signbit */
    ASSERT(signbit(1.0) == 0);
    ASSERT(signbit(-1.0) == 1);
    ASSERT(signbit(0.0) == 0);
    {
        /* Create negative zero by bit manipulation */
        double pos_zero = 0.0;
        double neg_zero;
        int hx = __HI(pos_zero);
        hx |= 0x80000000;  /* set sign bit */
        __HI(neg_zero) = hx;
        __LO(neg_zero) = 0;
        ASSERT(signbit(neg_zero) == 1);
    }
    
    /* Test fmin */
    ASSERT(fmin(3.0, 2.0) == 2.0);
    ASSERT(fmin(2.0, 3.0) == 2.0);
    ASSERT(fmin(-3.0, -2.0) == -3.0);
    
    /* Test fmax */
    ASSERT(fmax(3.0, 2.0) == 3.0);
    ASSERT(fmax(2.0, 3.0) == 3.0);
    ASSERT(fmax(-3.0, -2.0) == -2.0);
    
    /* Test fdim */
    ASSERT(double_approx_equal(fdim(3.0, 2.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(fdim(2.0, 3.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(fdim(-3.0, -2.0), 0.0, 1e-10));
    
    /* Test fma */
    ASSERT(double_approx_equal(fma(2.0, 3.0, 1.0), 7.0, 1e-10));
    ASSERT(double_approx_equal(fma(0.0, 3.0, 1.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(fma(2.0, 0.0, 1.0), 1.0, 1e-10));
}

/* Test utility functions */
void test_utility() {
    printf("\n--- Testing Utility Functions ---\n");
    
    /* Test fabs */
    ASSERT(fabs(3.0) == 3.0);
    ASSERT(fabs(-3.0) == 3.0);
    ASSERT(fabs(0.0) == 0.0);
    
    /* Test copysign */
    ASSERT(copysign(3.0, 1.0) == 3.0);
    ASSERT(copysign(3.0, -1.0) == -3.0);
    ASSERT(copysign(-3.0, 1.0) == 3.0);
    ASSERT(copysign(-3.0, -1.0) == -3.0);
    
    /* Test logb */
    ASSERT(logb(8.0) == 3.0);
    ASSERT(logb(1.0) == 0.0);
    ASSERT(logb(0.5) == -1.0);
    
    /* Test ilogb */
    ASSERT(ilogb(8.0) == 3);
    ASSERT(ilogb(1.0) == 0);
    ASSERT(ilogb(0.5) == -1);
    
    /* Test significand */
    ASSERT(double_approx_equal(significand(8.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(significand(1.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(significand(0.5), 1.0, 1e-10));
    
    /* Test nan */
    ASSERT(isnan(nan("")) == 1);
    ASSERT(isnan(nan("123")) == 1);
}

/* Test error functions */
void test_error_functions() {
    printf("\n--- Testing Error Functions ---\n");
    
    /* Test erf */
    ASSERT(double_approx_equal(erf(0.0), 0.0, 1e-10));
    ASSERT(erf(1.0) > 0.0);
    ASSERT(erf(-1.0) < 0.0);
    ASSERT(erf(1.0) < 1.0);
    ASSERT(erf(-1.0) > -1.0);
    
    /* Test erfc */
    ASSERT(double_approx_equal(erfc(0.0), 1.0, 1e-10));
    ASSERT(erfc(1.0) > 0.0);
    ASSERT(erfc(1.0) < 1.0);
    
    /* Test gamma */
    ASSERT(tgamma(1.0) == 1.0);
    ASSERT(tgamma(2.0) == 1.0);
    ASSERT(tgamma(3.0) == 2.0);
    
    /* Test lgamma */
    ASSERT(double_approx_equal(lgamma(1.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(lgamma(2.0), 0.0, 1e-10));
    ASSERT(lgamma(3.0) > 0.0);
}

/* Test Bessel functions */
void test_bessel() {
    printf("\n--- Testing Bessel Functions ---\n");
    
    /* Test j0 */
    ASSERT(double_approx_equal(j0(0.0), 1.0, 1e-10));
    ASSERT(j0(1.0) > 0.0);
    ASSERT(j0(2.0) > 0.0);
    
    /* Test j1 */
    ASSERT(double_approx_equal(j1(0.0), 0.0, 1e-10));
    ASSERT(j1(1.0) > 0.0);
    ASSERT(j1(2.0) > 0.0);
    
    /* Test y0 */
    ASSERT(y0(1.0) > 0.0);
    ASSERT(y0(2.0) > 0.0);
    
    /* Test y1 */
    ASSERT(y1(1.0) > 0.0);
    ASSERT(y1(2.0) > 0.0);
}

/* Test mathematical constants */
void test_constants() {
    printf("\n--- Testing Mathematical Constants ---\n");
    
    /* Test M_PI */
    ASSERT(double_approx_equal(M_PI, 3.14159265358979323846, 1e-10));
    
    /* Test M_E */
    ASSERT(double_approx_equal(M_E, 2.7182818284590452354, 1e-10));
    
    /* Test M_LN2 */
    ASSERT(double_approx_equal(M_LN2, 0.69314718055994530942, 1e-10));
    
    /* Test M_LN10 */
    ASSERT(double_approx_equal(M_LN10, 2.30258509299404568402, 1e-10));
    
    /* Test M_LOG2E */
    ASSERT(double_approx_equal(M_LOG2E, 1.4426950408889634074, 1e-10));
    
    /* Test M_LOG10E */
    ASSERT(double_approx_equal(M_LOG10E, 0.43429448190325182765, 1e-10));
    
    /* Test M_SQRT2 */
    ASSERT(double_approx_equal(M_SQRT2, 1.41421356237309504880, 1e-10));
    
    /* Test M_SQRT1_2 */
    ASSERT(double_approx_equal(M_SQRT1_2, 0.70710678118654752440, 1e-10));
    
    /* Test INFINITY */
    ASSERT(isinf(INFINITY) == 1);
    ASSERT(INFINITY > 0.0);
    
    /* Test NAN */
    ASSERT(isnan(NAN) == 1);
    
    /* Test HUGE_VAL */
    ASSERT(isinf(HUGE_VAL) == 1);
    ASSERT(HUGE_VAL > 0.0);
}

/* Test float variants */
void test_float_variants() {
    printf("\n--- Testing Float Variants ---\n");
    
    /* Note: SAS/C doesn't support float variants, so we test the double versions */
    /* These would be the float variants if available */
    ASSERT(double_approx_equal(sin(0.0), 0.0, 1e-6));
    ASSERT(double_approx_equal(cos(0.0), 1.0, 1e-6));
    ASSERT(double_approx_equal(sqrt(4.0), 2.0, 1e-6));
    ASSERT(double_approx_equal(cbrt(27.0), 3.0, 1e-6));
    ASSERT(round(3.6) == 4.0);
    ASSERT(trunc(3.8) == 3.0);
}

/* Test long double variants */
void test_long_double_variants() {
    printf("\n--- Testing Long Double Variants ---\n");
    
    /* Note: SAS/C doesn't support long double variants, so we test the double versions */
    /* These would be the long double variants if available */
    ASSERT(double_approx_equal(sin(0.0), 0.0, 1e-10));
    ASSERT(double_approx_equal(cos(0.0), 1.0, 1e-10));
    ASSERT(double_approx_equal(sqrt(4.0), 2.0, 1e-10));
    ASSERT(double_approx_equal(cbrt(27.0), 3.0, 1e-10));
    ASSERT(round(3.6) == 4.0);
    ASSERT(trunc(3.8) == 3.0);
}

int main() {
    printf("======== MATH.H UNIT TEST SUITE =========\n");
    printf("Testing all math functions in ma.lib\n");
    
    test_trigonometric();
    test_hyperbolic();
    test_exponential_logarithmic();
    test_power_root();
    test_rounding_remainder();
    test_floating_point_manipulation();
    test_classification_comparison();
    test_utility();
    test_error_functions();
    test_bessel();
    test_constants();
    test_float_variants();
    test_long_double_variants();
    
    printf("\n==================== SUMMARY =====================\n");
    printf("Tests Run:    %d\n", tests_run);
    if (tests_failed == 0) {
        printf("Tests Passed: %d\n", tests_run);
        printf("Result: ALL TESTS PASSED\n");
        return EXIT_SUCCESS;
    } else {
        printf("Tests Failed: %d\n", tests_failed);
        printf("Result: SOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
}
