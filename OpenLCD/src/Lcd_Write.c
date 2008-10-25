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

/** \brief OpenLCD Lcd Write Implementation File
 **
 ** This file implements the Lcd_Write service interface
 **
 ** \file Lcd_Write.c
 **
 **/

/** \addtogroup Lcd
 ** @{ */
/** \addtogroup Lcd_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081025 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Lcd_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
extern Lcd_ReturnType Lcd_Write
(
	const Lcd_MsgRefType msg,
	Lcd_MsgLength length

{
	Lcd_ReturnType ret;
	
	ret = LCD_E_OK;

	return ret;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

