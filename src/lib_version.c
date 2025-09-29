/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_lib_version.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * lib_version - Library version information
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Define _IEEE_ constant if not already defined */
#ifndef _IEEE_
#define _IEEE_ 1
#endif

int _LIB_VERSION = _IEEE_;
