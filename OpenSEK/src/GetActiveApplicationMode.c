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

/** \brief OpenSEK GetActiveApplicationMode Implementation File
 **
 ** This file implements the GetActiveApplicationMode API
 **
 ** \file GetActiveApplicationMode.c
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20080713 v0.1.0 MaCe       - initial version
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
AppModeType GetActiveApplicationMode
(
	void
)
{
	/** \req OSEK_SYS_3.24 The system service AppModeType
	 ** GetActiveApplicationMode ( void ) shall be defined */

	/** \req OSEK_SYS_3.24.1 This service shall return the current
	 ** application mode */

	/** \req OSEK_ERR_1.1.1 The macro GetActiveApplicationMode()
	 ** shall be provided */

	return ApplicationMode;
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

