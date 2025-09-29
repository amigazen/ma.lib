/* Copyright (c) 1993             by SAS Institute Inc., Cary NC     */

#ifndef __COMPLEX_H
#define __COMPLEX_H


#ifndef _MATH_H
#include <math.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

class complex {
public:
   // constructors
   complex(){}
   complex(double r, double i = 0.0)  _INLINE_FUNC({ re = r; im = i; })

   // complex operators
   friend complex operator+ (complex a, complex b)
              _INLINE_FUNC({return complex(a.re+b.re,a.im+b.im);})
   friend complex operator- (complex a)
              _INLINE_FUNC({return complex(-a.re,-a.im);})
   friend complex operator- (complex a, complex b)
              _INLINE_FUNC({return complex(a.re-b.re,a.im-b.im);})
   friend complex operator* (complex a, complex b)
              _INLINE_FUNC({return complex(a.re*b.re-a.im*b.im,
                                            a.re*b.im+a.im*b.re);})
   friend complex operator/ (complex a, complex b);
   friend complex operator/ (complex a, double d)
              _INLINE_FUNC({return complex(a.re/d,a.im/d);})

   friend int     operator==(complex a, complex b)
              _INLINE_FUNC({return a.re==b.re && a.im==b.im;})
   friend int     operator!=(complex a, complex b)
              _INLINE_FUNC({return a.re!=b.re || a.im!=b.im;})

   void    operator+=(complex a) _INLINE_FUNC({re += a.re; im += a.im;})
   void    operator-=(complex a) _INLINE_FUNC({re -= a.re; im -= a.im;})
   void    operator*=(complex a)
              _INLINE_FUNC({double re_temp;
                            re_temp = re*a.re - im*a.im;
                            im = re*a.im + im*a.re;
                            re = re_temp;})
   void    operator/=(complex a) _INLINE_FUNC({(*this) = (*this) / a;})
   void    operator/=(double d) _INLINE_FUNC({re /= d; im /= d;})

   // cartesian and polar coordinate functions
   friend double  abs   (complex a);
   friend double  arg   (complex a) _INLINE_FUNC({return atan2(a.im,a.re);})
   friend complex conj  (complex a) _INLINE_FUNC({return complex(a.re,-a.im);})
   friend double  imag  (complex a) _INLINE_FUNC({return a.im;})
   friend double  norm  (complex a) _INLINE_FUNC({return a.re*a.re+a.im*a.im;})
   friend complex polar (double r, double t = 0.0)
             _INLINE_FUNC({return complex(r*cos(t),r*sin(t));})
   friend double  real  (complex a) _INLINE_FUNC({return a.re;})

   // exponential, logarithmic, power, and square root functions
   friend complex exp  (complex a);
   friend complex log  (complex a);
   friend complex pow  (double d, complex a);
   friend complex pow  (complex a, int i);
   friend complex pow  (complex a, double d);
   friend complex pow  (complex x, complex y);
   friend complex sqrt (complex a);

   // trignometric and hyperbolic functions
   friend complex sin  (complex a);
   friend complex cos  (complex a);
   friend complex sinh (complex a);
   friend complex cosh (complex a);

private:
   double re, im;
   int unbalanced();
   complex sinhcosh(int sincos);
   complex powzero();
};

// I/O functions 
ostream& operator<<(ostream&, complex);
istream& operator>>(istream&, complex&);


#endif /* __COMPLEX_H */



