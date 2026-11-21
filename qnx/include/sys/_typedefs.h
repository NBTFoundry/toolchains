/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the POSIX types several headers share
 * (internal). Each is defined once, here. */
#ifndef _NBT_QNX_SYS__TYPEDEFS_H
#define _NBT_QNX_SYS__TYPEDEFS_H

#include <sys/_qnx_types.h>
#define __need_size_t
#define __need_NULL
#include <stddef.h>

typedef __nbt_ssize_t ssize_t;
typedef __nbt_off_t off_t;
typedef __nbt_off64_t off64_t;
typedef __nbt_time_t time_t;
typedef __nbt_clock_t clock_t;
typedef __nbt_mode_t mode_t;
typedef __nbt_dev_t dev_t;
typedef __nbt_pid_t pid_t;
typedef __nbt_id_t id_t;
typedef __nbt_uid_t uid_t;
typedef __nbt_gid_t gid_t;
typedef __nbt_ino_t ino_t;
typedef __nbt_suseconds_t suseconds_t;
typedef _Uint32t useconds_t;
typedef int timer_t;
typedef __nbt_clockid_t clockid_t;
typedef struct iovec iov_t;

typedef __nbt_pthread_t pthread_t;
typedef struct _thread_attr pthread_attr_t;
typedef __nbt_sync_t pthread_mutex_t;
typedef __nbt_sync_attr_t pthread_mutexattr_t;
typedef __nbt_sync_t pthread_cond_t;
typedef __nbt_sync_attr_t pthread_condattr_t;
typedef int pthread_key_t;
typedef struct _pthread_once pthread_once_t;
typedef struct _pthread_rwlock pthread_rwlock_t;
typedef struct _sync_attr pthread_rwlockattr_t;
typedef struct _sync_attr pthread_barrierattr_t;
typedef struct {
	unsigned int __barrier;
	unsigned int __count;
	__nbt_sync_t __lock;
	__nbt_sync_t __bcond;
} pthread_barrier_t;
typedef struct _sync pthread_spinlock_t;

struct timespec {
	time_t tv_sec;
	long tv_nsec;
};

struct sched_param {
	_Int32t sched_priority;
	_Int32t sched_curpriority;
	union {
		_Int32t __reserved[8];
		struct {
			_Int32t __ss_low_priority;
			_Int32t __ss_max_repl;
			struct timespec __ss_repl_period;
			struct timespec __ss_init_budget;
		} __ss;
	} __ss_un;
};
#define sched_ss_low_priority __ss_un.__ss.__ss_low_priority
#define sched_ss_max_repl __ss_un.__ss.__ss_max_repl
#define sched_ss_repl_period __ss_un.__ss.__ss_repl_period
#define sched_ss_init_budget __ss_un.__ss.__ss_init_budget
typedef struct sched_param sched_param_t;

#endif
