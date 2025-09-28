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

### Library Variants

ma.lib provides all the same build variants as SAS/C's scm.lib:

- **ma.lib** - Standard version
- **ma040.lib** - Optimized for 68040 CPU
- **ma881.lib** - Uses 68881 FPU assembler
- **maffp.lib** - Uses Amiga FFP math libraries
- **maieee.lib** - Uses Amiga IEEE math libraries

### C99 Standard Functions
- **Inverse Hyperbolic**: `acosh()`, `asinh()`, `atanh()`
- **Advanced Exponential/Logarithmic**: `expm1()`, `log1p()`
- **Rounding**: `rint()`, `remainder()`, `remquo()`
- **Power/Root**: `cbrt()`, `hypot()`
- **Floating-Point Manipulation**: `copysign()`, `nextafter()`, `scalbn()`, `logb()`, `ilogb()`
- **Classification**: `finite()`, `isnan()`, `isinf()`, `fpclassify()`, `isfinite()`, `isnormal()`, `signbit()`

### POSIX.1 Functions
- **Error Functions**: `erf()`, `erfc()`
- **Gamma Functions**: `tgamma()`, `lgamma()`, `gamma_r()`, `lgamma_r()`
- **Bessel Functions**: `j0()`, `j1()`, `jn()`, `y0()`, `y1()`, `yn()`

### C99 Complex Numbers
- **Basic Operations**: `cabs()`, `carg()`, `creal()`, `cimag()`, `conj()`
- **Trigonometric**: `cacos()`, `casin()`, `catan()`, `ccos()`, `csin()`, `ctan()`
- **Hyperbolic**: `cacosh()`, `casinh()`, `catanh()`, `ccosh()`, `csinh()`, `ctanh()`
- **Exponential/Logarithmic**: `cexp()`, `clog()`, `cpow()`, `csqrt()`

### IEEE 754 Functions
- **Min/Max**: `fmin()`, `fmax()`, `fdim()`, `fma()`
- **NaN Functions**: `nan()`, `nanf()`, `nanl()`

## Contact 

- At GitHub https://github.com/amigazen/ma.lib/ 
- on the web at http://www.amigazen.com/amigapython/ (Amiga browser compatible)
- or email unsui@amigazen.com