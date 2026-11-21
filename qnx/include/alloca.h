/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: stack allocation, by the compiler. */
#ifndef _NBT_QNX_ALLOCA_H
#define _NBT_QNX_ALLOCA_H

#define alloca(size) __builtin_alloca(size)

#endif
