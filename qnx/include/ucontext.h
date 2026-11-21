/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the context an SA_SIGINFO handler gets
 * (ARM registers, then the VFP state). */
#ifndef _NBT_QNX_UCONTEXT_H
#define _NBT_QNX_UCONTEXT_H

#include <signal.h>

typedef struct arm_cpu_registers {
	_Uint32t gpr[16];
	_Uint32t spsr;
} ARM_CPU_REGISTERS;

#define ARM_REG_R0 0
#define ARM_REG_FP 11
#define ARM_REG_IP 12
#define ARM_REG_SP 13
#define ARM_REG_LR 14
#define ARM_REG_PC 15
#define ARM_REG_SPSR 16

typedef struct arm_fpu_registers {
	union {
		struct vfp {
			union {
				_Uint64t X[32];
				_Uint32t S[32];
				_Uint64t D[32];
			} reg;
			_Uint32t fpscr;
			_Uint32t fpexc;
			_Uint32t fpinst;
			_Uint32t fpinst2;
		} vfp;
	} un;
} ARM_FPU_REGISTERS;

typedef struct {
	ARM_CPU_REGISTERS cpu;
	ARM_FPU_REGISTERS fpu;
} mcontext_t;

#define GET_REGIP(regs) ((regs)->gpr[ARM_REG_PC])
#define GET_REGSP(regs) ((regs)->gpr[ARM_REG_SP])

struct __ucontext_t {
	struct __ucontext_t *uc_link;
	sigset_t uc_sigmask;
	stack_t uc_stack;
	mcontext_t uc_mcontext;
};

#endif
