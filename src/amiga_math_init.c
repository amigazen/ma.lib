/*
 * amiga_math_init.c - AmigaOS math library initialization
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file handles initialization and cleanup of AmigaOS math libraries
 * for optimal performance in ma.lib.
 */

#ifndef _AMIGA_MATH_INIT_C
#define _AMIGA_MATH_INIT_C

#include <exec/exec.h>
#include <dos/dos.h>
#include <libraries/mathffp.h>
#include <libraries/mathieeedp.h>
#include <libraries/mathieeesp.h>
#include <libraries/mathtrans.h>
#include <amiga/math.h>

/* Global state */
static m99_math_type_t current_math_type = M99_MATH_AUTO;
static int optimization_flags = M99_OPT_FPU | M99_OPT_IEEE;
static m99_math_error_t last_error = M99_ERR_NONE;

/*
 * amiga_math_init - Initialize AmigaOS math libraries
 * 
 * Returns 1 on success, 0 on failure.
 */
int amiga_math_init(void)
{
    /* Try to open mathffp.library */
    MathFFPBase = (struct MathFFPBase *)OpenLibrary("mathffp.library", 0);
    
    /* Try to open mathieeedoubbas.library */
    MathIEEEBase = (struct MathIEEEBase *)OpenLibrary("mathieeedoubbas.library", 0);
    
    /* Try to open mathtrans.library */
    MathTransBase = (struct MathTransBase *)OpenLibrary("mathtrans.library", 0);
    
    /* Check if we have at least one math library */
    if (!MathFFPBase && !MathIEEEBase && !MathTransBase) {
        last_error = M99_ERR_LIB_OPEN;
        return 0;
    }
    
    /* Auto-detect best math library if not specified */
    if (current_math_type == M99_MATH_AUTO) {
        if (MathTransBase) {
            current_math_type = M99_MATH_TRANS;
        } else if (MathIEEEBase) {
            current_math_type = M99_MATH_IEEE;
        } else if (MathFFPBase) {
            current_math_type = M99_MATH_FFP;
        }
    }
    
    last_error = M99_ERR_NONE;
    return 1;
}

/*
 * amiga_math_cleanup - Cleanup AmigaOS math libraries
 */
void amiga_math_cleanup(void)
{
    if (MathFFPBase) {
        CloseLibrary((struct Library *)MathFFPBase);
        MathFFPBase = NULL;
    }
    
    if (MathIEEEBase) {
        CloseLibrary((struct Library *)MathIEEEBase);
        MathIEEEBase = NULL;
    }
    
    if (MathTransBase) {
        CloseLibrary((struct Library *)MathTransBase);
        MathTransBase = NULL;
    }
}

/*
 * m99_set_math_type - Set math library type
 */
void m99_set_math_type(m99_math_type_t type)
{
    current_math_type = type;
}

/*
 * m99_get_math_type - Get current math library type
 */
m99_math_type_t m99_get_math_type(void)
{
    return current_math_type;
}

/*
 * m99_has_ffp - Check if FFP library is available
 */
int m99_has_ffp(void)
{
    return (MathFFPBase != NULL);
}

/*
 * m99_has_ieee - Check if IEEE library is available
 */
int m99_has_ieee(void)
{
    return (MathIEEEBase != NULL);
}

/*
 * m99_has_trans - Check if transcendental library is available
 */
int m99_has_trans(void)
{
    return (MathTransBase != NULL);
}

/*
 * m99_set_optimization - Set optimization flags
 */
void m99_set_optimization(int flags)
{
    optimization_flags = flags;
}

/*
 * m99_get_optimization - Get optimization flags
 */
int m99_get_optimization(void)
{
    return optimization_flags;
}

/*
 * m99_get_error - Get last error
 */
m99_math_error_t m99_get_error(void)
{
    return last_error;
}

/*
 * m99_get_error_string - Get error string
 */
const char *m99_get_error_string(m99_math_error_t error)
{
    switch (error) {
        case M99_ERR_NONE:
            return "No error";
        case M99_ERR_LIB_OPEN:
            return "Failed to open math library";
        case M99_ERR_LIB_CLOSE:
            return "Failed to close math library";
        case M99_ERR_INVALID_ARG:
            return "Invalid argument";
        case M99_ERR_OVERFLOW:
            return "Overflow";
        case M99_ERR_UNDERFLOW:
            return "Underflow";
        case M99_ERR_DOMAIN:
            return "Domain error";
        case M99_ERR_RANGE:
            return "Range error";
        default:
            return "Unknown error";
    }
}

/*
 * m99_clear_error - Clear error state
 */
void m99_clear_error(void)
{
    last_error = M99_ERR_NONE;
}

#endif /* _AMIGA_MATH_INIT_C */
