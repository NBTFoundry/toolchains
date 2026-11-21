/* SPDX-License-Identifier: MPL-2.0 */
/* Directory streams for NBT app modules (picolibc leaves <sys/dirent.h> to the
 * platform). Implemented over the host ABI's dir_* calls in
 * sdk/module/runtime/sys.c. */
#ifndef NBT_MODULE_SYS_DIRENT_H
#define NBT_MODULE_SYS_DIRENT_H

#include <sys/types.h>

/* The types POSIX code names (the BSD and Linux values); the runtime
 * reports only DT_DIR, DT_REG and DT_UNKNOWN. */
#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
#define DT_WHT 14

struct dirent {
  ino_t d_ino;
  unsigned char d_type;
  char d_name[256];
};

typedef struct nbt_dir DIR;

#endif
