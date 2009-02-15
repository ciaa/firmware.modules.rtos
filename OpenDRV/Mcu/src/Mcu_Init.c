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

/** \brief OpenDRV Clk Init implementation file
 **
 ** This file implements the Clk_Init API
 **
 ** \file Clk_Init.c
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Clk
 ** \ingroup OpenDRV
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090124 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Clk_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_CLK_START_SEC_CODE
 * #include "MemMap.h" */

Clk_ReturnType Clk_Init
(
	Clk_ConfigRefType config
)
{
	Clk_Init_Arch(config);
}

/** TODO */
/* #define OpenDRV_CLK_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

