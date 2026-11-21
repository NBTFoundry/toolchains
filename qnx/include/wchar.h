/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: wide characters. */
#ifndef _NBT_QNX_WCHAR_H
#define _NBT_QNX_WCHAR_H

#include <sys/_qnx_types.h>
#include <stdarg.h>
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>

#include <bits/types/mbstate_t.h>
typedef _Wintt wint_t;
typedef struct _Filet FILE;
struct tm;

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#define WCHAR_MAX __WCHAR_MAX__
#endif
#define WEOF ((wint_t)(-1))

__BEGIN_DECLS
wint_t btowc(int __c);
int wctob(wint_t __c);
int mbsinit(const mbstate_t *__ps);
size_t mbrlen(const char *__restrict __s, size_t __n, mbstate_t *__restrict __ps);
size_t mbrtowc(wchar_t *__restrict __pwc, const char *__restrict __s, size_t __n, mbstate_t *__restrict __ps);
size_t mbsrtowcs(wchar_t *__restrict __dst, const char **__restrict __src, size_t __len, mbstate_t *__restrict __ps);
size_t wcrtomb(char *__restrict __s, wchar_t __wc, mbstate_t *__restrict __ps);
size_t wcsrtombs(char *__restrict __dst, const wchar_t **__restrict __src, size_t __len, mbstate_t *__restrict __ps);
wint_t fgetwc(FILE *__fp);
wchar_t *fgetws(wchar_t *__restrict __s, int __n, FILE *__restrict __fp);
wint_t fputwc(wchar_t __c, FILE *__fp);
int fputws(const wchar_t *__restrict __s, FILE *__restrict __fp);
int fwide(FILE *__fp, int __mode);
int fwprintf(FILE *__restrict __fp, const wchar_t *__restrict __fmt, ...);
int fwscanf(FILE *__restrict __fp, const wchar_t *__restrict __fmt, ...);
wint_t getwc(FILE *__fp);
wint_t getwchar(void);
wint_t putwc(wchar_t __c, FILE *__fp);
wint_t putwchar(wchar_t __c);
int swprintf(wchar_t *__restrict __s, size_t __n, const wchar_t *__restrict __fmt, ...);
int swscanf(const wchar_t *__restrict __s, const wchar_t *__restrict __fmt, ...);
wint_t ungetwc(wint_t __c, FILE *__fp);
int vfwprintf(FILE *__restrict __fp, const wchar_t *__restrict __fmt, va_list __ap);
int vfwscanf(FILE *__restrict __fp, const wchar_t *__restrict __fmt, va_list __ap);
int vswprintf(wchar_t *__restrict __s, size_t __n, const wchar_t *__restrict __fmt, va_list __ap);
int vswscanf(const wchar_t *__restrict __s, const wchar_t *__restrict __fmt, va_list __ap);
int vwprintf(const wchar_t *__restrict __fmt, va_list __ap);
int vwscanf(const wchar_t *__restrict __fmt, va_list __ap);
int wprintf(const wchar_t *__restrict __fmt, ...);
int wscanf(const wchar_t *__restrict __fmt, ...);
double wcstod(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr);
float wcstof(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr);
long double wcstold(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr);
long wcstol(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr, int __base);
long long wcstoll(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr, int __base);
unsigned long wcstoul(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr, int __base);
unsigned long long wcstoull(const wchar_t *__restrict __nptr, wchar_t **__restrict __endptr, int __base);
wchar_t *wcscat(wchar_t *__restrict __s1, const wchar_t *__restrict __s2);
wchar_t *wcschr(const wchar_t *__s, wchar_t __c);
int wcscmp(const wchar_t *__s1, const wchar_t *__s2);
int wcscoll(const wchar_t *__s1, const wchar_t *__s2);
wchar_t *wcscpy(wchar_t *__restrict __s1, const wchar_t *__restrict __s2);
size_t wcscspn(const wchar_t *__s1, const wchar_t *__s2);
size_t wcsftime(wchar_t *__restrict __s, size_t __max, const wchar_t *__restrict __fmt, const struct tm *__restrict __tp);
size_t wcslen(const wchar_t *__s);
wchar_t *wcsncat(wchar_t *__restrict __s1, const wchar_t *__restrict __s2, size_t __n);
int wcsncmp(const wchar_t *__s1, const wchar_t *__s2, size_t __n);
wchar_t *wcsncpy(wchar_t *__restrict __s1, const wchar_t *__restrict __s2, size_t __n);
wchar_t *wcspbrk(const wchar_t *__s1, const wchar_t *__s2);
wchar_t *wcsrchr(const wchar_t *__s, wchar_t __c);
size_t wcsspn(const wchar_t *__s1, const wchar_t *__s2);
wchar_t *wcsstr(const wchar_t *__restrict __s1, const wchar_t *__restrict __s2);
wchar_t *wcstok(wchar_t *__restrict __s1, const wchar_t *__restrict __s2, wchar_t **__restrict __ptr);
size_t wcsxfrm(wchar_t *__restrict __s1, const wchar_t *__restrict __s2, size_t __n);
wchar_t *wmemchr(const wchar_t *__s, wchar_t __c, size_t __n);
int wmemcmp(const wchar_t *__s1, const wchar_t *__s2, size_t __n);
wchar_t *wmemcpy(wchar_t *__restrict __s1, const wchar_t *__restrict __s2, size_t __n);
wchar_t *wmemmove(wchar_t *__s1, const wchar_t *__s2, size_t __n);
wchar_t *wmemset(wchar_t *__s, wchar_t __c, size_t __n);
__END_DECLS

#endif
