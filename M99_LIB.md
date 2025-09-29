# M99.LIB - Math Library Extensions for SAS/C

## Overview

This document catalogs all the POSIX.1 and C99 math functions that are **NOT** provided by SAS/C's scm.lib, but are available in our libm99 collection. These functions are essential for creating a comprehensive C99/POSIX-compliant math library for the Amiga platform.

## Functions Already Available in SAS/C scm.lib

The following math functions are already provided by SAS/C and do NOT need to be included in m99.lib:

### C89/ANSI Standard Functions (Available in SAS/C)
- `abs()` - absolute value
- `acos()` - arccosine function
- `asin()` - arcsine function  
- `atan()` - arctangent function
- `atan2()` - arctangent of x/y
- `ceil()` - get floating-point limits
- `cos()` - cosine function
- `cosh()` - hyperbolic cosine function
- `exp()` - exponential function
- `fabs()` - floating-point absolute value
- `floor()` - get the floor of a real number
- `fmod()` - floating-point modulus operations
- `frexp()` - split floating-point value
- `ldexp()` - combine floating-point value
- `log()` - natural logarithm function
- `log10()` - base 10 logarithm function
- `modf()` - split a floating-point value
- `pow()` - raise a number to a power
- `sin()` - sine function
- `sinh()` - hyperbolic sine function
- `sqrt()` - square root function
- `tan()` - tangent function
- `tanh()` - hyperbolic tangent function

### SAS/C Specific Extensions (Available)
- `cot()` - cotangent function (UNIX extension)
- `pow2()` - raise 2 to a power (SAS/C specific)

---

## Functions MISSING from SAS/C (Required for m99.lib)

### **1. C99 Standard Functions**

#### **Inverse Hyperbolic Functions**
- `acosh()` - inverse hyperbolic cosine
- `asinh()` - inverse hyperbolic sine
- `atanh()` - inverse hyperbolic tangent

#### **Advanced Exponential/Logarithmic Functions**
- `expm1()` - exp(x) - 1 (more accurate for small x)
- `log1p()` - log(1 + x) (more accurate for small x)

#### **Rounding and Remainder Functions**
- `rint()` - round to nearest integer
- `remainder()` - IEEE remainder function
- `remquo()` - remainder with quotient

#### **Power and Root Functions**
- `cbrt()` - cube root
- `hypot()` - hypotenuse function (sqrt(x² + y²))

#### **Floating-Point Manipulation**
- `copysign()` - copy sign of a number
- `nextafter()` - next representable floating-point value
- `scalbn()` - scale by power of 2
- `scalb()` - scale by power of radix
- `logb()` - extract exponent
- `ilogb()` - extract exponent as integer
- `significand()` - extract significand

#### **Classification Functions**
- `finite()` - test for finite value
- `isnan()` - test for NaN
- `isinf()` - test for infinity
- `fpclassify()` - classify floating-point value
- `isfinite()` - test for finite value (macro)
- `isnormal()` - test for normal value (macro)
- `signbit()` - test sign bit (macro)

#### **Comparison Functions**
- `isgreater()` - compare without exceptions (macro)
- `isgreaterequal()` - compare without exceptions (macro)
- `isless()` - compare without exceptions (macro)
- `islessequal()` - compare without exceptions (macro)
- `islessgreater()` - compare without exceptions (macro)
- `isunordered()` - test for unordered (macro)

### **2. POSIX.1 Standard Functions**

#### **Error Functions**
- `erf()` - error function
- `erfc()` - complementary error function

#### **Gamma Functions**
- `gamma()` - gamma function (deprecated, use tgamma)
- `tgamma()` - true gamma function
- `lgamma()` - log gamma function
- `gamma_r()` - reentrant gamma function
- `lgamma_r()` - reentrant log gamma function

#### **Bessel Functions**
- `j0()` - Bessel function of the first kind, order 0
- `j1()` - Bessel function of the first kind, order 1
- `jn()` - Bessel function of the first kind, order n
- `y0()` - Bessel function of the second kind, order 0
- `y1()` - Bessel function of the second kind, order 1
- `yn()` - Bessel function of the second kind, order n

### **3. C99 Complex Number Functions**

#### **Basic Complex Operations**
- `cabs()` - complex absolute value
- `carg()` - complex argument (phase)
- `cimag()` - imaginary part
- `creal()` - real part
- `conj()` - complex conjugate

#### **Complex Trigonometric Functions**
- `cacos()` - complex arccosine
- `casin()` - complex arcsine
- `catan()` - complex arctangent
- `ccos()` - complex cosine
- `csin()` - complex sine
- `ctan()` - complex tangent

#### **Complex Hyperbolic Functions**
- `cacosh()` - complex inverse hyperbolic cosine
- `casinh()` - complex inverse hyperbolic sine
- `catanh()` - complex inverse hyperbolic tangent
- `ccosh()` - complex hyperbolic cosine
- `csinh()` - complex hyperbolic sine
- `ctanh()` - complex hyperbolic tangent

#### **Complex Exponential/Logarithmic Functions**
- `cexp()` - complex exponential
- `clog()` - complex natural logarithm
- `clog10()` - complex base-10 logarithm

#### **Complex Power Functions**
- `cpow()` - complex power function
- `csqrt()` - complex square root

#### **Complex Projection**
- `cproj()` - projection onto Riemann sphere

### **4. Additional IEEE 754 Functions**

#### **Min/Max Functions**
- `fmin()` - minimum of two values
- `fmax()` - maximum of two values
- `fdim()` - positive difference
- `fma()` - fused multiply-add

#### **NaN Functions**
- `nan()` - generate quiet NaN
- `nanf()` - generate quiet NaN (float)
- `nanl()` - generate quiet NaN (long double)

### **5. Long Double Functions**

All of the above functions should also be available in long double versions with 'l' suffix:
- `acosl()`, `asinl()`, `atanl()`, `atan2l()`
- `ceill()`, `floorl()`, `truncl()`, `roundl()`
- `cosl()`, `sinl()`, `tanl()`
- `coshl()`, `sinhl()`, `tanhl()`
- `acoshl()`, `asinhl()`, `atanhl()`
- `expl()`, `exp2l()`, `expm1l()`
- `logl()`, `log2l()`, `log10l()`, `log1pl()`
- `powl()`, `sqrtl()`, `cbrtl()`, `hypotl()`
- etc.

### **6. Float Functions**

All functions should also be available in float versions with 'f' suffix:
- `acosf()`, `asinf()`, `atanf()`, `atan2f()`
- `ceilf()`, `floorf()`, `truncf()`, `roundf()`
- `cosf()`, `sinf()`, `tanf()`
- `coshf()`, `sinhf()`, `tanhf()`
- `acoshf()`, `asinhf()`, `atanhf()`
- `expf()`, `exp2f()`, `expm1f()`
- `logf()`, `log2f()`, `log10f()`, `log1pf()`
- `powf()`, `sqrtf()`, `cbrtf()`, `hypotf()`
- etc.

## Implementation Sources

### Available in libm99 Collection:
1. **FDLIBM** - Provides most C99 and POSIX functions
2. **Berkeley libm** - Additional implementations and MC68881 optimized versions
3. **Complex library** - Basic complex number operations
4. **Custom implementations** - For any remaining gaps

### Implementation Priority:

1. **High Priority (Essential for Python 2.7):**
   - `finite()`, `isnan()`, `isinf()`
   - `hypot()`, `copysign()`
   - `acosh()`, `asinh()`, `atanh()`
   - `expm1()`, `log1p()`
   - Complex number functions

2. **Medium Priority (C99 Compliance):**
   - Bessel functions (`j0`, `j1`, `jn`, `y0`, `y1`, `yn`)
   - Error functions (`erf`, `erfc`)
   - Gamma functions (`tgamma`, `lgamma`)
   - Advanced floating-point functions

3. **Lower Priority (Complete IEEE 754):**
   - Float/long double variants
   - Comparison macros
   - Advanced classification functions

## Build Considerations

- **C89 Compatibility**: Ensure all implementations compile with SAS/C
- **Amiga Optimization**: Use MC68881/68882 FPU when available
- **Memory Constraints**: Optimize for Amiga's limited memory
- **Standards Compliance**: Follow C99/POSIX specifications
- **Error Handling**: Implement proper errno and exception handling

## Estimated Function Count

- **Core missing functions**: ~40-50 functions
- **With float/long double variants**: ~120-150 functions
- **Total with complex numbers**: ~180-200 functions

This represents a significant enhancement to the Amiga's mathematical capabilities, bringing it up to modern C99/POSIX standards.
