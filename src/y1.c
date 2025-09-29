/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/w_j1.c and e_j1.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double y1(double x)
 * Bessel function of the second kind, order 1
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
huge    = 1e300,
one     = 1.0,
invsqrtpi=  5.64189583547756279280e-01, /* 0x3FE20DD7, 0x50429B6D */
tpi      =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
/* R0/S0 on [0, 2.00] */
R00  = -6.25000000000000000000e-02, /* 0xBFB00000, 0x00000000 */
R01  =  1.40705666955189706048e-03, /* 0x3F570D9F, 0x98FECC04 */
R02  = -1.59955631084035597520e-05, /* 0xBEF0C5C6, 0xBA169668 */
R03  =  4.96727999609584448412e-08, /* 0x3E6AAAFA, 0x49CA0A9A */
S01  =  1.91537599538363460805e-02, /* 0x3F939D0B, 0x12637E53 */
S02  =  1.85946785588630915560e-04, /* 0x3F285F56, 0xB9CDF664 */
S03  =  1.17718464042623683263e-06, /* 0x3EB3BFF8, 0x333F8498 */
S04  =  5.04636257076217042715e-09, /* 0x3E35AC88, 0xC97DFF2C */
S05  =  1.23542274426137913908e-11; /* 0x3DAB2ACF, 0x2B2323A4 */

static const double
U0[5] = { -1.96057090646238940668e-01, /* 0xBFC91866, 0x143CBC8A */
  5.04438716639811282616e-02, /* 0x3FA9D3C7, 0x76292CD1 */
 -1.91256895875763547298e-03, /* 0xBF5F55E1, 0x4844FCA4 */
  2.35252600561610495928e-05, /* 0x3EF8AB03, 0x8FA6B88E */
 -9.19099158039878874504e-08, /* 0xBE78AC00, 0x569105B4 */
},
V0[5] = {  1.99167318236649903973e-02, /* 0x3F962510, 0x883E4F2A */
  2.02552581025135171496e-04, /* 0x3F4A0199, 0x8CAC645A */
  1.35608801097516229404e-06, /* 0x3EB6C05A, 0x894E8CA6 */
  6.22741452364621501295e-09, /* 0x3E3ABF1D, 0x5BA69A86 */
  1.66559246207992079114e-11, /* 0x3DB25039, 0xD435988A */
};

static double zero = 0.0;

/* Helper function declarations */
static double pone(double x);
static double qone(double x);

static double __ieee754_y1(double x)
{
    double z, s,c,ss,cc,u,v;
    int hx,ix,lx;

    hx = __HI(x);
    ix = 0x7fffffff&hx;
    lx = __LO(x);
    /* if Y1(NaN) is NaN, y1(-inf) is NaN, y1(inf) is 0  */
    if(ix>=0x7ff00000) return  one/(x+x*x); 
    if((ix|lx)==0) return -one/zero;
    if(hx<0) return zero/zero;
    if(ix >= 0x40000000) {  /* |x| >= 2.0 */
        /* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x1)+q1(x)*cos(x1))
         * where x1 = x-pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
         *                      =  1/sqrt(2) * (sin(x) + cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
        s = sin(x);
        c = cos(x);
        ss = s-c;
        cc = s+c;
        /*
         * j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
         * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x)
         */
        if(ix<0x7fe00000) {  /* make sure x+x not overflow */
            z = -cos(x+x);
            if ((s*c)<zero) cc = z/ss;
            else            ss = z/cc;
        }
        if(ix>0x48000000) z = (invsqrtpi*ss)/sqrt(x);
        else {
            u = pone(x); v = qone(x);
            z = invsqrtpi*(u*ss+v*cc)/sqrt(x);
        }
        return z;
    }
    if(ix<=0x3c900000) {	/* x < 2**-54 */
        return(-tpi/x);
    }
    z = x*x;
    u = U0[0]+z*(U0[1]+z*(U0[2]+z*(U0[3]+z*U0[4])));
    v = one+z*(V0[0]+z*(V0[1]+z*(V0[2]+z*(V0[3]+z*V0[4]))));
    return(x*(u/v) + tpi*(j1(x)*log(x)-one/x));
}

/* For x >= 8, the asymptotic expansions of pone is
 *	1 + 15/128 s^2 - 4725/2^15 s^4 - ...,	where s = 1/x.
 * We approximate pone by
 *	pone(x) = 1 + (R/S)
 * where  R = pr0 + pr1*s^2 + pr2*s^4 + ... + pr5*s^10
 * 	  S = 1 + ps0*s^2 + ... + ps4*s^10
 * and
 *	| pone(x)-1-R/S | <= 2  ** ( -60.06)
 */
static const double pr8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
  1.17187499999988647970e-01, /* 0x3FBDFFFF, 0xFFFFFCCE */
  1.32394806593073575130e+01, /* 0x402A7A9D, 0x357F7FCE */
  4.12051854307378562225e+02, /* 0x4079C0D4, 0x652EA590 */
  3.87474538913960532227e+03, /* 0x40AE457D, 0xA3A532ED */
  7.91447954031891731574e+03, /* 0x40BEEA7A, 0xC3271DD5 */
};
static const double ps8[5] = {
  1.14207370375678408436e+02, /* 0x405C8D45, 0x8E656CAC */
  3.65093083420853453394e+03, /* 0x40AC85DC, 0x964D274F */
  3.69562060269033463555e+04, /* 0x40E20B86, 0x7C42E73B */
  9.76027935934950801311e+04, /* 0x40F89D26, 0x5F28560B */
  3.08042720627888811578e+04, /* 0x40DE1D3C, 0x1D15F9BA */
};

static const double pr5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
 -1.02539062499992714161e-11, /* 0xBDFF7FFF, 0xFFFFFD61 */
  1.05927761479573995480e-01, /* 0x3FB1A626, 0x33145C07 */
  6.23753324503260060396e+00, /* 0x4018FEC0, 0xE44D8A3E */
  1.24549843548281732562e+02, /* 0x405BFDCD, 0x7C5D42BC */
  5.07336126165400214518e+02, /* 0x407F8797, 0x7F30A8C4 */
  5.33404000691139088730e+02, /* 0x407F9F9F, 0x8F8A8B2C */
};
static const double ps5[5] = {
  5.92445284019365963525e+01, /* 0x404DA4EA, 0xA5B7B05B */
  9.35098154644738267552e+02, /* 0x40884541, 0x655D1F3D */
  5.67575122662611769434e+03, /* 0x40B48020, 0xB5F61D6A */
  1.00302182980404279816e+04, /* 0x40C2F1F2, 0x0F6C96E0 */
  4.44248843811431112368e+03, /* 0x40AC2F1F, 0x2F6C96E0 */
};

static const double pr3[6] = {
 -3.02503916137373818024e-09, /* 0xBE1D7F7B, 0x4D42BAB6 */
  1.05968157946261439663e-01, /* 0x3FB1A626, 0x33145C07 */
  2.29172917971851089183e+00, /* 0x4001F2A7, 0x0F55FA32 */
  1.09259541164480178203e+01, /* 0x4026C691, 0x4A4CC6E6 */
  1.93337325128313787781e+01, /* 0x403969B0, 0x4FC9CBE7 */
  8.66007176181468424324e+00, /* 0x40215555, 0x4FCA4AAB */
};
static const double ps3[5] = {
  3.47913095001280598966e+01, /* 0x4041CA77, 0x0C6E8F0F */
  3.36762458747825746741e+02, /* 0x40750C33, 0x4F6C77B5 */
  1.04687139975775130551e+03, /* 0x40913BEB, 0x6C8E6212 */
  8.90819846323241601626e+02, /* 0x408BDDA9, 0x0E9A3270 */
  2.59058202655126269284e+02, /* 0x406B9A0F, 0x0F4A0EDB */
};

static const double pr2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
 -1.78381727510958865572e-07, /* 0xB43F8932, 0x3C968D10 */
  1.02542639086317742611e-01, /* 0x3FB1A626, 0x33145C07 */
  1.26717765301435800317e+01, /* 0x4028C640, 0x4F20E8D6 */
  1.04938124420420462312e+02, /* 0x405B28A3, 0xEE48AE2C */
  3.00738625558740231720e+02, /* 0x407B190D, 0x44A8A0D4 */
  2.08023756446676961377e+02, /* 0x406A066A, 0xE0445A4C */
};
static const double ps2[5] = {
  3.03655848355219184498e+01, /* 0x403E5D96, 0xF7C07AED */
  2.69348118608049844624e+02, /* 0x4070D3F0, 0x4418D308 */
  8.44783757595320139466e+02, /* 0x408A6647, 0x22F3A285 */
  8.82935845112488550512e+02, /* 0x408B977C, 0x9C5CC214 */
  2.12666374311797616138e+02, /* 0x406A955F, 0x0E4C1F11 */
};

static double pone(double x)
{
    const double *p,*q;
    double z,r,s;
    int ix;
    ix = 0x7fffffff&__HI(x);
    if(ix>=0x40200000)     {p = pr8; q= ps8;}
    else if(ix>=0x40122E8B){p = pr5; q= ps5;}
    else if(ix>=0x4006DB6D){p = pr3; q= ps3;}
    else if(ix>=0x40000000){p = pr2; q= ps2;}
    z = one/(x*x);
    r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
    s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*q[4]))));
    return one+ r/s;
}

/* For x >= 8, the asymptotic expansions of qone is
 *	3/8 s - 105/1024 s^3 - ..., where s = 1/x.
 * We approximate qone by
 *	qone(x) = s*(0.375 + (R/S))
 * where  R = qr0 + qr1*s^2 + qr2*s^4 + ... + qr5*s^10
 * 	  S = 1 + qs0*s^2 + ... + qs4*s^10
 * and
 *	| qone(x)/s -0.375-R/S | <= 2  ** ( -61.13)
 */
static const double qr8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
 -1.02539062499992714161e-01, /* 0xBFBA3FFF, 0xFFFFFDF3 */
 -1.62717534544589987888e+01, /* 0xC0304591, 0xA26779F7 */
 -7.59601722513950107896e+02, /* 0xC087BCD0, 0x53E4B076 */
 -1.18498066702429587167e+04, /* 0xC0C724E7, 0x40F22415 */
 -4.84385124285750353010e+04, /* 0xC0E7A6D0, 0x65D09C6A */
};
static const double qs8[6] = {
  1.61395369700722909556e+02, /* 0x4062CA0D, 0xB2ED2F3A */
  7.82538599923348465381e+03, /* 0x40BE9162, 0xD0D88419 */
  1.33875336287249578163e+05, /* 0x4101DFE0, 0x0F64C61F */
  7.19657722683231389983e+05, /* 0x4125F6B7, 0xC7643C47 */
  6.66601232617776375264e+05, /* 0x412457D2, 0x771AAD51 */
 -2.94490264303834643215e+05, /* 0xC111F969, 0x0EA5AA18 */
};

static const double qr5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
 -2.08979931141764104297e-11, /* 0xBDB6FA43, 0x1AA1A098 */
 -1.02539050241375426231e-01, /* 0xBFBA3FFF, 0xFFFFFDF3 */
 -8.05644828123936029840e+00, /* 0xC0201FE6, 0xBAFBD0D4 */
 -1.83669607474888320239e+02, /* 0xC066F56D, 0x6CA57E46 */
 -1.37319376065508163265e+03, /* 0xC09574C6, 0x6931734F */
 -2.61244440467315680587e+03, /* 0xC0A468E0, 0x5FDA79A7 */
};
static const double qs5[6] = {
  8.12765501384335777857e+01, /* 0x405451B2, 0xFF5A11B4 */
  1.99179873760472086909e+03, /* 0x409F1F31, 0xE77BF839 */
  1.74684851924908907677e+04, /* 0x40D10F1F, 0x0D64CE19 */
  4.98514270910352279316e+04, /* 0x40E8576D, 0xAB99ABB3 */
  2.79480751638918189862e+04, /* 0x40DB4B04, 0xCF7C364B */
 -4.71918354795128470869e+03, /* 0xC0B26F2E, 0xFCFFA004 */
};

static const double qr3[6] = {
 -5.07831226461766561369e-09, /* 0xBE35CFA9, 0xD38FC84F */
 -1.02537829820837089745e-01, /* 0xBFBA3FFF, 0xFFFFFDF3 */
 -4.61011581139473403113e+00, /* 0xC01270C4, 0x3302D9FF */
 -5.78472216562783643212e+01, /* 0xC04C3017, 0x4A9C701F */
 -2.28244540737631695038e+02, /* 0xC06C87D3, 0x4718D55F */
 -2.19210128478909325622e+02, /* 0xC06B66B9, 0x5F5C1BF6 */
};
static const double qs3[6] = {
  4.76651550323729509273e+01, /* 0x4047A523, 0xCCD4219C */
  6.73865112676699709415e+02, /* 0x408845A1, 0x3C1E8A42 */
  3.38015286679526343505e+03, /* 0x40AA684E, 0x44E7B0EB */
  5.54772909720722782367e+03, /* 0x40B5ABB3, 0x0D5AAC9B */
  1.90311919338810798763e+03, /* 0x4099BC0B, 0x0C474C21 */
 -1.35201191444307340817e+02, /* 0xC060E670, 0x290A311F */
};

static const double qr2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
 -1.78381727510958865572e-07, /* 0xB43F8932, 0x3C968D10 */
 -1.02517042607985553460e-01, /* 0xBFBA3E3E, 0xDF46B3C4 */
 -2.75220568278187460720e+00, /* 0xC0060484, 0x69BD4C42 */
 -1.96636162643703721721e+01, /* 0xC033A2D7, 0x4B9D421F */
 -4.23253133372830490089e+01, /* 0xC04529A3, 0x10410421 */
 -2.13719211703704061733e+01, /* 0xC0355F36, 0x0F73AF3F */
};
static const double qs2[6] = {
  2.95333629060523854548e+01, /* 0x403D888A, 0x78AE64BF */
  2.52981549982190529169e+02, /* 0x406F9F68, 0x8F14C92C */
  7.57534234881228524592e+02, /* 0x408739AC, 0xEA46A2A3 */
  7.39393205320467245656e+02, /* 0x40871A25, 0x4D1C1517 */
  1.55949003336610323663e+02, /* 0x40637D5A, 0x104C1450 */
 -4.95949898822628210127e+00, /* 0xC013A686, 0x0C4A8453 */
};

static double qone(double x)
{
    const double *p,*q;
    double s,r,z;
    int ix;
    ix = 0x7fffffff&__HI(x);
    if(ix>=0x40200000)     {p = qr8; q= qs8;}
    else if(ix>=0x40122E8B){p = qr5; q= qs5;}
    else if(ix>=0x4006DB6D){p = qr3; q= qs3;}
    else if(ix>=0x40000000){p = qr2; q= qs2;}
    z = one/(x*x);
    r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
    s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*(q[4]+z*q[5])))));
    return (.375 + r/s)/x;
}

double y1(double x)
{
    return __ieee754_y1(x);
}
