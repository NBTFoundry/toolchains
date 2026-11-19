/* SPDX-License-Identifier: MPL-2.0 */
/* Directory streams for NBT app modules (picolibc leaves <sys/dirent.h> to the
 * platform). Implemented over the host ABI's dir_* calls in
 * sdk/module/runtime/sys.c. */
#ifndef NBT_MODULE_SYS_DIRENT_H
#define NBT_MODULE_SYS_DIRENT_H

#include <sys/types.h>

#define DT_UNKNOWN 0
#define DT_DIR 4
#define DT_REG 8

struct dirent {
  ino_t d_ino;
  unsigned char d_type;
  char d_name[256];
};

typedef struct nbt_dir DIR;

#endif
