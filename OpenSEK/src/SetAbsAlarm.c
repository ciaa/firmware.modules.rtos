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

/** \brief OpenSEK SetAbsAlarm Implementation File
 **
 ** This file implements the SetAbsAlarm API
 **
 ** \file SetAbsAlarm.c
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
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"

StatusType SetAbsAlarm
(
	AlarmType AlarmID,
	TickType Start,
	TickType Cycle
)
{
	/* \req OSEK_SYS_3.22 The system service StatusType
	 ** SetAbsAlarm ( AlarmType AlarmID, TickType Start, TickType Cycle )
	 ** shall be defined */

	/* \req OSEK_SYS_3.22.3-1/2 Possible return values in Standard mode are E_OK,
	 ** E_OS_STATE */
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	/* check if the alarm id is in range */
	if(AlarmID >= ALARMS_COUNT)
	{
		/* \req OSEK_SYS_3.22.4-1/2 Extra possible return values in Extended mode
		 ** are E_OS_ID, E_OS_VALUE */
		ret = E_OS_ID;
	}
	/* check that increment and cycle are in range */
	else if( (Start > CountersConst[AlarmsConst[AlarmID].Counter].MaxAllowedValue) ||
				( ( Cycle != 0 ) &&
					( (Cycle > CountersConst[AlarmsConst[AlarmID].Counter].MaxAllowedValue) ||
						(Cycle < CountersConst[AlarmsConst[AlarmID].Counter].MinCycle) ) ) )
	{
		/* \req OSEK_SYS_3.22.4-2/2 Extra possible return values in Extended mode
		 ** are E_OS_ID, E_OS_VALUE */
		ret = E_OS_VALUE;
	}
	else
#endif
	/* check if the alarm is disable */
	if(AlarmsVar[AlarmID].AlarmState != 0)
   {
		/* \req OSEK_SYS_3.22.3-2/2 Possible return values in Standard mode are E_OK,
		 ** E_OS_STATE */
      ret = E_OS_STATE;
   }
	else
	{

		IntSecure_Start();

		/* enable alarm */
		AlarmsVar[AlarmID].AlarmState = 1;

		/* set abs alarm */
		AlarmsVar[AlarmID].AlarmTime = GetCounter(AlarmsConst[AlarmID].Counter) - Start;
		AlarmsVar[AlarmID].AlarmCycleTime = Cycle;

		IntSecure_End();
	}

#if (HOOK_ERRORHOOK == ENABLE)
	/* \req OSEK_ERR_1.3-14/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-14/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_SetAbsAlarm);
		SetError_Param1(AlarmID);
		SetError_Param2(Start);
		SetError_Param3(Cycle);
		SetError_Ret(ret);
		SetError_Msg("SetAbsAlarm returns != than E_OK");
		SetError_ErrorHook();
	}
#endif

	return ret;
}

#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

