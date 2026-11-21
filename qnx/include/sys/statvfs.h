/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: file system information (64-bit counts as
 * low and high words). */
#ifndef _NBT_QNX_SYS_STATVFS_H
#define _NBT_QNX_SYS_STATVFS_H

#include <sys/types.h>

struct statvfs {
	unsigned long f_bsize;
	unsigned long f_frsize;
#ifdef __NBT_OFF64
	fsblkcnt_t f_blocks;
	fsblkcnt_t f_bfree;
	fsblkcnt_t f_bavail;
	fsfilcnt_t f_files;
	fsfilcnt_t f_ffree;
	fsfilcnt_t f_favail;
#else
	fsblkcnt_t f_blocks;
	fsblkcnt_t f_blocks_hi;
	fsblkcnt_t f_bfree;
	fsblkcnt_t f_bfree_hi;
	fsblkcnt_t f_bavail;
	fsblkcnt_t f_bavail_hi;
	fsfilcnt_t f_files;
	fsfilcnt_t f_files_hi;
	fsfilcnt_t f_ffree;
	fsfilcnt_t f_ffree_hi;
	fsfilcnt_t f_favail;
	fsfilcnt_t f_favail_hi;
#endif
	unsigned long f_fsid;
	char f_basetype[16];
	unsigned long f_flag;
	unsigned long f_namemax;
	unsigned long f_filler[21];
};

struct statvfs64 {
	unsigned long f_bsize;
	unsigned long f_frsize;
	fsblkcnt64_t f_blocks;
	fsblkcnt64_t f_bfree;
	fsblkcnt64_t f_bavail;
	fsfilcnt64_t f_files;
	fsfilcnt64_t f_ffree;
	fsfilcnt64_t f_favail;
	unsigned long f_fsid;
	char f_basetype[16];
	unsigned long f_flag;
	unsigned long f_namemax;
	unsigned long f_filler[21];
};

#define ST_RDONLY 0x01
#define ST_NOEXEC 0x02
#define ST_NOSUID 0x04
#define ST_NOCREAT 0x08
#define ST_OFF32 0x10
#define ST_NOATIME 0x20

__BEGIN_DECLS
int statvfs(const char *__restrict __path, struct statvfs *__restrict __buf) __NBT_ALIAS64("statvfs64");
int fstatvfs(int __fd, struct statvfs *__buf) __NBT_ALIAS64("fstatvfs64");
int statvfs64(const char *__restrict __path, struct statvfs64 *__restrict __buf);
int fstatvfs64(int __fd, struct statvfs64 *__buf);
__END_DECLS

#endif
