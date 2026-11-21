/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: select() and descriptor sets (256 bits). */
#ifndef _NBT_QNX_SYS_SELECT_H
#define _NBT_QNX_SYS_SELECT_H

#include <sys/_typedefs.h>

typedef int __fd_mask;
typedef __fd_mask fd_mask;
#define __NFDBITS ((int)(sizeof(__fd_mask) * 8))
#define NFDBITS __NFDBITS
#define FD_SETSIZE 256

typedef struct fd_set {
	__fd_mask fds_bits[(FD_SETSIZE + __NFDBITS - 1) / __NFDBITS];
} fd_set;

#define FD_SET(fd, p) ((p)->fds_bits[(fd) / __NFDBITS] |= (1 << ((fd) % __NFDBITS)))
#define FD_CLR(fd, p) ((p)->fds_bits[(fd) / __NFDBITS] &= ~(1 << ((fd) % __NFDBITS)))
#define FD_ISSET(fd, p) ((p)->fds_bits[(fd) / __NFDBITS] & (1 << ((fd) % __NFDBITS)))
#define FD_ZERO(p) __builtin_memset((p), 0, sizeof *(p))

struct timeval {
	time_t tv_sec;
	suseconds_t tv_usec;
};

__BEGIN_DECLS
int select(int __nfds, fd_set *__readfds, fd_set *__writefds, fd_set *__errorfds, struct timeval *__timeout);
__END_DECLS

#endif
