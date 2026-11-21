/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: system data types (sys/cdefs.h). */
#ifndef _NBT_QNX_SYS_TYPES_H
#define _NBT_QNX_SYS_TYPES_H

#include <sys/_qnx_types.h>
#include <sys/_typedefs.h>
#include <stdint.h>

typedef _Uint64t ino64_t;
typedef _Uint32t nlink_t;
typedef __nbt_blkcnt_t blkcnt_t;
typedef _Uint64t blkcnt64_t;
typedef _Uint32t blksize_t;
typedef __nbt_fsblkcnt_t fsblkcnt_t;
typedef _Uint64t fsblkcnt64_t;
typedef __nbt_fsfilcnt_t fsfilcnt_t;
typedef _Uint64t fsfilcnt64_t;
typedef _Uint32t key_t;

typedef __nbt_sync_t sync_t;
typedef __nbt_sync_attr_t sync_attr_t;

typedef char *caddr_t;
typedef _Uint32t paddr_t;
typedef _Uint32t paddr32_t;
typedef _Uint64t paddr64_t;
typedef _Int32t daddr_t;
typedef _Uint16t msg_t;

typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef _Uint8t u_int8_t;
typedef _Uint16t u_int16_t;
typedef _Uint32t u_int32_t;
typedef _Uint64t u_int64_t;

struct _clockadjust {
	unsigned long tick_count;
	long tick_nsec_inc;
};

struct _itimer {
	_Uint64t nsec;
	_Uint64t interval_nsec;
};

/* Device numbers: node, major and minor. */
#define minor(dev) ((int)((dev) & 0x3ff))
#define major(dev) ((int)(((dev) >> 10) & 0x3f))
#define makedev(node, maj, min) ((dev_t)(((node) << 16) | ((maj) << 10) | (min)))

#endif
