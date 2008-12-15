/*
 *   
 *
 * Copyright  1990-2008 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt).
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions.
 */

/* sin(x)
 * Return sine function of x.
 *
 * kernel function:
 *  __kernel_sin        ... sine function on [-pi/4,pi/4]
 *  __kernel_cos        ... cose function on [-pi/4,pi/4]
 *  __ieee754_rem_pio2  ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *  [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *  in [-pi/4 , +pi/4], and let n = k mod 4.
 *  We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *      0          S       C         T
 *      1          C      -S        -1/T
 *      2         -S      -C         T
 *      3         -C       S        -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *  TRIG(x) returns trig(x) nearly rounded
 */
#include "incls/_precompiled.incl"
#include "incls/_JFP_lib_sin.cpp.incl"

#if ENABLE_FLOAT

#ifdef __cplusplus
extern "C" {
#endif

double jvm_fplib_sin(double x) {
  double y[2], z = 0.0;
  int n, ix;

  /* High word of x. */
  ix = __JHI(x);

  /* |x| ~< pi/4 */
  ix &= 0x7fffffff;
  if (ix <= 0x3fe921fb) {
    return sine_kernel(x, z, 0);
  } else if (ix >= 0x7ff00000) {
    /* sin(Inf or NaN) is NaN */
    return jvm_dsub(x, x);
  } else {
    /* argument reduction needed */
    n = ieee754_rem_pio2(x, y);
    switch(n & 3) {
    case 0: return sine_kernel(y[0], y[1], 1);
    case 1: return cosine_kernel(y[0], y[1]);
    case 2: x = sine_kernel(y[0], y[1], 1);
      return jvm_dneg(x);
    default:
      x = cosine_kernel(y[0], y[1]);
      return jvm_dneg(x);
    }
  }
}

#ifdef __cplusplus
}
#endif

#endif // ENABLE_FLOAT
