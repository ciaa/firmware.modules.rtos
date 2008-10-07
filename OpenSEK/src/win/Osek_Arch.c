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

/** \brief OpenSEK Arch Implementation File
 **
 ** \file Osek_Arch.c
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
 * 20080922 v0.2.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
InterruptFlagsType InterruptMask;

InterruptStateType InterruptState;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void ScheduleInterrupts(void)
{
	int loopi = 0;
	uint32 InterruptToBeExecuted;

	if (InterruptState)
	{
		InterruptToBeExecuted = ( InterruptFlag & ( (InterruptFlagsType) ~InterruptMask ) );
		while(InterruptToBeExecuted != 0)
		{
			if (InterruptToBeExecuted & 1)
			{
				InterruptFlag &= ~(1<<loopi);

				InterruptTable[loopi]();
			}

			InterruptToBeExecuted >>=1;
			loopi++;
		}
	}
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

