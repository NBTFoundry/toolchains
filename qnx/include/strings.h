/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: BSD string functions. */
#ifndef _NBT_QNX_STRINGS_H
#define _NBT_QNX_STRINGS_H

#include <sys/cdefs.h>
#define __need_size_t
#include <stddef.h>

__BEGIN_DECLS
int bcmp(const void *__s1, const void *__s2, size_t __n);
void bcopy(const void *__s1, void *__s2, size_t __n);
void bzero(void *__s, size_t __n);
int ffs(int __i);
char *index(const char *__s, int __c);
char *rindex(const char *__s, int __c);
int strcasecmp(const char *__s1, const char *__s2);
int strncasecmp(const char *__s1, const char *__s2, size_t __n);
__END_DECLS

#endif
