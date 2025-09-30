#ifndef LONG_LONG_H
#define LONG_LONG_H

/*
 * Long long emulation for AmigaOS with SAS/C.
 * This header provides a struct-based 64-bit integer type
 * for systems that don't natively support long long.
 */

#include <limits.h>

/* Define a struct-based long long type for SAS/C compatibility */
typedef struct {
    unsigned long hi;  /* High 32 bits */
    unsigned long lo;  /* Low 32 bits */
} long_long_t;

/* Define unsigned version for uint64_t compatibility */
typedef struct {
    unsigned long hi;  /* High 32 bits */
    unsigned long lo;  /* Low 32 bits */
} unsigned_long_long_t;

/* lldiv_t structure for long long division results */
typedef struct {
    long_long_t quot;  /* Quotient */
    long_long_t rem;   /* Remainder */
} lldiv_t;

/* Constants for the emulated long long type */
#define LONG_LONG_MAX_HI 0x7FFFFFFF
#define LONG_LONG_MAX_LO 0xFFFFFFFF
#define LONG_LONG_MIN_HI 0x80000000
#define LONG_LONG_MIN_LO 0x00000000

/* Complete 64-bit constants for external use */
/* Note: C89 doesn't support compound literals, so we use functions */
long_long_t get_long_long_max(void);
long_long_t get_long_long_min(void);

/* Helper macros for working with long_long_t */
#define LONG_LONG_IS_NEGATIVE(x) ((x).hi & 0x80000000)
#define LONG_LONG_IS_ZERO(x) ((x).hi == 0 && (x).lo == 0)
#define LONG_LONG_IS_POSITIVE(x) (!LONG_LONG_IS_NEGATIVE(x) && !LONG_LONG_IS_ZERO(x))

/* Basic function prototypes */
long_long_t long_to_long_long(long value);
long_long_t handle_overflow(int negative);
long_long_t long_long_negate(long_long_t value);
long_long_t get_long_long_max(void);
long_long_t get_long_long_min(void);

/* String conversion functions */
long_long_t strtoll(const char *str, char **endptr, int base);
long_long_t atoll(const char *str);
unsigned_long_long_t strtoull(const char *str, char **endptr, int base);

/* Conversion functions */
long long_long_to_long(long_long_t value);
unsigned long long_long_to_ulong(long_long_t value);

/* Complete arithmetic operations */
long_long_t long_long_add(long_long_t a, long_long_t b);
long_long_t long_long_sub(long_long_t a, long_long_t b);
long_long_t long_long_mul(long_long_t a, long_long_t b);
long_long_t long_long_div(long_long_t a, long_long_t b);
long_long_t long_long_mod(long_long_t a, long_long_t b);
void long_long_divmod(long_long_t a, long_long_t b, long_long_t *quotient, long_long_t *remainder);

/* Bitwise shift operations */
long_long_t long_long_shl(long_long_t value, int shift);
long_long_t long_long_shr(long_long_t value, int shift);
long_long_t long_long_sar(long_long_t value, int shift);

/* Bitwise logical operations */
long_long_t long_long_and(long_long_t a, long_long_t b);
long_long_t long_long_or(long_long_t a, long_long_t b);
long_long_t long_long_xor(long_long_t a, long_long_t b);
long_long_t long_long_not(long_long_t a);

/* Comparison functions */
int long_long_eq(long_long_t a, long_long_t b);
int long_long_lt(long_long_t a, long_long_t b);
int long_long_gt(long_long_t a, long_long_t b);
int long_long_le(long_long_t a, long_long_t b);
int long_long_ge(long_long_t a, long_long_t b);

/* Utility functions */
int long_long_is_zero(long_long_t value);
int long_long_is_negative(long_long_t value);
int long_long_is_positive(long_long_t value);
int long_long_clz(long_long_t value);
int long_long_ctz(long_long_t value);
int long_long_popcount(long_long_t value);

/* Division function */
lldiv_t lldiv(long_long_t numer, long_long_t denom);

#endif /* LONG_LONG_H */
