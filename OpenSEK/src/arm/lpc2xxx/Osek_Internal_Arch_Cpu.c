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

/** \brief OpenSEK Internal ARCH CPU Dependece Implementation File
 **
 ** \file arm/Osek_Internal_Arch_Cpu.c
 ** \arch arm/lpc2xxx
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090227 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

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
	T0CTCR = 0b00;	/* bit 1-0: 00 Timer mode
										01 Counter mode at rising edge
										10 Counter mode at falling edge
										11 Counter mode both edges
							bit 3-2: only valid when bit 1-0 != 0
										00 CAPn.0 for timer n
										01 CAPn.1 for timer n
										1x reserved
							bit 7-4: reserved
						*/

	T0PR = 30;	/* 32-bits prescaler register */

	/* set Timer Control Register TCR */
	T0TCR = 0b11;	/* bit 0:	enable counter
							bit 1:	reset counter
							bit 7-2: reserved */

	T0TCR = 0b01;	/* bit 1:	clear reset now */

	
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

