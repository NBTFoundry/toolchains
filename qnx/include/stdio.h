/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: standard input and output. FILE is the C
 * library's own structure: only pointers to it cross into user code. */
#ifndef _NBT_QNX_STDIO_H
#define _NBT_QNX_STDIO_H

#include <sys/_typedefs.h>
#include <stdarg.h>

typedef struct _Filet FILE;
typedef _Fpost fpos_t;

#define BUFSIZ 1024
#define FILENAME_MAX 255
#define FOPEN_MAX 16
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define TMP_MAX (26 * 26 * 26)
#define L_tmpnam 255
#define L_ctermid 16
#define P_tmpdir "/tmp/"

__BEGIN_DECLS
/* The three standard streams are the library's own objects. */
extern FILE _Stdin, _Stdout, _Stderr;
#define stdin (&_Stdin)
#define stdout (&_Stdout)
#define stderr (&_Stderr)

void clearerr(FILE *__fp);
int fclose(FILE *__fp);
int feof(FILE *__fp);
int ferror(FILE *__fp);
int fflush(FILE *__fp);
int fgetc(FILE *__fp);
int fgetpos(FILE *__restrict __fp, fpos_t *__restrict __pos);
char *fgets(char *__restrict __s, int __n, FILE *__restrict __fp);
FILE *fopen(const char *__restrict __path, const char *__restrict __mode) __NBT_ALIAS64("fopen64");
int fprintf(FILE *__restrict __fp, const char *__restrict __fmt, ...) __NBT_PRINTF(2, 3);
int fputc(int __c, FILE *__fp);
int fputs(const char *__restrict __s, FILE *__restrict __fp);
size_t fread(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __fp);
FILE *freopen(const char *__restrict __path, const char *__restrict __mode, FILE *__restrict __fp);
int fscanf(FILE *__restrict __fp, const char *__restrict __fmt, ...) __NBT_SCANF(2, 3);
int fseek(FILE *__fp, long __offset, int __whence);
int fsetpos(FILE *__fp, const fpos_t *__pos);
long ftell(FILE *__fp);
size_t fwrite(const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __fp);
int getc(FILE *__fp);
int getchar(void);
char *gets(char *__s);
void perror(const char *__s);
int printf(const char *__restrict __fmt, ...) __NBT_PRINTF(1, 2);
int putc(int __c, FILE *__fp);
int putchar(int __c);
int puts(const char *__s);
int remove(const char *__path);
int rename(const char *__old, const char *__new);
void rewind(FILE *__fp);
int scanf(const char *__restrict __fmt, ...) __NBT_SCANF(1, 2);
void setbuf(FILE *__restrict __fp, char *__restrict __buf);
int setvbuf(FILE *__restrict __fp, char *__restrict __buf, int __mode, size_t __size);
int snprintf(char *__restrict __s, size_t __n, const char *__restrict __fmt, ...) __NBT_PRINTF(3, 4);
int sprintf(char *__restrict __s, const char *__restrict __fmt, ...) __NBT_PRINTF(2, 3);
int sscanf(const char *__restrict __s, const char *__restrict __fmt, ...) __NBT_SCANF(2, 3);
FILE *tmpfile(void);
char *tmpnam(char *__s);
int ungetc(int __c, FILE *__fp);
int vfprintf(FILE *__restrict __fp, const char *__restrict __fmt, va_list __ap) __NBT_PRINTF(2, 0);
int vfscanf(FILE *__restrict __fp, const char *__restrict __fmt, va_list __ap) __NBT_SCANF(2, 0);
int vprintf(const char *__restrict __fmt, va_list __ap) __NBT_PRINTF(1, 0);
int vscanf(const char *__restrict __fmt, va_list __ap) __NBT_SCANF(1, 0);
int vsnprintf(char *__restrict __s, size_t __n, const char *__restrict __fmt, va_list __ap) __NBT_PRINTF(3, 0);
int vsprintf(char *__restrict __s, const char *__restrict __fmt, va_list __ap) __NBT_PRINTF(2, 0);
int vsscanf(const char *__restrict __s, const char *__restrict __fmt, va_list __ap) __NBT_SCANF(2, 0);

/* POSIX */
char *ctermid(char *__s);
FILE *fdopen(int __fd, const char *__mode);
int fileno(FILE *__fp);
void flockfile(FILE *__fp);
int ftrylockfile(FILE *__fp);
void funlockfile(FILE *__fp);
int fseeko(FILE *__fp, off_t __offset, int __whence) __NBT_ALIAS64("fseeko64");
off_t ftello(FILE *__fp) __NBT_ALIAS64("ftello64");
int fseeko64(FILE *__fp, off64_t __offset, int __whence);
off64_t ftello64(FILE *__fp);
FILE *fopen64(const char *__path, const char *__mode);
int getc_unlocked(FILE *__fp);
int getchar_unlocked(void);
int putc_unlocked(int __c, FILE *__fp);
int putchar_unlocked(int __c);
FILE *popen(const char *__command, const char *__mode);
int pclose(FILE *__fp);
char *tempnam(const char *__dir, const char *__pfx);
int getw(FILE *__fp);
int putw(int __w, FILE *__fp);
int fgetchar(void);
int fputchar(int __c);
__END_DECLS

#endif
