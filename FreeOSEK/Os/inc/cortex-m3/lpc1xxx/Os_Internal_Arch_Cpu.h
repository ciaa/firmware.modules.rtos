/* Copyright 2008, 2009, Mariano Cerdeiro
 * Copyright 2011 Sebastián Viviani
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
 ** \file cortex-m3/lpc1xxx/Os_Internal_Arch_Cpu.h
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
 * MaCe			 Mariano Cerdeiro
 * SLV			 Sebastián Viviani
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20110126 v0.1.0 SLV  imported from arm7 0.1.1
 */

/*==================[cpu macros]=============================================*/

/*==================[inclusions]=============================================*/
#ifndef CPU
#error CPU is not defined
#elif (CPU == lpc1768)
#include "lpc17xx.h"
#else
#error not defined CPU
#endif

/*==================[macros]=================================================*/
#if (CPU == lpc1768)
/** \brief Size of the VIC entries */
#define VICVectAddrSIZE	32
#else
#error VICVectAddrSIZE not defined
#endif

/*==================[typedef]================================================*/
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void StartOs_Arch_Cpu(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_CPU_H_ */

