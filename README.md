# ma.lib 

This is ma.lib, a standard C99 math library for Amiga for use with SAS/C

## [amigazen project](http://www.amigazen.com)

*A web, suddenly*

*Forty years meditation*

*Minds awaken, free*

**amigazen project** uses modern software development tools and methods to update and rerelease classic Amiga open source software. Our releases include a new AWeb, a new Amiga Python 2, and the ToolKit project - a universal SDK for Amiga.

Key to our approach is ensuring every project can be built with the same common set of development tools and configurations, so we created the ToolKit project to provide a standard configuration for Amiga development. All *amigazen project* releases will be guaranteed to build against the ToolKit standard so that anyone can download and begin contributing straightaway without having to tailor the toolchain for their own setup.

This software is redistributed on terms described in the documentation, particularly the file LICENSE.md

Our philosophy is based on openness:

*Open* to anyone and everyone	- *Open* source and free for all	- *Open* your mind and create!

PRs for all of our projects are gratefully received at [GitHub](https://github.com/amigazen/). While our focus now is on classic 68k software, we do intend that all amigazen project releases can be ported to other Amiga-like systems including AROS and MorphOS where feasible.

## About ma.lib

The SAS/C compiler's sc.lib and scm.lib standard libraries are frozen in time, implementing the 'C89' ANSI C standard.

While David Gay's unix.lib, now updated and forming the basis of the UniLib3 C library for Amiga, also maintained by amigazen project, adds missing C99 and POSIX C functions, it does not include the additional math library, or 'libm', functions mandated by the standards.

ma.lib is therefore an additional library complementary to unix.lib and scm.lib, designed to fill in the missing math functions, including an implementation of complex.h that wraps SAS/C's C++ complex number support (ironically SAS/C does come with C++ complex number classes), and delivered as part of the UniLib3 project and ToolKit SDK from amigazen project.

The name ma.lib is chosen in order not to clash with other similar C math libs commonly found on Amiga, such as clib2's 'math.lib', GCC's 'libm' or SAS/C scm.lib. 

Interpreting the name is left to the reader, perhaps it means 'math addon' or 'm.lib for Amiga', while the concept of _ma_ in Japanese culture and zen buddhism relates to the "space between".

## About ToolKit

**ToolKit** exists to solve the problem that most Amiga software was written in the 1980s and 90s, by individuals working alone, each with their own preferred setup for where their dev tools are run from, where their include files, static libs and other toolchain artifacts could be found, which versions they used and which custom modifications they made. Open source collaboration did not exist as we know it in 2025. 

**ToolKit** from amigazen project is a work in progress to make a standardised installation of not just the Native Developer Kit, but the compilers, build tools and third party components needed to be able to consistently build projects in collaboration with others, without each contributor having to change build files to work with their particular toolchain configuration. 

All *amigazen project* releases will release in a ready to build configuration according to the ToolKit standard.

Each component of **ToolKit** is open source and will have it's own github repo, while ToolKit itself will eventually be released as an easy to install package containing the redistributable components, as well as scripts to easily install the parts that are not freely redistributable from archive.

## Features

### Standards Compliance
- **100% C89 Standard** - Complete ANSI C89 math library compliance
- **100% C99 Standard** - Full C99 math library implementation
- **100% POSIX.1** - Complete POSIX.1 math function support
- **100% IEEE 754** - Full IEEE 754 floating-point standard compliance

### Library Variants

ma.lib provides all the same build variants as SAS/C's scm.lib:

- **ma.lib** - Standard version
- **ma040.lib** - Optimized for 68040 CPU
- **ma881.lib** - Uses 68881 FPU assembler
- **maffp.lib** - Uses Amiga FFP math libraries
- **maieee.lib** - Uses Amiga IEEE math libraries

### C89 Standard Functions (Complete)
- **Trigonometric**: `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `atan2()`
- **Hyperbolic**: `sinh()`, `cosh()`, `tanh()`
- **Exponential/Logarithmic**: `exp()`, `log()`, `log10()`
- **Power/Root**: `pow()`, `sqrt()`
- **Other**: `fabs()`, `floor()`, `ceil()`, `fmod()`, `frexp()`, `ldexp()`, `modf()`

### C99 Standard Functions
- **Inverse Hyperbolic**: `acosh()`, `asinh()`, `atanh()`
- **Advanced Exponential/Logarithmic**: `expm1()`, `log1p()`, `exp2()`, `log2()`
- **Rounding**: `rint()`, `remainder()`, `remquo()`, `trunc()`, `round()`, `nearbyint()`
- **Integer Rounding**: `lround()`, `llround()`, `lrint()`, `llrint()`
- **Power/Root**: `cbrt()`, `hypot()`
- **Floating-Point Manipulation**: `copysign()`, `nextafter()`, `nexttoward()`, `scalbn()`, `scalbln()`, `scalb()`, `logb()`, `ilogb()`, `significand()`
- **Classification**: `finite()`, `isnan()`, `isinf()`, `fpclassify()`, `isfinite()`, `isnormal()`, `signbit()`

### POSIX.1 Functions
- **Error Functions**: `erf()`, `erfc()`
- **Gamma Functions**: `tgamma()`, `lgamma()`, `gamma()`, `gamma_r()`, `lgamma_r()`
- **Bessel Functions**: `j0()`, `j1()`, `jn()`, `y0()`, `y1()`, `yn()`

### C99 Complex Numbers (Complete Implementation)
- **Basic Operations**: `cabs()`, `carg()`, `creal()`, `cimag()`, `conj()`, `cproj()`
- **Trigonometric**: `cacos()`, `casin()`, `catan()`, `ccos()`, `csin()`, `ctan()`
- **Hyperbolic**: `cacosh()`, `casinh()`, `catanh()`, `ccosh()`, `csinh()`, `ctanh()`
- **Exponential/Logarithmic**: `cexp()`, `clog()`, `cpow()`, `csqrt()`
- **Arithmetic**: `cadd()`, `csub()`, `cmul()`, `cdiv()`, `cneg()`, `cscale()`, `cmod()`

### IEEE 754 Functions
- **Min/Max**: `fmin()`, `fmax()`, `fdim()`, `fma()`
- **NaN Functions**: `nan()`, `nanf()`, `nanl()`

### Float and Long Double Variants
- **Complete Coverage** - All functions have `f` (float) and `l` (long double) variants
- **200+ Functions** - Full implementation across all precision types

### Mathematical Constants
- **C89 Constants**: `M_E`, `M_LOG2E`, `M_LOG10E`, `M_LN2`, `M_LN10`, `M_PI`, `M_PI_2`, `M_PI_4`, `M_1_PI`, `M_2_PI`, `M_2_SQRTPI`, `M_SQRT2`, `M_SQRT1_2`, `HUGE_VAL`
- **Additional Constants**: `M_SQRT3`, `M_SQRT5`, `M_PHI`, `M_EULER`, `M_LNPI`, `M_LN2PI`, `M_GAMMA`
- **C99 Constants**: `INFINITY`, `NAN`

### Error Handling
- **C89 Compliant** - Proper `errno` setting for domain and range errors
- **Domain Errors** - `EDOM` for invalid arguments (e.g., negative sqrt, |x|>1 for asin/acos)
- **Range Errors** - `ERANGE` for overflow/underflow conditions
- **Math Error Handler** - `matherr()` function for custom error handling

### Amiga Integration
- **Native Performance** - Uses Amiga math libraries when available
- **Fallback Support** - High-quality fdlibm implementations as fallback
- **SAS/C Compatible** - Designed specifically for SAS/C compiler
- **C++ Complex Support** - Wraps SAS/C's native C++ complex number classes

### Library Compatibility
- **Co-exists with scm.lib** - ma.lib can be used alongside SAS/C's scm.lib or standalone, as implements a complete libm
- **Linker Order Control** - Order libraries in linker command to control function precedence:
  - `ma.lib scm.lib` - Use ma.lib functions in preference, fallback to scm.lib only for functions not part of C99/POSIX standards
  - `scm.lib ma.lib` - Use scm.lib functions in preference, fallback to ma.lib to provide additional C99 functions

## Usage

### Basic Usage
```c
#include <math.h>
#include <complex.h>

double result = sqrt(2.0);  // Uses ma.lib implementation
```

### Linker Command Examples
```bash
# Use ma.lib functions when available, fallback to scm.lib
sc LINK TO program program.c LIB ma.lib scm.lib

# Use scm.lib functions when available, fallback to ma.lib  
sc LINK TO program program.c LIB scm.lib ma.lib

# Use only ma.lib (recommended for new projects)
sc LINK TO program program.c LIB ma.lib
```

## Contact 

- At GitHub https://github.com/amigazen/ma.lib/ 
- on the web at http://www.amigazen.com/amigapython/ (Amiga browser compatible)
- or email unsui@amigazen.com