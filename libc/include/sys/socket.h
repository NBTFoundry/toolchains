/* SPDX-License-Identifier: MPL-2.0 */
/* The part of sockets an NBT app module sees: the manager's bridge input
 * datagrams, received through the host ABI (sdk/module/runtime/sys.c). Lifecycle
 * hands out pseudo descriptors for them; no other socket exists. */
#ifndef NBT_MODULE_SYS_SOCKET_H
#define NBT_MODULE_SYS_SOCKET_H

#include <stddef.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int socklen_t;

#define SOL_SOCKET 0xffff
#define SO_TYPE 0x1008
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define MSG_DONTWAIT 0x80

ssize_t recv(int fd, void* buf, size_t len, int flags);
int getsockopt(int fd, int level, int name, void* value, socklen_t* len);

#ifdef __cplusplus
}
#endif

#endif
