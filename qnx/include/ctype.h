/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: character classes, as the C library's
 * functions (no table macros). */
#ifndef _NBT_QNX_CTYPE_H
#define _NBT_QNX_CTYPE_H

#include <sys/cdefs.h>

__BEGIN_DECLS
int isalnum(int __c);
int isalpha(int __c);
int isblank(int __c);
int iscntrl(int __c);
int isdigit(int __c);
int isgraph(int __c);
int islower(int __c);
int isprint(int __c);
int ispunct(int __c);
int isspace(int __c);
int isupper(int __c);
int isxdigit(int __c);
int tolower(int __c);
int toupper(int __c);
int isascii(int __c);
int toascii(int __c);
int _tolower(int __c);
int _toupper(int __c);
__END_DECLS

#endif
