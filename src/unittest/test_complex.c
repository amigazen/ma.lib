/*
 * Unit tests for complex.h functions
 * 
 * This file tests all complex number functions in m99.lib
 * It is written in pure ANSI C89 for SAS/C compatibility
 */

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/* Test case counters */
static int tests_run = 0;
static int tests_failed = 0;

/* Function prototypes */
void assert_test(const char* test_name, int condition, const char* file, int line);
void test_complex_creation(void);
void test_complex_arithmetic(void);
void test_cabs(void);
void test_carg(void);
void test_conj(void);
void test_cexp(void);
void test_clog(void);
void test_csqrt(void);
void test_csin(void);
void test_ccos(void);
void test_ctan(void);
void test_csinh(void);
void test_ccosh(void);
void test_ctanh(void);
void test_casin(void);
void test_cacos(void);
void test_catan(void);
void test_casinh(void);
void test_cacosh(void);
void test_catanh(void);
void test_cpow(void);
int complex_approx_equal(complex_t a, complex_t b, double tolerance);
int double_approx_equal(double a, double b, double tolerance);

/* Complex arithmetic function prototypes */
complex_t cadd(complex_t a, complex_t b);
complex_t csub(complex_t a, complex_t b);
complex_t cmul(complex_t a, complex_t b);
complex_t cdiv(complex_t a, complex_t b);

/* Simple assertion function */
void assert_test(const char* test_name, int condition, const char* file, int line) {
    tests_run++;
    if (!condition) {
        printf("[FAIL] %s:%d: %s failed\n", file, line, test_name);
        tests_failed++;
    } else {
        printf("[PASS] %s:%d: %s passed\n", file, line, test_name);
    }
}

#define ASSERT(condition) assert_test(#condition, (condition), __FILE__, __LINE__)

/* Helper function to check if two complex numbers are approximately equal */
int complex_approx_equal(complex_t a, complex_t b, double tolerance) {
    double real_diff = fabs(creal(a) - creal(b));
    double imag_diff = fabs(cimag(a) - cimag(b));
    return (real_diff < tolerance) && (imag_diff < tolerance);
}

/* Helper function to check if two doubles are approximately equal */
int double_approx_equal(double a, double b, double tolerance) {
    return fabs(a - b) < tolerance;
}

void test_complex_creation() {
    complex_t z1, z2, z3;
    
    printf("\n--- Testing Complex Number Creation ---\n");
    
    z1.re = 3.0; z1.im = 4.0;
    z2.re = 1.0; z2.im = 2.0;
    z3.re = 0.0; z3.im = 0.0;
    
    ASSERT(creal(z1) == 3.0);
    ASSERT(cimag(z1) == 4.0);
    ASSERT(creal(z2) == 1.0);
    ASSERT(cimag(z2) == 2.0);
    ASSERT(creal(z3) == 0.0);
    ASSERT(cimag(z3) == 0.0);
}

void test_complex_arithmetic() {
    complex_t z1, z2, z3, z4;
    complex_t sum, diff, prod, quot;
    complex_t expected_sum, expected_diff, expected_prod, expected_quot;
    
    printf("\n--- Testing Complex Arithmetic ---\n");
    
    z1.re = 3.0; z1.im = 4.0;
    z2.re = 1.0; z2.im = 2.0;
    z3.re = 0.0; z3.im = 0.0;
    z4.re = 1.0; z4.im = 0.0;
    
    sum = cadd(z1, z2);
    diff = csub(z1, z2);
    prod = cmul(z1, z2);
    quot = cdiv(z1, z2);
    
    expected_sum.re = 4.0; expected_sum.im = 6.0;
    expected_diff.re = 2.0; expected_diff.im = 2.0;
    expected_prod.re = -5.0; expected_prod.im = 10.0;
    expected_quot.re = 2.2; expected_quot.im = -0.4;
    
    ASSERT(complex_approx_equal(sum, expected_sum, 1e-10));
    ASSERT(complex_approx_equal(diff, expected_diff, 1e-10));
    ASSERT(complex_approx_equal(prod, expected_prod, 1e-10));
    ASSERT(complex_approx_equal(quot, expected_quot, 1e-10));
}

void test_cabs() {
    complex_t z1, z2, z3, z4;
    double abs1, abs2, abs3, abs4;
    
    printf("\n--- Testing cabs function ---\n");
    
    z1.re = 3.0; z1.im = 4.0;
    z2.re = 0.0; z2.im = 5.0;
    z3.re = 0.0; z3.im = 0.0;
    z4.re = -3.0; z4.im = -4.0;
    
    abs1 = cabs(z1);
    abs2 = cabs(z2);
    abs3 = cabs(z3);
    abs4 = cabs(z4);
    
    ASSERT(double_approx_equal(abs1, 5.0, 1e-10));
    ASSERT(double_approx_equal(abs2, 5.0, 1e-10));
    ASSERT(double_approx_equal(abs3, 0.0, 1e-10));
    ASSERT(double_approx_equal(abs4, 5.0, 1e-10));
}

void test_carg() {
    complex_t z1, z2, z3, z4, z5;
    double arg1, arg2, arg3, arg4, arg5;
    
    printf("\n--- Testing carg function ---\n");
    
    z1.re = 1.0; z1.im = 0.0;
    z2.re = 0.0; z2.im = 1.0;
    z3.re = -1.0; z3.im = 0.0;
    z4.re = 0.0; z4.im = -1.0;
    z5.re = 1.0; z5.im = 1.0;
    
    arg1 = carg(z1);
    arg2 = carg(z2);
    arg3 = carg(z3);
    arg4 = carg(z4);
    arg5 = carg(z5);
    
    ASSERT(double_approx_equal(arg1, 0.0, 1e-10));
    ASSERT(double_approx_equal(arg2, M_PI/2.0, 1e-10));
    ASSERT(double_approx_equal(arg3, M_PI, 1e-10));
    ASSERT(double_approx_equal(arg4, -M_PI/2.0, 1e-10));
    ASSERT(double_approx_equal(arg5, M_PI/4.0, 1e-10));
}

void test_conj() {
    complex_t z1, z2, z3, z4;
    complex_t conj1, conj2, conj3, conj4;
    complex_t expected1, expected2, expected3, expected4;
    
    printf("\n--- Testing conj ---\n");
    
    z1.re = 3.0; z1.im = 4.0;
    z2.re = 1.0; z2.im = -2.0;
    z3.re = 5.0; z3.im = 0.0;
    z4.re = 0.0; z4.im = 3.0;
    
    conj1 = conj(z1);
    conj2 = conj(z2);
    conj3 = conj(z3);
    conj4 = conj(z4);
    
    expected1.re = 3.0; expected1.im = -4.0;
    expected2.re = 1.0; expected2.im = 2.0;
    expected3.re = 5.0; expected3.im = -0.0;
    expected4.re = 0.0; expected4.im = -3.0;
    
    ASSERT(complex_approx_equal(conj1, expected1, 1e-10));
    ASSERT(complex_approx_equal(conj2, expected2, 1e-10));
    ASSERT(complex_approx_equal(conj3, expected3, 1e-10));
    ASSERT(complex_approx_equal(conj4, expected4, 1e-10));
}

void test_cexp() {
    complex_t z1, z2, z3, z4;
    complex_t exp1, exp2, exp3, exp4;
    complex_t expected1, expected2, expected3, expected4;
    
    printf("\n--- Testing cexp ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = M_PI/2.0;
    z4.re = 1.0; z4.im = M_PI/2.0;
    
    exp1 = cexp(z1);
    exp2 = cexp(z2);
    exp3 = cexp(z3);
    exp4 = cexp(z4);
    
    expected1.re = 1.0; expected1.im = 0.0;
    expected2.re = M_E; expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = 1.0;
    expected4.re = 0.0; expected4.im = M_E;
    
    ASSERT(complex_approx_equal(exp1, expected1, 1e-10));
    ASSERT(complex_approx_equal(exp2, expected2, 1e-10));
    ASSERT(complex_approx_equal(exp3, expected3, 1e-10));
    ASSERT(complex_approx_equal(exp4, expected4, 1e-10));
}

void test_clog() {
    complex_t z1, z2, z3, z4;
    complex_t log1, log2, log3, log4;
    complex_t expected1, expected2, expected3, expected4;
    
    printf("\n--- Testing clog ---\n");
    
    z1.re = 1.0; z1.im = 0.0;
    z2.re = M_E; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    z4.re = 0.0; z4.im = M_E;
    
    log1 = clog(z1);
    log2 = clog(z2);
    log3 = clog(z3);
    log4 = clog(z4);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = 1.0; expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = M_PI/2.0;
    expected4.re = 1.0; expected4.im = M_PI/2.0;
    
    ASSERT(complex_approx_equal(log1, expected1, 1e-10));
    ASSERT(complex_approx_equal(log2, expected2, 1e-10));
    ASSERT(complex_approx_equal(log3, expected3, 1e-10));
    ASSERT(complex_approx_equal(log4, expected4, 1e-10));
}

void test_csqrt() {
    complex_t z1, z2, z3, z4;
    complex_t sqrt1, sqrt2, sqrt3, sqrt4;
    complex_t expected1, expected2, expected3, expected4;
    
    printf("\n--- Testing csqrt ---\n");
    
    z1.re = 4.0; z1.im = 0.0;
    z2.re = 0.0; z2.im = 4.0;
    z3.re = 1.0; z3.im = 0.0;
    z4.re = 0.0; z4.im = 0.0;
    
    sqrt1 = csqrt(z1);
    sqrt2 = csqrt(z2);
    sqrt3 = csqrt(z3);
    sqrt4 = csqrt(z4);
    
    expected1.re = 2.0; expected1.im = 0.0;
    expected2.re = sqrt(2.0); expected2.im = sqrt(2.0);
    expected3.re = 1.0; expected3.im = 0.0;
    expected4.re = 0.0; expected4.im = 0.0;
    
    ASSERT(complex_approx_equal(sqrt1, expected1, 1e-10));
    ASSERT(complex_approx_equal(sqrt2, expected2, 1e-10));
    ASSERT(complex_approx_equal(sqrt3, expected3, 1e-10));
    ASSERT(complex_approx_equal(sqrt4, expected4, 1e-10));
}

void test_csin() {
    complex_t z1, z2, z3;
    complex_t sin1, sin2, sin3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing csin ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = M_PI/2.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    sin1 = csin(z1);
    sin2 = csin(z2);
    sin3 = csin(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = 1.0; expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = sinh(1.0);
    
    ASSERT(complex_approx_equal(sin1, expected1, 1e-10));
    ASSERT(complex_approx_equal(sin2, expected2, 1e-10));
    ASSERT(complex_approx_equal(sin3, expected3, 1e-10));
}

void test_ccos() {
    complex_t z1, z2, z3;
    complex_t cos1, cos2, cos3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing ccos ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = M_PI/2.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    cos1 = ccos(z1);
    cos2 = ccos(z2);
    cos3 = ccos(z3);
    
    expected1.re = 1.0; expected1.im = 0.0;
    expected2.re = 0.0; expected2.im = 0.0;
    expected3.re = cosh(1.0); expected3.im = 0.0;
    
    ASSERT(complex_approx_equal(cos1, expected1, 1e-10));
    ASSERT(complex_approx_equal(cos2, expected2, 1e-10));
    ASSERT(complex_approx_equal(cos3, expected3, 1e-10));
}

void test_ctan() {
    complex_t z1, z2;
    complex_t tan1, tan2;
    complex_t expected1, expected2;
    
    printf("\n--- Testing ctan ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = M_PI/4.0; z2.im = 0.0;
    
    tan1 = ctan(z1);
    tan2 = ctan(z2);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = 1.0; expected2.im = 0.0;
    
    ASSERT(complex_approx_equal(tan1, expected1, 1e-10));
    ASSERT(complex_approx_equal(tan2, expected2, 1e-10));
}

void test_csinh() {
    complex_t z1, z2, z3;
    complex_t sinh1, sinh2, sinh3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing csinh ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = M_PI/2.0;
    
    sinh1 = csinh(z1);
    sinh2 = csinh(z2);
    sinh3 = csinh(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = sinh(1.0); expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = 1.0;
    
    ASSERT(complex_approx_equal(sinh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(sinh2, expected2, 1e-10));
    ASSERT(complex_approx_equal(sinh3, expected3, 1e-10));
}

void test_ccosh() {
    complex_t z1, z2, z3;
    complex_t cosh1, cosh2, cosh3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing ccosh ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = M_PI/2.0;
    
    cosh1 = ccosh(z1);
    cosh2 = ccosh(z2);
    cosh3 = ccosh(z3);
    
    expected1.re = 1.0; expected1.im = 0.0;
    expected2.re = cosh(1.0); expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = 0.0;
    
    ASSERT(complex_approx_equal(cosh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(cosh2, expected2, 1e-10));
    ASSERT(complex_approx_equal(cosh3, expected3, 1e-10));
}

void test_ctanh() {
    complex_t z1, z2;
    complex_t tanh1, tanh2;
    complex_t expected1, expected2;
    
    printf("\n--- Testing ctanh ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    
    tanh1 = ctanh(z1);
    tanh2 = ctanh(z2);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = tanh(1.0); expected2.im = 0.0;
    
    ASSERT(complex_approx_equal(tanh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(tanh2, expected2, 1e-10));
}

void test_casin() {
    complex_t z1, z2, z3;
    complex_t asin1, asin2, asin3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing casin ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    asin1 = casin(z1);
    asin2 = casin(z2);
    asin3 = casin(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = M_PI/2.0; expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = asinh(1.0);
    
    ASSERT(complex_approx_equal(asin1, expected1, 1e-10));
    ASSERT(complex_approx_equal(asin2, expected2, 1e-10));
    ASSERT(complex_approx_equal(asin3, expected3, 1e-10));
}

void test_cacos() {
    complex_t z1, z2, z3;
    complex_t acos1, acos2, acos3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing cacos ---\n");
    
    z1.re = 1.0; z1.im = 0.0;
    z2.re = 0.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    acos1 = cacos(z1);
    acos2 = cacos(z2);
    acos3 = cacos(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = M_PI/2.0; expected2.im = 0.0;
    expected3.re = M_PI/2.0; expected3.im = -asinh(1.0);
    
    ASSERT(complex_approx_equal(acos1, expected1, 1e-10));
    ASSERT(complex_approx_equal(acos2, expected2, 1e-10));
    ASSERT(complex_approx_equal(acos3, expected3, 1e-10));
}

void test_catan() {
    complex_t z1, z2, z3;
    complex_t atan1, atan2, atan3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing catan ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    atan1 = catan(z1);
    atan2 = catan(z2);
    atan3 = catan(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = M_PI/4.0; expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = INFINITY;
    
    ASSERT(complex_approx_equal(atan1, expected1, 1e-10));
    ASSERT(complex_approx_equal(atan2, expected2, 1e-10));
    ASSERT(complex_approx_equal(atan3, expected3, 1e-10));
}

void test_casinh() {
    complex_t z1, z2, z3;
    complex_t asinh1, asinh2, asinh3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing casinh ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 1.0; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    asinh1 = casinh(z1);
    asinh2 = casinh(z2);
    asinh3 = casinh(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = asinh(1.0); expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = M_PI/2.0;
    
    ASSERT(complex_approx_equal(asinh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(asinh2, expected2, 1e-10));
    ASSERT(complex_approx_equal(asinh3, expected3, 1e-10));
}

void test_cacosh() {
    complex_t z1, z2;
    complex_t acosh1, acosh2;
    complex_t expected1, expected2;
    
    printf("\n--- Testing cacosh ---\n");
    
    z1.re = 1.0; z1.im = 0.0;
    z2.re = 0.0; z2.im = 1.0;
    
    acosh1 = cacosh(z1);
    acosh2 = cacosh(z2);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = 0.0; expected2.im = M_PI/2.0;
    
    ASSERT(complex_approx_equal(acosh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(acosh2, expected2, 1e-10));
}

void test_catanh() {
    complex_t z1, z2, z3;
    complex_t atanh1, atanh2, atanh3;
    complex_t expected1, expected2, expected3;
    
    printf("\n--- Testing catanh ---\n");
    
    z1.re = 0.0; z1.im = 0.0;
    z2.re = 0.5; z2.im = 0.0;
    z3.re = 0.0; z3.im = 1.0;
    
    atanh1 = catanh(z1);
    atanh2 = catanh(z2);
    atanh3 = catanh(z3);
    
    expected1.re = 0.0; expected1.im = 0.0;
    expected2.re = atanh(0.5); expected2.im = 0.0;
    expected3.re = 0.0; expected3.im = M_PI/4.0;
    
    ASSERT(complex_approx_equal(atanh1, expected1, 1e-10));
    ASSERT(complex_approx_equal(atanh2, expected2, 1e-10));
    ASSERT(complex_approx_equal(atanh3, expected3, 1e-10));
}

void test_cpow() {
    complex_t z1, z2, z3;
    complex_t pow1, pow2, pow3;
    complex_t expected1, expected2, expected3;
    complex_t exp1, exp2, exp3;
    
    printf("\n--- Testing cpow ---\n");
    
    z1.re = 2.0; z1.im = 0.0;
    z2.re = 2.0; z2.im = 0.0;
    z3.re = 1.0; z3.im = 0.0;
    
    exp1.re = 2.0; exp1.im = 0.0;
    exp2.re = 3.0; exp2.im = 0.0;
    exp3.re = 0.0; exp3.im = 0.0;
    
    pow1 = cpow(z1, exp1);
    pow2 = cpow(z2, exp2);
    pow3 = cpow(z3, exp3);
    
    expected1.re = 4.0; expected1.im = 0.0;
    expected2.re = 8.0; expected2.im = 0.0;
    expected3.re = 1.0; expected3.im = 0.0;
    
    ASSERT(complex_approx_equal(pow1, expected1, 1e-10));
    ASSERT(complex_approx_equal(pow2, expected2, 1e-10));
    ASSERT(complex_approx_equal(pow3, expected3, 1e-10));
}

int main() {
    printf("=== Complex Number Unit Tests ===\n");
    printf("Testing ma.lib complex number functions\n");
    
    test_complex_creation();
    test_complex_arithmetic();
    test_cabs();
    test_carg();
    test_conj();
    test_cexp();
    test_clog();
    test_csqrt();
    test_csin();
    test_ccos();
    test_ctan();
    test_csinh();
    test_ccosh();
    test_ctanh();
    test_casin();
    test_cacos();
    test_catan();
    test_casinh();
    test_cacosh();
    test_catanh();
    test_cpow();
    
    printf("\n=== Test Results ===\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests failed: %d\n", tests_failed);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    
    if (tests_failed == 0) {
        printf("\n*** ALL TESTS PASSED! ***\n");
        return 0;
    } else {
        printf("\n*** %d TESTS FAILED! ***\n", tests_failed);
        return 1;
    }
}