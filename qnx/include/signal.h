/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: signals, signal information and events. */
#ifndef _NBT_QNX_SIGNAL_H
#define _NBT_QNX_SIGNAL_H

#include <sys/_typedefs.h>

typedef int sig_atomic_t;

/* 64 signals. */
typedef struct {
	long __bits[2];
} sigset_t;

typedef struct {
	void *ss_sp;
	size_t ss_size;
	int ss_flags;
} stack_t;

typedef struct __ucontext_t ucontext_t;

union sigval {
	int sival_int;
	void *sival_ptr;
};

#define SIGEV_NONE 0
#define SIGEV_SIGNAL 1
#define SIGEV_SIGNAL_CODE 2
#define SIGEV_SIGNAL_THREAD 3
#define SIGEV_PULSE 4
#define SIGEV_UNBLOCK 5
#define SIGEV_INTR 6
#define SIGEV_THREAD 7

/* What a timer or a server sends on an event: a signal, a pulse on a
 * connection, or a thread. */
struct sigevent {
	int sigev_notify;
	union {
		int __sigev_signo;
		int __sigev_coid;
		int __sigev_id;
		void (*__sigev_notify_function)(union sigval);
	} __sigev_un1;
	union sigval sigev_value;
	union {
		struct {
			short __sigev_code;
			short __sigev_priority;
		} __st;
		pthread_attr_t *__sigev_notify_attributes;
	} __sigev_un2;
};
#define sigev_signo __sigev_un1.__sigev_signo
#define sigev_coid __sigev_un1.__sigev_coid
#define sigev_id __sigev_un1.__sigev_id
#define sigev_notify_function __sigev_un1.__sigev_notify_function
#define sigev_notify_attributes __sigev_un2.__sigev_notify_attributes
#define sigev_code __sigev_un2.__st.__sigev_code
#define sigev_priority __sigev_un2.__st.__sigev_priority

#define SIGEV_NONE_INIT(e) ((e)->sigev_notify = SIGEV_NONE)
#define SIGEV_SIGNAL_INIT(e, s) ((e)->sigev_notify = SIGEV_SIGNAL, (e)->sigev_signo = (s))
#define SIGEV_PULSE_INIT(e, c, p, code, v) \
	((e)->sigev_notify = SIGEV_PULSE, (e)->sigev_coid = (c), (e)->sigev_priority = (p), \
	 (e)->sigev_value.sival_ptr = (void *)(v), (e)->sigev_code = (code))
#define SIGEV_UNBLOCK_INIT(e) ((e)->sigev_notify = SIGEV_UNBLOCK)
#define SIGEV_INTR_INIT(e) ((e)->sigev_notify = SIGEV_INTR)
#define SIGEV_THREAD_INIT(e, f, v, a) \
	((e)->sigev_notify = SIGEV_THREAD, (e)->sigev_notify_function = (f), \
	 (e)->sigev_value.sival_ptr = (void *)(v), (e)->sigev_notify_attributes = (a))
#define SIGEV_PULSE_PRIO_INHERIT (-1)

typedef struct _siginfo {
	int si_signo;
	int si_code;
	int si_errno;
	union {
		int __pad[7];
		struct {
			pid_t __pid;
			union {
				struct {
					uid_t __uid;
					union sigval __value;
				} __kill;
				struct {
					clock_t __utime;
					int __status;
					clock_t __stime;
				} __chld;
			} __pdata;
		} __proc;
		struct {
			int __fltno;
			void *__fltip;
			void *__addr;
			int __bdslot;
		} __fault;
	} __data;
} siginfo_t;
#define si_pid __data.__proc.__pid
#define si_value __data.__proc.__pdata.__kill.__value
#define si_uid __data.__proc.__pdata.__kill.__uid
#define si_status __data.__proc.__pdata.__chld.__status
#define si_utime __data.__proc.__pdata.__chld.__utime
#define si_stime __data.__proc.__pdata.__chld.__stime
#define si_fltno __data.__fault.__fltno
#define si_trapno si_fltno
#define si_addr __data.__fault.__addr
#define si_fltip __data.__fault.__fltip

#define SI_USER 0
#define SI_QUEUE (-2)
#define SI_TIMER (-3)
#define SI_ASYNCIO (-4)
#define SI_MESGQ (-5)
#define SI_NOTIFY (-6)
#define SI_IRQ (-7)
#define SI_NOINFO 127
#define ILL_ILLOPC 1
#define ILL_ILLOPN 2
#define ILL_ILLADR 3
#define ILL_ILLTRP 4
#define ILL_PRVOPC 5
#define ILL_PRVREG 6
#define ILL_COPROC 7
#define ILL_BADSTK 8
#define SEGV_MAPERR 1
#define SEGV_ACCERR 2
#define SEGV_STKERR 3
#define SEGV_GPERR 4
#define SEGV_IRQERR 5
#define BUS_ADRALN 1
#define BUS_ADRERR 2
#define BUS_OBJERR 3
#define CLD_EXITED 1
#define CLD_KILLED 2
#define CLD_DUMPED 3
#define CLD_TRAPPED 4
#define CLD_STOPPED 5
#define CLD_CONTINUED 6
#define TRAP_BRKPT 1
#define TRAP_TRACE 2
#define FPE_INTDIV 1
#define FPE_INTOVF 2
#define FPE_FLTDIV 3
#define FPE_FLTOVF 4
#define FPE_FLTUND 5
#define FPE_FLTRES 6
#define FPE_FLTINV 7
#define FPE_FLTSUB 8

struct sigaction {
	union {
		void (*_sa_handler)(int);
		void (*_sa_sigaction)(int, siginfo_t *, void *);
	} __sa_un;
	int sa_flags;
	sigset_t sa_mask;
};
#define sa_handler __sa_un._sa_handler
#define sa_sigaction __sa_un._sa_sigaction

#define SIG_ERR ((void (*)(int)) - 1)
#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_HOLD ((void (*)(int))2)

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGIOT 6
#define SIGABRT 6
#define SIGEMT 7
#define SIGFPE 8
#define SIGKILL 9
#define SIGBUS 10
#define SIGSEGV 11
#define SIGSYS 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGUSR1 16
#define SIGUSR2 17
#define SIGCHLD 18
#define SIGCLD SIGCHLD
#define SIGPWR 19
#define SIGWINCH 20
#define SIGURG 21
#define SIGPOLL 22
#define SIGIO SIGPOLL
#define SIGSTOP 23
#define SIGTSTP 24
#define SIGCONT 25
#define SIGTTIN 26
#define SIGTTOU 27
#define SIGVTALRM 28
#define SIGPROF 29
#define SIGXCPU 30
#define SIGXFSZ 31
#define NSIG 57
#define _NSIG 57
#define SIGRTMIN 41
#define SIGRTMAX 56

#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#define SA_NOCLDSTOP 0x0001
#define SA_SIGINFO 0x0002
#define SA_RESETHAND 0x0004
#define SA_NODEFER 0x0010
#define SA_NOCLDWAIT 0x0020
#define SS_ONSTACK 1
#define SS_DISABLE 2

__BEGIN_DECLS
int raise(int __sig);
void (*signal(int __sig, void (*__func)(int)))(int);
int kill(pid_t __pid, int __sig);
int killpg(pid_t __pgrp, int __sig);
int sigaction(int __sig, const struct sigaction *__restrict __act, struct sigaction *__restrict __oact);
int sigaddset(sigset_t *__set, int __sig);
int sigdelset(sigset_t *__set, int __sig);
int sigemptyset(sigset_t *__set);
int sigfillset(sigset_t *__set);
int sigismember(const sigset_t *__set, int __sig);
int sigpending(sigset_t *__set);
int sigprocmask(int __how, const sigset_t *__restrict __set, sigset_t *__restrict __oset);
int sigsuspend(const sigset_t *__mask);
int sigqueue(pid_t __pid, int __sig, const union sigval __value);
int sigwait(const sigset_t *__restrict __set, int *__restrict __sig);
int sigwaitinfo(const sigset_t *__restrict __set, siginfo_t *__restrict __info);
int sigtimedwait(const sigset_t *__restrict __set, siginfo_t *__restrict __info,
		 const struct timespec *__restrict __timeout);
int pthread_kill(pthread_t __thr, int __sig);
int pthread_sigmask(int __how, const sigset_t *__restrict __set, sigset_t *__restrict __oset);
__END_DECLS

#endif
