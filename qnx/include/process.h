/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: processes, the QNX way (spawn*() and the
 * program's own path). stdlib.h includes it, as QNX's does. */
#ifndef _NBT_QNX_PROCESS_H
#define _NBT_QNX_PROCESS_H

#include <sys/cdefs.h>

__BEGIN_DECLS
/* The running program's path into buf (PATH_MAX bytes); buf, or NULL. */
char *_cmdname(char *__buf);
__END_DECLS

#include <spawn.h>

#endif
