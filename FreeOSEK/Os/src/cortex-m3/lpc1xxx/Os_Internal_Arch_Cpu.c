/* Copyright 2008, 2009, Mariano Cerdeiro
 * Copyright 2011 Sebastián Viviani
 * 
 *  * This file is part of FreeOSEK.
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

/** \brief FreeOSEK Os Internal ARCH CPU Dependece Implementation File
 **
 ** \file cortex-m3/lpc1xxx/Os_Internal_Arch_Cpu.c
 ** \arch cortex-m3/lpc1xxx
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * SLV			Sebastián Viviani
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20110126 v0.1.0 SLV imported from arm7 0.1.2
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void StartOs_Arch_Cpu
(
	void
)
{
#if (ALARMS_COUNT != 0)
	/* TODO this has to be improved */
	TIM0->CTCR = 0;	/* bit 1-0: 00 Timer mode
										01 Counter mode at rising edge
										10 Counter mode at falling edge
										11 Counter mode both edges
							bit 3-2: only valid when bit 1-0 != 0
										00 CAPn.0 for timer n
										01 CAPn.1 for timer n
										1x reserved
							bit 7-4: reserved
						*/

	TIM0->PR = 12;		/* 32-bits prescaler register */
						/* 1 incremenet every 1us */

	/* set Timer Control Register TCR */
	TIM0->TCR = 0x3;	/* bit 0:	enable counter
							bit 1:	reset counter
							bit 7-2: reserved */

	TIM0->TCR = 0x1;	/* bit 1:	clear reset now */

	TIM0->MR0 = 1000;	/* timer match 0 every 1ms*/

	TIM0->MCR = 0x3;	/* bit 0: interrupt if MR0 match the TC
							bit 1: reset TC if MR0 match */

	/* set the TIMER0 as FIQ Interrupt */
	//((VICType*)VIC_BASE_ADDR)->IntSelect |= 1<<4;
	

	/* enable TIMER0 interrupt */
	NVIC_EnableIRQ( TIMER0_IRQn );
#endif /* #if (ALARMS_COUNT != 0) */

	/* enable interrupts */
	__enable_irq();
/*
	__asm__ __volatile__
	("											\
		MRS R7, CPSR 				\n\t	\
		AND R7, R7, #0xFFFFFF9F \n\t	\
		MSR CPSR, R7				\n\t	\
	 " : : : "r7" );
	 */
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


