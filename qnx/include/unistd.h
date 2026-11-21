/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: POSIX system interfaces. */
#ifndef _NBT_QNX_UNISTD_H
#define _NBT_QNX_UNISTD_H

#include <sys/_typedefs.h>

#define _POSIX_VERSION 200112L
#define _POSIX_THREADS 200112L
#define _POSIX_THREAD_SAFE_FUNCTIONS 200112L
#define _POSIX_TIMERS 200112L
#define _POSIX_MONOTONIC_CLOCK 200112L
#define _POSIX_SEMAPHORES 200112L
#define _POSIX_SPAWN 200112L
#define _POSIX_READER_WRITER_LOCKS 200112L
#define _POSIX_BARRIERS 200112L
#define _POSIX_SPIN_LOCKS 200112L
#define _POSIX_TIMEOUTS 200112L
#define _POSIX_CLOCK_SELECTION 200112L

#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0
#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define F_ULOCK 0
#define F_LOCK 1
#define F_TLOCK 2
#define F_TEST 3

#define _CS_PATH 1
#define _CS_HOSTNAME 2
#define _CS_RELEASE 3
#define _CS_VERSION 4
#define _CS_MACHINE 5
#define _CS_ARCHITECTURE 6
#define _CS_SYSNAME 11
#define _CS_LIBPATH 200
#define _CS_DOMAIN 201
#define _CS_TIMEZONE 203
#define _CS_LOCALE 204

#define _SC_ARG_MAX 1
#define _SC_CHILD_MAX 2
#define _SC_CLK_TCK 3
#define _SC_NGROUPS_MAX 4
#define _SC_OPEN_MAX 5
#define _SC_JOB_CONTROL 6
#define _SC_SAVED_IDS 7
#define _SC_VERSION 8
#define _SC_PAGESIZE 11
#define _SC_PAGE_SIZE _SC_PAGESIZE
#define _SC_STREAM_MAX 13
#define _SC_TZNAME_MAX 14
#define _SC_SEM_NSEMS_MAX 22
#define _SC_SEM_VALUE_MAX 23
#define _SC_TIMER_MAX 25
#define _SC_LOGIN_NAME_MAX 42
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 43
#define _SC_THREAD_KEYS_MAX 44
#define _SC_THREAD_STACK_MIN 45
#define _SC_THREAD_THREADS_MAX 46
#define _SC_TTY_NAME_MAX 47
#define _SC_THREADS 48
#define _SC_THREAD_SAFE_FUNCTIONS 55
#define _SC_ATEXIT_MAX 66
#define _SC_AVPHYS_PAGES 67
#define _SC_LINE_MAX 81
#define _SC_NPROCESSORS_CONF 90
#define _SC_NPROCESSORS_ONLN 91
#define _SC_PHYS_PAGES 93
#define _SC_MONOTONIC_CLOCK 140
#define _SC_HOST_NAME_MAX 154
#define _SC_IOV_MAX 155
#define _SC_SYMLOOP_MAX 161

#define _PC_LINK_MAX 1
#define _PC_MAX_CANON 2
#define _PC_MAX_INPUT 3
#define _PC_NAME_MAX 4
#define _PC_PATH_MAX 5
#define _PC_PIPE_BUF 6
#define _PC_NO_TRUNC 7
#define _PC_VDISABLE 8
#define _PC_CHOWN_RESTRICTED 9
#define _PC_FILESIZEBITS 16
#define _PC_SYMLINK_MAX 17

__BEGIN_DECLS
extern char **environ;
extern int optind, opterr, optopt;
extern char *optarg;

int access(const char *__path, int __mode);
unsigned alarm(unsigned __seconds);
int chdir(const char *__path);
int chown(const char *__path, uid_t __owner, gid_t __group);
int close(int __fd);
size_t confstr(int __name, char *__buf, size_t __len);
int dup(int __fd);
int dup2(int __fd, int __fd2);
int execl(const char *__path, const char *__arg0, ...);
int execle(const char *__path, const char *__arg0, ...);
int execlp(const char *__file, const char *__arg0, ...);
int execv(const char *__path, char *const __argv[]);
int execve(const char *__path, char *const __argv[], char *const __envp[]);
int execvp(const char *__file, char *const __argv[]);
void _exit(int __status) __NBT_NORETURN;
int fchdir(int __fd);
int fchown(int __fd, uid_t __owner, gid_t __group);
int fdatasync(int __fd);
pid_t fork(void);
long fpathconf(int __fd, int __name);
int fsync(int __fd);
int ftruncate(int __fd, off_t __length) __NBT_ALIAS64("ftruncate64");
int ftruncate64(int __fd, off64_t __length);
char *getcwd(char *__buf, size_t __size);
gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);
int getgroups(int __size, gid_t __list[]);
int gethostname(char *__name, size_t __len);
int getopt(int __argc, char *const __argv[], const char *__optstring);
int getpagesize(void);
pid_t getpgid(pid_t __pid);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
pid_t getsid(pid_t __pid);
uid_t getuid(void);
int isatty(int __fd);
int lchown(const char *__path, uid_t __owner, gid_t __group);
int link(const char *__path1, const char *__path2);
int lockf(int __fd, int __function, off_t __size) __NBT_ALIAS64("lockf64");
off_t lseek(int __fd, off_t __offset, int __whence) __NBT_ALIAS64("lseek64");
off64_t lseek64(int __fd, off64_t __offset, int __whence);
int nice(int __incr);
long pathconf(const char *__path, int __name);
int pause(void);
int pipe(int __fds[2]);
ssize_t pread(int __fd, void *__buf, size_t __n, off_t __offset) __NBT_ALIAS64("pread64");
ssize_t pread64(int __fd, void *__buf, size_t __n, off64_t __offset);
ssize_t pwrite(int __fd, const void *__buf, size_t __n, off_t __offset) __NBT_ALIAS64("pwrite64");
ssize_t pwrite64(int __fd, const void *__buf, size_t __n, off64_t __offset);
ssize_t read(int __fd, void *__buf, size_t __n);
int readlink(const char *__restrict __path, char *__restrict __buf, size_t __bufsize);
int rmdir(const char *__path);
int setegid(gid_t __gid);
int seteuid(uid_t __uid);
int setgid(gid_t __gid);
int setpgid(pid_t __pid, pid_t __pgid);
pid_t setpgrp(void);
int setregid(gid_t __rgid, gid_t __egid);
int setreuid(uid_t __ruid, uid_t __euid);
pid_t setsid(void);
int setuid(uid_t __uid);
unsigned sleep(unsigned __seconds);
int symlink(const char *__path1, const char *__path2);
void sync(void);
long sysconf(int __name);
pid_t tcgetpgrp(int __fd);
int tcsetpgrp(int __fd, pid_t __pgrp);
int truncate(const char *__path, off_t __length) __NBT_ALIAS64("truncate64");
char *ttyname(int __fd);
int ttyname_r(int __fd, char *__buf, size_t __size);
useconds_t ualarm(useconds_t __usecs, useconds_t __interval);
int unlink(const char *__path);
int usleep(useconds_t __usec);
pid_t vfork(void);
ssize_t write(int __fd, const void *__buf, size_t __n);

/* QNX */
unsigned delay(unsigned __milliseconds);
int readcond(int __fd, void *__buf, int __n, int __min, int __time, int __timeout);
int ionotify(int __fd, int __action, int __flags, const struct sigevent *__event);
off_t tell(int __fd) __NBT_ALIAS64("tell64");
int eof(int __fd);
int flink(int __fd, const char *__path);
int getdomainname(char *__name, size_t __len);
char **__get_environ_ptr(void);
__END_DECLS

#endif
