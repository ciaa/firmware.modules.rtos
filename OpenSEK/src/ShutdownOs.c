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

/** \brief OpenSEK ShutdownOs Implementation File
 **
 ** This file implements the ShutdownOs API
 **
 ** \file ShutdownOs.c
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * KLi          Kang Li
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081113 v0.1.1 KLi        - Added memory layout attribute macros
 * 20080810 v0.1.0 MaCe       - initial version
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
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"

void ShutdownOs
(
	StatusType Error
)
{
	/* \req OSEK_SYS_3.26 The system service void
	 ** ShutdownOS ( StatusType Error ) shall be defined */

#if (HOOK_SHUTDOWNHOOK == ENABLE)
	/* \req OSEK_ERR_1.2 The ShutdownHook hook routine shall be called when a
	 ** system shutdown is requested by the application or by the operating
	 ** system in case of a severe error */
	ShutdownHook();
#endif

	/* this function shall never return */
	while(1);
}

#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

