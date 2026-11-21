/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: ioctl() and BSD request numbers (direction,
 * parameter length, group, number). */
#ifndef _NBT_QNX_SYS_IOCTL_H
#define _NBT_QNX_SYS_IOCTL_H

#include <sys/cdefs.h>

#define IOCPARM_MASK 0x3fff
#define IOCPARM_LEN(x) (((x) >> 16) & IOCPARM_MASK)
#define IOCBASECMD(x) ((x) & ~(IOCPARM_MASK << 16))
#define IOCGROUP(x) (((x) >> 8) & 0xff)
#define IOC_VOID 0x00000000
#define IOC_OUT 0x40000000
#define IOC_IN 0x80000000
#define IOC_INOUT (IOC_IN | IOC_OUT)
#define IOC_DIRMASK 0xc0000000
#define _IOC(inout, group, num, len) ((inout) | (((len) & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define _IO(g, n) _IOC(IOC_VOID, (g), (n), 0)
#define _IOR(g, n, t) _IOC(IOC_OUT, (g), (n), sizeof(t))
#define _IOW(g, n, t) _IOC(IOC_IN, (g), (n), sizeof(t))
#define _IOWR(g, n, t) _IOC(IOC_INOUT, (g), (n), sizeof(t))

struct winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

#define TIOCSWINSZ _IOW('t', 103, struct winsize)
#define TIOCGWINSZ _IOR('t', 104, struct winsize)
#define FIOCLEX _IO('f', 1)
#define FIONCLEX _IO('f', 2)
#define FIOASYNC _IOW('f', 125, int)
#define FIONBIO _IOW('f', 126, int)
#define FIONREAD _IOR('f', 127, int)

__BEGIN_DECLS
int ioctl(int __fd, int __cmd, ...);
__END_DECLS

#endif
