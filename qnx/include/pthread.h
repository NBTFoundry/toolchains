/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: POSIX threads, as the C library's
 * functions (none of its inline fast paths). */
#ifndef _NBT_QNX_PTHREAD_H
#define _NBT_QNX_PTHREAD_H

#include <sys/_typedefs.h>
#include <time.h>
#include <sched.h>

#define _NTO_SYNC_NONRECURSIVE 0x80000000
#define _NTO_SYNC_NOERRORCHECK 0x40000000
#define _NTO_SYNC_PRIOCEILING 0x20000000
#define _NTO_SYNC_PRIONONE 0x10000000
#define _NTO_SYNC_WAKEUP 0x08000000
#define _NTO_SYNC_COUNTMASK 0x00ffffff
#define _NTO_SYNC_INITIALIZER 0xffffffff
#define _NTO_SYNC_DESTROYED 0xfffffffe
#define _NTO_SYNC_NAMED_SEM 0xfffffffd
#define _NTO_SYNC_SEM 0xfffffffc
#define _NTO_SYNC_COND 0xfffffffb
#define _NTO_SYNC_SPIN 0xfffffffa

#define PTHREAD_CREATE_JOINABLE 0x00
#define PTHREAD_CREATE_DETACHED 0x01
#define PTHREAD_INHERIT_SCHED 0x00
#define PTHREAD_EXPLICIT_SCHED 0x02
#define PTHREAD_SCOPE_SYSTEM 0x00
#define PTHREAD_SCOPE_PROCESS 0x04
#define PTHREAD_CANCEL_ENABLE 0x00
#define PTHREAD_CANCEL_DISABLE 0x10
#define PTHREAD_CANCEL_DEFERRED 0x00
#define PTHREAD_CANCEL_ASYNCHRONOUS 0x20
#define PTHREAD_CANCELED ((void *)-1)
#define PTHREAD_PRIO_INHERIT 0
#define PTHREAD_PRIO_NONE 1
#define PTHREAD_PRIO_PROTECT 2
#define PTHREAD_PROCESS_PRIVATE 0x00
#define PTHREAD_PROCESS_SHARED 0x01
#define PTHREAD_RECURSIVE_DISABLE 0x00
#define PTHREAD_RECURSIVE_ENABLE 0x02
#define PTHREAD_MUTEX_DEFAULT 0
#define PTHREAD_MUTEX_ERRORCHECK 1
#define PTHREAD_MUTEX_RECURSIVE 2
#define PTHREAD_MUTEX_NORMAL 3
#define PTHREAD_BARRIER_SERIAL_THREAD ((int)-1)

/* Statically initialised objects: the kernel creates them on first use. */
#define PTHREAD_MUTEX_INITIALIZER { (int)_NTO_SYNC_NONRECURSIVE, _NTO_SYNC_INITIALIZER }
#define PTHREAD_RMUTEX_INITIALIZER { 0, _NTO_SYNC_INITIALIZER }
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER PTHREAD_RMUTEX_INITIALIZER
#define PTHREAD_COND_INITIALIZER { (int)_NTO_SYNC_COND, _NTO_SYNC_INITIALIZER }
#define PTHREAD_ONCE_INIT { 0, PTHREAD_MUTEX_INITIALIZER }
#define PTHREAD_RWLOCK_INITIALIZER \
	{ 0, 0, 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, -2U }

static __inline__ int pthread_equal(pthread_t __t1, pthread_t __t2) { return __t1 == __t2; }

__BEGIN_DECLS
int pthread_atfork(void (*__prepare)(void), void (*__parent)(void), void (*__child)(void));
int pthread_attr_destroy(pthread_attr_t *__attr);
int pthread_attr_getdetachstate(const pthread_attr_t *__attr, int *__state);
int pthread_attr_getguardsize(const pthread_attr_t *__restrict __attr, size_t *__restrict __size);
int pthread_attr_getinheritsched(const pthread_attr_t *__restrict __attr, int *__restrict __inherit);
int pthread_attr_getschedparam(const pthread_attr_t *__restrict __attr, struct sched_param *__restrict __param);
int pthread_attr_getschedpolicy(const pthread_attr_t *__restrict __attr, int *__restrict __policy);
int pthread_attr_getscope(const pthread_attr_t *__restrict __attr, int *__restrict __scope);
int pthread_attr_getstackaddr(const pthread_attr_t *__restrict __attr, void **__restrict __addr);
int pthread_attr_getstacksize(const pthread_attr_t *__restrict __attr, size_t *__restrict __size);
int pthread_attr_init(pthread_attr_t *__attr);
int pthread_attr_setdetachstate(pthread_attr_t *__attr, int __state);
int pthread_attr_setguardsize(pthread_attr_t *__attr, size_t __size);
int pthread_attr_setinheritsched(pthread_attr_t *__attr, int __inherit);
int pthread_attr_setschedparam(pthread_attr_t *__restrict __attr, const struct sched_param *__restrict __param);
int pthread_attr_setschedpolicy(pthread_attr_t *__attr, int __policy);
int pthread_attr_setscope(pthread_attr_t *__attr, int __scope);
int pthread_attr_setstackaddr(pthread_attr_t *__attr, void *__addr);
int pthread_attr_setstacksize(pthread_attr_t *__attr, size_t __size);
int pthread_cancel(pthread_t __thr);
int pthread_create(pthread_t *__restrict __thr, const pthread_attr_t *__restrict __attr,
		   void *(*__start)(void *), void *__restrict __arg);
int pthread_detach(pthread_t __thr);
void pthread_exit(void *__value) __NBT_NORETURN;
int pthread_getconcurrency(void);
int pthread_getschedparam(pthread_t __thr, int *__restrict __policy, struct sched_param *__restrict __param);
int pthread_join(pthread_t __thr, void **__value);
int pthread_timedjoin(pthread_t __thr, void **__value, const struct timespec *__abstime);
pthread_t pthread_self(void);
int pthread_setcancelstate(int __state, int *__old);
int pthread_setcanceltype(int __type, int *__old);
int pthread_setconcurrency(int __level);
int pthread_setschedparam(pthread_t __thr, int __policy, const struct sched_param *__param);
int pthread_setschedprio(pthread_t __thr, int __prio);
void pthread_testcancel(void);
int pthread_getcpuclockid(pthread_t __thr, clockid_t *__clock_id);
int pthread_setname_np(pthread_t __thr, const char *__name);
int pthread_getname_np(pthread_t __thr, char *__name, int __len);
int pthread_abort(pthread_t __thr);

void *pthread_getspecific(pthread_key_t __key);
int pthread_key_create(pthread_key_t *__key, void (*__destructor)(void *));
int pthread_key_delete(pthread_key_t __key);
int pthread_setspecific(pthread_key_t __key, const void *__value);
int pthread_once(pthread_once_t *__once, void (*__init)(void));

int pthread_mutexattr_destroy(pthread_mutexattr_t *__attr);
int pthread_mutexattr_init(pthread_mutexattr_t *__attr);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *__restrict __attr, int *__restrict __pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *__attr, int __pshared);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *__restrict __attr, int *__restrict __protocol);
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *__attr, int __protocol);
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *__restrict __attr, int *__restrict __ceiling);
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *__attr, int __ceiling);
int pthread_mutexattr_getrecursive(const pthread_mutexattr_t *__attr, int *__recursive);
int pthread_mutexattr_setrecursive(pthread_mutexattr_t *__attr, int __recursive);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *__restrict __attr, int *__restrict __type);
int pthread_mutexattr_settype(pthread_mutexattr_t *__attr, int __type);
int pthread_mutex_destroy(pthread_mutex_t *__mutex);
int pthread_mutex_init(pthread_mutex_t *__restrict __mutex, const pthread_mutexattr_t *__restrict __attr);
int pthread_mutex_lock(pthread_mutex_t *__mutex);
int pthread_mutex_timedlock(pthread_mutex_t *__restrict __mutex, const struct timespec *__restrict __abstime);
int pthread_mutex_trylock(pthread_mutex_t *__mutex);
int pthread_mutex_unlock(pthread_mutex_t *__mutex);

int pthread_condattr_destroy(pthread_condattr_t *__attr);
int pthread_condattr_init(pthread_condattr_t *__attr);
int pthread_condattr_getpshared(const pthread_condattr_t *__restrict __attr, int *__restrict __pshared);
int pthread_condattr_setpshared(pthread_condattr_t *__attr, int __pshared);
int pthread_condattr_getclock(const pthread_condattr_t *__restrict __attr, clockid_t *__restrict __clock);
int pthread_condattr_setclock(pthread_condattr_t *__attr, clockid_t __clock);
int pthread_cond_broadcast(pthread_cond_t *__cond);
int pthread_cond_destroy(pthread_cond_t *__cond);
int pthread_cond_init(pthread_cond_t *__restrict __cond, const pthread_condattr_t *__restrict __attr);
int pthread_cond_signal(pthread_cond_t *__cond);
int pthread_cond_timedwait(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex,
			   const struct timespec *__restrict __abstime);
int pthread_cond_wait(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex);

int pthread_rwlockattr_init(pthread_rwlockattr_t *__attr);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *__attr);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *__restrict __attr, int *__restrict __pshared);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *__attr, int __pshared);
int pthread_rwlock_destroy(pthread_rwlock_t *__lock);
int pthread_rwlock_init(pthread_rwlock_t *__restrict __lock, const pthread_rwlockattr_t *__restrict __attr);
int pthread_rwlock_rdlock(pthread_rwlock_t *__lock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *__lock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict __lock, const struct timespec *__restrict __abstime);
int pthread_rwlock_wrlock(pthread_rwlock_t *__lock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *__lock);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict __lock, const struct timespec *__restrict __abstime);
int pthread_rwlock_unlock(pthread_rwlock_t *__lock);

int pthread_barrierattr_init(pthread_barrierattr_t *__attr);
int pthread_barrierattr_destroy(pthread_barrierattr_t *__attr);
int pthread_barrier_destroy(pthread_barrier_t *__barrier);
int pthread_barrier_init(pthread_barrier_t *__restrict __barrier, const pthread_barrierattr_t *__restrict __attr,
			 unsigned __count);
int pthread_barrier_wait(pthread_barrier_t *__barrier);

int pthread_spin_init(pthread_spinlock_t *__lock, int __pshared);
int pthread_spin_destroy(pthread_spinlock_t *__lock);
int pthread_spin_lock(pthread_spinlock_t *__lock);
int pthread_spin_trylock(pthread_spinlock_t *__lock);
int pthread_spin_unlock(pthread_spinlock_t *__lock);
__END_DECLS

#endif
