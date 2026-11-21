/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: scheduling. */
#ifndef _NBT_QNX_SCHED_H
#define _NBT_QNX_SCHED_H

#include <sys/_typedefs.h>

#define SCHED_NOCHANGE 0
#define SCHED_FIFO 1
#define SCHED_RR 2
#define SCHED_OTHER 3
#define SCHED_SPORADIC 4
#define SCHED_ADJTOHEAD 5
#define SCHED_ADJTOTAIL 6
#define SCHED_SETPRIO 7
#define SCHED_MAXPOLICY 7

__BEGIN_DECLS
int getprio(pid_t __pid);
int setprio(pid_t __pid, int __priority);
int sched_getparam(pid_t __pid, struct sched_param *__param);
int sched_getscheduler(pid_t __pid);
int sched_setparam(pid_t __pid, const struct sched_param *__param);
int sched_setscheduler(pid_t __pid, int __policy, const struct sched_param *__param);
int sched_yield(void);
int sched_rr_get_interval(pid_t __pid, struct timespec *__t);
int sched_get_priority_min(int __policy);
int sched_get_priority_max(int __policy);
__END_DECLS

#endif
