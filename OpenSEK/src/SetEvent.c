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

/** \brief OpenSEK SetEvent Implementation File
 **
 ** This file implements the SetEvent API
 **
 ** \file SetEvent.c
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20080814 v0.1.0 MaCe			- initial version
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
StatusType SetEvent
(
	TaskType TaskID,
	EventMaskType Mask
)
{
	/** \req OSEK_SYS_3.15 The system service StatusType
	 ** SetEvent ( TaskType TaskID, EventMaskType Mask ) shall be defined */

	/** \req OSEK_SYS_3.15.2: Possible return values in Standard mode is E_OK */
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if ( TaskID >= TASKS_COUNT )
	{
		/** \req OSEK_SYS_3.15.3-1/3 Extra possible return values in Extended mode
		 ** are E_OS_ID, E_OS_ACCESS, E_OS_STATE */
		ret = E_OS_ID;
	}
	else if ( !TasksConst[TaskID].ConstFlags.Extended )
	{
		/** \req OSEK_SYS_3.15.3-2/3 Extra possible return values in Extended mode
		 ** are E_OS_ID, E_OS_ACCESS, E_OS_STATE */
		ret = E_OS_ACCESS;
	}
	else if ( TasksVar[TaskID].Flags.State == TASK_ST_SUSPENDED )
	{
		/** \req OSEK_SYS_3.15.3-3/3 Extra possible return values in Extended mode
		 ** are E_OS_ID, E_OS_ACCESS, E_OS_STATE */
		ret = E_OS_STATE;
	}
	else
#endif
	{
		/* enter to critical code */
		IntSecure_Start();

		/* the event shall be set only if the task is running ready or waiting */
		if ( 	( TasksVar[TaskID].Flags.State == TASK_ST_RUNNING ) ||
				( TasksVar[TaskID].Flags.State == TASK_ST_READY ) ||
				( TasksVar[TaskID].Flags.State == TASK_ST_WAITING) )
		{
			/* set the events */
			/** \req OSEK_SYS_3.15.1-1/2 The events of task TaskID are set according to the
			 ** event mask Mask. Calling SetEvent causes the task TaskID to be
			 ** transferred to the ready state, if it was waiting for at least one
			 ** of the events specified in Mask */
			TasksVar[TaskID].Events |= ( Mask & TasksConst[TaskID].EventsMask );

			/* if the task is waiting and one waiting event occurrs set it to ready */
			if (	( TasksVar[TaskID].Flags.State == TASK_ST_WAITING ) &&
					( TasksVar[TaskID].EventsWait & TasksVar[TaskID].Events ) )
			{
				/** \req OSEK_SYS_3.15.1-2/2 The events of task TaskID are set according to the
				 ** event mask Mask. Calling SetEvent causes the task TaskID to be
				 ** transferred to the ready state, if it was waiting for at least one
				 ** of the events specified in Mask */
				AddReady(TaskID);

				IntSecure_End();

				(void)Schedule();
			}
			else
			{
				IntSecure_End();
			}
		}
		else
		{
			IntSecure_End();
		}
	}


#if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
		(HOOK_ERRORHOOK == ENABLE) )
	/** \req OSEK_ERR_1.3-8/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/** \req OSEK_ERR_1.3.1-8/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_SetEvent);
		SetError_Param1(TaskID);
		SetError_Param2(Mask);
		SetError_Ret(ret);
		SetError_Msg("ActivateTask returns != than E_OK");
		SetError_ErrorHook();
	}
#endif

	return ret;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

