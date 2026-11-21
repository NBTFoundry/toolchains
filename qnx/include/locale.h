/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: locales (categories are bit masks). */
#ifndef _NBT_QNX_LOCALE_H
#define _NBT_QNX_LOCALE_H

#include <sys/cdefs.h>
#define __need_NULL
#include <stddef.h>

#define LC_COLLATE 0x01
#define LC_CTYPE 0x02
#define LC_MONETARY 0x04
#define LC_NUMERIC 0x08
#define LC_TIME 0x10
#define LC_MESSAGES 0x20
#define LC_ALL 0x3f

struct lconv {
	char *currency_symbol;
	char *int_curr_symbol;
	char *mon_decimal_point;
	char *mon_grouping;
	char *mon_thousands_sep;
	char *negative_sign;
	char *positive_sign;
	char frac_digits;
	char int_frac_digits;
	char n_cs_precedes;
	char n_sep_by_space;
	char n_sign_posn;
	char p_cs_precedes;
	char p_sep_by_space;
	char p_sign_posn;
	char int_n_cs_precedes;
	char int_n_sep_by_space;
	char int_n_sign_posn;
	char int_p_cs_precedes;
	char int_p_sep_by_space;
	char int_p_sign_posn;
	char *decimal_point;
	char *grouping;
	char *thousands_sep;
	char *_Frac_grouping;
	char *_Frac_sep;
	char *_False;
	char *_True;
	char *_No;
	char *_Yes;
	char *_Nostr;
	char *_Yesstr;
	char *_Reserved[8];
};

__BEGIN_DECLS
struct lconv *localeconv(void);
char *setlocale(int __category, const char *__locale);
__END_DECLS

#endif
