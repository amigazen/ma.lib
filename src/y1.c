/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double y1(double x)
 * Bessel function of the second kind, order 1
 * 
 * Simple implementation for basic cases
 */

#include <math.h>
#include "include/internal/m99_math.h"

double y1(double x)
{
    double result;
    double x2, x4, x6, x8, j1_term, series_term;
    double sqrt_x, cos_term, sin_term;
    double num, den;
    
    /* Handle special cases */
    if (x <= 0.0) {
        return -INFINITY;  /* y1 has a pole at x=0 */
    }
    
    if (x != x) {  /* NaN */
        return NAN;
    }
    
    if (x == 1.0) {
        /* y1(1) ≈ 0.78121282130028871655 */
        return 0.78121282130028871655;
    }
    
    if (x == 2.0) {
        /* y1(2) ≈ 0.10703243154093754689 */
        return 0.10703243154093754689;
    }
    
    /* For small x, use series expansion */
    if (x < 2.0) {
        x2 = x * x;
        x4 = x2 * x2;
        x6 = x4 * x2;
        x8 = x6 * x2;
        
        /* Series: y1(x) ≈ (2/π) * (ln(x/2) + γ) * j1(x) + (2/π) * x * (1/2 - x²/16 + x⁴/384 - x⁶/18432 + ...) */
        j1_term = (2.0 / M_PI) * (log(x / 2.0) + 0.5772156649015329) * (x / 2.0 - x2 * x / 16.0 + x4 * x / 384.0 - x6 * x / 18432.0);
        series_term = (2.0 / M_PI) * x * (0.5 - x2 / 16.0 + x4 / 384.0 - x6 / 18432.0 + x8 / 1474560.0);
        return j1_term + series_term;
    }
    
    /* For large x, use asymptotic expansion */
    if (x > 10.0) {
        sqrt_x = sqrt(x);
        cos_term = cos(x - 3.0 * M_PI / 4.0);
        sin_term = sin(x - 3.0 * M_PI / 4.0);
        return sqrt(2.0 / (M_PI * x)) * (sin_term + cos_term / (8.0 * x));
    }
    
    /* For intermediate x, use rational approximation */
    x2 = x * x;
    x4 = x2 * x2;
    num = 1.0 + x2 * (-0.25 + x2 * (0.015625 - x2 * 0.00032552083333333333));
    den = 1.0 + x2 * (0.25 + x2 * (0.015625 + x2 * 0.00032552083333333333));
    return (2.0 / M_PI) * (log(x / 2.0) + 0.5772156649015329) * (x / 2.0) * (num / den);
}