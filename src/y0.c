/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/w_j0.c and e_j0.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double y0(double x)
 * Bessel function of the second kind, order 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
one   = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
invsqrtpi=  5.64189583547756279280e-01, /* 0x3FE20DD7, 0x50429B6D */
tpi   =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
/* R0/S0 on [0, 2.00] */
R02  =  1.56249999999999947958e-02, /* 0x3F8FFFFF, 0xFFFFFFFD */
R03  = -1.89979294238854721787e-04, /* 0xBF28E6A5, 0xB61AC6E9 */
R04  =  1.82954049532700665670e-06, /* 0x3FEB923A, 0xC7EBDEF1 */
R05  = -4.61832688532103189199e-09, /* 0xBFE71588, 0xD9CBFAD6 */
S01  =  1.56191029464890010492e-02, /* 0x3F8FFCE8, 0x82C8C2A4 */
S02  =  1.16926784663337450260e-04, /* 0x3F1EA6D2, 0xDD57DBF4 */
S03  =  5.13546550207318111446e-07, /* 0x3EA13B54, 0xCE84D5A9 */
S04  =  1.16614003333790000205e-09; /* 0x3E1408BC, 0xF4745D8F */

static const double
u00  = -7.38042951086872317523e-02, /* 0xBFB2E4D6, 0x99CBD01F */
u01  =  1.76666452509181115538e-01, /* 0x3FC69D01, 0x9DE9E3FC */
u02  = -1.38185671945596898896e-02, /* 0xBF8C4CE8, 0xB16CFA97 */
u03  =  3.47453432093683650238e-04, /* 0x3F36C54D, 0x20B29B6B */
u04  = -3.81407053724364161125e-06, /* 0xBECFFEA7, 0x73D25CAD */
u05  =  1.95590137035022920206e-08, /* 0x3E550057, 0x3B4EABD4 */
u06  = -3.98205194132103398453e-11, /* 0xBDC5E43D, 0x693FB3C8 */
v01  =  1.27304834834123699328e-02, /* 0x3F8A1270, 0x91C9C71A */
v02  =  7.60068627350353253702e-05, /* 0x3F13ECBB, 0xF578C6C1 */
v03  =  2.59150851840457805467e-07, /* 0x3E91642D, 0x7FF202FD */
v04  =  4.41110311332675467403e-10; /* 0x3DFE5018, 0x3BD6D9EF */

static double zero = 0.0;

/* Helper function declarations */
static double pzero(double x);
static double qzero(double x);

static double __ieee754_y0(double x)
{
    double z, s,c,ss,cc,u,v;
    int hx,ix,lx;

    hx = __HI(x);
    ix = 0x7fffffff&hx;
    lx = __LO(x);
    /* Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0  */
    if(ix>=0x7ff00000) return  one/(x+x*x); 
    if((ix|lx)==0) return -one/zero;
    if(hx<0) return zero/zero;
    if(ix >= 0x40000000) {  /* |x| >= 2.0 */
        /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
         * where x0 = x-pi/4
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
         * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
         * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
         */
        if(ix<0x7fe00000) {  /* make sure x+x not overflow */
            z = -cos(x+x);
            if ((s*c)<zero) cc = z/ss;
            else            ss = z/cc;
        }
        if(ix>0x48000000) z = (invsqrtpi*ss)/sqrt(x);
        else {
            u = pzero(x); v = qzero(x);
            z = invsqrtpi*(u*ss+v*cc)/sqrt(x);
        }
        return z;
    }
    if(ix<=0x3e400000) {	/* x < 2**-27 */
        return(u00 + tpi*log(x));
    }
    z = x*x;
    u = u00+z*(u01+z*(u02+z*(u03+z*(u04+z*(u05+z*u06)))));
    v = one+z*(v01+z*(v02+z*(v03+z*v04)));
    return(u/v + tpi*(j0(x)*log(x)));
}

/* The asymptotic expansions of pzero is
 *	1 - 9/128 s^2 + 11025/98304 s^4 - ...,	where s = 1/x.
 * For x >= 2, We approximate pzero by
 * 	pzero(x) = 1 + (R/S)
 * where  R = pR0 + pR1*s^2 + pR2*s^4 + ... + pR5*s^10
 * 	  S = 1 + pS0*s^2 + ... + pS4*s^10
 * and
 *	| pzero(x)-1-R/S | <= 2  ** ( -60.26)
 */
static const double pR8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
 -7.03124999999900357484e-02, /* 0xBFB1FFFF, 0xFFFFFD32 */
 -8.08167041275349795626e+00, /* 0xC02029D0, 0xB44FA779 */
 -2.57063105679704847262e+02, /* 0xC0701102, 0x7B19E863 */
 -2.48521641009428822144e+03, /* 0xC0A36A6E, 0xCD4DCAFC */
 -5.25304380490729545272e+03, /* 0xC0B4850B, 0x36CC643D */
};
static const double pS8[5] = {
  1.16534364619668181717e+02, /* 0x405D2233, 0x07A96751 */
  3.83374475364121826715e+03, /* 0x40ADF37D, 0x50596938 */
  4.05978572648472545552e+04, /* 0x40E3D2BB, 0x6EB6B05F */
  1.16752972564375915681e+05, /* 0x40FC810F, 0x8F9FA9BD */
  4.76277284146730962675e+04, /* 0x40E74177, 0x4F2C49DC */
};

static const double pR5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
 -1.14125464691894502584e-11, /* 0xBDA918B1, 0x47E495CC */
 -7.03124940873599280078e-02, /* 0xBFB1FFFF, 0xE69AFBC6 */
 -4.15961064470587782438e+00, /* 0xC010A370, 0xF90C6BBF */
 -6.76747652265167261021e+01, /* 0xC050EB2F, 0x5A7D1783 */
 -3.31231299649172967747e+02, /* 0xC074B3B3, 0x6742CC63 */
 -3.46433388365604912451e+02, /* 0xC075A6EF, 0x28A38BD7 */
};
static const double pS5[5] = {
  6.07539382692300335975e+01, /* 0x404E6081, 0x0C98C5DE */
  1.05125230595704579173e+03, /* 0x40906D02, 0x5C7E2864 */
  5.97897094333855784498e+03, /* 0x40B75AF8, 0x8FBE1D60 */
  9.62544514357774460223e+03, /* 0x40C2CCB8, 0xFA76FA38 */
  2.40605815922939109441e+03, /* 0x40A2CC1D, 0xC70BE864 */
};

static const double pR3[6] = {/* for x in [4.547,2.8571]=1/[0.2199,0.35001] */
 -2.54704601771951915620e-09, /* 0xBE25E103, 0x6FE1AA86 */
 -7.03119616381481654654e-02, /* 0xBFB1FFF6, 0xF7C0E24B */
 -2.40903221549529611423e+00, /* 0xC00345B2, 0xAEA48074 */
 -2.19659774734883086467e+01, /* 0xC035F74A, 0x4CB94E14 */
 -5.80791704701737572236e+01, /* 0xC04D0A22, 0x420A1A45 */
 -3.14479470594888503854e+01, /* 0xC03F72AC, 0xA892D80F */
};
static const double pS3[5] = {
  3.58560338055209726349e+01, /* 0x4041ED92, 0x84077DD3 */
  3.61513983050303863820e+02, /* 0x40769839, 0x464A7C0E */
  1.19360783792111533330e+03, /* 0x4092A66E, 0x6D1061D6 */
  1.12799679856907414432e+03, /* 0x40919FFC, 0xB8C39B7E */
  1.73580930813335754692e+02, /* 0x4065B296, 0xFC379081 */
};

static const double pR2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
 -8.87534333032526411254e-08, /* 0xB77BE32F, 0x0C4D27A9 */
 -7.03030995483624743247e-02, /* 0xBFB1FF62, 0x495E1E42 */
 -1.45073846780952986357e+00, /* 0xBFF73629, 0x0A74E917 */
 -7.63569613823527770791e+00, /* 0xC01E8AF3, 0xEEDA7A79 */
 -1.11931668860356747786e+01, /* 0xC02662E6, 0xC5246303 */
 -3.23364579351335335033e+00, /* 0xC009DE81, 0xAF8FE70F */
};
static const double pS2[5] = {
  2.22202997532088808441e+01, /* 0x40363865, 0x908B5959 */
  1.36206794218215208048e+02, /* 0x4061069E, 0x0EE8878F */
  2.70470278658083486789e+02, /* 0x4070E786, 0x42EA079B */
  1.53875394208320329881e+02, /* 0x4067CF5F, 0x55C7C319 */
  1.46576176948256193810e+01, /* 0x402D50B3, 0x5A3D6B6D */
};

static double pzero(double x)
{
    const double *p,*q;
    double z,r,s;
    int ix;
    ix = 0x7fffffff&__HI(x);
    if(ix>=0x40200000)     {p = pR8; q= pS8;}
    else if(ix>=0x40122E8B){p = pR5; q= pS5;}
    else if(ix>=0x4006DB6D){p = pR3; q= pS3;}
    else if(ix>=0x40000000){p = pR2; q= pS2;}
    z = one/(x*x);
    r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
    s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*q[4]))));
    return one+ r/s;
}

/* For x >= 8, the asymptotic expansions of qzero is
 *	-1/8 s + 75/1024 s^3 - ..., where s = 1/x.
 * We approximate pzero by
 *	qzero(x) = s*(-1.25 + (R/S))
 * where  R = qR0 + qR1*s^2 + qR2*s^4 + ... + qR5*s^10
 * 	  S = 1 + qS0*s^2 + ... + qS4*s^10
 * and
 *	| qzero(x)/s +1.25-R/S | <= 2  ** ( -61.22)
 */
static const double qR8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
  7.32421874999935051953e-02, /* 0x3FB2BFFF, 0xFFFFFE2C */
  1.17682064682252693899e+01, /* 0x40278952, 0xBBFBFD27 */
  5.57673380256401856059e+02, /* 0x40804D1A, 0x031C1854 */
  8.85919720756468632317e+03, /* 0x40C14D99, 0x3E18F46D */
  3.70146267776887834771e+04, /* 0x40E212D4, 0x0E901566 */
};
static const double qS8[6] = {
  1.63776026895689824414e+02, /* 0x406478D5, 0x365B39BC */
  8.09834494656449805916e+03, /* 0x40BFA8F9, 0x0F8A31DB */
  1.42538291419120476348e+05, /* 0x41016652, 0x54C38A0A */
  8.03309257119514397345e+05, /* 0x412883DA, 0x83A52B43 */
  8.40501579819060512818e+05, /* 0x4129A66B, 0x28DE0B3B */
 -3.43899293537866615225e+05, /* 0xC114FD6D, 0x2C9530C5 */
};

static const double qR5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
 -1.08979979833581830835e-11, /* 0xBDA6B7B2, 0x53C4FD2A */
  7.32468780056748722658e-02, /* 0x3FB2BFFF, 0xFFFFFE2C */
  5.83563508962056953777e+00, /* 0x401757B0, 0xB0953C30 */
  1.35111577286449829671e+02, /* 0x4060E592, 0x0B4E1D07 */
  1.02724376596164097464e+03, /* 0x40900CFD, 0x8C4D0C8E */
  1.98997785864605384631e+03, /* 0x409F17E4, 0x53C25E09 */
};
static const double qS5[6] = {
  5.27905119051413824990e+01, /* 0x404A49F8, 0x0C4D681A */
  1.5068710410*85824797e+03, /* 0x40A75018, 0x5C5A8A5F */
  1.84869534643679530330e+04, /* 0x40C936CD, 0xE7E2DA40 */
  7.42409295383372760027e+04, /* 0x40E92F21, 0x8F9A019D */
  7.84387080907596713674e+04, /* 0x40EA4A29, 0xB281E8D2 */
 -1.73270791145947546124e+04, /* 0xC0B74EA4, 0x0D4F1EDA */
};

static const double qR3[6] = {/* for x in [4.547,2.8571]=1/[0.2199,0.35001] */
 -2.02504646702646847331e-09, /* 0xBE4448D2, 0xBE4D2F55 */
  7.32419366627982553312e-02, /* 0x3FB2BFFF, 0xFFFFFE2C */
  2.16719149857892088114e+00, /* 0x4000F6EC, 0x0F1A0F35 */
  1.14332472587284111371e+01, /* 0x40264C6A, 0x0C236681 */
  1.87074449963770379982e+01, /* 0x403A78B8, 0x0D6AAC7A */
  5.10600580820660042797e+00, /* 0x401A47EF, 0x8E484A93 */
};
static const double qS3[6] = {
  4.76651550323729509273e+01, /* 0x4047A523, 0xCCD4219C */
  6.73865112676699709415e+02, /* 0x408845A1, 0x3C1E8A42 */
  3.38015286679526343505e+03, /* 0x40AA684E, 0x44E7B0EB */
  5.54772909720722782367e+03, /* 0x40B5ABB3, 0x0D5AAC9B */
  1.90311919338810798763e+03, /* 0x4099BC0B, 0x0C474C21 */
 -1.35201191444307340817e+02, /* 0xC060E670, 0x290A311F */
};

static const double qR2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
 -1.78381727510958865572e-07, /* 0xB43F8932, 0x3C968D10 */
  7.32420629033423525056e-02, /* 0x3FB2BFFF, 0xFFFFFE2C */
  1.05061055642533046483e+00, /* 0x3FF0751A, 0x7F18A042 */
  5.47593808499534494600e+00, /* 0x4015D3B7, 0x7D5D1D20 */
  8.64453103284145798909e+00, /* 0x4020514B, 0x6A5D6C6C */
  3.38713271780158654040e+00, /* 0x400AB822, 0x8A0C7638 */
};
static const double qS2[6] = {
  2.48580649099903415526e+01, /* 0x403D922F, 0x7A545F32 */
  1.65076348074498771950e+02, /* 0x4062D0D1, 0x0F2B44E8 */
  4.32881060491290266891e+02, /* 0x4079C77A, 0x0F1A20D0 */
  4.85390399635913696487e+02, /* 0x407E5F4C, 0x0C4E4C6B */
  1.94550657148261396415e+02, /* 0x40626908, 0x0C4E4C6B */
 -1.48351190656462576227e+01, /* 0xC0871A18, 0x0C4E4C6B */
};

static double qzero(double x)
{
    const double *p,*q;
    double s,r,z;
    int ix;
    ix = 0x7fffffff&__HI(x);
    if(ix>=0x40200000)     {p = qR8; q= qS8;}
    else if(ix>=0x40122E8B){p = qR5; q= qS5;}
    else if(ix>=0x4006DB6D){p = qR3; q= qS3;}
    else if(ix>=0x40000000){p = qR2; q= qS2;}
    z = one/(x*x);
    r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
    s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*(q[4]+z*q[5])))));
    return (-.125 + r/s)/x;
}

double y0(double x)
{
    return __ieee754_y0(x);
}
