/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: poll(). */
#ifndef _NBT_QNX_POLL_H
#define _NBT_QNX_POLL_H

#include <sys/cdefs.h>

typedef unsigned int nfds_t;

struct pollfd {
	int fd;
	short events;
	short revents;
};

#define POLLRDNORM 0x0001
#define POLLOUT 0x0002
#define POLLWRNORM POLLOUT
#define POLLRDBAND 0x0004
#define POLLIN (POLLRDNORM | POLLRDBAND)
#define POLLPRI 0x0008
#define POLLWRBAND 0x0010
#define POLLERR 0x0020
#define POLLHUP 0x0040
#define POLLNVAL 0x1000
#define INFTIM (-1)

__BEGIN_DECLS
int poll(struct pollfd *__fds, nfds_t __nfds, int __timeout);
__END_DECLS

#endif
