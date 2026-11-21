/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: device control. A command holds its data
 * size, class, number and direction. */
#ifndef _NBT_QNX_DEVCTL_H
#define _NBT_QNX_DEVCTL_H

#include <sys/types.h>

#define _POSIX_DEVDIR_NONE 0
#define _POSIX_DEVDIR_TO 0x80000000
#define _POSIX_DEVDIR_FROM 0x40000000
#define _POSIX_DEVDIR_TOFROM (_POSIX_DEVDIR_TO | _POSIX_DEVDIR_FROM)
#define _POSIX_DEVDIR_CMD_MASK 0x0000FFFF
#define DEVDIR_NONE _POSIX_DEVDIR_NONE
#define DEVDIR_TO _POSIX_DEVDIR_TO
#define DEVDIR_FROM _POSIX_DEVDIR_FROM
#define DEVDIR_TOFROM _POSIX_DEVDIR_TOFROM
#define DEVDIR_CMD_MASK _POSIX_DEVDIR_CMD_MASK

#define _DCMD_ALL 0x01
#define _DCMD_FSYS 0x02
#define _DCMD_BLK _DCMD_FSYS
#define _DCMD_CHR 0x03
#define _DCMD_NET 0x04
#define _DCMD_MISC 0x05
#define _DCMD_IP 0x06
#define _DCMD_MIXER 0x07
#define _DCMD_PROC 0x08
#define _DCMD_MEM 0x09
#define _DCMD_INPUT 0x0A
#define _DCMD_CAM 0x0C
#define _DCMD_USB 0x0D
#define _DCMD_MEDIA 0x0E

#define __DIOF(class, cmd, data) ((sizeof(data) << 16) + ((class) << 8) + (cmd) + _POSIX_DEVDIR_FROM)
#define __DIOT(class, cmd, data) ((sizeof(data) << 16) + ((class) << 8) + (cmd) + _POSIX_DEVDIR_TO)
#define __DIOTF(class, cmd, data) ((sizeof(data) << 16) + ((class) << 8) + (cmd) + _POSIX_DEVDIR_TOFROM)
#define __DION(class, cmd) (((class) << 8) + (cmd) + _POSIX_DEVDIR_NONE)
#define get_device_command(cmd) ((cmd) & DEVDIR_CMD_MASK)
#define get_device_direction(cmd) ((cmd) & DEVDIR_TOFROM)

struct iovec;

__BEGIN_DECLS
int devctl(int __fd, int __dcmd, void *__data, size_t __nbytes, int *__info);
int devctlv(int __fd, int __dcmd, int __sparts, int __rparts, const struct iovec *__sv, const struct iovec *__rv,
	    int *__info);
__END_DECLS

#endif
