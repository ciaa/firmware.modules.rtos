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

#ifndef _OS_INTERNAL_ARCH_CPU_H_
#define _OS_INTERNAL_ARCH_CPU_H_
/** \brief FreeOSEK Os Internal Architecture Cpu Dependent Header File
 **
 ** \file arm7/at91sam7x/Os_Internal_Arch_Cpu.h
 ** \arch arm7/at91sam7x
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
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.0 KT	initial version
 */

/*==================[cpu macros]=============================================*/
/** \brief at91sam7x cpu definition */
#define at91sam7x128	1
/** \brief at91sam7x cpu definition */
#define at91sam7x256	2
/** \brief at91sam7x cpu definition */
#define at91sam7x512	3

/*==================[inclusions]=============================================*/
#ifndef CPU
#error No CPU defined
#elif (CPU == at91sam7x128)
#include "AT91SAM7X128.h"
#elif (CPU == at91sam7x256)
#include "AT91SAM7X256.h"
#elif (CPU == at91sam7x512)
#include "AT91SAM7X512.h"
#else
#error Wrong CPU defined
#endif

/*==================[macros]=================================================*/
/** \brief Main clock frequency in Hz */
#define MCK_FREQ					48000000

/** \brief CPU-dependent implementation of clearing timer interrupt flag */
#define ClearTimerInterrupt_Cpu() \
{ \
	static volatile uint32 dummy; \
	dummy = AT91C_BASE_PITC->PITC_PIVR; \
}

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void StartOs_Arch_Cpu(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_CPU_H_ */

