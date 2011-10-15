/* Copyright 2011 Tamas Kenderes
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief FreeOSEK Driver StartUp assembler file for arm7/at91sam7x
 **
 ** \file arm7/at91sam7x/StartUp.s
 ** \arch arm7/at91sam7x
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_StartUp
 ** @{ */
/** \addtogroup FreeOSEK_Drv_StartUp_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.0 KT	initial version based on lpc2xxx/StartUp.s
 */

/*==================[inclusions]=============================================*/

/*==================[macros and definitions]=================================*/
/* Stack Sizes definitions */
.set  UND_STACK_SIZE, 0x00000004		/* stack for "undefined instruction" interrupts is 4 bytes  */
.set  ABT_STACK_SIZE, 0x00000004		/* stack for "abort" interrupts is 4 bytes                  */
.set  FIQ_STACK_SIZE, 0x00000004		/* stack for "FIQ" interrupts  is 4 bytes                   */
.set  IRQ_STACK_SIZE, 0X00000100		/* stack for "IRQ" normal interrupts is 256 bytes           */
.set  SVC_STACK_SIZE, 0x00000004		/* stack for "SVC" supervisor mode is 4 bytes               */

/* Interrupts Modes */
.set  MODE_USR, 0x10	/* Normal User Mode */
.set  MODE_FIQ, 0x11	/* FIQ Processing Fast Interrupts Mode */
.set  MODE_IRQ, 0x12	/* IRQ Processing Standard Interrupts Mode */
.set  MODE_SVC, 0x13	/* Supervisor Processing Software Interrupts Mode */
.set  MODE_ABT, 0x17	/* Abort Processing memory Faults Mode */
.set  MODE_UND, 0x1B	/* Undefined Processing Undefined Instructions Mode      */
.set  MODE_SYS, 0x1F	/* System Running Priviledged Operating System Tasks  Mode  */

.set  I_BIT, 0x80		/* when I bit is set, IRQ is disabled (CPSR) */
.set  F_BIT, 0x40		/* when F bit is set, FIQ is disabled (CPSR) */

/* Addresses for the at91sam7x-specific interrupt handler */
.set AT91C_BASE_AIC, 0xFFFFF000
.set AIC_IVR,        0x00000100
.set AIC_EOICR,      0x00000130

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
.text
.align	4
.arm

.global	ResetHandler
.global	IrqHandler
.global	_startup
.func		_startup

_startup:

_vectors:
			ldr PC, Reset_Addr
			ldr PC, Undef_Addr
			ldr PC, SWI_Addr
			ldr PC, PAbt_Addr
			ldr PC, DAbt_Addr
			nop						/* Reserved */
			ldr PC, IRQ_Addr
			ldr PC, FIQ_Addr

Reset_Addr:  .word  ResetHandler					/* defined in this module below */
Undef_Addr:  .word  DefaultUndefHandler_Arch	/* defined in Osek_Internal_Arch.c */
SWI_Addr:    .word  DefaultSwiHandler_Arch	/* defined in Osek_Internal_Arch.c */
PAbt_Addr:   .word  DefaultAbortHandler_Arch	/* defined in Osek_Internal_Arch.c */
DAbt_Addr:   .word  DefaultAbortHandler_Arch	/* defined in Osek_Internal_Arch.c */
IRQ_Addr:    .word  IrqHandler					/* defined in this module below */
FIQ_Addr:    .word  DefaultFiqHandler_Arch	/* defined in Osek_Internal_Arch.c */
             .word  0								/* rounds the vectors and ISR
																addresses to 64 bytes total */

ResetHandler:
	/* Set up a stack for each mode. Note that this only sets up a usable stack for
		user mode. Also each mode is set up with interrupts initially disabled. */
	ldr     r0, =_stack_end
	msr     CPSR_c, #MODE_UND|I_BIT|F_BIT    /* Undefined Instruction Mode  */
	mov     sp, r0
	sub     r0, r0, #UND_STACK_SIZE
	msr     CPSR_c, #MODE_ABT|I_BIT|F_BIT    /* Abort Mode */
	mov     sp, r0
	sub     r0, r0, #ABT_STACK_SIZE
	msr     CPSR_c, #MODE_FIQ|I_BIT|F_BIT    /* FIQ Mode */
	mov     sp, r0
	sub     r0, r0, #FIQ_STACK_SIZE
	msr     CPSR_c, #MODE_IRQ|I_BIT|F_BIT    /* IRQ Mode */
	mov     sp, r0
	sub     r0, r0, #IRQ_STACK_SIZE
	msr     CPSR_c, #MODE_SVC|I_BIT|F_BIT    /* Supervisor Mode */
	mov     sp, r0
	sub     r0, r0, #SVC_STACK_SIZE
	msr     CPSR_c, #MODE_SYS|I_BIT|F_BIT    /* User Mode */
	mov     sp, r0

	/* Copy .data section (Copy from ROM to RAM) */
	ldr     R1, =_etext
	ldr     R2, =_data
	ldr     R3, =_edata
1:
	cmp     R2, R3
	ldrlo   R0, [R1], #4
	strlo   R0, [R2], #4
	blo     1b

	/* Clear .bss section (Zero init)  */
	mov     R0, #0
	ldr     R1, =_bss_start
	ldr     R2, =_bss_end
2:
	cmp     R1, R2
	strlo   R0, [R1], #4
	blo     2b

	/* Enter the C code  */
	b       main

IrqHandler:
/* Save interrupt context on the stack (also allows nesting) */
	sub     lr, lr, #4
	stmfd   sp!, {lr}
	mrs     lr, SPSR
	stmfd   sp!, {r0, lr}

/* Write in the IVR to support Protect Mode (JTAG debuggers, etc.) */
	ldr     lr, =AT91C_BASE_AIC
	ldr     r0, [r14, #AIC_IVR]
	str     lr, [r14, #AIC_IVR]

/* Branch to interrupt handler in IRQ mode */
	stmfd   sp!, {r1-r3, r4, r12, lr}
	mov     lr, pc
	bx      r0
	ldmia   sp!, {r1-r3, r4, r12, lr}
	msr     CPSR_c, #MODE_IRQ | I_BIT

/* Acknowledge interrupt */
	ldr     lr, =AT91C_BASE_AIC
	str     lr, [r14, #AIC_EOICR]

/* Restore interrupt context and branch back to calling code */
	ldmia   sp!, {r0, lr}
	msr     SPSR_cxsf, lr
	ldmia   sp!, {pc}^

.endfunc
.end

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
