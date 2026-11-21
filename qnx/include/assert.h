/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: assert. No include guard: NDEBUG may change
 * between inclusions. */
#include <sys/cdefs.h>

#undef assert
#ifdef NDEBUG
#define assert(e) ((void)0)
#else
__BEGIN_DECLS
extern void __assert(const char *__expr, const char *__file, unsigned __line, const char *__func);
__END_DECLS
#define assert(e) ((e) ? (void)0 : __assert(#e, __FILE__, __LINE__, __func__))
#endif

#if !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(static_assert)
#define static_assert _Static_assert
#endif
