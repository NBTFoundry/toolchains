/* SPDX-License-Identifier: MPL-2.0 */
/* poll() for modules and guests: declared so portable code compiles; a module
 * has no descriptors worth waiting on, so it fails with ENOSYS. */
#ifndef NBT_MODULE_POLL_H
#define NBT_MODULE_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

struct pollfd {
  int fd;
  short events;
  short revents;
};
typedef unsigned int nfds_t;

#define POLLIN 0x001
#define POLLPRI 0x002
#define POLLOUT 0x004
#define POLLERR 0x008
#define POLLHUP 0x010
#define POLLNVAL 0x020

int poll(struct pollfd* fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
}
#endif

#endif
