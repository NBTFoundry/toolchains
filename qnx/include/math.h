/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: mathematics (libm). Classification macros
 * are the compiler's; long double is double on ARM. */
#ifndef _NBT_QNX_MATH_H
#define _NBT_QNX_MATH_H

#include <sys/cdefs.h>

typedef float float_t;
typedef double double_t;

#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define HUGE_VALL (__builtin_huge_vall())
#define INFINITY (__builtin_inff())
#define NAN (__builtin_nanf(""))
#define MAXFLOAT 3.40282347e+38F

#define FP_NAN 2
#define FP_INFINITE 1
#define FP_ZERO 0
#define FP_SUBNORMAL (-2)
#define FP_NORMAL (-1)
#define FP_ILOGB0 (-2147483647 - 1)
#define FP_ILOGBNAN 2147483647
#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)

#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#define isfinite(x) __builtin_isfinite(x)
#define isinf(x) __builtin_isinf_sign(x)
#define isnan(x) __builtin_isnan(x)
#define isnormal(x) __builtin_isnormal(x)
#define signbit(x) __builtin_signbit(x)
#define isgreater(x, y) __builtin_isgreater(x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#define isless(x, y) __builtin_isless(x, y)
#define islessequal(x, y) __builtin_islessequal(x, y)
#define islessgreater(x, y) __builtin_islessgreater(x, y)
#define isunordered(x, y) __builtin_isunordered(x, y)

#define M_E 2.7182818284590452354
#define M_LOG2E 1.4426950408889634074
#define M_LOG10E 0.43429448190325182765
#define M_LN2 0.69314718055994530942
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962
#define M_1_PI 0.31830988618379067154
#define M_2_PI 0.63661977236758134308
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440

/* name(double), namef(float) and namel(long double) for each function. */
#define __NBT_MATH1(n) double n(double); float n##f(float); long double n##l(long double);
#define __NBT_MATH2(n) double n(double, double); float n##f(float, float); long double n##l(long double, long double);

__BEGIN_DECLS
__NBT_MATH1(acos) __NBT_MATH1(asin) __NBT_MATH1(atan) __NBT_MATH2(atan2)
__NBT_MATH1(cos) __NBT_MATH1(sin) __NBT_MATH1(tan)
__NBT_MATH1(acosh) __NBT_MATH1(asinh) __NBT_MATH1(atanh)
__NBT_MATH1(cosh) __NBT_MATH1(sinh) __NBT_MATH1(tanh)
__NBT_MATH1(exp) __NBT_MATH1(exp2) __NBT_MATH1(expm1)
__NBT_MATH1(log) __NBT_MATH1(log10) __NBT_MATH1(log1p) __NBT_MATH1(log2) __NBT_MATH1(logb)
__NBT_MATH1(cbrt) __NBT_MATH1(fabs) __NBT_MATH2(hypot) __NBT_MATH2(pow) __NBT_MATH1(sqrt)
__NBT_MATH1(erf) __NBT_MATH1(erfc) __NBT_MATH1(lgamma) __NBT_MATH1(tgamma)
__NBT_MATH1(ceil) __NBT_MATH1(floor) __NBT_MATH1(nearbyint) __NBT_MATH1(rint) __NBT_MATH1(round)
__NBT_MATH1(trunc) __NBT_MATH2(fmod) __NBT_MATH2(remainder) __NBT_MATH2(copysign)
__NBT_MATH2(nextafter) __NBT_MATH2(fdim) __NBT_MATH2(fmax) __NBT_MATH2(fmin)
double frexp(double, int *); float frexpf(float, int *); long double frexpl(long double, int *);
double ldexp(double, int); float ldexpf(float, int); long double ldexpl(long double, int);
double modf(double, double *); float modff(float, float *); long double modfl(long double, long double *);
double scalbn(double, int); float scalbnf(float, int); long double scalbnl(long double, int);
double scalbln(double, long); float scalblnf(float, long); long double scalblnl(long double, long);
int ilogb(double); int ilogbf(float); int ilogbl(long double);
long lrint(double); long lrintf(float); long lrintl(long double);
long long llrint(double); long long llrintf(float); long long llrintl(long double);
long lround(double); long lroundf(float); long lroundl(long double);
long long llround(double); long long llroundf(float); long long llroundl(long double);
double remquo(double, double, int *); float remquof(float, float, int *); long double remquol(long double, long double, int *);
double nan(const char *); float nanf(const char *); long double nanl(const char *);
double nexttoward(double, long double); float nexttowardf(float, long double); long double nexttowardl(long double, long double);
double fma(double, double, double); float fmaf(float, float, float); long double fmal(long double, long double, long double);
double j0(double); double j1(double); double jn(int, double);
double y0(double); double y1(double); double yn(int, double);
__END_DECLS

#undef __NBT_MATH1
#undef __NBT_MATH2

#endif
