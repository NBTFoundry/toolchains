/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: mbstate_t alone, for headers that need only
 * the type (libc++ looks for it here). */
#ifndef _NBT_QNX_BITS_TYPES_MBSTATE_T_H
#define _NBT_QNX_BITS_TYPES_MBSTATE_T_H

#include <sys/_qnx_types.h>

typedef _Mbstatet mbstate_t;

#endif
