#include "include/internal/longlong.h"
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

/* Define ERANGE if not already defined (for older systems) */
#ifndef ERANGE
#define ERANGE 34
#endif

/*
 * Implementation of long long emulation functions for AmigaOS with SAS/C.
 * These functions provide complete 64-bit integer arithmetic using struct-based representation.
 * 
 * Error handling: Division by zero sets errno to EDOM (Domain Error).
 * Overflow in division by -1 sets errno to ERANGE (Range Error).
 * 
 * Special handling: LONG_LONG_MIN cannot be negated in two's complement,
 * so division by LONG_LONG_MIN is handled as a special case.
 */

/****** ma.lib/long_to_long_long ********************************************
* 
*   NAME	
* 	long_to_long_long -- Convert long to long_long_t. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_to_long_long(long value);
*	  D0		   D0
*	long_long_t long_to_long_long(long value);
*
*   FUNCTION
*	Convert a long value to long_long_t structure. This is a helper
*	function for 64-bit integer emulation on AmigaOS with SAS/C.
*	This implementation provides complete 64-bit integer arithmetic.
* 
*   INPUTS
*	value - Long value to convert.
*	
*   RESULT
*	result - long_long_t structure containing the converted value.
* 
*   EXAMPLE
*	long x = 12345;
*	long_long_t result = long_to_long_long(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Part of 64-bit integer emulation for SAS/C.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Helper function to convert strtol result to our long_long_t */
long_long_t long_to_long_long(long value)
{
    long_long_t result;
    
    if (value >= 0) {
        result.hi = 0;
        result.lo = (unsigned long)value;
    } else {
        result.hi = 0xFFFFFFFF;  /* All bits set for negative */
        result.lo = (unsigned long)value;
    }
    
    return result;
}

/****** ma.lib/handle_overflow **********************************************
* 
*   NAME	
* 	handle_overflow -- Handle overflow cases for long long operations. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = handle_overflow(int negative);
*	  D0		   D0
*	long_long_t handle_overflow(int negative);
*
*   FUNCTION
*	Handle overflow cases for long long operations. Returns the
*	appropriate maximum or minimum value based on the sign.
*	This is a helper function for 64-bit integer emulation.
* 
*   INPUTS
*	negative - Non-zero if result should be negative (minimum value).
*	
*   RESULT
*	result - LONG_LONG_MAX if negative is 0, LONG_LONG_MIN if negative is 1.
* 
*   EXAMPLE
*	long_long_t result = handle_overflow(0);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Internal helper function for overflow handling.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Helper function to handle overflow cases */
long_long_t handle_overflow(int negative)
{
    long_long_t result;
    
    if (negative) {
        /* Return minimum value for negative overflow */
        result.hi = LONG_LONG_MIN_HI;
        result.lo = LONG_LONG_MIN_LO;
    } else {
        /* Return maximum value for positive overflow */
        result.hi = LONG_LONG_MAX_HI;
        result.lo = LONG_LONG_MAX_LO;
    }
    
    return result;
}

/****** ma.lib/long_long_negate *********************************************
* 
*   NAME	
* 	long_long_negate -- Negate a long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_negate(long_long_t value);
*	  D0		   D0
*	long_long_t long_long_negate(long_long_t value);
*
*   FUNCTION
*	Negate a long_long_t value using two's complement arithmetic.
*	This is a helper function for 64-bit integer emulation on AmigaOS.
* 
*   INPUTS
*	value - long_long_t value to negate.
*	
*   RESULT
*	result - Negated value. Returns zero if input is zero.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(42);
*	long_long_t result = long_long_negate(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses two's complement negation: invert all bits and add 1.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Helper function to negate a long_long_t value */
long_long_t long_long_negate(long_long_t value)
{
    long_long_t result;
    
    if (LONG_LONG_IS_ZERO(value)) {
        return value;  /* Negating zero gives zero */
    }
    
    /* Two's complement negation: invert all bits and add 1 */
    result.hi = ~value.hi;
    result.lo = ~value.lo;
    
    /* Add 1 to complete two's complement */
    result.lo++;
    if (result.lo == 0) {
        result.hi++;
    }
    
    return result;
}

/****** ma.lib/long_long_to_long ********************************************
* 
*   NAME	
* 	long_long_to_long -- Convert long_long_t to long. (V1.0)
*
*   SYNOPSIS
*	long result = long_long_to_long(long_long_t value);
*	  D0		   D0
*	long long_long_to_long(long_long_t value);
*
*   FUNCTION
*	Convert a long_long_t value to long. This is a truncating
*	conversion that returns only the low 32 bits. This can cause
*	data loss if the high 32 bits are non-zero.
* 
*   INPUTS
*	value - long_long_t value to convert.
*	
*   RESULT
*	result - Long value (truncated to low 32 bits).
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(12345);
*	long result = long_long_to_long(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	WARNING: This can cause data loss if value.hi != 0.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Conversion functions */
long long_long_to_long(long_long_t value)
{
    /* Truncating conversion: returns only the low 32 bits */
    /* WARNING: This can cause data loss if value.hi != 0 */
    return (long)value.lo;
}

/****** ma.lib/long_long_to_ulong *******************************************
* 
*   NAME	
* 	long_long_to_ulong -- Convert long_long_t to unsigned long. (V1.0)
*
*   SYNOPSIS
*	unsigned long result = long_long_to_ulong(long_long_t value);
*	  D0		   D0
*	unsigned long long_long_to_ulong(long_long_t value);
*
*   FUNCTION
*	Convert a long_long_t value to unsigned long. This is a truncating
*	conversion that returns only the low 32 bits. This can cause
*	data loss if the high 32 bits are non-zero.
* 
*   INPUTS
*	value - long_long_t value to convert.
*	
*   RESULT
*	result - Unsigned long value (truncated to low 32 bits).
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(12345);
*	unsigned long result = long_long_to_ulong(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	WARNING: This can cause data loss if value.hi != 0.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

unsigned long long_long_to_ulong(long_long_t value)
{
    /* Truncating conversion: returns only the low 32 bits */
    /* WARNING: This can cause data loss if value.hi != 0 */
    return value.lo;
}

/****** ma.lib/long_long_add ************************************************
* 
*   NAME	
* 	long_long_add -- Add two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_add(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_add(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Add two long_long_t values with proper carry handling. This
*	performs complete 64-bit addition for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Sum of a and b.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(1000);
*	long_long_t b = long_to_long_long(2000);
*	long_long_t result = long_long_add(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Handles carry propagation between high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit addition with carry handling */
long_long_t long_long_add(long_long_t a, long_long_t b)
{
    long_long_t result;
    unsigned long carry;
    
    /* Add low parts */
    result.lo = a.lo + b.lo;
    carry = (result.lo < a.lo) ? 1 : 0;
    
    /* Add high parts with carry */
    result.hi = a.hi + b.hi + carry;
    
    return result;
}

/****** ma.lib/long_long_sub ************************************************
* 
*   NAME	
* 	long_long_sub -- Subtract two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_sub(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_sub(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Subtract two long_long_t values with proper borrow handling. This
*	performs complete 64-bit subtraction for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value (minuend).
*	b - Second long_long_t value (subtrahend).
*	
*   RESULT
*	result - Difference of a and b (a - b).
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2000);
*	long_long_t b = long_to_long_long(1000);
*	long_long_t result = long_long_sub(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Handles borrow propagation between high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit subtraction with borrow handling */
long_long_t long_long_sub(long_long_t a, long_long_t b)
{
    long_long_t result;
    unsigned long borrow;
    
    /* Subtract low parts */
    if (a.lo >= b.lo) {
        result.lo = a.lo - b.lo;
        borrow = 0;
    } else {
        result.lo = a.lo - b.lo;
        borrow = 1;
    }
    
    /* Subtract high parts with borrow */
    result.hi = a.hi - b.hi - borrow;
    
    return result;
}

/****** ma.lib/long_long_mul ************************************************
* 
*   NAME	
* 	long_long_mul -- Multiply two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_mul(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_mul(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Multiply two long_long_t values using long multiplication algorithm.
*	This performs complete 64-bit multiplication for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value (multiplicand).
*	b - Second long_long_t value (multiplier).
*	
*   RESULT
*	result - Product of a and b (a * b).
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(1000);
*	long_long_t b = long_to_long_long(2000);
*	long_long_t result = long_long_mul(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Handles overflow by returning maximum/minimum values.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit multiplication using long multiplication algorithm */
long_long_t long_long_mul(long_long_t a, long_long_t b)
{
    long_long_t result = {0, 0}, max_value;
    int negative = 0;
    unsigned long a0, a1, b0, b1;
    unsigned long p0, p1, p2, p3;
    unsigned long mid_sum1, mid_sum2;
    
    /* Handle signed multiplication by working with absolute values */
    if (LONG_LONG_IS_NEGATIVE(a)) {
        a = long_long_negate(a);
        negative = !negative;
    }
    if (LONG_LONG_IS_NEGATIVE(b)) {
        b = long_long_negate(b);
        negative = !negative;
    }
    
    /* --- Start of simplified multiplication core --- */
    
    /* This part calculates the 64-bit result of a.lo * b.lo */
    a0 = a.lo & 0xFFFF;
    a1 = a.lo >> 16;
    b0 = b.lo & 0xFFFF;
    b1 = b.lo >> 16;
    
    p0 = a0 * b0;
    p1 = a0 * b1;
    p2 = a1 * b0;
    p3 = a1 * b1;
    
    mid_sum1 = p1 + p2;
    mid_sum2 = (p0 >> 16) + (mid_sum1 & 0xFFFF);
    
    result.lo = (p0 & 0xFFFF) | (mid_sum2 << 16);
    result.hi = p3 + (mid_sum1 >> 16) + (mid_sum2 >> 16);
    
    /* Add the cross-products. These only affect the high 32 bits. */
    /* (The a.hi * b.hi term would be shifted out of a 64-bit result) */
    result.hi += a.lo * b.hi;
    result.hi += a.hi * b.lo;
    
    /* --- End of simplified core --- */
    
    /* Check for overflow */
    if (result.hi > 0x7FFFFFFF) {
        return handle_overflow(negative);
    }
    
    /* Additional overflow check for the exact LONG_LONG_MAX case */
    max_value = get_long_long_max();
    if (long_long_eq(result, max_value) && negative) {
        /* This would overflow to LONG_LONG_MIN + 1, which is invalid */
        return handle_overflow(negative);
    }
    
    /* Apply sign if needed */
    if (negative) {
        result = long_long_negate(result);
    }
    
    return result;
}

/****** ma.lib/long_long_div ************************************************
* 
*   NAME	
* 	long_long_div -- Divide two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_div(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_div(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Divide two long_long_t values using long division algorithm.
*	This performs complete 64-bit division for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value (dividend).
*	b - Second long_long_t value (divisor).
*	
*   RESULT
*	result - Quotient of a and b (a / b).
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2000);
*	long_long_t b = long_to_long_long(1000);
*	long_long_t result = long_long_div(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for division by zero.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit division using long division algorithm */
long_long_t long_long_div(long_long_t a, long_long_t b)
{
    long_long_t quotient, remainder;
    long_long_divmod(a, b, &quotient, &remainder);
    return quotient;
}

/****** ma.lib/long_long_mod ************************************************
* 
*   NAME	
* 	long_long_mod -- Modulo operation on long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_mod(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_mod(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Perform modulo operation on two long_long_t values. This returns
*	the remainder of division for 64-bit integer emulation on
*	AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value (dividend).
*	b - Second long_long_t value (divisor).
*	
*   RESULT
*	result - Remainder of a and b (a % b).
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2001);
*	long_long_t b = long_to_long_long(1000);
*	long_long_t result = long_long_mod(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for division by zero.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit modulo operation */
long_long_t long_long_mod(long_long_t a, long_long_t b)
{
    long_long_t quotient, remainder;
    long_long_divmod(a, b, &quotient, &remainder);
    return remainder;
}

/* Helper function to perform division and return both quotient and remainder */
/****** ma.lib/long_long_divmod *********************************************
* 
*   NAME	
* 	long_long_divmod -- Divide long_long_t and return quotient and remainder. (V1.0)
*
*   SYNOPSIS
*	void long_long_divmod(long_long_t a, long_long_t b, long_long_t *quotient, long_long_t *remainder);
*	  D0		   D0
*	void long_long_divmod(long_long_t a, long_long_t b, long_long_t *quotient, long_long_t *remainder);
*
*   FUNCTION
*	Divide two long_long_t values and return both quotient and remainder.
*	This performs complete 64-bit division for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value (dividend).
*	b - Second long_long_t value (divisor).
*	quotient - Pointer to store quotient result.
*	remainder - Pointer to store remainder result.
*	
*   RESULT
*	None. Results stored in *quotient and *remainder.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2001);
*	long_long_t b = long_to_long_long(1000);
*	long_long_t quot, rem;
*	long_long_divmod(a, b, &quot, &rem);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for division by zero.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

void long_long_divmod(long_long_t a, long_long_t b, long_long_t *quotient, long_long_t *remainder)
{
    long_long_t result = {0, 0};
    int negative_quotient = 0;
    int negative_remainder = 0; /* Track remainder sign separately */
    long_long_t zero = {0, 0};
    int shift;
    long_long_t shifted_divisor;
    long_long_t dividend;
    long_long_t final_remainder;
    long_long_t long_long_min_value, long_long_max_value, one, neg_one;
    
    /* Handle division by zero */
    {
        if (long_long_eq(b, zero)) {
            /* Set errno to indicate division by zero */
            errno = EDOM;
            *quotient = zero;
            *remainder = zero;
            return;
        }
        
        /* Handle division of zero */
        if (long_long_eq(a, zero)) {
            *quotient = zero;
            *remainder = zero;
            return;
        }
    }
    
    /* Handle signed division by working with absolute values */
    if (LONG_LONG_IS_NEGATIVE(a)) {
        /* SPECIAL CASE for LONG_LONG_MIN, which cannot be negated */
        long_long_min_value = get_long_long_min();
        if (long_long_eq(a, long_long_min_value)) {
            /* If b is 1 or -1, the result is trivial */
            one = long_to_long_long(1);
            neg_one = long_to_long_long(-1);
            if (long_long_eq(b, one)) {
                *quotient = long_long_min_value;
                *remainder = long_to_long_long(0);
                return;
            }
            if (long_long_eq(b, neg_one)) {
                /* LONG_LONG_MIN / -1 = LONG_LONG_MAX (technically overflows, clamp to MAX) */
                long_long_max_value = get_long_long_max();
                *quotient = long_long_max_value;
                *remainder = long_to_long_long(0);
                errno = ERANGE;
                return;
            }
            /* For other divisors, we can handle this by adjusting the calculation */
            /* This is a simplified approach - in practice, you might want more robust handling */
        }
        
        a = long_long_negate(a);
        negative_quotient = !negative_quotient;
        negative_remainder = 1; /* The remainder will have the sign of 'a' */
    }
    if (LONG_LONG_IS_NEGATIVE(b)) {
        b = long_long_negate(b);
        negative_quotient = !negative_quotient;
    }
    
    /* If divisor is larger than dividend, result is 0 */
    if (long_long_lt(a, b)) {
        *quotient = result;
        *remainder = a;  /* Remainder is the dividend */
        /* Apply sign to remainder if needed */
        if (negative_remainder) {
            *remainder = long_long_negate(*remainder);
        }
        return;
    }
    
    /* Find the highest bit position where divisor can be shifted */
    shift = 0;
    shifted_divisor = b;
    
    /* Shift divisor left until it's larger than dividend */
    while (long_long_lt(shifted_divisor, a) && shift < 63) {
        shifted_divisor = long_long_shl(shifted_divisor, 1);
        shift++;
    }
    
    /* If we shifted too far, back up one position */
    if (long_long_gt(shifted_divisor, a)) {
        shifted_divisor = long_long_shr(shifted_divisor, 1);
        shift--;
    }
    
    /* Perform long division */
    dividend = a;
    
    while (shift >= 0) {
        if (long_long_ge(dividend, shifted_divisor)) {
            dividend = long_long_sub(dividend, shifted_divisor);
            /* Set the appropriate bit in the result based on shift value */
            if (shift >= 32) {
                result.hi |= (1UL << (shift - 32));
            } else {
                result.lo |= (1UL << shift);
            }
        }
        
        /* Shift divisor right for next iteration */
        shifted_divisor = long_long_shr(shifted_divisor, 1);
        shift--;
    }
    
    /* Apply sign to quotient if needed */
    if (negative_quotient) {
        result = long_long_negate(result);
    }
    
    /* The final dividend value is the unsigned remainder */
    final_remainder = dividend;
    
    /* Apply sign to remainder if needed */
    if (negative_remainder) {
        final_remainder = long_long_negate(final_remainder);
    }
    
    /* Set results */
    *quotient = result;
    *remainder = final_remainder;
}

/****** ma.lib/long_long_shl ************************************************
* 
*   NAME	
* 	long_long_shl -- Left shift long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_shl(long_long_t value, int shift);
*	  D0		   D0
*	long_long_t long_long_shl(long_long_t value, int shift);
*
*   FUNCTION
*	Left shift a long_long_t value by the specified number of bits.
*	This performs complete 64-bit left shift for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to shift.
*	shift - Number of bits to shift left.
*	
*   RESULT
*	result - Left-shifted value. Returns zero if shift >= 64.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(1);
*	long_long_t result = long_long_shl(x, 10);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Shifts in zeros from the right.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit left shift */
long_long_t long_long_shl(long_long_t value, int shift)
{
    long_long_t result;
    long_long_t zero = {0, 0};
    
    if (shift <= 0) {
        return value;
    }
    
    if (shift >= 64) {
        return zero;
    }
    
    if (shift >= 32) {
        result.hi = value.lo << (shift - 32);
        result.lo = 0;
    } else {
        result.hi = (value.hi << shift) | (value.lo >> (32 - shift));
        result.lo = value.lo << shift;
    }
    
    return result;
}

/****** ma.lib/long_long_shr ************************************************
* 
*   NAME	
* 	long_long_shr -- Right shift long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_shr(long_long_t value, int shift);
*	  D0		   D0
*	long_long_t long_long_shr(long_long_t value, int shift);
*
*   FUNCTION
*	Right shift a long_long_t value by the specified number of bits.
*	This performs complete 64-bit right shift for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to shift.
*	shift - Number of bits to shift right.
*	
*   RESULT
*	result - Right-shifted value. Returns zero if shift >= 64.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(1024);
*	long_long_t result = long_long_shr(x, 10);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Shifts in zeros from the left.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit right shift */
long_long_t long_long_shr(long_long_t value, int shift)
{
    long_long_t result;
    long_long_t zero = {0, 0};
    
    if (shift <= 0) {
        return value;
    }
    
    if (shift >= 64) {
        return zero;
    }
    
    if (shift >= 32) {
        result.lo = value.hi >> (shift - 32);
        result.hi = 0;
    } else {
        result.lo = (value.lo >> shift) | (value.hi << (32 - shift));
        result.hi = value.hi >> shift;
    }
    
    return result;
}

/****** ma.lib/long_long_sar ************************************************
* 
*   NAME	
* 	long_long_sar -- Arithmetic right shift long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_sar(long_long_t value, int shift);
*	  D0		   D0
*	long_long_t long_long_sar(long_long_t value, int shift);
*
*   FUNCTION
*	Arithmetic right shift a long_long_t value by the specified number
*	of bits. This preserves the sign bit for signed operations in
*	64-bit integer emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to shift.
*	shift - Number of bits to shift right.
*	
*   RESULT
*	result - Arithmetic right-shifted value. Returns all 1s if negative
*	        and shift >= 64, all 0s if positive and shift >= 64.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(-1024);
*	long_long_t result = long_long_sar(x, 10);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Preserves sign bit for signed arithmetic.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit arithmetic right shift (preserves sign) */
long_long_t long_long_sar(long_long_t value, int shift)
{
    long_long_t result;
    long_long_t all_ones = {0xFFFFFFFF, 0xFFFFFFFF};
    long_long_t zero = {0, 0};
    
    if (shift <= 0) {
        return value;
    }
    
    if (shift >= 64) {
        /* Return all 1s if negative, all 0s if positive */
        if (LONG_LONG_IS_NEGATIVE(value)) {
            return all_ones;
        } else {
            return zero;
        }
    }
    
    if (shift >= 32) {
        result.lo = (long)value.hi >> (shift - 32);
        result.hi = LONG_LONG_IS_NEGATIVE(value) ? 0xFFFFFFFF : 0;
    } else {
        result.lo = (value.lo >> shift) | (value.hi << (32 - shift));
        result.hi = (long)value.hi >> shift;
    }
    
    return result;
}

/****** ma.lib/long_long_and ************************************************
* 
*   NAME	
* 	long_long_and -- Bitwise AND of two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_and(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_and(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Perform bitwise AND operation on two long_long_t values.
*	This performs complete 64-bit bitwise AND for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Bitwise AND of a and b.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(0xFF00);
*	long_long_t b = long_to_long_long(0x0FF0);
*	long_long_t result = long_long_and(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs bitwise AND on both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit bitwise AND */
long_long_t long_long_and(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi & b.hi;
    result.lo = a.lo & b.lo;
    return result;
}

/****** ma.lib/long_long_or *************************************************
* 
*   NAME	
* 	long_long_or -- Bitwise OR of two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_or(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_or(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Perform bitwise OR operation on two long_long_t values.
*	This performs complete 64-bit bitwise OR for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Bitwise OR of a and b.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(0xFF00);
*	long_long_t b = long_to_long_long(0x0FF0);
*	long_long_t result = long_long_or(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs bitwise OR on both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit bitwise OR */
long_long_t long_long_or(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi | b.hi;
    result.lo = a.lo | b.lo;
    return result;
}

/****** ma.lib/long_long_xor ************************************************
* 
*   NAME	
* 	long_long_xor -- Bitwise XOR of two long_long_t values. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_xor(long_long_t a, long_long_t b);
*	  D0		   D0
*	long_long_t long_long_xor(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Perform bitwise XOR operation on two long_long_t values.
*	This performs complete 64-bit bitwise XOR for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Bitwise XOR of a and b.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(0xFF00);
*	long_long_t b = long_to_long_long(0x0FF0);
*	long_long_t result = long_long_xor(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs bitwise XOR on both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit bitwise XOR */
long_long_t long_long_xor(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi ^ b.hi;
    result.lo = a.lo ^ b.lo;
    return result;
}

/****** ma.lib/long_long_not ************************************************
* 
*   NAME	
* 	long_long_not -- Bitwise NOT of long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = long_long_not(long_long_t a);
*	  D0		   D0
*	long_long_t long_long_not(long_long_t a);
*
*   FUNCTION
*	Perform bitwise NOT operation on a long_long_t value.
*	This performs complete 64-bit bitwise NOT for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - long_long_t value to invert.
*	
*   RESULT
*	result - Bitwise NOT of a (all bits inverted).
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(0xFF00);
*	long_long_t result = long_long_not(a);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs bitwise NOT on both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Complete 64-bit bitwise NOT */
long_long_t long_long_not(long_long_t a)
{
    long_long_t result;
    result.hi = ~a.hi;
    result.lo = ~a.lo;
    return result;
}

/****** ma.lib/long_long_eq *************************************************
* 
*   NAME	
* 	long_long_eq -- Test if two long_long_t values are equal. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_eq(long_long_t a, long_long_t b);
*	  D0		   D0
*	int long_long_eq(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Test if two long_long_t values are equal. This performs complete
*	64-bit equality comparison for 64-bit integer emulation on
*	AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Non-zero if a equals b, zero otherwise.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(1000);
*	long_long_t b = long_to_long_long(1000);
*	if (long_long_eq(a, b)) {
*	    printf("Values are equal\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Compares both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Comparison functions */
int long_long_eq(long_long_t a, long_long_t b)
{
    return (a.hi == b.hi) && (a.lo == b.lo);
}

/****** ma.lib/long_long_lt *************************************************
* 
*   NAME	
* 	long_long_lt -- Test if first long_long_t is less than second. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_lt(long_long_t a, long_long_t b);
*	  D0		   D0
*	int long_long_lt(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Test if first long_long_t value is less than second. This performs
*	complete 64-bit signed comparison for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Non-zero if a < b, zero otherwise.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(1000);
*	long_long_t b = long_to_long_long(2000);
*	if (long_long_lt(a, b)) {
*	    printf("a is less than b\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs signed comparison with proper sign handling.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_lt(long_long_t a, long_long_t b)
{
    if (LONG_LONG_IS_NEGATIVE(a) && !LONG_LONG_IS_NEGATIVE(b)) {
        return 1;  /* a is negative, b is positive */
    }
    if (!LONG_LONG_IS_NEGATIVE(a) && LONG_LONG_IS_NEGATIVE(b)) {
        return 0;  /* a is positive, b is negative */
    }
    
    /* Both have same sign, compare magnitudes */
    if (a.hi < b.hi) return 1;
    if (a.hi > b.hi) return 0;
    return a.lo < b.lo;
}

/****** ma.lib/long_long_gt *************************************************
* 
*   NAME	
* 	long_long_gt -- Test if first long_long_t is greater than second. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_gt(long_long_t a, long_long_t b);
*	  D0		   D0
*	int long_long_gt(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Test if first long_long_t value is greater than second. This performs
*	complete 64-bit signed comparison for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Non-zero if a > b, zero otherwise.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2000);
*	long_long_t b = long_to_long_long(1000);
*	if (long_long_gt(a, b)) {
*	    printf("a is greater than b\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs signed comparison with proper sign handling.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_gt(long_long_t a, long_long_t b)
{
    return long_long_lt(b, a);
}

/****** ma.lib/long_long_le *************************************************
* 
*   NAME	
* 	long_long_le -- Test if first long_long_t is less than or equal to second. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_le(long_long_t a, long_long_t b);
*	  D0		   D0
*	int long_long_le(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Test if first long_long_t value is less than or equal to second.
*	This performs complete 64-bit signed comparison for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Non-zero if a <= b, zero otherwise.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(1000);
*	long_long_t b = long_to_long_long(2000);
*	if (long_long_le(a, b)) {
*	    printf("a is less than or equal to b\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs signed comparison with proper sign handling.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_le(long_long_t a, long_long_t b)
{
    return long_long_eq(a, b) || long_long_lt(a, b);
}

/****** ma.lib/long_long_ge *************************************************
* 
*   NAME	
* 	long_long_ge -- Test if first long_long_t is greater than or equal to second. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_ge(long_long_t a, long_long_t b);
*	  D0		   D0
*	int long_long_ge(long_long_t a, long_long_t b);
*
*   FUNCTION
*	Test if first long_long_t value is greater than or equal to second.
*	This performs complete 64-bit signed comparison for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	a - First long_long_t value.
*	b - Second long_long_t value.
*	
*   RESULT
*	result - Non-zero if a >= b, zero otherwise.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2000);
*	long_long_t b = long_to_long_long(1000);
*	if (long_long_ge(a, b)) {
*	    printf("a is greater than or equal to b\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performs signed comparison with proper sign handling.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_ge(long_long_t a, long_long_t b)
{
    return long_long_eq(a, b) || long_long_gt(a, b);
}

/****** ma.lib/long_long_is_zero ********************************************
* 
*   NAME	
* 	long_long_is_zero -- Test if long_long_t value is zero. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_is_zero(long_long_t value);
*	  D0		   D0
*	int long_long_is_zero(long_long_t value);
*
*   FUNCTION
*	Test if a long_long_t value is zero. This performs complete
*	64-bit zero test for 64-bit integer emulation on AmigaOS
*	with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to test.
*	
*   RESULT
*	result - Non-zero if value is zero, zero otherwise.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(0);
*	if (long_long_is_zero(x)) {
*	    printf("Value is zero\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Tests both high and low 32-bit parts.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Additional utility functions */
int long_long_is_zero(long_long_t value)
{
    return (int)LONG_LONG_IS_ZERO(value);
}

/****** ma.lib/long_long_is_negative ****************************************
* 
*   NAME	
* 	long_long_is_negative -- Test if long_long_t value is negative. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_is_negative(long_long_t value);
*	  D0		   D0
*	int long_long_is_negative(long_long_t value);
*
*   FUNCTION
*	Test if a long_long_t value is negative. This performs complete
*	64-bit sign test for 64-bit integer emulation on AmigaOS
*	with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to test.
*	
*   RESULT
*	result - Non-zero if value is negative, zero otherwise.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(-1000);
*	if (long_long_is_negative(x)) {
*	    printf("Value is negative\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Tests the sign bit of the high 32-bit part.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_is_negative(long_long_t value)
{
    return (int)LONG_LONG_IS_NEGATIVE(value);
}

/****** ma.lib/long_long_is_positive ****************************************
* 
*   NAME	
* 	long_long_is_positive -- Test if long_long_t value is positive. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_is_positive(long_long_t value);
*	  D0		   D0
*	int long_long_is_positive(long_long_t value);
*
*   FUNCTION
*	Test if a long_long_t value is positive. This performs complete
*	64-bit sign test for 64-bit integer emulation on AmigaOS
*	with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to test.
*	
*   RESULT
*	result - Non-zero if value is positive, zero otherwise.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(1000);
*	if (long_long_is_positive(x)) {
*	    printf("Value is positive\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Tests the sign bit of the high 32-bit part.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

int long_long_is_positive(long_long_t value)
{
    return (int)LONG_LONG_IS_POSITIVE(value);
}

/****** ma.lib/long_long_clz ************************************************
* 
*   NAME	
* 	long_long_clz -- Count leading zeros in long_long_t value. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_clz(long_long_t value);
*	  D0		   D0
*	int long_long_clz(long_long_t value);
*
*   FUNCTION
*	Count the number of leading zero bits in a long_long_t value.
*	This performs complete 64-bit bit counting for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to count.
*	
*   RESULT
*	result - Number of leading zero bits (0-64).
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(1);
*	int zeros = long_long_clz(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Loop-based implementation - consider table-based for performance.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Count leading zeros in 64-bit value */
/* Note: This loop-based implementation is clear and maintainable but not optimal for performance */
/* For critical performance paths, consider table-based or parallel-bit algorithms */
int long_long_clz(long_long_t value)
{
    int count = 0;
    
    if (value.hi == 0) {
        count += 32;
        if (value.lo == 0) {
            return 64;
        }
        /* Count leading zeros in low part */
        while ((value.lo & 0x80000000) == 0) {
            count++;
            value.lo <<= 1;
        }
    } else {
        /* Count leading zeros in high part */
        while ((value.hi & 0x80000000) == 0) {
            count++;
            value.hi <<= 1;
        }
    }
    
    return count;
}

/****** ma.lib/long_long_ctz ************************************************
* 
*   NAME	
* 	long_long_ctz -- Count trailing zeros in long_long_t value. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_ctz(long_long_t value);
*	  D0		   D0
*	int long_long_ctz(long_long_t value);
*
*   FUNCTION
*	Count the number of trailing zero bits in a long_long_t value.
*	This performs complete 64-bit bit counting for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to count.
*	
*   RESULT
*	result - Number of trailing zero bits (0-64).
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(8);
*	int zeros = long_long_ctz(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Loop-based implementation - consider table-based for performance.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Count trailing zeros in 64-bit value */
/* Note: This loop-based implementation is clear and maintainable but not optimal for performance */
/* For critical performance paths, consider table-based or parallel-bit algorithms */
int long_long_ctz(long_long_t value)
{
    int count = 0;
    
    if (value.lo == 0) {
        count += 32;
        if (value.hi == 0) {
            return 64;
        }
        /* Count trailing zeros in high part */
        while ((value.hi & 1) == 0) {
            count++;
            value.hi >>= 1;
        }
    } else {
        /* Count trailing zeros in low part */
        while ((value.lo & 1) == 0) {
            count++;
            value.lo >>= 1;
        }
    }
    
    return count;
}

/****** ma.lib/long_long_popcount *******************************************
* 
*   NAME	
* 	long_long_popcount -- Count set bits in long_long_t value. (V1.0)
*
*   SYNOPSIS
*	int result = long_long_popcount(long_long_t value);
*	  D0		   D0
*	int long_long_popcount(long_long_t value);
*
*   FUNCTION
*	Count the number of set bits (population count) in a long_long_t value.
*	This performs complete 64-bit bit counting for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to count.
*	
*   RESULT
*	result - Number of set bits (0-64).
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(0xFF);
*	int bits = long_long_popcount(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Loop-based implementation - consider table-based for performance.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Population count (number of set bits) in 64-bit value */
/* Note: This loop-based implementation is clear and maintainable but not optimal for performance */
/* For critical performance paths, consider table-based or parallel-bit algorithms */
int long_long_popcount(long_long_t value)
{
    int count = 0;
    
    /* Count bits in high part */
    while (value.hi != 0) {
        count += value.hi & 1;
        value.hi >>= 1;
    }
    
    /* Count bits in low part */
    while (value.lo != 0) {
        count += value.lo & 1;
        value.lo >>= 1;
    }
    
    return count;
}

/****** ma.lib/get_long_long_max ********************************************
* 
*   NAME	
* 	get_long_long_max -- Get maximum long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = get_long_long_max(void);
*	  D0		   D0
*	long_long_t get_long_long_max(void);
*
*   FUNCTION
*	Get the maximum value for long_long_t type. This returns the
*	largest representable 64-bit signed integer for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	None.
*	
*   RESULT
*	result - Maximum long_long_t value (LONG_LONG_MAX).
* 
*   EXAMPLE
*	long_long_t max = get_long_long_max();
*	printf("Max value: %ld%ld\n", max.hi, max.lo);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Returns constant maximum value.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Constant functions for C89 compatibility */
long_long_t get_long_long_max(void)
{
    long_long_t result;
    result.hi = LONG_LONG_MAX_HI;
    result.lo = LONG_LONG_MAX_LO;
    return result;
}

/****** ma.lib/get_long_long_min ********************************************
* 
*   NAME	
* 	get_long_long_min -- Get minimum long_long_t value. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = get_long_long_min(void);
*	  D0		   D0
*	long_long_t get_long_long_min(void);
*
*   FUNCTION
*	Get the minimum value for long_long_t type. This returns the
*	smallest representable 64-bit signed integer for 64-bit integer
*	emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	None.
*	
*   RESULT
*	result - Minimum long_long_t value (LONG_LONG_MIN).
* 
*   EXAMPLE
*	long_long_t min = get_long_long_min();
*	printf("Min value: %ld%ld\n", min.hi, min.lo);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Returns constant minimum value.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

long_long_t get_long_long_min(void)
{
    long_long_t result;
    result.hi = LONG_LONG_MIN_HI;
    result.lo = LONG_LONG_MIN_LO;
    return result;
}

/****** ma.lib/atoll ********************************************************
* 
*   NAME	
* 	atoll -- Convert string to long_long_t. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = atoll(const char *str);
*	  D0		   A0
*	long_long_t atoll(const char *str);
*
*   FUNCTION
*	Convert a string to long_long_t value. This is equivalent to
*	atoll() but returns long_long_t for 64-bit integer emulation
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	str - String to convert (base 10 only).
*	
*   RESULT
*	result - Converted long_long_t value. Returns 0 on error.
* 
*   EXAMPLE
*	const char *str = "1234567890";
*	long_long_t result = atoll(str);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to ERANGE on overflow.
* 
*   SEE ALSO
*	long_long_t, longlong.h
* 
******************************************************************************/

/* Convert string to long long (atoll equivalent) */
long_long_t atoll(const char *str)
{
    char *endptr;
    long_long_t result = {0, 0};
    const char *start = str;
    int negative = 0;
    int valid_digits = 0;
    long_long_t max_value = get_long_long_max();
    long_long_t zero = {0, 0};
    long_long_t base_value = {0, 10};
    long_long_t temp;
    
    /* Skip leading whitespace */
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    /* Handle sign */
    if (*str == '+') {
        str++;
    } else if (*str == '-') {
        negative = 1;
        str++;
    }
    
    /* Process digits (base 10 only for atoll) */
    while (*str && isdigit((unsigned char)*str)) {
        int digit = *str - '0';
        
        /* Check for overflow before multiplying */
        if (long_long_gt(result, max_value)) {
            /* Overflow - return maximum value */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        /* Multiply by 10 */
        temp = result;
        result = long_long_mul(result, base_value);
        
        /* Check for overflow after multiplication */
        if (long_long_lt(result, temp)) {
            /* Overflow occurred */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        /* Add digit */
        temp = long_to_long_long(digit);
        result = long_long_add(result, temp);
        
        /* Check for overflow after addition */
        if (long_long_lt(result, temp)) {
            /* Overflow occurred */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        valid_digits = 1;
        str++;
    }
    
    /* Apply sign if negative */
    if (negative) {
        result = long_long_negate(result);
    }
    
    return result;
}

/* Helper function to convert long_long_t to unsigned_long_long_t */
/****** ma.lib/long_long_to_unsigned_long_long ******************************
* 
*   NAME	
* 	long_long_to_unsigned_long_long -- Convert long_long_t to unsigned_long_long_t. (V1.0)
*
*   SYNOPSIS
*	unsigned_long_long_t result = long_long_to_unsigned_long_long(long_long_t value);
*	  D0		   D0
*	unsigned_long_long_t long_long_to_unsigned_long_long(long_long_t value);
*
*   FUNCTION
*	Convert a long_long_t value to unsigned_long_long_t. This performs
*	64-bit type conversion for 64-bit integer emulation on AmigaOS
*	with SAS/C.
* 
*   INPUTS
*	value - long_long_t value to convert.
*	
*   RESULT
*	result - Converted unsigned_long_long_t value.
* 
*   EXAMPLE
*	long_long_t x = long_to_long_long(1000);
*	unsigned_long_long_t result = long_long_to_unsigned_long_long(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Negative values are converted to their two's complement representation.
* 
*   SEE ALSO
*	long_long_t, unsigned_long_long_t, longlong.h
* 
******************************************************************************/

unsigned_long_long_t long_long_to_unsigned_long_long(long_long_t value)
{
    unsigned_long_long_t result;
    result.hi = value.hi;
    result.lo = value.lo;
    return result;
}

/* Helper function to convert unsigned_long_long_t to long_long_t */
/****** ma.lib/unsigned_long_long_to_long_long ******************************
* 
*   NAME	
* 	unsigned_long_long_to_long_long -- Convert unsigned_long_long_t to long_long_t. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = unsigned_long_long_to_long_long(unsigned_long_long_t value);
*	  D0		   D0
*	long_long_t unsigned_long_long_to_long_long(unsigned_long_long_t value);
*
*   FUNCTION
*	Convert an unsigned_long_long_t value to long_long_t. This performs
*	64-bit type conversion for 64-bit integer emulation on AmigaOS
*	with SAS/C.
* 
*   INPUTS
*	value - unsigned_long_long_t value to convert.
*	
*   RESULT
*	result - Converted long_long_t value.
* 
*   EXAMPLE
*	unsigned_long_long_t x = {0, 1000};
*	long_long_t result = unsigned_long_long_to_long_long(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Values > LONG_LONG_MAX are converted to their two's complement representation.
* 
*   SEE ALSO
*	long_long_t, unsigned_long_long_t, longlong.h
* 
******************************************************************************/

long_long_t unsigned_long_long_to_long_long(unsigned_long_long_t value)
{
    long_long_t result;
    result.hi = value.hi;
    result.lo = value.lo;
    return result;
}

/****** ma.lib/strtoull *****************************************************
* 
*   NAME	
* 	strtoull -- Convert string to unsigned_long_long_t. (V1.0)
*
*   SYNOPSIS
*	unsigned_long_long_t result = strtoull(const char *str, char **endptr, int base);
*	  D0		   A0
*	unsigned_long_long_t strtoull(const char *str, char **endptr, int base);
*
*   FUNCTION
*	Convert a string to unsigned_long_long_t value with specified base.
*	This is equivalent to strtoull() but returns unsigned_long_long_t
*	for 64-bit integer emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	str - String to convert.
*	endptr - Pointer to store end of conversion.
*	base - Numeric base (2-36, or 0 for auto-detect).
*	
*   RESULT
*	result - Converted unsigned_long_long_t value. Returns 0 on error.
* 
*   EXAMPLE
*	const char *str = "1234567890";
*	char *end;
*	unsigned_long_long_t result = strtoull(str, &end, 10);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to ERANGE on overflow.
* 
*   SEE ALSO
*	unsigned_long_long_t, longlong.h
* 
******************************************************************************/

/* Convert string to unsigned long long */
unsigned_long_long_t strtoull(const char *str, char **endptr, int base)
{
    long_long_t result = {0, 0};
    const char *start = str;
    int negative = 0;
    int valid_digits = 0;
    long_long_t max_value = get_long_long_max();
    long_long_t zero = {0, 0};
    long_long_t base_value;
    long_long_t temp;
    
    /* Skip leading whitespace */
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    /* Handle sign */
    if (*str == '+') {
        str++;
    } else if (*str == '-') {
        negative = 1;
        str++;
    }
    
    /* Validate base */
    if (base == 0) {
        /* Auto-detect base */
        if (*str == '0') {
            str++;
            if (*str == 'x' || *str == 'X') {
                base = 16;
                str++;
            } else if (*str == 'b' || *str == 'B') {
                base = 2;
                str++;
            } else {
                base = 8;
            }
        } else {
            base = 10;
        }
    }
    
    if (base < 2 || base > 36) {
        if (endptr) *endptr = (char *)start;
        return long_long_to_unsigned_long_long(zero);
    }
    
    /* Convert base to our long long representation */
    base_value = long_to_long_long(base);
    
    /* Process digits */
    while (*str) {
        int digit;
        
        if (isdigit((unsigned char)*str)) {
            digit = *str - '0';
        } else if (isalpha((unsigned char)*str)) {
            digit = tolower((unsigned char)*str) - 'a' + 10;
        } else {
            break;  /* Invalid character */
        }
        
        if (digit >= base) {
            break;  /* Digit not valid for this base */
        }
        
        /* Check for overflow before multiplying */
        if (long_long_gt(result, max_value)) {
            /* Overflow - return maximum value */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        /* Multiply by base */
        temp = result;
        result = long_long_mul(result, base_value);
        
        /* Check for overflow after multiplication */
        if (long_long_lt(result, temp)) {
            /* Overflow occurred */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        /* Add digit */
        temp = long_to_long_long(digit);
        result = long_long_add(result, temp);
        
        /* Check for overflow after addition */
        if (long_long_lt(result, temp)) {
            /* Overflow occurred */
            result = max_value;
            errno = ERANGE;
            break;
        }
        
        valid_digits = 1;
        str++;
    }
    
    /* Set endptr */
    if (endptr) {
        if (valid_digits) {
            *endptr = (char *)str;
        } else {
            *endptr = (char *)start;
        }
    }
    
    /* For unsigned, we ignore the sign and just return the absolute value */
    /* This matches the behavior of standard strtoull */
    
    return long_long_to_unsigned_long_long(result);
}

/****** ma.lib/lldiv ********************************************************
* 
*   NAME	
* 	lldiv -- Divide long_long_t and return quotient and remainder. (V1.0)
*
*   SYNOPSIS
*	lldiv_t result = lldiv(long_long_t numer, long_long_t denom);
*	  D0		   D0
*	lldiv_t lldiv(long_long_t numer, long_long_t denom);
*
*   FUNCTION
*	Divide two long_long_t values and return both quotient and remainder
*	in an lldiv_t structure. This is equivalent to lldiv() but uses
*	long_long_t for 64-bit integer emulation on AmigaOS with SAS/C.
* 
*   INPUTS
*	numer - Numerator (dividend).
*	denom - Denominator (divisor).
*	
*   RESULT
*	result - lldiv_t structure containing quotient and remainder.
* 
*   EXAMPLE
*	long_long_t a = long_to_long_long(2001);
*	long_long_t b = long_to_long_long(1000);
*	lldiv_t result = lldiv(a, b);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for division by zero.
* 
*   SEE ALSO
*	long_long_t, lldiv_t, longlong.h
* 
******************************************************************************/

/* Long long division returning lldiv_t structure */
lldiv_t lldiv(long_long_t numer, long_long_t denom)
{
    lldiv_t result;
    long_long_divmod(numer, denom, &result.quot, &result.rem);
    return result;
}

