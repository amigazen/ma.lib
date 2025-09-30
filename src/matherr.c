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

/****** ma.lib/matherr **************************************************
* 
*   NAME	
* 	matherr -- Math error handler function. (V1.0)
*
*   SYNOPSIS
*	int result = matherr(struct exception *e);
*	  D0		   A0
*	int matherr(struct exception *e);
*
*   FUNCTION
*	Handle math library errors. This function is called when a math
*	function encounters an error condition such as domain error, range
*	error, or overflow. The default implementation allows the system
*	to handle errors normally.
* 
*   INPUTS
*	e - Pointer to exception structure containing error details.
*	    Contains type, name, arg1, arg2, retval, and other fields.
*	
*   RESULT
*	result - 0 to use default error handling, non-zero to suppress
*	        default error handling and use custom behavior.
* 
*   EXAMPLE
*	
*	int matherr(struct exception *e) {
*	    if (e->type == DOMAIN) {
*	        printf("Domain error in %s\n", e->name);
*	        e->retval = 0.0;
*	        return 1;  
*	    }
*	    return 0;  
*	}
*
*   NOTES
*	This function is C89 compliant. Applications can override this
*	function to provide custom error handling.
* 
*   SEE ALSO
*	math.h, errno.h
* 
******************************************************************************/

int matherr(struct exception *e)
{
    /* Default behavior - let the system handle errors */
    return 0;
}
