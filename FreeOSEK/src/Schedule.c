/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *
 *
 */

/** \brief FreeOSEK Schedule Implementation File
 **
 ** This file implements the Schedule API
 **
 ** \file Schedule.c
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Global
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
 * 20090130 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20081113 v0.1.1 KLi  Added memory layout attribute macros
 * 20080810 v0.1.0 MaCe initial version
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
#define FreeOSEK_START_SEC_CODE
#include "MemMap.h"
#endif

StatusType Schedule
(
	void
)
{
	/* \req OSEK_SYS_3.4 The system service StatusType Schedule ( void ) shall
	 ** be defined */

	/* \req OSEK_SYS_3.4.4 Possible return values in Standard mode is E_OK */
	StatusType ret = E_OK;
	TaskType nexttask;
	TaskType actualtask;

	/* \req OSEK_SYS_3.3.5 Extra possible return values in Extended mode are E_OS
	 ** CALLEVEL, E_OS_RESOURCE  */
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
   if ( GetCallingContext() != CONTEXT_TASK )
   {
		/* \req OSEK_SYS_3.3.5 Extra possible return values in Extended mode
		 ** are E_OS_CALLEVEL, E_OS_RESOURCE */
      ret = E_OS_CALLEVEL;
   }
	else if (GetRunningTask() != INVALID_TASK)
	{
		if ( TasksVar[GetRunningTask()].Resources != 0 )
      {
					/* \req OSEK_SYS_3.3.5 Extra possible return values in Extended mode
					 ** are E_OS_CALLEVEL, E_OS_RESOURCE */
               ret = E_OS_RESOURCE;
		}
	}
	else
	{
		/* nothing to check Runngin Task is invalid */
	}

	if (ret == E_OK)
#endif
	{
		/* get actual running task */
		actualtask = GetRunningTask();

		/* get next task */
		nexttask = GetNextTask();

		/* while until one or boths are not more invalid tasks */
		while (	( actualtask == INVALID_TASK ) &&
					( nexttask == INVALID_TASK) )
		{
			/* macro used to indicate the processor that we are in idle time */
			osekpause();

			/* get next task */
			nexttask = GetNextTask();
		};

		/* if the actual task is invalid */
		if ( actualtask == INVALID_TASK )
		{
			/* set task state to running */
			TasksVar[nexttask].Flags.State = TASK_ST_RUNNING;
			/* set as running task */
			SetRunningTask(nexttask);
			/* jmp tp the next task */
			JmpTask(nexttask);
		}
		else
		{
			/* check priorities */
			/* \req OSEK_SYS_3.4.1 If a task with a lower or equal priority than the
			 ** ceiling priority of the internal resource and higher priority than
			 ** the priority of the calling task is ready */
			if ( TasksConst[nexttask].StaticPriority > TasksVar[actualtask].ActualPriority )
			{
				/* \req OSEK_SYS_3.4.1.1 the internal resource of the task shall be
				 ** released */

				ReleaseInternalResources();
				/* \req OSEK_SYS_3.4.1.2 the current task is put into the ready state */
				TasksVar[actualtask].Flags.State = TASK_ST_READY;

				/* set the new task to running */
			 	TasksVar[nexttask].Flags.State = TASK_ST_RUNNING;

				/* \req OSEK_SYS_3.4.1.3 its context is saved */
				/* \req OSEK_SYS_3.4.1.4 and the higher-priority task is executed */
				CallTask(nexttask);
			}
			else
			{
				/* \req OSEK_SYS_3.4.2 Otherwise the calling task is continued */
			}

		}
	}

#if (HOOK_ERRORHOOK == ENABLE)
	/* \req OSEK_ERR_1.3-4/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-4/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
	if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_Schedule);
		SetError_Ret(ret);
		SetError_Msg("Schedule Task returns != than E_OK");
		SetError_ErrorHook();
	}
#endif

	return ret;
}

#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

