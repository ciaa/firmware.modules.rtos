/* Copyright 2008, 2009, Mariano Cerdeiro
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
 * that communicate with FreeOSEK solely through the OpenSEK defined interface. 
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

/** \brief OpenDRV StartUp assembler file for arm
 **
 ** \file arm/SrtartUp_Asm.s
 ** \arch arm
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_StartUp
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081126 v0.1.0 MaCe       - initial version based on software without
 *                              author.
 */

/*==================[inclusions]=============================================*/

/*==================[macros and definitions]=================================*/
/* Stack Sizes definitions */
.set  UND_STACK_SIZE, 0x00000030	/* stack for "undefined instruction" interrupts is 4 bytes */
.set  ABT_STACK_SIZE, 0x00000030	/* stack for "abort" interrupts is 4 bytes */
.set  FIQ_STACK_SIZE, 0x00000030	/* stack for "FIQ" interrupts  is 4 bytes */
.set  IRQ_STACK_SIZE, 0X00000030	/* stack for "IRQ" normal interrupts is 4 bytes */
.set  SVC_STACK_SIZE, 0x00000030	/* stack for "SVC" supervisor mode is 4 bytes */

/* Interrupts Modes */
.set  MODE_USR, 0x10	/* Normal User Mode */
.set  MODE_FIQ, 0x11	/* FIQ Processing Fast Interrupts Mode */
.set  MODE_IRQ, 0x12	/* IRQ Processing Standard Interrupts Mode */
.set  MODE_SVC, 0x13	/* Supervisor Processing Software Interrupts Mode */
.set  MODE_ABT, 0x17	/* Abort Processing memory Faults Mode */
.set  MODE_UND, 0x1B	/* Undefined Processing Undefined Instructions Mode      */
.set  MODE_SYS, 0x1F	/* System Running Priviledged Operating System Tasks  Mode  */

.set  I_BIT, 0x80	/* when I bit is set, IRQ is disabled (program status registers) */
.set  F_BIT, 0x40	/* when F bit is set, FIQ is disabled (program status registers) */

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
.text
.arm

.global	Reset_Handler
.global	_startup
.func		_startup

_startup:

_vectors:
			ldr PC, Reset_Addr
			ldr PC, Undef_Addr
			ldr PC, SWI_Addr
			ldr PC, PAbt_Addr
			ldr PC, DAbt_Addr
			nop						/* Reserved Vector (holds Philips ISP checksum) */
			ldr PC, [PC,#-0xFF]  /* IRQ Vector */
			ldr PC, FIQ_Addr		/* Fast Interrupt */

Reset_Addr:     .word   Reset_Handler
Undef_Addr:     .word   UNDEF_Routine	/* defined in StartUp.c  */
SWI_Addr:       .word   SWI_Routine		/* defined in StartUp.c  */
PAbt_Addr:      .word   UNDEF_Routine	/* defined in StartUp.c  */
DAbt_Addr:      .word   UNDEF_Routine	/* defined in StartUp.c  */
IRQ_Addr:       .word   IRQ_Routine		/* defined in StartUp.c  */
FIQ_Addr:       .word   FIQ_Routine		/* defined in StartUp.c  */
                .word   0					/* rounds the vectors and ISR addresses to 64 bytes total  */

Reset_Handler:
	/* Setup a stack for each mode - note that this only sets up a usable stack
   	for User mode.   Also each mode is setup with interrupts initially disabled. */

	ldr   r0, = SEC_STACK_END
	msr   CPSR_c, #MODE_UND|I_BIT|F_BIT    /* Undefined Instruction Mode  */
	mov   sp, r0
	sub   r0, r0, #UND_STACK_SIZE
	msr   CPSR_c, #MODE_ABT|I_BIT|F_BIT    /* Abort Mode */
	mov   sp, r0
	sub   r0, r0, #ABT_STACK_SIZE
	msr   CPSR_c, #MODE_FIQ|I_BIT|F_BIT    /* FIQ Mode */
	mov   sp, r0
	sub   r0, r0, #FIQ_STACK_SIZE
	msr   CPSR_c, #MODE_IRQ|I_BIT|F_BIT    /* IRQ Mode */
	mov   sp, r0
	sub   r0, r0, #IRQ_STACK_SIZE
	msr   CPSR_c, #MODE_SVC|I_BIT|F_BIT    /* Supervisor Mode */
	mov   sp, r0
	sub   r0, r0, #SVC_STACK_SIZE
	msr   CPSR_c, #MODE_SYS|I_BIT|F_BIT    /* User Mode */
	mov   sp, r0

	/* copy .data section (Copy from ROM to RAM) */
	ldr     R1, = SEC_END_CODE
	ldr     R2, = SEC_START_DATA_INIT
	ldr     R3, = SEC_END_DATA_INIT
1:
	cmp     R2, R3
	ldrlo   R0, [R1], #4
	strlo   R0, [R2], #4
   blo     1b

	/* Clear .bss section (Zero init)  */
	mov     R0, #0
	ldr     R1, = SEC_START_DATA
   ldr     R2, = SEC_END_DATA
2:
	cmp     R1, R2
	strlo   R0, [R1], #4
   blo     2b

	/* Enter the C code  */
   b       StartUp

.endfunc
.end

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

