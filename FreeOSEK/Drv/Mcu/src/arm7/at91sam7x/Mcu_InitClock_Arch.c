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

/** \brief FreeOSEK Driver Mcu Init Arch implementation file
 **
 ** This file implements the Mcu_InitClock_Arch API
 **
 ** The implementation is based on the file board_lowlevel.c in at91lib
 ** supplied by Atmel Corporation.
 **
 ** \file arm7/at91sam7x/Mcu_InitClock_Arch.c
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
#include "Mcu_Internal.h"
#include "Mcu_Internal_Arch.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_MCU_START_SEC_CODE
 * #include "MemMap.h" */

Std_ReturnType Mcu_InitClock_Arch
(
	Mcu_ClockType ClockSettings
)
{
	/*
	 * Initialize main oscillator
	 */
	AT91C_BASE_PMC->PMC_MOR = MCU_OSCOUNT | AT91C_CKGR_MOSCEN;
	while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS));

	/* Initialize PLL at 96MHz (96.109) and USB clock to 48MHz */
	AT91C_BASE_PMC->PMC_PLLR = MCU_USBDIV | MCU_CKGR_PLL | MCU_PLLCOUNT |
		MCU_MUL | MCU_DIV;
	while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCK));

	/* Wait for the master clock if it was already initialized */
	while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));

	/*
	 * Switch to fast clock
	 */
	/* Switch to slow clock + prescaler */
	AT91C_BASE_PMC->PMC_MCKR = MCU_PRESCALER;
	while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));

	/* Switch to fast clock + prescaler */
	AT91C_BASE_PMC->PMC_MCKR |= AT91C_PMC_CSS_PLL_CLK;
	while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));
}

/** TODO */
/* #define OpenDRV_MCU_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

