/* Copyright 2008, 2009, 2011, Mariano Cerdeiro
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

#ifndef _OS_INTERNAL_ARCH_CPU_H_
#define _OS_INTERNAL_ARCH_CPU_H_
/** \brief FreeOSEK Os Internal Architecture Cpu Dependent Header File
 **
 ** \file avr/at90can/Os_Internal_Arch_Cpu.h
 ** \arch avr/at90can
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
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
  * 20110114 v0.1.0 MaCe	initial version
 */  

/*==================[cpu macros]=============================================*/
/** \brief at90can32 cpu definition */
#define at90can32	1
/** \brief at90can64 cpu definition */
#define at90can	2
/** \brief at90can128 cpu definition */
#define at90can128	3

/*==================[inclusions]=============================================*/
#ifndef CPU
#error CPU is not defined
#elif (CPU == at90can128)
#include "at90can128.h"
#else
#error not defined CPU
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/** \brief VIC type definition
 **
 ** This type is a structure used to control the VIC (Vector Interrupt
 ** Controller) of the LPCxxxx uController.
 **
 **/
typedef struct
{
	volatile uint32	IRQStatus;	/* IRQ Status Register */
	volatile uint32	FIQStatus;	/* FIQ Status Register */
	volatile uint32	RawIntr;		/* Raw Interrupt Status Register */
	volatile uint32	IntSelect;	/* Interrupt Select Register */
	volatile uint32	IntEnable;	/* Interrupt Enable Register */
	volatile uint32	IntEnClr;	/* Interrupt Enable Clear Register */
	volatile uint32	SoftInt;		/* Software Interrupt Register */
	volatile uint32	SoftIntClr;	/* Software Interrupt Clear Register */
	volatile uint32	Protection;	/* Protection enable register */
	volatile uint32	SWPrioMask;	/* Software Priority Mask Register */
	volatile uint32	reserved1[54];
	/* Vector Address Register 0..31 */
	volatile uint32	Address;		/* IRQ Address */
} VICType;

typedef struct
{
	volatile uint32	IR;
	volatile uint32	TCR;
	volatile uint32	TC;
	volatile uint32	PR;
	volatile uint32	PC;
	volatile uint32	MCR;
	volatile uint32	MR0;
	volatile uint32	MR1;
	volatile uint32	MR3;
	volatile uint32	CCR;
	volatile uint32	CR0;
	volatile uint32	CR1;
	volatile uint32	CR2;
	volatile uint32	CR3;
	volatile uint32	EMR;
	volatile uint32	reserved1[12];
	volatile uint32	CTCR;
} TIMERType;	

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void StartOs_Arch_Cpu(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_CPU_H_ */

