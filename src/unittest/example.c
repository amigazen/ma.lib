/*
 * example.c - Example program demonstrating m99.lib functions
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This program demonstrates the use of C99 and POSIX.1 math functions
 * provided by m99.lib.
 */

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <errno.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>


int main(void)
{
    double x, y, result;
    double complex z, w;
    
    printf("ma.lib Math Library Extensions Example\n");
    printf("=====================================\n\n");
    
    /* Initialize AmigaOS math libraries if available */
#ifdef __AMIGA__
    if (amiga_math_init()) {
        printf("Amiga math libraries initialized successfully\n");
        printf("Available libraries:\n");
        if (m99_has_ffp()) printf("  - mathffp.library\n");
        if (m99_has_ieee()) printf("  - mathieeedoubbas.library\n");
        if (m99_has_trans()) printf("  - mathtrans.library\n");
        printf("\n");
    } else {
        printf("Warning: Could not initialize Amiga math libraries\n");
        printf("Using standard implementations\n\n");
    }
#endif
    
    /* Test inverse hyperbolic functions */
    printf("Inverse Hyperbolic Functions:\n");
    printf("-----------------------------\n");
    
    x = 1.5;
    result = acosh(x);
    printf("acosh(%.1f) = %.6f\n", x, result);
    
    x = 0.5;
    result = asinh(x);
    printf("asinh(%.1f) = %.6f\n", x, result);
    
    x = 0.5;
    result = atanh(x);
    printf("atanh(%.1f) = %.6f\n", x, result);
    
    /* Test advanced exponential/logarithmic functions */
    printf("\nAdvanced Exponential/Logarithmic Functions:\n");
    printf("------------------------------------------\n");
    
    x = 0.001;
    result = expm1(x);
    printf("expm1(%.3f) = %.6f\n", x, result);
    
    x = 0.001;
    result = log1p(x);
    printf("log1p(%.3f) = %.6f\n", x, result);
    
    /* Test rounding and remainder functions */
    printf("\nRounding and Remainder Functions:\n");
    printf("--------------------------------\n");
    
    x = 3.7;
    result = rint(x);
    printf("rint(%.1f) = %.1f\n", x, result);
    
    x = 3.2;
    result = rint(x);
    printf("rint(%.1f) = %.1f\n", x, result);
    
    x = 10.0;
    y = 3.0;
    result = remainder(x, y);
    printf("remainder(%.1f, %.1f) = %.6f\n", x, y, result);
    
    /* Test power and root functions */
    printf("\nPower and Root Functions:\n");
    printf("------------------------\n");
    
    x = 27.0;
    result = cbrt(x);
    printf("cbrt(%.1f) = %.6f\n", x, result);
    
    x = 3.0;
    y = 4.0;
    result = hypot(x, y);
    printf("hypot(%.1f, %.1f) = %.6f\n", x, y, result);
    
    /* Test floating-point manipulation functions */
    printf("\nFloating-Point Manipulation Functions:\n");
    printf("------------------------------------\n");
    
    x = -3.14;
    y = 2.71;
    result = copysign(x, y);
    printf("copysign(%.2f, %.2f) = %.6f\n", x, y, result);
    
    x = 1.0;
    y = 2.0;
    result = nextafter(x, y);
    printf("nextafter(%.1f, %.1f) = %.6f\n", x, y, result);
    
    /* Test classification functions */
    printf("\nClassification Functions:\n");
    printf("------------------------\n");
    
    x = 1.0;
    printf("isfinite(%.1f) = %d\n", x, isfinite(x));
    printf("isnormal(%.1f) = %d\n", x, isnormal(x));
    printf("signbit(%.1f) = %d\n", x, signbit(x));
    
    x = INFINITY;
    printf("isfinite(INFINITY) = %d\n", isfinite(x));
    printf("isinf(INFINITY) = %d\n", isinf(x));
    
    x = NAN;
    printf("isnan(NAN) = %d\n", isnan(x));
    
    /* Test error functions */
    printf("\nError Functions:\n");
    printf("---------------\n");
    
    x = 1.0;
    result = erf(x);
    printf("erf(%.1f) = %.6f\n", x, result);
    
    x = 1.0;
    result = erfc(x);
    printf("erfc(%.1f) = %.6f\n", x, result);
    
    /* Test gamma functions */
    printf("\nGamma Functions:\n");
    printf("---------------\n");
    
    x = 2.0;
    result = tgamma(x);
    printf("tgamma(%.1f) = %.6f\n", x, result);
    
    x = 2.0;
    result = lgamma(x);
    printf("lgamma(%.1f) = %.6f\n", x, result);
    
    /* Test Bessel functions */
    printf("\nBessel Functions:\n");
    printf("----------------\n");
    
    x = 1.0;
    result = j0(x);
    printf("j0(%.1f) = %.6f\n", x, result);
    
    x = 1.0;
    result = j1(x);
    printf("j1(%.1f) = %.6f\n", x, result);
    
    x = 1.0;
    result = y0(x);
    printf("y0(%.1f) = %.6f\n", x, result);
    
    /* Test complex number functions */
    printf("\nComplex Number Functions:\n");
    printf("------------------------\n");
    
    z = 3.0 + 4.0*I;
    result = cabs(z);
    printf("cabs(%.1f+%.1fi) = %.6f\n", creal(z), cimag(z), result);
    
    z = 1.0 + 1.0*I;
    result = carg(z);
    printf("carg(%.1f+%.1fi) = %.6f\n", creal(z), cimag(z), result);
    
    z = 1.0 + 2.0*I;
    w = cexp(z);
    printf("cexp(%.1f+%.1fi) = %.6f+%.6fi\n", creal(z), cimag(z), creal(w), cimag(w));
    
    z = 1.0 + 1.0*I;
    w = csqrt(z);
    printf("csqrt(%.1f+%.1fi) = %.6f+%.6fi\n", creal(z), cimag(z), creal(w), cimag(w));
    
    /* Test IEEE 754 functions */
    printf("\nIEEE 754 Functions:\n");
    printf("------------------\n");
    
    x = 3.0;
    y = 2.0;
    result = fmin(x, y);
    printf("fmin(%.1f, %.1f) = %.6f\n", x, y, result);
    
    x = 3.0;
    y = 2.0;
    result = fmax(x, y);
    printf("fmax(%.1f, %.1f) = %.6f\n", x, y, result);
    
    x = 3.0;
    y = 2.0;
    result = fdim(x, y);
    printf("fdim(%.1f, %.1f) = %.6f\n", x, y, result);
    
    printf("\nExample program completed successfully!\n");
    
    /* Cleanup Amiga math libraries if initialized */
    amiga_math_cleanup();
    
    return 0;
}
