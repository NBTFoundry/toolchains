/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: starting processes, the POSIX way and the
 * QNX way (spawn() with a descriptor map and an inheritance record). */
#ifndef _NBT_QNX_SPAWN_H
#define _NBT_QNX_SPAWN_H

#include <sys/types.h>
#include <signal.h>
#include <sched.h>

typedef _Uintptrt posix_spawnattr_t;
typedef _Uintptrt posix_spawn_file_actions_t;

#define POSIX_SPAWN_SETPGROUP 0x00000001
#define POSIX_SPAWN_SETSIGMASK 0x00000002
#define POSIX_SPAWN_SETSIGDEF 0x00000004
#define POSIX_SPAWN_SETSIGIGN 0x00000008
#define POSIX_SPAWN_SETSCHEDULER 0x00000040
#define POSIX_SPAWN_RESETIDS 0x00000080
#define POSIX_SPAWN_SETSCHEDPARAM 0x00000400
#define POSIX_SPAWN_NOZOMBIE 0x00002000

__BEGIN_DECLS
int posix_spawnattr_init(posix_spawnattr_t *__attr);
int posix_spawnattr_destroy(posix_spawnattr_t *__attr);
int posix_spawnattr_getflags(const posix_spawnattr_t *__restrict __attr, short *__restrict __flags);
int posix_spawnattr_setflags(posix_spawnattr_t *__attr, short __flags);
int posix_spawnattr_getsigdefault(const posix_spawnattr_t *__restrict __attr, sigset_t *__restrict __set);
int posix_spawnattr_setsigdefault(posix_spawnattr_t *__restrict __attr, const sigset_t *__restrict __set);
int posix_spawnattr_getsigmask(const posix_spawnattr_t *__restrict __attr, sigset_t *__restrict __set);
int posix_spawnattr_setsigmask(posix_spawnattr_t *__restrict __attr, const sigset_t *__restrict __set);
int posix_spawnattr_getpgroup(const posix_spawnattr_t *__restrict __attr, pid_t *__restrict __pgroup);
int posix_spawnattr_setpgroup(posix_spawnattr_t *__attr, pid_t __pgroup);
int posix_spawnattr_getschedparam(const posix_spawnattr_t *__restrict __attr, struct sched_param *__restrict __param);
int posix_spawnattr_setschedparam(posix_spawnattr_t *__restrict __attr, const struct sched_param *__restrict __param);
int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *__restrict __attr, int *__restrict __policy);
int posix_spawnattr_setschedpolicy(posix_spawnattr_t *__attr, int __policy);
int posix_spawnattr_getxflags(const posix_spawnattr_t *__restrict __attr, uint32_t *__restrict __flags);
int posix_spawnattr_setxflags(posix_spawnattr_t *__attr, uint32_t __flags);
int posix_spawn_file_actions_init(posix_spawn_file_actions_t *__actions);
int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *__actions);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *__actions, int __fd);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *__actions, int __fd, int __newfd);
int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *__restrict __actions, int __fd,
				     const char *__restrict __path, int __oflag, mode_t __mode);
int posix_spawn(pid_t *__restrict __pid, const char *__restrict __path, const posix_spawn_file_actions_t *__actions,
		const posix_spawnattr_t *__restrict __attr, char *const __argv[], char *const __envp[]);
int posix_spawnp(pid_t *__restrict __pid, const char *__restrict __file, const posix_spawn_file_actions_t *__actions,
		 const posix_spawnattr_t *__restrict __attr, char *const __argv[], char *const __envp[]);
__END_DECLS

/* QNX spawn(): what the child inherits. */
typedef struct inheritance {
	unsigned long flags;
	pid_t pgroup;
	sigset_t sigmask;
	sigset_t sigdefault;
	sigset_t sigignore;
	unsigned long stack_max;
	long policy;
	_Uint32t nd;
	_Uint32t runmask;
	struct sched_param param;
} spawn_inheritance_type;

#define SPAWN_SETGROUP POSIX_SPAWN_SETPGROUP
#define SPAWN_SETSIGMASK POSIX_SPAWN_SETSIGMASK
#define SPAWN_SETSIGDEF POSIX_SPAWN_SETSIGDEF
#define SPAWN_SETSIGIGN POSIX_SPAWN_SETSIGIGN
#define SPAWN_TCSETPGROUP 0x00000080
#define SPAWN_SETND 0x00000100
#define SPAWN_SETSID 0x00000200
#define SPAWN_EXPLICIT_SCHED POSIX_SPAWN_SETSCHEDPARAM
#define SPAWN_SETSTACKMAX 0x00001000
#define SPAWN_NOZOMBIE POSIX_SPAWN_NOZOMBIE
#define SPAWN_DEBUG 0x00004000
#define SPAWN_HOLD 0x00008000
#define SPAWN_EXEC 0x00010000
#define SPAWN_SEARCH_PATH 0x00020000
#define SPAWN_CHECK_SCRIPT 0x00040000
#define SPAWN_FDCLOSED (-1)
#define SPAWN_FDOPEN (-2)
#define SPAWN_NEWPGROUP 0

__BEGIN_DECLS
pid_t spawn(const char *__path, int __fd_count, const int __fd_map[], const struct inheritance *__inherit,
	    char *const __argv[], char *const __envp[]);
pid_t spawnp(const char *__file, int __fd_count, const int __fd_map[], const struct inheritance *__inherit,
	     char *const __argv[], char *const __envp[]);
pid_t spawnl(int __mode, const char *__path, const char *__arg0, ...);
pid_t spawnlp(int __mode, const char *__file, const char *__arg0, ...);
pid_t spawnv(int __mode, const char *__path, char *const __argv[]);
pid_t spawnvp(int __mode, const char *__file, char *const __argv[]);
pid_t spawnve(int __mode, const char *__path, char *const __argv[], char *const __envp[]);
__END_DECLS
#define P_WAIT 0
#define P_NOWAIT 1
#define P_OVERLAY 2
#define P_NOWAITO 3

#endif
