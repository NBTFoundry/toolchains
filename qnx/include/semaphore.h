/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: POSIX semaphores (kernel sync objects). */
#ifndef _NBT_QNX_SEMAPHORE_H
#define _NBT_QNX_SEMAPHORE_H

#include <sys/types.h>

typedef sync_t sem_t;
#define SEM_FAILED ((sem_t *)-1)

struct timespec;

__BEGIN_DECLS
sem_t *sem_open(const char *__name, int __oflag, ...);
int sem_close(sem_t *__sem);
int sem_destroy(sem_t *__sem);
int sem_getvalue(sem_t *__restrict __sem, int *__restrict __value);
int sem_init(sem_t *__sem, int __pshared, unsigned __value);
int sem_post(sem_t *__sem);
int sem_trywait(sem_t *__sem);
int sem_unlink(const char *__name);
int sem_wait(sem_t *__sem);
int sem_timedwait(sem_t *__restrict __sem, const struct timespec *__restrict __abstime);
__END_DECLS

#endif
