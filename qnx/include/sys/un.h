/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: local (Unix domain) socket addresses. */
#ifndef _NBT_QNX_SYS_UN_H
#define _NBT_QNX_SYS_UN_H

#include <sys/socket.h>

struct sockaddr_un {
	_Uint8t sun_len;
	sa_family_t sun_family;
	char sun_path[104];
};

#endif
