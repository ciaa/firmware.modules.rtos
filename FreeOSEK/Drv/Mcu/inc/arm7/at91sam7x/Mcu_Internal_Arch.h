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

#ifndef _MCU_INTERNAL_ARCH_H_
#define _MCU_INTERNAL_ARCH_H_
/** \brief FreeOSEK Driver Mcu Internal Header File
 **
 ** Mcu Internal Header File
 **
 ** \file arm7/at91sam7x/Mcu_Internal_Arch.h
 ** \arch arm7/at91sam7x
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Mcu
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Mcu_Internal
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

/*==================[inclusions]=============================================*/
#include "AT91SAM7X512.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/* Startup time of main oscillator (in number of slow clock ticks). */
#define MCU_OSCOUNT				(AT91C_CKGR_OSCOUNT & (0x40 << 8))

/* USB PLL divisor value to obtain a 48MHz clock. */
#define MCU_USBDIV				AT91C_CKGR_USBDIV_1

/* PLL frequency range. */
#define MCU_CKGR_PLL				AT91C_CKGR_OUT_0

/* PLL startup time (in number of slow clock ticks). */
#define MCU_PLLCOUNT				(16 << 8)

/* PLL MUL value. */
#define MCU_MUL					(AT91C_CKGR_MUL & (72 << 16))

/* PLL DIV value. */
#define MCU_DIV					(AT91C_CKGR_DIV & 14)

/* Master clock prescaler value. */
#define MCU_PRESCALER			AT91C_PMC_PRES_CLK_2

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
Std_ReturnType Mcu_InitClock_Arch
(
	Mcu_ClockType ClockSettings
);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MCU_INTERNAL_ARCH_H_ */

