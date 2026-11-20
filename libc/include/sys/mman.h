/* SPDX-License-Identifier: MPL-2.0 */
/* Memory mappings for NBT app modules, as JIT compilers use them: anonymous
 * private mappings, protection changes (executable pages included) and, from
 * the compiler, __clear_cache. The SDK's module runtime implements them over
 * the host ABI (sdk/module/runtime/mman.c). There are no file mappings: mmap
 * with a descriptor fails with ENODEV, MAP_FIXED with EINVAL, and an address
 * hint is ignored. */
#ifndef NBT_MODULE_SYS_MMAN_H
#define NBT_MODULE_SYS_MMAN_H

#include <sys/types.h> /* off_t, size_t */

#ifdef __cplusplus
extern "C" {
#endif

#define PROT_NONE 0x0
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4

#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS

#define MAP_FAILED ((void*)-1)

void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset);
int munmap(void* addr, size_t len);
int mprotect(void* addr, size_t len, int prot);

#ifdef __cplusplus
}
#endif

#endif
