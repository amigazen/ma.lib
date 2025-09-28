/*
 * m99 Math Library - rint function
 * 
 * C99/POSIX rint function for m99.lib
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
double rint(double num)
{
    double ipart;
    int ival;
    double frac;

    frac = modf(num, &ipart);

    ival = ipart;
    if ((frac > 0.5) || ((frac == 0.5) && (ival % 2))) {
        ival++;
    }

    return (double)ival;
}
