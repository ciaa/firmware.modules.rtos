/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking OpenSEK statically or dynamically with other modules is making a
 * combined work based on OpenSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of OpenSEK give
 * you permission to combine OpenSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with OpenSEK solely through the OpenSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for OpenSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of OpenSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
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

/** \brief OpenSEK GetAlarm Implementation File
 **
 ** This file implements the GetAlarm API
 **
 ** \file GetAlarm.c
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
 * 20090128 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20081113 v0.1.1 KLi  Added memory layout attribute macros
 * 20080713 v0.1.0 MaCe initial version
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
#if (OSEK_MEMMAP == ENABLE)
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"
#endif

StatusType GetAlarm
(
	AlarmType AlarmID,
	TickRefType Tick
)
{
	/* \req OSEK_SYS_3.20 The system service StatusType
	 ** GetAlarm ( AlarmType AlarmID, TickRefType Tick) shall be defined */

	/* \req OSEK_SYS_3.20.2 Possible return values in Standard mode is E_OK */
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	/* check if it handle of a valid AlarmID */
	if (AlarmID >= ALARMS_COUNT)
	{
		/* \req OSEK_SYS_3.20.3-1/2 Extra possible return values in Extended mode
		 ** are E_OS_NOFUNC, E_OS_ID */
		ret = E_OS_ID;
	}
	/* check if the alarm is running */
	else if(AlarmsVar[AlarmID].AlarmState == 0)
	{
		/* \req OSEK_SYS_3.20.3-2/2 Extra possible return values in Extended mode
		 ** are E_OS_NOFUNC, E_OS_ID */
		ret = E_OS_NOFUNC;
	}
	else
#endif
	{
		/* \req OSEK_SYS_3.20.1 The system service GetAlarm shall return the
		 ** relative value in ticks before the alarm AlarmID expires */
		*Tick = AlarmsVar[AlarmID].AlarmTime;
	}

#if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
		(HOOK_ERRORHOOK == ENABLE) )
	/* \req OSEK_ERR_1.3-12/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-12/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_GetAlarm);
      SetError_Param1(AlarmID);
		SetError_Param2((uint32)Tick);
      SetError_Ret(ret);
      SetError_Msg("GetAlarm returns != than E_OK");
      SetError_ErrorHook();
   }
#endif
	
	return ret;
}

#if (OSEK_MEMMAP == ENABLE)
#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

