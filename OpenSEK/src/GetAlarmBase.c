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

/** \brief OpenSEK ActivateTask Implementation File
 **
 ** This file implements the ActiveTask API
 **
 ** \file GetAlarmBase.c
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
StatusType GetAlarmBase
(
	AlarmType AlarmID,
	AlarmBaseRefType Info
)
{
	/* \req OSEK_SYS_3.19 The system service StatusType
	 ** GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info )
	 ** shall be defined. */

	/* \req OSEK_SYS_3.19.2 Possible return values in Standard mode is E_OK */
	StatusType ret = E_OK;

	CounterType counter;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	/* check that the AlarmID is in range */
	if(AlarmID >= ALARMS_COUNT)
	{
		/* \req OSEK_SYS_3.19.: Extra possible return values in Extended mode
		 ** is E_OS_ID */
		ret = E_OS_ID;
	}
	else
#endif
	{
		/* get counter of this alarm */
		counter = AlarmsConst[AlarmID].Counter;

		/* \req OSEK_SYS_3.19.1 The system service GetAlarmBase reads the alarm base
		 ** characteristics. The return value Info is a structure in which the
		 ** information of data type AlarmBaseType is stored */
		Info->MaxAllowedValue = CountersConst[counter].MaxAllowedValue;
		Info->TicksPerBase = CountersConst[counter].TicksPerBase;
		Info->MinCycle = CountersConst[counter].MinCycle;
	}

#if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
	 	(HOOK_ERRORHOOK == ENABLE) )
	/* \req OSEK_ERR_1.3-12/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-12/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
	if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_GetAlarmBase);
		SetError_Param1(AlarmID);
		SetError_Param2((uint32)Info);
		SetError_Ret(ret);
		SetError_Msg("GetAlarmBase returns != than E_OK");
		SetError_ErrorHook();
	}
#endif
	
	return ret;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

