/*
 * Complex Number Usage Example for ma.lib
 * 
 * This example demonstrates how to use the C99-compatible complex number
 * API provided by ma.lib, which wraps SAS/C's C++ complex class.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "include/internal/complex_internal.h"

int main(void)
{
    /* Create complex numbers using different methods */
    complex_t z1 = {3.0, 4.0};                    /* Direct struct initialization */
    complex_t z2 = cpack(1.0, 2.0);              /* Using cpack function */
    complex_t z3 = CMPLX(5.0, 6.0);              /* Using CMPLX macro */
    
    /* Access real and imaginary parts */
    printf("z1 = %.2f + %.2fi\n", creal(z1), cimag(z1));
    printf("z2 = %.2f + %.2fi\n", creal(z2), cimag(z2));
    printf("z3 = %.2f + %.2fi\n", creal(z3), cimag(z3));
    
    /* Basic operations */
    complex_t sum = cadd(z1, z2);
    complex_t product = cmul(z1, z2);
    complex_t conjugate = conj(z1);
    
    printf("\nOperations:\n");
    printf("z1 + z2 = %.2f + %.2fi\n", creal(sum), cimag(sum));
    printf("z1 * z2 = %.2f + %.2fi\n", creal(product), cimag(product));
    printf("conj(z1) = %.2f + %.2fi\n", creal(conjugate), cimag(conjugate));
    
    /* Mathematical functions */
    double magnitude = cabs(z1);
    double argument = carg(z1);
    complex_t exponential = cexp(z1);
    complex_t logarithm = clog(z1);
    complex_t square_root = csqrt(z1);
    
    printf("\nMathematical functions:\n");
    printf("|z1| = %.2f\n", magnitude);
    printf("arg(z1) = %.2f radians\n", argument);
    printf("exp(z1) = %.2f + %.2fi\n", creal(exponential), cimag(exponential));
    printf("log(z1) = %.2f + %.2fi\n", creal(logarithm), cimag(logarithm));
    printf("sqrt(z1) = %.2f + %.2fi\n", creal(square_root), cimag(square_root));
    
    /* Demonstrate that the API works with SAS/C's C++ complex class */
    printf("\nAll operations use SAS/C's optimized C++ complex class internally!\n");
    
    return 0;
}
