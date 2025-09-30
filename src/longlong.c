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

/* Conversion functions */
long long_long_to_long(long_long_t value)
{
    /* Truncating conversion: returns only the low 32 bits */
    /* WARNING: This can cause data loss if value.hi != 0 */
    return (long)value.lo;
}

unsigned long long_long_to_ulong(long_long_t value)
{
    /* Truncating conversion: returns only the low 32 bits */
    /* WARNING: This can cause data loss if value.hi != 0 */
    return value.lo;
}

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

/* Complete 64-bit division using long division algorithm */
long_long_t long_long_div(long_long_t a, long_long_t b)
{
    long_long_t quotient, remainder;
    long_long_divmod(a, b, &quotient, &remainder);
    return quotient;
}

/* Complete 64-bit modulo operation */
long_long_t long_long_mod(long_long_t a, long_long_t b)
{
    long_long_t quotient, remainder;
    long_long_divmod(a, b, &quotient, &remainder);
    return remainder;
}

/* Helper function to perform division and return both quotient and remainder */
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

/* Complete 64-bit bitwise AND */
long_long_t long_long_and(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi & b.hi;
    result.lo = a.lo & b.lo;
    return result;
}

/* Complete 64-bit bitwise OR */
long_long_t long_long_or(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi | b.hi;
    result.lo = a.lo | b.lo;
    return result;
}

/* Complete 64-bit bitwise XOR */
long_long_t long_long_xor(long_long_t a, long_long_t b)
{
    long_long_t result;
    result.hi = a.hi ^ b.hi;
    result.lo = a.lo ^ b.lo;
    return result;
}

/* Complete 64-bit bitwise NOT */
long_long_t long_long_not(long_long_t a)
{
    long_long_t result;
    result.hi = ~a.hi;
    result.lo = ~a.lo;
    return result;
}

/* Comparison functions */
int long_long_eq(long_long_t a, long_long_t b)
{
    return (a.hi == b.hi) && (a.lo == b.lo);
}

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

int long_long_gt(long_long_t a, long_long_t b)
{
    return long_long_lt(b, a);
}

int long_long_le(long_long_t a, long_long_t b)
{
    return long_long_eq(a, b) || long_long_lt(a, b);
}

int long_long_ge(long_long_t a, long_long_t b)
{
    return long_long_eq(a, b) || long_long_gt(a, b);
}

/* Additional utility functions */
int long_long_is_zero(long_long_t value)
{
    return (int)LONG_LONG_IS_ZERO(value);
}

int long_long_is_negative(long_long_t value)
{
    return (int)LONG_LONG_IS_NEGATIVE(value);
}

int long_long_is_positive(long_long_t value)
{
    return (int)LONG_LONG_IS_POSITIVE(value);
}

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

/* Constant functions for C89 compatibility */
long_long_t get_long_long_max(void)
{
    long_long_t result;
    result.hi = LONG_LONG_MAX_HI;
    result.lo = LONG_LONG_MAX_LO;
    return result;
}

long_long_t get_long_long_min(void)
{
    long_long_t result;
    result.hi = LONG_LONG_MIN_HI;
    result.lo = LONG_LONG_MIN_LO;
    return result;
}

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
unsigned_long_long_t long_long_to_unsigned_long_long(long_long_t value)
{
    unsigned_long_long_t result;
    result.hi = value.hi;
    result.lo = value.lo;
    return result;
}

/* Helper function to convert unsigned_long_long_t to long_long_t */
long_long_t unsigned_long_long_to_long_long(unsigned_long_long_t value)
{
    long_long_t result;
    result.hi = value.hi;
    result.lo = value.lo;
    return result;
}

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

/* Long long division returning lldiv_t structure */
lldiv_t lldiv(long_long_t numer, long_long_t denom)
{
    lldiv_t result;
    long_long_divmod(numer, denom, &result.quot, &result.rem);
    return result;
}
