/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: file control (32-bit offsets; the *64
 * functions take 64-bit ones). */
#ifndef _NBT_QNX_FCNTL_H
#define _NBT_QNX_FCNTL_H

#include <sys/_typedefs.h>
#include <sys/stat.h>

#define O_RDONLY 000000
#define O_WRONLY 000001
#define O_RDWR 000002
#define O_ACCMODE 000003
#define O_APPEND 000010
#define O_DSYNC 000020
#define O_SYNC 000040
#define O_RSYNC 000100
#define O_NONBLOCK 000200
#define O_NDELAY O_NONBLOCK
#define O_CREAT 000400
#define O_TRUNC 001000
#define O_EXCL 002000
#define O_NOCTTY 004000
#define O_CLOEXEC 020000
#define O_REALIDS 040000
#define O_LARGEFILE 0100000
#define O_ASYNC 0200000
#define O_TEXT 000000
#define O_BINARY 000000

#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define F_SETLK 6
#define F_SETLKW 7
#define F_ALLOCSP 10
#define F_FREESP 11
#define F_GETLK 14
#define F_SETLK64 106
#define F_SETLKW64 107
#define F_GETLK64 114
#define F_GETOWN 35
#define F_SETOWN 36
#define FD_CLOEXEC 0x01
#define F_RDLCK 1
#define F_WRLCK 2
#define F_UNLCK 3

#define LOCK_SH 0x1
#define LOCK_EX 0x2
#define LOCK_NB 0x4
#define LOCK_UN 0x8

typedef struct flock {
	_Int16t l_type;
	_Int16t l_whence;
	_Int32t l_zero1;
#ifdef __NBT_OFF64
	off_t l_start;
	off_t l_len;
#else
	off_t l_start;
	off_t l_start_hi;
	off_t l_len;
	off_t l_len_hi;
#endif
	pid_t l_pid;
	_Uint32t l_sysid;
} flock_t;

typedef struct flock64 {
	_Int16t l_type;
	_Int16t l_whence;
	_Int32t l_zero1;
	off64_t l_start;
	off64_t l_len;
	pid_t l_pid;
	_Uint32t l_sysid;
} flock64_t;

__BEGIN_DECLS
int open(const char *__path, int __oflag, ...) __NBT_ALIAS64("open64");
int open64(const char *__path, int __oflag, ...);
int creat(const char *__path, mode_t __mode) __NBT_ALIAS64("creat64");
int creat64(const char *__path, mode_t __mode);
int fcntl(int __fd, int __cmd, ...);
int flock(int __fd, int __operation);
int sopen(const char *__path, int __oflag, int __share, ...);
__END_DECLS

#endif
