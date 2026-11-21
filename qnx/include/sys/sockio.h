/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: socket and interface ioctl requests. */
#ifndef _NBT_QNX_SYS_SOCKIO_H
#define _NBT_QNX_SYS_SOCKIO_H

#include <sys/ioctl.h>
#include <net/if.h>

#define SIOCSIFADDR _IOW('i', 12, struct ifreq)
#define SIOCSIFFLAGS _IOW('i', 16, struct ifreq)
#define SIOCGIFFLAGS _IOWR('i', 17, struct ifreq)
#define SIOCSIFBRDADDR _IOW('i', 19, struct ifreq)
#define SIOCSIFNETMASK _IOW('i', 22, struct ifreq)
#define SIOCGIFADDR _IOWR('i', 33, struct ifreq)
#define SIOCGIFBRDADDR _IOWR('i', 35, struct ifreq)
#define SIOCGIFNETMASK _IOWR('i', 37, struct ifreq)
#define SIOCGIFCONF _IOWR('i', 38, struct ifconf)
#define SIOCGIFMTU _IOWR('i', 126, struct ifreq)
#define SIOCSIFMTU _IOW('i', 127, struct ifreq)

#endif
