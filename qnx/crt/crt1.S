/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: program entry. The loader (ldqnx.so.2)
 * jumps here with the exit function to register in r0 and the arguments on
 * the stack: argc, argv[], NULL, envp[], NULL, auxv[]. This sets up the C
 * library, runs the constructors and calls main(), as the car's own
 * programs start. */
	.syntax unified
	.arm
	.text
	.globl	_start
	.type	_start, %function
_start:
	mov	r4, r0			@ the loader's exit function
	ldr	r0, [sp]		@ argc
	add	r1, sp, #4		@ argv
	add	r2, r1, r0, lsl #2
	add	r2, r2, #4		@ envp: past argv's NULL
	mov	r3, r2
1:	ldr	ip, [r3], #4		@ auxv: past envp's NULL
	teq	ip, #0
	bne	1b
	push	{r4}			@ fifth argument of _init_libc
	mov	r4, r0
	mov	r5, r1
	mov	r6, r2
	bl	_init_libc(PLT)		@ (argc, argv, envp, auxv, exit function)
	add	sp, sp, #4
	adr	r7, .Lgot
	ldr	r8, .Lgot
	add	r8, r8, r7		@ r8 = the GOT
	ldr	r0, .Lpreinit_start
	ldr	r0, [r8, r0]
	ldr	r1, .Lpreinit_end
	ldr	r1, [r8, r1]
	bl	_preinit_array(PLT)
	ldr	r0, .Lfini
	ldr	r0, [r8, r0]
	bl	atexit(PLT)
	ldr	r0, .Lfini_start
	ldr	r0, [r8, r0]
	ldr	r1, .Lfini_end
	ldr	r1, [r8, r1]
	bl	_fini_array(PLT)
	bl	_init
	ldr	r0, .Linit_start
	ldr	r0, [r8, r0]
	ldr	r1, .Linit_end
	ldr	r1, [r8, r1]
	bl	_init_array(PLT)
	ldr	r0, .Lerrno
	ldr	r0, [r8, r0]		@ the main thread's errno
	mov	r1, #0
	str	r1, [r0]
	mov	r0, r4
	mov	r1, r5
	mov	r2, r6
	bl	main
	bl	exit(PLT)
2:	b	2b

	.align	2
.Lgot:	.word	_GLOBAL_OFFSET_TABLE_ - .Lgot
.Lpreinit_start: .word	__preinit_array_start(GOT)
.Lpreinit_end:	.word	__preinit_array_end(GOT)
.Lfini:		.word	_fini(GOT)
.Lfini_start:	.word	__fini_array_start(GOT)
.Lfini_end:	.word	__fini_array_end(GOT)
.Linit_start:	.word	__init_array_start(GOT)
.Linit_end:	.word	__init_array_end(GOT)
.Lerrno:	.word	errno(GOT)
	.size	_start, . - _start

/* The arrays run the constructors and destructors; .init and .fini stay
 * empty. */
	.globl	_init
	.type	_init, %function
_init:	bx	lr
	.size	_init, . - _init
	.globl	_fini
	.type	_fini, %function
_fini:	bx	lr
	.size	_fini, . - _fini

/* QNX note type 3: the main thread's stack (1 MiB reserved), as the QNX
 * linker writes it; without it the stack is a few kilobytes. */
	.section .note.qnx.stack, "a", %note
	.balign	4
	.word	4, 8, 3
	.asciz	"QNX"
	.word	0, 0x100000

/* The loader, here rather than as --dynamic-linker=/usr/lib/...: MSYS2
 * rewrites that argument into a Windows path when make runs ld.lld.exe.
 * lld makes PT_INTERP from a section of this name; "R" keeps it from
 * --gc-sections, as nothing refers to it. */
	.section .interp, "aR", %progbits
	.asciz	"/usr/lib/ldqnx.so.2"

	.section .note.GNU-stack, "", %progbits
