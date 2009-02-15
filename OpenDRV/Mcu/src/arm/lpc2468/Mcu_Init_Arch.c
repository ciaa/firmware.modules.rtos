/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief OpenDRV Mcu Init Arch implementation file
 **
 ** This file implements the Mcu_Init_Arch API
 **
 ** \file Mcu_Init_Arch.c
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu
 ** \ingroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu_Internal
 ** \ingroup OpenDRV_Mcu
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090215 v0.1.1 MaCe	raname the driver to Mcu
 * 20090124 v0.1.0 MaCe initial version
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

Mcu_ReturnType Mcu_Init_Arch
(
	Mcu_ConfigRefType Config
)
{

	volatile unsigned long MValue;
	volatile unsigned long NValue;

	if ( PLLSTAT & (1 << 25) )
	{
		PLLCON = 1;			/* Enable PLL, disconnected */
		PLLFEED = 0xaa;
		PLLFEED = 0x55;
	}

	PLLCON = 0;				/* Disable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;

	SCS |= 0x20;			/* Enable main OSC */
	while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

	CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

	PLLCFG = PLL_MValue | (PLL_NValue << 16);
	PLLFEED = 0xaa;
	PLLFEED = 0x55;

	PLLCON = 1;				/* Enable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;

	CCLKCFG = CCLKDivValue;	/* Set clock divider */

	while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */

	MValue = PLLSTAT & 0x00007FFF;
	NValue = (PLLSTAT & 0x00FF0000) >> 16;
	while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

	PLLCON = 3;				/* enable and connect */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Check connect bit status */
}

/** TODO */
/* #define OpenDRV_MCU_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

