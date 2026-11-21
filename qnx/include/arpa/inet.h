/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: Internet address conversion (libsocket). */
#ifndef _NBT_QNX_ARPA_INET_H
#define _NBT_QNX_ARPA_INET_H

#include <netinet/in.h>

__BEGIN_DECLS
in_addr_t inet_addr(const char *__cp);
int inet_aton(const char *__cp, struct in_addr *__addr);
in_addr_t inet_lnaof(struct in_addr __in);
struct in_addr inet_makeaddr(in_addr_t __net, in_addr_t __host);
in_addr_t inet_netof(struct in_addr __in);
in_addr_t inet_network(const char *__cp);
char *inet_ntoa(struct in_addr __in);
const char *inet_ntop(int __af, const void *__restrict __src, char *__restrict __dst, socklen_t __size);
int inet_pton(int __af, const char *__restrict __src, void *__restrict __dst);
__END_DECLS

#endif
