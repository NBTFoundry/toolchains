/* SPDX-License-Identifier: MPL-2.0 */
/* Unnamed POSIX semaphores for NBT app modules (sdk/module/runtime/pthread.c). */
#ifndef NBT_MODULE_SEMAPHORE_H
#define NBT_MODULE_SEMAPHORE_H

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  volatile uint32_t value;
  volatile uint32_t waiters;
} sem_t;

int sem_init(sem_t* sem, int pshared, unsigned value);
int sem_destroy(sem_t* sem);
int sem_wait(sem_t* sem);
int sem_trywait(sem_t* sem);
int sem_timedwait(sem_t* sem, const struct timespec* abstime);
int sem_post(sem_t* sem);
int sem_getvalue(sem_t* sem, int* value);

#ifdef __cplusplus
}
#endif

#endif
