/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: general utilities. */
#ifndef _NBT_QNX_STDLIB_H
#define _NBT_QNX_STDLIB_H

#include <sys/cdefs.h>
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>

#define RAND_MAX 32767u
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct {
	int quot;
	int rem;
} div_t;
typedef struct {
	long quot;
	long rem;
} ldiv_t;
typedef struct {
	long long quot;
	long long rem;
} lldiv_t;

__BEGIN_DECLS
extern char _Mbcurmax;
#define MB_CUR_MAX ((size_t)_Mbcurmax)

void abort(void) __NBT_NORETURN;
int abs(int __j);
int atexit(void (*__func)(void));
double atof(const char *__nptr);
int atoi(const char *__nptr);
long atol(const char *__nptr);
long long atoll(const char *__nptr);
void *bsearch(const void *__key, const void *__base, size_t __n, size_t __size, int (*__compar)(const void *, const void *));
void *calloc(size_t __n, size_t __size);
div_t div(int __numer, int __denom);
void exit(int __status) __NBT_NORETURN;
void _Exit(int __status) __NBT_NORETURN;
void free(void *__ptr);
char *getenv(const char *__name);
long labs(long __j);
ldiv_t ldiv(long __numer, long __denom);
long long llabs(long long __j);
lldiv_t lldiv(long long __numer, long long __denom);
void *malloc(size_t __size);
int mblen(const char *__s, size_t __n);
size_t mbstowcs(wchar_t *__restrict __pwcs, const char *__restrict __s, size_t __n);
int mbtowc(wchar_t *__restrict __pwc, const char *__restrict __s, size_t __n);
void qsort(void *__base, size_t __n, size_t __size, int (*__compar)(const void *, const void *));
int rand(void);
void *realloc(void *__ptr, size_t __size);
void srand(unsigned __seed);
double strtod(const char *__restrict __nptr, char **__restrict __endptr);
float strtof(const char *__restrict __nptr, char **__restrict __endptr);
long double strtold(const char *__restrict __nptr, char **__restrict __endptr);
long strtol(const char *__restrict __nptr, char **__restrict __endptr, int __base);
unsigned long strtoul(const char *__restrict __nptr, char **__restrict __endptr, int __base);
long long strtoll(const char *__restrict __nptr, char **__restrict __endptr, int __base);
unsigned long long strtoull(const char *__restrict __nptr, char **__restrict __endptr, int __base);
int system(const char *__cmd);
size_t wcstombs(char *__restrict __s, const wchar_t *__restrict __pwcs, size_t __n);
int wctomb(char *__s, wchar_t __wchar);

/* POSIX and others */
int __cxa_atexit(void (*__func)(void *), void *__arg, void *__dso);
long a64l(const char *__s);
char *l64a(long __value);
double drand48(void);
double erand48(unsigned short __x[3]);
long jrand48(unsigned short __x[3]);
void lcong48(unsigned short __param[7]);
long lrand48(void);
long mrand48(void);
long nrand48(unsigned short __x[3]);
unsigned short *seed48(unsigned short __seed16v[3]);
void srand48(long __seed);
int rand_r(unsigned *__seed);
char *realpath(const char *__restrict __path, char *__restrict __resolved);
int setenv(const char *__name, const char *__value, int __overwrite);
int unsetenv(const char *__name);
int putenv(char *__string);
int clearenv(void);
int mkstemp(char *__template);
char *mktemp(char *__template);
int getsubopt(char **__optionp, char *const *__tokens, char **__valuep);
int daemon(int __nochdir, int __noclose);
void *memalign(size_t __alignment, size_t __size);
int posix_memalign(void **__memptr, size_t __alignment, size_t __size);
void *valloc(size_t __size);
char *itoa(int __value, char *__buf, int __radix);
char *ltoa(long __value, char *__buf, int __radix);
char *ultoa(unsigned long __value, char *__buf, int __radix);
char *utoa(unsigned __value, char *__buf, int __radix);
/* QNX's stdlib.h brings process.h's _cmdname() too. */
char *_cmdname(char *__buf);
__END_DECLS

#ifdef __GNUC__
#include <alloca.h>
#endif

#endif
