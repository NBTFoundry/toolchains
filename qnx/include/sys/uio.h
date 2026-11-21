/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: scatter and gather I/O. */
#ifndef _NBT_QNX_SYS_UIO_H
#define _NBT_QNX_SYS_UIO_H

#include <sys/_typedefs.h>

#define UIO_MAXIOV 1024
#define UIO_SMALLIOV 8


__BEGIN_DECLS
ssize_t readv(int __fd, const struct iovec *__iov, int __nparts);
ssize_t writev(int __fd, const struct iovec *__iov, int __nparts);
__END_DECLS

#endif
