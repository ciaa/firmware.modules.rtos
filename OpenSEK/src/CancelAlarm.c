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

/** \brief OpenSEK CancelAlarm Implementation File
 **
 ** This file implements the CancelAlarm API
 **
 ** \file CancelAlarm.c
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
StatusType CancelAlarm
(
	AlarmType AlarmID
)
{
	/* \req OSEK_SYS_3.23 The system service StatusType
	 ** CancelAlarm ( AlarmType AlarmID ) shall be defined */

	/* \req OSEK_SYS_3.23.2-1/2 Possible return values in Standard mode are
	 ** E_OK, E_OS_NOFUNC */
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)	
	/* check if alarm id is in the valid range */
	if(AlarmID >= ALARMS_COUNT)
	{
		/* \req SEK_SYS_3.23.3: Extra possible return values in Extended mode ar
		 **  E_OS_ID */
		ret = E_OS_ID;
	}
	else
#endif
	if(AlarmsVar[AlarmID].AlarmState == 0)
	{
		/* \req OSEK_SYS_3.23.2-2/2 Possible return values in Standard mode are
		 ** E_OK, E_OS_NOFUNC */
		ret = E_OS_NOFUNC;
	}
	else
	{
		/* \req OSEK_SYS_3.23.1 The system service shall cancel the alarm AlarmID */
		AlarmsVar[AlarmID].AlarmState = 0;
	}

#if (HOOK_ERRORHOOK == ENABLE)
	/* \req OSEK_ERR_1.3-15/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-15/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_CancelAlarm);
		SetError_Param1(AlarmID);
		SetError_Ret(ret);
		SetError_Msg("CancelAlarm returns != than E_OK");
		SetError_ErrorHook();
	}
#endif
	
	return ret;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
