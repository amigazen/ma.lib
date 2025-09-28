/*
 * ma.lib Math Library Error Handler
 * 
 * Provides error handling for ma.lib math functions.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/*
 * Default math error handler
 * 
 * Returns 0 to use default error handling,
 * non-zero to suppress default error handling
 */
int matherr(struct exception *e)
{
    /* Default behavior - let the system handle errors */
    return 0;
}
