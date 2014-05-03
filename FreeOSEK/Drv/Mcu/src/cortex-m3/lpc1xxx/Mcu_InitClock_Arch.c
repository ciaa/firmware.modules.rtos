/* Copyright 2008, 2009, Mariano Cerdeiro
 * Copyright 2011 Sebastián Viviani
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
 ** \file arm7/lpc2xxx/Mcu_InitClock_Arch.c
 ** \arch arm7/lpc2xxx
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
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090216 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Mcu_Internal.h"

/*==================[macros and definitions]=================================*/
#define PLL_MValue	11
#define PLL_NValue	0
#define CCLKDivValue	4
#define USBCLKDivValue	5

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

	volatile unsigned long MValue;
	volatile unsigned long NValue;

	if ( SC->PLL0STAT & (1 << 25) )
	{
		SC->PLL0CON = 1;			/* Enable PLL, disconnected */
		SC->PLL0FEED = PLLFEED_FEED1;
		SC->PLL0FEED = PLLFEED_FEED2;
	}

	SC->PLL0CON = 0;				/* Disable PLL, disconnected */
	SC->PLL0FEED = PLLFEED_FEED1;
	SC->PLL0FEED = PLLFEED_FEED2;

	(SC->SCS) |= 0x20;			/* Enable main OSC */
	while( !(SC->SCS & 0x40) );	/* Wait until main OSC is usable */

	SC->CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

	SC->PLL0CFG = PLL_MValue | (PLL_NValue << 16);
	SC->PLL0FEED = PLLFEED_FEED1;
	SC->PLL0FEED = PLLFEED_FEED2;

	SC->PLL0CON = 1;				/* Enable PLL, disconnected */
	SC->PLL0FEED = PLLFEED_FEED1;
	SC->PLL0FEED = PLLFEED_FEED2;

	SC->CCLKCFG = CCLKDivValue;	/* Set clock divider */

	while ( ((SC->PLL0STAT & (1 << 26)) == 0) );	/* Check lock bit status */

	MValue = SC->PLL0STAT & 0x00007FFF;
	NValue = (SC->PLL0STAT & 0x00FF0000) >> 16;
	while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

	SC->PLL0CON = 3;				/* enable and connect */
	SC->PLL0FEED = PLLFEED_FEED1;
	SC->PLL0FEED = PLLFEED_FEED2;
	while ( ((SC->PLL0STAT & (1 << 25)) == 0) );	/* Check connect bit status */
}

/** TODO */
/* #define OpenDRV_MCU_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

