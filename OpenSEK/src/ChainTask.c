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

/** \brief OpenSEK ChainTask Implementation File
 **
 ** This file implements the ChainTask API
 **
 ** \file ChainTask.c
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
 * 20090130 v0.1.2 MaCe add OSEK_MEMMAP check
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

StatusType ChainTask
(
	TaskType taskid
)
{
	/* \req OSEK_SYS_3.3 The system service StatusType
	 ** ChainTask ( TaskType TaskID ) shall be defined. */

	
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if ( taskid >= TASKS_COUNT )
	{
		/* \req OSEK_SYS_3.3.10-1/3 Added possible return values in Extended mode
		 ** are E_OS_ID, E_OS_RESOURCE, E_OS_CALLEVEL */
		ret = E_OS_ID;
	}
	else if ( GetCallingContext() != CONTEXT_TASK )
	{
		/* \req OSEK_SYS_3.3.10-2/3 Added possible return values in Extended mode
		 ** are E_OS_ID, E_OS_RESOURCE, E_OS_CALLEVEL */
		ret = E_OS_CALLEVEL;
	}
	/* check if any resource is still reserved for this task */
	else if ( TasksVar[GetRunningTask()].Resources != 0 )
	{
		/* \req OSEK_SYS_3.3.10-3/3 Added possible return values in Extended mode
		 ** are E_OS_ID, E_OS_RESOURCE, E_OS_CALLEVEL */
		ret = E_OS_RESOURCE;
	}
	else
#endif
	if ( ( (TasksVar[taskid].Activations + 1) > TasksConst[taskid].MaxActivations) && 
		  ( taskid != GetRunningTask()) )
	{
		/* \req OSEK_SYS_3.3.8 If E_OS_LIMIT is returned the activation is ignored */
		/* \req OSEK_SYS_3.3.9-1/2 Possible return values in Standard mode are:
		 ** no return or E_OS_LIMIT */
		ret = E_OS_LIMIT;
	}
	else
	{
		
		IntSecure_Start();

		/* release internal resources */
		/* \req OSEK_SYS_3.3.4 If an internal resource is assigned to the calling
		 ** task it shall be automatically released, even if the succeeding task is
		 ** identical with the current task. */
		ReleaseInternalResources();

		/* decrement activations for this task */
		TasksVar[GetRunningTask()].Activations--;

		if (TasksVar[GetRunningTask()].Activations == 0)
		{
			/* if no more activations set state to suspended */
			/* \req OSEK_SYS_3.3.1-1/2 This service causes the termination of the calling task. */
			TasksVar[GetRunningTask()].Flags.State = TASK_ST_SUSPENDED;
		}
		else
		{
			/* if more activations set state to ready */
			/* \req OSEK_SYS_3.3.1-2/2 This service causes the termination of the calling task. */
			TasksVar[GetRunningTask()].Flags.State = TASK_ST_READY;
		}


		/* set entry point for this task again */
		/* \req OSEK_SYS_3.1.2-1/3 The operating system shall ensure that the task
 		 ** code is being executed from the first statement. */
		SetEntryPoint(GetRunningTask());
		/* remove ready list */
		RemoveTask(GetRunningTask());
		/* set running task to invalid */
		SetRunningTask(INVALID_TASK);
		/* increment activations */
		TasksVar[taskid].Activations++;
		/* activate task */
		/* \req OSEK_SYS_3.3.2 After termination of the calling task a succeeding
		 **  task TaskID shall be activated. */
		/* \req OSEK_SYS_3.3.3 If the succeeding task is identical with the current
		 ** task, this does not result in multiple requests. The task is not
		 ** transferred to the suspended state, but will immediately become ready
		 ** again. */
		AddReady(taskid);

		if(TasksVar[taskid].Flags.State ==  TASK_ST_SUSPENDED)
		{
			/* \req OSEK_SYS_3.3.7 When an extended task is transferred from suspended
			 ** state into ready state all its events are cleared.*/
			TasksVar[taskid].Events = 0;
		}

		IntSecure_End();

		/* call scheduler, never returns */
		/* \req OSEK_SYS_3.3.5 If called successfully, ChainTask does not return
		 ** to the call level and the status can not be evaluated. */
		/* \req OSEK_SYS_3.3.6 If the service ChainTask is called successfully,
		 ** this enforces a rescheduling. */
		/* \req OSEK_SYS_3.3.9-2/2 Possible return values in Standard mode are:
		 ** no return or E_OS_LIMIT */
		(void)Schedule();

	}

#if (HOOK_ERRORHOOK == ENABLE)
   /* \req OSEK_ERR_1.3-3/xx The ErrorHook hook routine shall be called if a
	 ** system service returns a StatusType value not equal to E_OK.*/
   /* \req OSEK_ERR_1.3.1-3/xx The hook routine ErrorHook is not called if a
	 ** system service is called from the ErrorHook itself. */
	if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_ChainTask);
		SetError_Param1(taskid);
		SetError_Ret(ret);
		SetError_Msg("ChainTask returns != than E_OK");
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

