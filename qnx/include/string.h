/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: strings and memory. */
#ifndef _NBT_QNX_STRING_H
#define _NBT_QNX_STRING_H

#include <sys/cdefs.h>
#define __need_size_t
#define __need_NULL
#include <stddef.h>

__BEGIN_DECLS
void *memchr(const void *__s, int __c, size_t __n);
int memcmp(const void *__s1, const void *__s2, size_t __n);
void *memcpy(void *__restrict __s1, const void *__restrict __s2, size_t __n);
void *memmove(void *__s1, const void *__s2, size_t __n);
void *memset(void *__s, int __c, size_t __n);
char *strcat(char *__restrict __s1, const char *__restrict __s2);
char *strchr(const char *__s, int __c);
int strcmp(const char *__s1, const char *__s2);
int strcoll(const char *__s1, const char *__s2);
char *strcpy(char *__restrict __s1, const char *__restrict __s2);
size_t strcspn(const char *__s1, const char *__s2);
char *strerror(int __errnum);
size_t strlen(const char *__s);
char *strncat(char *__restrict __s1, const char *__restrict __s2, size_t __n);
int strncmp(const char *__s1, const char *__s2, size_t __n);
char *strncpy(char *__restrict __s1, const char *__restrict __s2, size_t __n);
char *strpbrk(const char *__s1, const char *__s2);
char *strrchr(const char *__s, int __c);
size_t strspn(const char *__s1, const char *__s2);
char *strstr(const char *__s1, const char *__s2);
char *strtok(char *__restrict __s1, const char *__restrict __s2);
size_t strxfrm(char *__restrict __s1, const char *__restrict __s2, size_t __n);

void *memccpy(void *__restrict __s1, const void *__restrict __s2, int __c, size_t __n);
char *strdup(const char *__s);
char *strtok_r(char *__s, const char *__sep, char **__lasts);
int strerror_r(int __errnum, char *__buf, size_t __buflen);
char *strsep(char **__stringp, const char *__delim);
char *strsignal(int __signo);
size_t strlcpy(char *__dst, const char *__src, size_t __size);
size_t strlcat(char *__dst, const char *__src, size_t __size);
char *strlwr(char *__s);
char *strupr(char *__s);
char *strrev(char *__s);
char *strnset(char *__s, int __c, size_t __n);
char *strset(char *__s, int __c);
int memicmp(const void *__s1, const void *__s2, size_t __n);
int stricmp(const char *__s1, const char *__s2);
int strnicmp(const char *__s1, const char *__s2, size_t __n);
__END_DECLS

#include <strings.h>

#endif
