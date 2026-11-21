/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: file status. struct stat holds 64-bit
 * inode numbers, sizes and block counts as low and high words. */
#ifndef _NBT_QNX_SYS_STAT_H
#define _NBT_QNX_SYS_STAT_H

#include <sys/types.h>

struct stat {
#ifdef __NBT_OFF64
	ino_t st_ino;
	off_t st_size;
#else
	ino_t st_ino;
	ino_t st_ino_hi;
	off_t st_size;
	off_t st_size_hi;
#endif
	dev_t st_dev;
	dev_t st_rdev;
	uid_t st_uid;
	gid_t st_gid;
	time_t st_mtime;
	time_t st_atime;
	time_t st_ctime;
	mode_t st_mode;
	nlink_t st_nlink;
	blksize_t st_blocksize;
	_Int32t st_nblocks;
	blksize_t st_blksize;
#ifdef __NBT_OFF64
	blkcnt_t st_blocks;
#else
	blkcnt_t st_blocks;
	blkcnt_t st_blocks_hi;
#endif
};

struct stat64 {
	ino64_t st_ino;
	off64_t st_size;
	dev_t st_dev;
	dev_t st_rdev;
	uid_t st_uid;
	gid_t st_gid;
	time_t st_mtime;
	time_t st_atime;
	time_t st_ctime;
	mode_t st_mode;
	nlink_t st_nlink;
	blksize_t st_blocksize;
	_Int32t st_nblocks;
	blksize_t st_blksize;
	blkcnt64_t st_blocks;
};

#define S_IFMT 0xF000
#define S_IFIFO 0x1000
#define S_IFCHR 0x2000
#define S_IFDIR 0x4000
#define S_IFNAM 0x5000
#define S_IFBLK 0x6000
#define S_IFREG 0x8000
#define S_IFLNK 0xA000
#define S_IFSOCK 0xC000
#define _S_IFMT S_IFMT
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#define S_ISNAM(m) (((m) & S_IFMT) == S_IFNAM)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)
#define S_ISUID 004000
#define S_ISGID 002000
#define S_ISVTX 001000
#define S_IRWXU 000700
#define S_IRUSR 000400
#define S_IWUSR 000200
#define S_IXUSR 000100
#define S_IRWXG 000070
#define S_IRGRP 000040
#define S_IWGRP 000020
#define S_IXGRP 000010
#define S_IRWXO 000007
#define S_IROTH 000004
#define S_IWOTH 000002
#define S_IXOTH 000001
#define S_IREAD S_IRUSR
#define S_IWRITE S_IWUSR
#define S_IEXEC S_IXUSR

__BEGIN_DECLS
int stat(const char *__restrict __path, struct stat *__restrict __buf) __NBT_ALIAS64("stat64");
int lstat(const char *__restrict __path, struct stat *__restrict __buf) __NBT_ALIAS64("lstat64");
int fstat(int __fd, struct stat *__buf) __NBT_ALIAS64("fstat64");
int stat64(const char *__restrict __path, struct stat64 *__restrict __buf);
int lstat64(const char *__restrict __path, struct stat64 *__restrict __buf);
int fstat64(int __fd, struct stat64 *__buf);
int chmod(const char *__path, mode_t __mode);
int fchmod(int __fd, mode_t __mode);
int mkdir(const char *__path, mode_t __mode);
int mkfifo(const char *__path, mode_t __mode);
int mknod(const char *__path, mode_t __mode, dev_t __dev);
mode_t umask(mode_t __mask);
__END_DECLS

#endif
