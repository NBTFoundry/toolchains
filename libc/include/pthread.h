/* SPDX-License-Identifier: MPL-2.0 */
/* POSIX threads for NBT app modules, implemented over the host ABI's threads
 * and address-keyed waiting (sdk/module/runtime/pthread.c). The types are the
 * module's own, fixed in size; nothing here is shared with the host's C
 * library. */
#ifndef NBT_MODULE_PTHREAD_H
#define NBT_MODULE_PTHREAD_H

#include <stddef.h>
#include <stdint.h>
#include <sched.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uintptr_t pthread_t;

typedef struct {
  uint32_t stack_size;
  int32_t detach_state;
} pthread_attr_t;

typedef struct {
  volatile uint32_t lock; /* 0 free, 1 locked, 2 locked with waiters */
  uint32_t type;
  volatile uintptr_t owner;
  uint32_t count;
} pthread_mutex_t;

typedef struct {
  uint32_t type;
} pthread_mutexattr_t;

typedef struct {
  volatile uint32_t seq;
  uint32_t reserved;
} pthread_cond_t;

typedef struct {
  int32_t clock;
} pthread_condattr_t;

typedef uint32_t pthread_key_t;

typedef struct {
  volatile uint32_t state;
} pthread_once_t;

#define PTHREAD_MUTEX_NORMAL 0
#define PTHREAD_MUTEX_RECURSIVE 1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

#define PTHREAD_MUTEX_INITIALIZER {0, PTHREAD_MUTEX_NORMAL, 0, 0}
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP {0, PTHREAD_MUTEX_RECURSIVE, 0, 0}
#define PTHREAD_COND_INITIALIZER {0, 0}
#define PTHREAD_ONCE_INIT {0}

#define PTHREAD_KEYS_MAX 64
#define PTHREAD_STACK_MIN 16384

int pthread_attr_init(pthread_attr_t* attr);
int pthread_attr_destroy(pthread_attr_t* attr);
int pthread_attr_setstacksize(pthread_attr_t* attr, size_t size);
int pthread_attr_getstacksize(const pthread_attr_t* attr, size_t* size);
int pthread_attr_setdetachstate(pthread_attr_t* attr, int state);
int pthread_attr_getdetachstate(const pthread_attr_t* attr, int* state);

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*fn)(void*), void* arg);
int pthread_join(pthread_t thread, void** result);
int pthread_detach(pthread_t thread);
pthread_t pthread_self(void);
int pthread_equal(pthread_t a, pthread_t b);
void pthread_exit(void* result) __attribute__((noreturn));

int pthread_mutexattr_init(pthread_mutexattr_t* attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t* attr);
int pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type);
int pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type);
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t* mutex);
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);

int pthread_condattr_init(pthread_condattr_t* attr);
int pthread_condattr_destroy(pthread_condattr_t* attr);
int pthread_condattr_setclock(pthread_condattr_t* attr, clockid_t clock);
int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr);
int pthread_cond_destroy(pthread_cond_t* cond);
int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);
int pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex, const struct timespec* abstime);
int pthread_cond_signal(pthread_cond_t* cond);
int pthread_cond_broadcast(pthread_cond_t* cond);

int pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);
void* pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void* value);

int pthread_once(pthread_once_t* once, void (*fn)(void));

/* picolibc's <sched.h> declares this only for POSIX-thread platforms. */
int sched_yield(void);

#ifdef __cplusplus
}
#endif

#endif
