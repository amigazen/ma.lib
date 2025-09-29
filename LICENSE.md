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

Complex maths functions are an original work of amigazen project, implementing C functions wrapping SAS/C's C++ complex number class and methods, with a little inspiration taken from Nick d'Alterio's complex number library for Amiga (1995)

Some maths functions originally by the Fred Fish himself, released into the public domain (1987), obtained via the PDC C compiler math library

log1 family of functions are derived from Python 2.7's _math.c fallback implementations

The following functions are derived from Sun Microsystem's 1995 release of fdlibm:
- finite(), finitef(), finitel() - Test if number is finite
- isnan(), isnanf(), isnanl() - Test if number is NaN
- isinf(), isinff(), isinfl() - Test if number is infinity
- copysign(), copysignf(), copysignl() - Copy sign from one number to another
- nextafter(), nextafterf(), nextafterl() - Next representable value toward target
- scalbn(), scalbnf(), scalbnl() - Scale by power of 2 (exponent manipulation)
- logb(), logbf(), logbl() - Extract binary exponent as double
- ilogb(), ilogbf(), ilogbl() - Extract binary exponent as integer
- Classification: finite(), isnan(), isinf() with float/long double variants
- Sign manipulation: copysign() with float/long double variants  
- Floating point operations: nextafter(), scalbn(), logb(), ilogb() with variants
- Basic math: fabs(), fmod(), modf(), remainder(), ceil(), floor() with variants
- Error functions: erf(), erfc() with complete fdlibm implementation
- Gamma functions: gamma(), lgamma(), gamma_r(), lgamma_r() with variants
- Bessel functions: j0() with complete fdlibm implementation
- Trigonometric: sin() with complete kernel functions and argument reduction
- Library support: signgam, lib_version globals