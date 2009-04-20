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

#ifndef _OSEK_INTERNAL_ARCH_CPU_H_
#define _OSEK_INTERNAL_ARCH_CPU_H_
/** \brief FreeOSEK Internal Architecture Cpu Dependent Header File
 **
 ** \file arm7/lpc2xxx/Osek_Internal_Arch_Cpu.h
 ** \arch arm7/lpc2xxx
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20090227 MaCe	initial version
 */  

/*==================[cpu macros]=============================================*/
/** \brief lpc2xxx cpu definition */
#define lpc2101	1
/** \brief lpc2xxx cpu definition */
#define lpc2102	2
/** \brief lpc2xxx cpu definition */
#define lpc2103	3
/** \brief lpc2xxx cpu definition */
#define lpc2104	4
/** \brief lpc2xxx cpu definition */
#define lpc2106	5
/** \brief lpc2xxx cpu definition */
#define lpc2109	6
/** \brief lpc2xxx cpu definition */
#define lpc2114	7
/** \brief lpc2xxx cpu definition */
#define lpc2119	8
/** \brief lpc2xxx cpu definition */
#define lpc2125	9
/** \brief lpc2xxx cpu definition */
#define lpc2129	10
/** \brief lpc2xxx cpu definition */
#define lpc2131	11
/** \brief lpc2xxx cpu definition */
#define lpc2132	12
/** \brief lpc2xxx cpu definition */
#define lpc2134	13
/** \brief lpc2xxx cpu definition */
#define lpc2136	14
/** \brief lpc2xxx cpu definition */
#define lpc2138	15
/** \brief lpc2xxx cpu definition */
#define lpc2141	16
/** \brief lpc2xxx cpu definition */
#define lpc2142	17
/** \brief lpc2xxx cpu definition */
#define lpc2144	18
/** \brief lpc2xxx cpu definition */
#define lpc2146	19
/** \brief lpc2xxx cpu definition */
#define lpc2148	20
/** \brief lpc2xxx cpu definition */
#define lpc2157	21
/** \brief lpc2xxx cpu definition */
#define lpc2158	22
/** \brief lpc2xxx cpu definition */
#define lpc2194	23
/** \brief lpc2xxx cpu definition */
#define lpc2210	24
/** \brief lpc2xxx cpu definition */
#define lpc2212	25
/** \brief lpc2xxx cpu definition */
#define lpc2214	26
/** \brief lpc2xxx cpu definition */
#define lpc2220	27
/** \brief lpc2xxx cpu definition */
#define lpc2290	28
/** \brief lpc2xxx cpu definition */
#define lpc2292	29
/** \brief lpc2xxx cpu definition */
#define lpc2294	30
/** \brief lpc2xxx cpu definition */
#define lpc2361	31
/** \brief lpc2xxx cpu definition */
#define lpc2362	32
/** \brief lpc2xxx cpu definition */
#define lpc2365	33
/** \brief lpc2xxx cpu definition */
#define lpc2366	34
/** \brief lpc2xxx cpu definition */
#define lpc2367	35
/** \brief lpc2xxx cpu definition */
#define lpc2368	36
/** \brief lpc2xxx cpu definition */
#define lpc2377	37
/** \brief lpc2xxx cpu definition */
#define lpc2378	38
/** \brief lpc2xxx cpu definition */
#define lpc2387	39
/** \brief lpc2xxx cpu definition */
#define lpc2388	40
/** \brief lpc2xxx cpu definition */
#define lpc2420	41
/** \brief lpc2xxx cpu definition */
#define lpc2458	42
/** \brief lpc2xxx cpu definition */
#define lpc2460	43
/** \brief lpc2xxx cpu definition */
#define lpc2468	44
/** \brief lpc2xxx cpu definition */
#define lpc2470	45
/** \brief lpc2xxx cpu definition */
#define lpc2478	46
/** \brief lpc2xxx cpu definition */
#define lpc2880	47
/** \brief lpc2xxx cpu definition */
#define lpc2888	48

/*==================[inclusions]=============================================*/
#ifndef CPU
#error CPU is not defined
#elif (CPU == lpc2468)
#include "lpc2468.h"
#elif (CPU == lpc2378)
#include "lpc23xx.h"
#else
#error not defined CPU
#endif

/*==================[macros]=================================================*/
#if (CPU == lpc2468)
/** \brief Size of the VIC entries */
#define VICVectAddrSIZE	32
#elif (CPU == lpc2378)
/** TODO check this */
#define VICVectAddrSIZE	16
#else
#error VICVectAddrSIZE not defined
#endif

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
	volatile uint32	VectAddr[VICVectAddrSIZE];
	volatile uint32	reserved2[64-VICVectAddrSIZE];
	/* Vector Priority Register 0..31 */
	volatile uint32	VectPriority[VICVectAddrSIZE];
	volatile	uint32	reserved3[832-VICVectAddrSIZE];
	volatile uint32	Address;		/* IRQ Address */
} VICType;

typedef struct
{
	volatile uint32	IR;
	volatile uint32	TCR;
	volatile	uint32	TC;
	volatile	uint32	PR;
	volatile	uint32	PC;
	volatile	uint32	MCR;
	volatile	uint32	MR0;
	volatile	uint32	MR1;
	volatile	uint32	MR3;
	volatile	uint32	CCR;
	volatile	uint32	CR0;
	volatile	uint32	CR1;
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
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_CPU_H_ */

