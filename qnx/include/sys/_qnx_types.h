/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the base types every other header builds on
 * (internal; include the standard headers instead). QNX 6.5 on ARMv7: ILP32,
 * 32-bit time_t and off_t, 64-bit long long aligned to 8. */
#ifndef _NBT_QNX_SYS__QNX_TYPES_H
#define _NBT_QNX_SYS__QNX_TYPES_H

#include <sys/cdefs.h>

/* _FILE_OFFSET_BITS=64: off_t, ino_t and the block counts are 64-bit and the
 * functions that take them are the C library's *64 entry points. */
#if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS - 0 == 64
#define __NBT_OFF64 1
#define __NBT_ALIAS64(name) __asm__(name)
#elif !defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS - 0 == 32
#define __NBT_ALIAS64(name)
#else
#error "_FILE_OFFSET_BITS must be 32 or 64"
#endif

/* The car's C library is QNX Neutrino. */
#ifndef __QNXNTO__
#define __QNXNTO__ 1
#endif
#ifndef __QNX__
#define __QNX__ 1
#endif
#ifndef __ARM__
#define __ARM__ 1
#endif
#ifndef __LITTLEENDIAN__
#define __LITTLEENDIAN__ 1
#endif

typedef signed char _Int8t;
typedef unsigned char _Uint8t;
typedef short _Int16t;
typedef unsigned short _Uint16t;
typedef int _Int32t;
typedef unsigned int _Uint32t;
typedef long long _Int64t;
typedef unsigned long long _Uint64t;
typedef int _Intptrt;
typedef unsigned int _Uintptrt;
typedef unsigned int _Sizet;
typedef int _Ssizet;
typedef long long _Longlong;
typedef unsigned long long _ULonglong;
typedef _Int32t _Offt;
typedef _Int64t _Off64t;
typedef _Uint32t _Paddrt;
typedef _Uint32t _Paddr32t;
typedef _Uint64t _Paddr64t;
typedef unsigned int _Wchart;
typedef long _Wintt;

typedef __SIZE_TYPE__ __nbt_size_t;
typedef int __nbt_ssize_t;
#ifdef __NBT_OFF64
typedef _Int64t __nbt_off_t;
typedef _Uint64t __nbt_ino_t;
typedef _Uint64t __nbt_blkcnt_t;
typedef _Uint64t __nbt_fsblkcnt_t;
typedef _Uint64t __nbt_fsfilcnt_t;
#else
typedef _Int32t __nbt_off_t;
typedef _Uint32t __nbt_ino_t;
typedef _Uint32t __nbt_blkcnt_t;
typedef _Uint32t __nbt_fsblkcnt_t;
typedef _Uint32t __nbt_fsfilcnt_t;
#endif
typedef _Int64t __nbt_off64_t;
typedef _Uint32t __nbt_time_t;
typedef _Uint32t __nbt_clock_t;
typedef _Uint32t __nbt_mode_t;
typedef _Uint32t __nbt_dev_t;
typedef _Int32t __nbt_pid_t;
typedef _Int32t __nbt_id_t;
typedef _Int32t __nbt_uid_t;
typedef _Int32t __nbt_gid_t;
typedef _Int32t __nbt_suseconds_t;
typedef int __nbt_clockid_t;
typedef _Int32t __nbt_pthread_t;
typedef _Uint32t __nbt_socklen_t;
typedef _Uint8t __nbt_sa_family_t;

/* A multibyte conversion state, and a stream position. */
typedef struct _Mbstatet {
	_Wchart _Wchar;
	char _State;
	char _Reserved[3];
} _Mbstatet;

typedef struct _Fpost {
	_Off64t _Off;
	_Mbstatet _Wstate;
} _Fpost;

/* The kernel's synchronisation object: mutexes, condition variables and
 * semaphores. __owner is the owning thread for a mutex; 0xffffffff marks a
 * statically initialised object, created on first use. */
typedef struct _sync {
	int __count;
	unsigned __owner;
} __nbt_sync_t;

typedef struct _sync_attr {
	int __protocol;
	int __flags;
	int __prioceiling;
	int __clockid;
	int __reserved[4];
} __nbt_sync_attr_t;

struct __timespec {
	__nbt_time_t __tv_sec;
	long __tv_nsec;
};

struct __sched_param {
	_Int32t __sched_priority;
	_Int32t __sched_curpriority;
	union {
		_Int32t __reserved[8];
		struct {
			_Int32t __ss_low_priority;
			_Int32t __ss_max_repl;
			struct __timespec __ss_repl_period;
			struct __timespec __ss_init_budget;
		} __ss;
	} __ss_un;
};

struct _thread_attr {
	int __flags;
	_Sizet __stacksize;
	void *__stackaddr;
	void (*__exitfunc)(void *__status);
	int __policy;
	struct __sched_param __param;
	unsigned __guardsize;
	unsigned __prealloc;
	int __spare[2];
};

struct _pthread_once {
	int __once;
	__nbt_sync_t __mutex;
};

struct _pthread_rwlock {
	int __active;
	void *__spare;
	int __blockedwriters;
	int __blockedreaders;
	int __heavy;
	__nbt_sync_t __lock;
	__nbt_sync_t __rcond;
	__nbt_sync_t __wcond;
	unsigned __owner;
};

#ifndef _NBT_IOVEC_DEFINED
#define _NBT_IOVEC_DEFINED
struct iovec {
	void *iov_base;
	_Sizet iov_len;
};
#endif

#endif
