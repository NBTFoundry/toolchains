/* SPDX-License-Identifier: MPL-2.0 */
/* File system statistics for NBT app modules: the host reports none, so
 * statvfs fails with ENOSYS (sdk/module/runtime/sys.c). Declared for libc++'s
 * std::filesystem::space. */
#ifndef NBT_MODULE_SYS_STATVFS_H
#define NBT_MODULE_SYS_STATVFS_H

#include <sys/types.h> /* fsblkcnt_t, fsfilcnt_t */

#ifdef __cplusplus
extern "C" {
#endif

struct statvfs {
  unsigned long f_bsize;
  unsigned long f_frsize;
  fsblkcnt_t f_blocks;
  fsblkcnt_t f_bfree;
  fsblkcnt_t f_bavail;
  fsfilcnt_t f_files;
  fsfilcnt_t f_ffree;
  fsfilcnt_t f_favail;
  unsigned long f_fsid;
  unsigned long f_flag;
  unsigned long f_namemax;
};

int statvfs(const char* path, struct statvfs* out);
int fstatvfs(int fd, struct statvfs* out);

#ifdef __cplusplus
}
#endif

#endif
