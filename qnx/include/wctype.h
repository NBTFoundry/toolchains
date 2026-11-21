/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: wide character classes. */
#ifndef _NBT_QNX_WCTYPE_H
#define _NBT_QNX_WCTYPE_H

#include <wchar.h>

typedef unsigned int wctype_t;
typedef const wchar_t *wctrans_t;

__BEGIN_DECLS
int iswalnum(wint_t __c);
int iswalpha(wint_t __c);
int iswblank(wint_t __c);
int iswcntrl(wint_t __c);
int iswdigit(wint_t __c);
int iswgraph(wint_t __c);
int iswlower(wint_t __c);
int iswprint(wint_t __c);
int iswpunct(wint_t __c);
int iswspace(wint_t __c);
int iswupper(wint_t __c);
int iswxdigit(wint_t __c);
int iswctype(wint_t __c, wctype_t __desc);
wctype_t wctype(const char *__property);
wint_t towlower(wint_t __c);
wint_t towupper(wint_t __c);
wint_t towctrans(wint_t __c, wctrans_t __desc);
wctrans_t wctrans(const char *__property);
__END_DECLS

#endif
