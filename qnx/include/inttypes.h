/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: format macros for the integer types
 * (ILP32: 64-bit values are long long). */
#ifndef _NBT_QNX_INTTYPES_H
#define _NBT_QNX_INTTYPES_H

#include <stdint.h>
#include <sys/cdefs.h>

#define __NBT_PRI8 "hh"
#define __NBT_PRI16 "h"
#define __NBT_PRI32 ""
#define __NBT_PRI64 "ll"
#define __NBT_PRIPTR ""

#define PRId8 __NBT_PRI8 "d"
#define PRId16 __NBT_PRI16 "d"
#define PRId32 __NBT_PRI32 "d"
#define PRId64 __NBT_PRI64 "d"
#define PRIi8 __NBT_PRI8 "i"
#define PRIi16 __NBT_PRI16 "i"
#define PRIi32 __NBT_PRI32 "i"
#define PRIi64 __NBT_PRI64 "i"
#define PRIo8 __NBT_PRI8 "o"
#define PRIo16 __NBT_PRI16 "o"
#define PRIo32 __NBT_PRI32 "o"
#define PRIo64 __NBT_PRI64 "o"
#define PRIu8 __NBT_PRI8 "u"
#define PRIu16 __NBT_PRI16 "u"
#define PRIu32 __NBT_PRI32 "u"
#define PRIu64 __NBT_PRI64 "u"
#define PRIx8 __NBT_PRI8 "x"
#define PRIx16 __NBT_PRI16 "x"
#define PRIx32 __NBT_PRI32 "x"
#define PRIx64 __NBT_PRI64 "x"
#define PRIX8 __NBT_PRI8 "X"
#define PRIX16 __NBT_PRI16 "X"
#define PRIX32 __NBT_PRI32 "X"
#define PRIX64 __NBT_PRI64 "X"

#define PRIdLEAST8 PRId8
#define PRIdLEAST16 PRId16
#define PRIdLEAST32 PRId32
#define PRIdLEAST64 PRId64
#define PRIuLEAST8 PRIu8
#define PRIuLEAST16 PRIu16
#define PRIuLEAST32 PRIu32
#define PRIuLEAST64 PRIu64
#define PRIxLEAST8 PRIx8
#define PRIxLEAST16 PRIx16
#define PRIxLEAST32 PRIx32
#define PRIxLEAST64 PRIx64
#define PRIdFAST8 PRId8
#define PRIdFAST16 PRId16
#define PRIdFAST32 PRId32
#define PRIdFAST64 PRId64
#define PRIuFAST8 PRIu8
#define PRIuFAST16 PRIu16
#define PRIuFAST32 PRIu32
#define PRIuFAST64 PRIu64
#define PRIxFAST8 PRIx8
#define PRIxFAST16 PRIx16
#define PRIxFAST32 PRIx32
#define PRIxFAST64 PRIx64

#define PRIdMAX PRId64
#define PRIiMAX PRIi64
#define PRIoMAX PRIo64
#define PRIuMAX PRIu64
#define PRIxMAX PRIx64
#define PRIXMAX PRIX64
#define PRIdPTR __NBT_PRIPTR "d"
#define PRIiPTR __NBT_PRIPTR "i"
#define PRIoPTR __NBT_PRIPTR "o"
#define PRIuPTR __NBT_PRIPTR "u"
#define PRIxPTR __NBT_PRIPTR "x"
#define PRIXPTR __NBT_PRIPTR "X"

#define SCNd8 __NBT_PRI8 "d"
#define SCNd16 __NBT_PRI16 "d"
#define SCNd32 __NBT_PRI32 "d"
#define SCNd64 __NBT_PRI64 "d"
#define SCNi8 __NBT_PRI8 "i"
#define SCNi16 __NBT_PRI16 "i"
#define SCNi32 __NBT_PRI32 "i"
#define SCNi64 __NBT_PRI64 "i"
#define SCNu8 __NBT_PRI8 "u"
#define SCNu16 __NBT_PRI16 "u"
#define SCNu32 __NBT_PRI32 "u"
#define SCNu64 __NBT_PRI64 "u"
#define SCNx8 __NBT_PRI8 "x"
#define SCNx16 __NBT_PRI16 "x"
#define SCNx32 __NBT_PRI32 "x"
#define SCNx64 __NBT_PRI64 "x"
#define SCNdMAX SCNd64
#define SCNuMAX SCNu64
#define SCNxMAX SCNx64
#define SCNdPTR __NBT_PRIPTR "d"
#define SCNuPTR __NBT_PRIPTR "u"
#define SCNxPTR __NBT_PRIPTR "x"

typedef struct {
	intmax_t quot;
	intmax_t rem;
} imaxdiv_t;

__BEGIN_DECLS
intmax_t imaxabs(intmax_t __j);
imaxdiv_t imaxdiv(intmax_t __numer, intmax_t __denom);
intmax_t strtoimax(const char *__nptr, char **__endptr, int __base);
uintmax_t strtoumax(const char *__nptr, char **__endptr, int __base);
__END_DECLS

#endif
