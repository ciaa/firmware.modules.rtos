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

/** \brief OpenDRV DIO Write Channel implementation file
 **
 ** This file implements the Dio_WriteChannel API
 **
 ** \file Dio_WriteChannel.c
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Dio
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
 * 20090227 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Dio_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_DIO_START_SEC_CODE
 * #include "MemMap.h" */

#if (DioDevErrorDetect == ENABLE)
void Dio_WriteChannel
(
	Dio_ChannelType ChannelId,
	Dio_LevelType Level
)
{
	/** TODO */
}
#endif /* #if (DioDevErrorDetect == ENABLE) */

/** TODO */
/* #define OpenDRV_DIO_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

