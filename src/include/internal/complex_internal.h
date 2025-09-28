/*
 * Internal Complex Number Operations
 * 
 * This header contains internal complex number operations
 * based on Nicolas d'Alterio's library, rewritten to be
 * C99/POSIX compliant and hidden from the public API.
 */

#ifndef _INTERNAL_COMPLEX_H
#define _INTERNAL_COMPLEX_H

/* Original Complex library structure from Nicolas d'Alterio */
struct Complex {
    double Real;
    double Imag;
};

typedef struct Complex COMPLEX;

/* Internal complex arithmetic functions - based on Nicolas d'Alterio's Com* functions */
/* ComAdd, ComSub, ComMul, ComDiv, ComMod, ComArg are defined in their respective .c files */

/* Internal complex utility functions */
COMPLEX ComNeg(COMPLEX z);
COMPLEX ComScale(COMPLEX z, double scale);

/* Internal complex trigonometric functions */
COMPLEX cacos_internal(COMPLEX z);
COMPLEX casin_internal(COMPLEX z);
COMPLEX catan_internal(COMPLEX z);
COMPLEX ccos_internal(COMPLEX z);
COMPLEX csin_internal(COMPLEX z);
COMPLEX ctan_internal(COMPLEX z);

/* Internal complex hyperbolic functions */
COMPLEX cacosh_internal(COMPLEX z);
COMPLEX casinh_internal(COMPLEX z);
COMPLEX catanh_internal(COMPLEX z);
COMPLEX ccosh_internal(COMPLEX z);
COMPLEX csinh_internal(COMPLEX z);
COMPLEX ctanh_internal(COMPLEX z);

/* Internal complex exponential/logarithmic functions */
COMPLEX cexp_internal(COMPLEX z);
COMPLEX clog_internal(COMPLEX z);
COMPLEX clog10_internal(COMPLEX z);
COMPLEX cpow_internal(COMPLEX z, COMPLEX w);
COMPLEX csqrt_internal(COMPLEX z);

/* Internal complex projection function */
COMPLEX cproj_internal(COMPLEX z);

#endif /* _INTERNAL_COMPLEX_H */