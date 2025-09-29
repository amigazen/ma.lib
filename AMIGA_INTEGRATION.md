# AmigaOS Math Library Integration Guide

## Overview

The m99.lib project now integrates with the `amiga-gcc-2.95.3-math-main` collection, providing **direct AmigaOS math library integration** using inline assembly. This approach is much more efficient than our previous method and follows the same pattern as the existing Amiga math libraries.

## Available Libraries

### 1. **libmdouble** - Double Precision Basic Operations
- **Functions**: `adddf3`, `divdf3`, `muldf3`, `subdf3`, `cmpdf2`, `negdf2`
- **Conversions**: `fixdfsi`, `floatsidf`
- **Standard**: `ceil`, `floor`, `fabs`
- **AmigaOS Library**: `mathieeedoubbas.library`

### 2. **libmfloat** - Single Precision Basic Operations
- **Functions**: `addsf3`, `divsf3`, `mulsf3`, `subsf3`, `cmpsf2`, `negsf2`
- **Conversions**: `fixsfsi`, `floatsisf`
- **Standard**: `ceilf`, `floorf`, `fabsf`
- **AmigaOS Library**: `mathieeesingbas.library`

### 3. **libmtransdouble** - Double Precision Transcendental Functions
- **Trigonometric**: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`
- **Hyperbolic**: `sinh`, `cosh`, `tanh`
- **Exponential/Logarithmic**: `exp`, `log`, `log10`, `sqrt`, `pow`
- **Special**: `sincos` (combined sin/cos computation)
- **Conversions**: `extendsfdf2`, `truncdfsf2`
- **AmigaOS Library**: `mathieeedoubtrans.library`

### 4. **libmtransfloat** - Single Precision Transcendental Functions
- **Functions**: Similar to libmtransdouble but for `float` type
- **AmigaOS Library**: `mathieeesingtrans.library`

### 5. **libminteger** - Integer Operations
- **Functions**: `mulsi3`, `divsi3`, `modsi3`, `udivsi3`, `umodsi3`
- **AmigaOS Library**: `utility.library`

## Integration Pattern

The integration follows the same pattern as the original `amiga-gcc-2.95.3-math-main` collection:

```c
extern struct MathIEEEBase *MathIeeeDoubTransBase;

__stdargs double amiga_ieee_sin(double x)
{
    register double result asm("d0");
    
    asm("move.l 8(sp),d0; move.l 12(sp),d1; movea.l %1,a6; jsr -36(a6);" :
        "=r"(result) : "m"(MathIeeeDoubTransBase) :
        "d1", "a0", "a1", "a6", "fp0", "fp1", "cc", "memory");
    return result;
}
```

## Key Features

### 1. **Direct AmigaOS Integration**
- Uses inline assembly to call AmigaOS math library functions directly
- No function call overhead
- Optimal performance on Amiga hardware

### 2. **FPU Detection**
- AmigaOS math libraries automatically detect and use FPU when available
- Falls back to software emulation on systems without FPU
- No manual FPU detection required

### 3. **Multiple Data Models**
- **Absolute**: Standard global data addressing
- **Base Relative**: 16-bit offset via A4 register (`-fbaserel`)
- **Base Relative 32**: 32-bit offset via A4 register (`-fbaserel32`, requires 68020+)

### 4. **Library Variants**
- **libmdouble.a** - Double precision basic operations
- **libmfloat.a** - Single precision basic operations
- **libmtransdouble.a** - Double precision transcendental functions
- **libmtransfloat.a** - Single precision transcendental functions
- **libminteger.a** - Integer operations

## Usage in m99.lib

### 1. **Include Headers**
```c
#include <amiga/math.h>
```

### 2. **Initialize Libraries**
```c
if (amiga_math_init()) {
    printf("AmigaOS math libraries initialized successfully\n");
}
```

### 3. **Use Functions**
```c
double result = amiga_ieee_sin(1.0);  // Direct AmigaOS call
double result2 = sin(1.0);            // Standard C99 function
```

### 4. **Cleanup**
```c
amiga_math_cleanup();
```

## Performance Benefits

### 1. **Native AmigaOS Performance**
- Direct calls to optimized AmigaOS math libraries
- FPU acceleration when available
- No emulation overhead

### 2. **Memory Efficiency**
- Small code size due to direct library calls
- No duplicate function implementations
- Shared library benefits

### 3. **Compatibility**
- Works with all AmigaOS versions
- Automatic FPU detection
- Fallback to software emulation

## Implementation Status

### ✅ **Completed**
- AmigaOS math library integration framework
- FFP math library integration (`amiga_math_ffp.c`)
- IEEE math library integration (`amiga_math_ieee.c`)
- Sample C99 functions (`cbrt.c`, `hypot.c`)

### 🔄 **In Progress**
- Complete C99/POSIX function implementations
- SAS/C compatibility layer
- Error handling and edge cases

### 📋 **Planned**
- Complex number function integration
- Performance optimization
- Comprehensive testing

## Build Integration

The `amiga-gcc-2.95.3-math-main` collection provides pre-built libraries in three variants:

- `lib/` - Absolute addressing
- `lib/libb/` - Base relative (16-bit)
- `lib/libb32/libm020/` - Base relative 32-bit (68020+)

These can be integrated into the m99.lib build system to provide the foundation for AmigaOS math library integration.

## Conclusion

The integration of `amiga-gcc-2.95.3-math-main` into m99.lib provides:

1. **Direct AmigaOS math library access** using inline assembly
2. **Optimal performance** with FPU acceleration
3. **Small code size** due to library calls
4. **Full compatibility** with AmigaOS math libraries
5. **Professional implementation** following established patterns

This integration significantly enhances the m99.lib project by providing native AmigaOS performance while maintaining C99/POSIX compatibility.
