# BSD 2-Clause License

Copyright (c) 2025 amigazen project

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Acknowledgements

## Complex Number Functions (amigazen project, 2025)
All complex number functions are original works of amigazen project, implementing C functions that wrap SAS/C's C++ complex number class and methods. These provide POSIX-compliant complex number support for C89 compatibility:
- Basic operations: cabs(), carg(), creal(), cimag(), conj(), cproj()
- Trigonometric: cacos(), casin(), catan(), ccos(), csin(), ctan()
- Hyperbolic: cacosh(), casinh(), catanh(), ccosh(), csinh(), ctanh()
- Exponential/Logarithmic: cexp(), clog(), cpow(), csqrt()
- Arithmetic: cadd(), csub(), cmul(), cdiv(), cneg(), cscale(), cmod()
- All float and long double variants (f and l suffixes)

## Functions from Sun Microsystems fdlibm (1993)
The following functions are derived from Sun Microsystems' 1993 release of fdlibm:

### Classification and Sign Functions
- finite(), finitef(), finitel() - Test if number is finite
- isnan(), isnanf(), isnanl() - Test if number is NaN
- isinf(), isinff(), isinfl() - Test if number is infinity
- copysign(), copysignf(), copysignl() - Copy sign from one number to another
- signbit() - Test sign bit of floating-point value

### Floating-Point Manipulation
- nextafter(), nextafterf(), nextafterl() - Next representable value toward target
- nexttoward(), nexttowardf(), nexttowardl() - Next representable value toward target
- scalbn(), scalbnf(), scalbnl() - Scale by power of 2 (exponent manipulation)
- scalbln(), scalblnf(), scalblnl() - Scale by power of 2 (long exponent)
- scalb(), scalbf(), scalbl() - Scale by power of 2 (legacy function)
- logb(), logbf(), logbl() - Extract binary exponent as double
- ilogb(), ilogbf(), ilogbl() - Extract binary exponent as integer
- significand(), significandf(), significandl() - Extract significand

### Basic Math Functions
- fabs(), fabsf(), fabsl() - Absolute value
- fmod(), fmodf(), fmodl() - Floating-point remainder
- modf(), modff(), modfl() - Break into fractional and integer parts
- remainder(), remainderf(), remainderl() - IEEE remainder function
- ceil(), ceilf(), ceill() - Ceiling function
- floor(), floorf(), floorl() - Floor function
- rint(), rintf(), rintl() - Round to nearest integer
- trunc(), truncf(), truncl() - Truncate toward zero
- round(), roundf(), roundl() - Round to nearest integer
- nearbyint(), nearbyintf(), nearbyintl() - Round to nearest integer
- lround(), lroundf(), lroundl() - Round to long integer
- llround(), llroundf(), llroundl() - Round to long long integer
- lrint(), lrintf(), lrintl() - Round to long integer
- llrint(), llrintf(), llrintl() - Round to long long integer

### Trigonometric Functions
- sin(), sinf(), sinl() - Sine function
- cos(), cosf(), cosl() - Cosine function
- tan(), tanf(), tanl() - Tangent function
- asin(), asinf(), asinl() - Arc sine function
- acos(), acosf(), acosl() - Arc cosine function
- atan(), atanf(), atanl() - Arc tangent function
- atan2(), atan2f(), atan2l() - Arc tangent of two variables

### Hyperbolic Functions
- sinh(), sinhf(), sinhl() - Hyperbolic sine
- cosh(), coshf(), coshl() - Hyperbolic cosine
- tanh(), tanhf(), tanhl() - Hyperbolic tangent
- asinh(), asinhf(), asinhl() - Inverse hyperbolic sine
- acosh(), acoshf(), acoshl() - Inverse hyperbolic cosine
- atanh(), atanhf(), atanhl() - Inverse hyperbolic tangent

### Exponential and Logarithmic Functions
- exp(), expf(), expl() - Exponential function
- log(), logf(), logl() - Natural logarithm
- log10(), log10f(), log10l() - Base-10 logarithm
- exp2(), exp2f(), exp2l() - Base-2 exponential
- log2(), log2f(), log2l() - Base-2 logarithm
- pow(), powf(), powl() - Power function
- sqrt(), sqrtf(), sqrtl() - Square root
- cbrt(), cbrtf(), cbrtl() - Cube root
- hypot(), hypotf(), hypotl() - Euclidean distance

### Error and Gamma Functions
- erf(), erff(), erfl() - Error function
- erfc(), erfcf(), erfcl() - Complementary error function
- tgamma(), tgammaf(), tgammal() - True gamma function
- lgamma(), lgammaf(), lgammal() - Log gamma function
- gamma(), gammaf(), gammal() - Gamma function (alias for tgamma)
- gamma_r(), gamma_rf(), gamma_rl() - Reentrant gamma function
- lgamma_r(), lgamma_rf(), lgamma_rl() - Reentrant log gamma function

### Bessel Functions
- j0(), j0f(), j0l() - Bessel function of first kind, order 0
- j1(), j1f(), j1l() - Bessel function of first kind, order 1
- jn(), jnf(), jnl() - Bessel function of first kind, order n
- y0(), y0f(), y0l() - Bessel function of second kind, order 0
- y1(), y1f(), y1l() - Bessel function of second kind, order 1
- yn(), ynf(), ynl() - Bessel function of second kind, order n

### Utility Functions
- frexp(), frexpf(), frexpl() - Break into mantissa and exponent
- ldexp(), ldexpf(), ldexpl() - Load exponent
- remquo(), remquof(), remquol() - Remainder with quotient
- fpclassify(), fpclassifyf(), fpclassifyl() - Classify floating-point value

### Library Support
- signgam - Global variable for gamma function sign
- lib_version - Library version information
- matherr() - Math error handler

## Functions from Python 2.7 (Python Software Foundation)
The following functions are derived from Python 2.7's _math.c fallback implementations:
- log1p(), log1pf(), log1pl() - log(1+x) for small x
- expm1(), expm1f(), expm1l() - exp(x)-1 for small x

## Original Functions by amigazen project (2025)
The following functions are original works of amigazen project:
- fmin(), fminf(), fminl() - Minimum of two values
- fmax(), fmaxf(), fmaxl() - Maximum of two values
- fdim(), fdimf(), fdiml() - Positive difference (max(x-y, 0))
- fma(), fmaf(), fmal() - Fused multiply-add operation
- nan(), nanf(), nanl() - Generate quiet NaN with optional tag
