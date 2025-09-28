/*
 * m99 Math Library Internal Header
 * 
 * This file gets included with all of the floating point math
 * library routines when they are compiled. Note that
 * this is the proper place to put machine dependencies
 * whenever possible.
 * 
 * Originally adapted from PDC/libsrc/LibSrc/Math/pml.h
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _INTERNAL_MATH_H
#define _INTERNAL_MATH_H

/* Disable debug macros for production */
#ifndef NO_DBUG
#    define DBUG_ENTER(a1)
#    define DBUG_RETURN(a1) return(a1)
#    define DBUG_VOID_RETURN return
#    define DBUG_EXECUTE(keyword,a1)
#    define DBUG_2(keyword,format)
#    define DBUG_3(keyword,format,a1)
#    define DBUG_4(keyword,format,a1,a2)
#    define DBUG_5(keyword,format,a1,a2,a3)
#    define DBUG_PUSH(a1)
#    define DBUG_POP()
#    define DBUG_PROCESS(a1)
#    define DBUG_FILE (stderr)
#endif

#include <errno.h>
#include <math.h>

/*
 * Math constants - using standard math.h values where available
 */
#ifndef PI
#define PI              3.14159265358979323846
#endif

/* Define missing constants for C89 compatibility */
#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif

#ifndef HUGE_VALF
#define HUGE_VALF (3.402823466e+38f)
#endif

#ifndef FLT_MAX
#define FLT_MAX (3.402823466e+38f)
#endif

#ifndef HUGE_VALL
#define HUGE_VALL (1.7976931348623157e+308L)
#endif

#ifndef LDBL_MAX
#define LDBL_MAX (1.7976931348623157e+308L)
#endif

/* POSIX types for better portability */
#ifndef double_t
#define double_t double
#endif

#ifndef float_t
#define float_t float
#endif

/* Long double fallback to double for C89 compatibility */
#ifndef long_double_t
#define long_double_t double
#endif

#ifndef sqrtl
#define sqrtl(x) sqrt((double)(x))
#endif

#ifndef logl
#define logl(x) log((double)(x))
#endif
#define TWOPI           (2.0 * PI)
#define HALFPI          (PI / 2.0)
#define FOURTHPI        (PI / 4.0)
#define SIXTHPI         (PI / 6.0)
#define LOG2E           1.4426950408889634074   /* Log to base 2 of e */
#define LOG10E          0.4342944819032518276
#define SQRT2           1.4142135623730950488
#define SQRT3           1.7320508075688772935
#define LN2             0.6931471805599453094
#define LNSQRT2         0.3465735902799726547

/*
 * Double precision limits - using standard values
 */
#ifndef MAXDOUBLE
#define MAXDOUBLE       DBL_MAX
#endif
#ifndef MINDOUBLE
#define MINDOUBLE       DBL_MIN
#endif
#ifndef DMAXEXP
#define DMAXEXP         DBL_MAX_EXP
#endif
#ifndef DMINEXP
#define DMINEXP         DBL_MIN_EXP
#endif

#define LOG2_MAXDOUBLE  (DMAXEXP + 1)
#define LOG2_MINDOUBLE  (DMINEXP - 1)
#define LOGE_MAXDOUBLE  (LOG2_MAXDOUBLE / LOG2E)
#define LOGE_MINDOUBLE  (LOG2_MINDOUBLE / LOG2E)

/*
 * Function-specific limits
 */
#define TANH_MAXARG 16
#define SQRT_MAXDOUBLE 1.304380e19

/*
 * Boolean constants
 */
#define TRUE 1
#define FALSE 0
#define VOID void

/*
 * Math error handling structure
 */
struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
};

/*
 * Error types - only define if not already defined
 */
#ifndef DOMAIN
#define DOMAIN          1
#endif
#ifndef SING
#define SING            2
#endif
#ifndef OVERFLOW
#define OVERFLOW        3
#endif
#ifndef UNDERFLOW
#define UNDERFLOW       4
#endif
#ifndef TLOSS
#define TLOSS           5
#endif
#ifndef PLOSS
#define PLOSS           6
#endif

#define MAX_ERRORS      8

#define LOG             1
#define COUNT           2
#define CONTINUE        4

/*
 * Math error handler function
 */
extern int matherr(struct exception *e);

#endif /* _INTERNAL_MATH_H */
