/*
 * ma.lib Math Library - rint function
 * 
 * C99/POSIX rint function for ma.lib
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>

/*
 * rint - round to nearest integer
 * 
 * Returns an integer rounded from a double. In case of fraction exactly
 * midway, round chooses nearest even value.
 */
double rint(double x)
{
    /* Simple implementation using floor and ceil */
    if (x >= 0.0) {
        double floor_x = floor(x);
        double frac = x - floor_x;
        if (frac < 0.5) {
            return floor_x;
        } else if (frac > 0.5) {
            return floor_x + 1.0;
        } else {
            /* Exactly 0.5 - round to even */
            if (fmod(floor_x, 2.0) == 0.0) {
                return floor_x;
            } else {
                return floor_x + 1.0;
            }
        }
    } else {
        double ceil_x = ceil(x);
        double frac = ceil_x - x;
        if (frac < 0.5) {
            return ceil_x;
        } else if (frac > 0.5) {
            return ceil_x - 1.0;
        } else {
            /* Exactly 0.5 - round to even */
            if (fmod(ceil_x, 2.0) == 0.0) {
                return ceil_x;
            } else {
                return ceil_x - 1.0;
            }
        }
    }
}
