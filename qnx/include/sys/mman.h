/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: memory mapping and shared memory. */
#ifndef _NBT_QNX_SYS_MMAN_H
#define _NBT_QNX_SYS_MMAN_H

#include <sys/_typedefs.h>

#define PROT_NONE 0x00000000
#define PROT_READ 0x00000100
#define PROT_WRITE 0x00000200
#define PROT_EXEC 0x00000400
#define PROT_NOCACHE 0x00000800

#define MAP_SHARED 0x00000001
#define MAP_PRIVATE 0x00000002
#define MAP_TYPE 0x0000000f
#define MAP_FIXED 0x00000010
#define MAP_ELF 0x00000020
#define MAP_NOSYNCFILE 0x00000040
#define MAP_LAZY 0x00000080
#define MAP_STACK 0x00001000
#define MAP_BELOW 0x00002000
#define MAP_NOINIT 0x00004000
#define MAP_PHYS 0x00010000
#define MAP_NOX64K 0x00020000
#define MAP_BELOW16M 0x00040000
#define MAP_ANON 0x00080000
#define MAP_ANONYMOUS MAP_ANON
#define MAP_FAILED ((void *)-1)

#define MS_ASYNC 0x0000001
#define MS_SYNC 0x0000002
#define MS_INVALIDATE 0x0000004
#define MS_INVALIDATE_ICACHE 0x1000000
#define MS_CACHE_ONLY 0x2000000
#define MCL_CURRENT 0x000000001
#define MCL_FUTURE 0x000000002
#define POSIX_MADV_NORMAL 0
#define POSIX_MADV_SEQUENTIAL 1
#define POSIX_MADV_RANDOM 2
#define POSIX_MADV_WILLNEED 3
#define POSIX_MADV_DONTNEED 4

__BEGIN_DECLS
void *mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd, off_t __off) __NBT_ALIAS64("mmap64");
void *mmap64(void *__addr, size_t __len, int __prot, int __flags, int __fd, off64_t __off);
int munmap(void *__addr, size_t __len);
int mprotect(void *__addr, size_t __len, int __prot);
int msync(void *__addr, size_t __len, int __flags);
int mlock(const void *__addr, size_t __len);
int munlock(const void *__addr, size_t __len);
int mlockall(int __flags);
int munlockall(void);
int posix_madvise(void *__addr, size_t __len, int __advice);
int shm_open(const char *__name, int __oflag, mode_t __mode);
int shm_unlink(const char *__name);
int shm_ctl(int __fd, int __flags, _Uint64t __physical, _Uint64t __size);
void *mmap_device_memory(void *__addr, size_t __len, int __prot, int __flags, _Uint64t __physical);
int munmap_device_memory(void *__addr, size_t __len);
_Uintptrt mmap_device_io(size_t __len, _Uint64t __io);
int munmap_device_io(_Uintptrt __io, size_t __len);
int mem_offset64(const void *__addr, int __fd, size_t __len, off64_t *__off, size_t *__contig_len);
__END_DECLS

#endif
