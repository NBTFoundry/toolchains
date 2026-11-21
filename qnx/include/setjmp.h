/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: non-local jumps. setjmp saves the signal
 * mask, as the C library's macro does. */
#ifndef _NBT_QNX_SETJMP_H
#define _NBT_QNX_SETJMP_H

#include <sys/_qnx_types.h>

typedef struct _jmp_buf {
	union {
		unsigned int __savearea[64];
		_Uint64t __alignment;
	} __jmpbuf_un;
	int __flg;
	long __msk[2];
} jmp_buf[1];
typedef jmp_buf sigjmp_buf;

__BEGIN_DECLS
int _setjmp(jmp_buf __env) __attribute__((__returns_twice__));
void _longjmp(jmp_buf __env, int __val) __NBT_NORETURN;
void __sigjmp_prolog(sigjmp_buf __env, int __savemask);
void siglongjmp(sigjmp_buf __env, int __val) __NBT_NORETURN;
__END_DECLS

#define sigsetjmp(env, savemask) (__sigjmp_prolog((env), (savemask)), _setjmp(env))
#define setjmp(env) sigsetjmp(env, 1)
#define longjmp(env, val) siglongjmp((env), (val))

#endif
