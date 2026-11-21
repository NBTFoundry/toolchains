/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: waiting for child processes. */
#ifndef _NBT_QNX_SYS_WAIT_H
#define _NBT_QNX_SYS_WAIT_H

#include <sys/_typedefs.h>
#include <signal.h>

#define WEXITED 0x0001
#define WTRAPPED 0x0002
#define WUNTRACED 0x0004
#define WSTOPPED WUNTRACED
#define WCONTINUED 0x0008
#define WNOHANG 0x0040
#define WNOWAIT 0x0080
#define WCOREFLG 0x0080

typedef enum { P_ALL, P_PID, P_PGID } idtype_t;

#define WIFEXITED(s) (((s) & 0xff) == 0)
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WIFSIGNALED(s) (((s) & 0xff) != 0 && ((s) & 0xff00) == 0)
#define WTERMSIG(s) ((s) & 0x7f)
#define WIFSTOPPED(s) (((s) & 0xff) == 0x7f && ((s) & 0xff00) != 0)
#define WSTOPSIG(s) (((s) >> 8) & 0xff)
#define WIFCONTINUED(s) (((s) & 0xffff) == 0xffff)
#define WCOREDUMP(s) ((s) & WCOREFLG)

struct rusage;

__BEGIN_DECLS
pid_t wait(int *__status);
pid_t waitpid(pid_t __pid, int *__status, int __options);
pid_t wait3(int *__status, int __options, struct rusage *__usage);
pid_t wait4(pid_t __pid, int *__status, int __options, struct rusage *__usage);
int waitid(idtype_t __idtype, id_t __id, siginfo_t *__info, int __options);
__END_DECLS

#endif
