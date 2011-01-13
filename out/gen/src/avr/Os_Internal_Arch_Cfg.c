/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

/** \brief FreeOSEK Os Generated Internal Achitecture Configuration Implementation File
 **
 ** \file Os_Internal_Arch_Cfg.c
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
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
  * 20110113 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
/** \brief InitTask context */
TaskContextType TaskContextInitTask;
/** \brief LedsTask context */
TaskContextType TaskContextLedsTask;
/** \brief ButtonsTask context */
TaskContextType TaskContextButtonsTask;


InterruptType InterruptTable[INTERUPTS_COUNT] =
{
/** TODO */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 0 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 1 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 2 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 3 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 4 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 5 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 6 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 7 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 8 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 9 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 10 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 11 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 12 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 13 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 14 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 15 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 16 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 17 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 18 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 19 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 20 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 21 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 22 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 23 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 24 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 25 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 26 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 27 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 28 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 29 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 30 */
	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt 31 */
};

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

