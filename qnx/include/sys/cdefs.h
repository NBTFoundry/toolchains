/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: declaration helpers shared by these headers.
 * The headers of this directory describe the C library of the head unit
 * (QNX Neutrino 6.5.0 SP1, ARMv7, little endian): its types, layouts,
 * constants and functions, so that a program built with them links against
 * the car's own libraries. They are written for this toolchain. */
#ifndef _NBT_QNX_SYS_CDEFS_H
#define _NBT_QNX_SYS_CDEFS_H

#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#define __NBT_NOEXCEPT throw()
#else
#define __BEGIN_DECLS
#define __END_DECLS
#define __NBT_NOEXCEPT
#endif

#define __NBT_NORETURN __attribute__((__noreturn__))
#define __NBT_PRINTF(f, a) __attribute__((__format__(__printf__, f, a)))
#define __NBT_SCANF(f, a) __attribute__((__format__(__scanf__, f, a)))

#ifndef __restrict
#if !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define __restrict restrict
#endif
#endif

#define __P(x) x
#define __CONCAT(x, y) x##y
#define __STRING(x) #x

#endif
