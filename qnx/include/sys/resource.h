/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: resource limits and usage (32-bit limits,
 * with high words). */
#ifndef _NBT_QNX_SYS_RESOURCE_H
#define _NBT_QNX_SYS_RESOURCE_H

#include <sys/_typedefs.h>
#include <sys/time.h>

#define PRIO_PROCESS 0
#define PRIO_PGRP 1
#define PRIO_USER 2
#define RLIMIT_CPU 0
#define RLIMIT_FSIZE 1
#define RLIMIT_DATA 2
#define RLIMIT_STACK 3
#define RLIMIT_CORE 4
#define RLIMIT_NOFILE 5
#define RLIMIT_AS 6
#define RLIMIT_MEMLOCK 7
#define RLIMIT_NPROC 8
#define RLIMIT_NTHR 9
#define RLIM_NLIMITS 10
#define RUSAGE_SELF 0
#define RUSAGE_CHILDREN (-1)

typedef unsigned long rlim_t;
#define RLIM_INFINITY 0x7fffffff
#define RLIM_SAVED_MAX 0x7ffffffe
#define RLIM_SAVED_CUR 0x7ffffffd

struct rlimit {
	rlim_t rlim_cur;
	rlim_t rlim_cur_hi;
	rlim_t rlim_max;
	rlim_t rlim_max_hi;
};

struct rusage {
	struct timeval ru_utime;
	struct timeval ru_stime;
	long ru_maxrss;
	long ru_ixrss;
	long ru_idrss;
	long ru_isrss;
	long ru_minflt;
	long ru_majflt;
	long ru_nswap;
	long ru_inblock;
	long ru_oublock;
	long ru_msgsnd;
	long ru_msgrcv;
	long ru_nsignals;
	long ru_nvcsw;
	long ru_nivcsw;
};

__BEGIN_DECLS
int getrlimit(int __resource, struct rlimit *__rlim);
int setrlimit(int __resource, const struct rlimit *__rlim);
int getpriority(int __which, id_t __who);
int setpriority(int __which, id_t __who, int __prio);
int getrusage(int __who, struct rusage *__usage);
__END_DECLS

#endif
