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

/** \brief OpenSEK StartOs Implementation File
 **
 ** This file implements the StartOs API
 **
 ** \file StartOs.c
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
void StartOs
(
	AppModeType Mode
)
{
	/* \req OSEK_SYS_3.25 The system service void
	 ** StartOS ( AppModeType Mode ) shall be defined */

	/* \req OSEK_SYS_3.25.1 This system service shall starts the operating
	 ** system */
	uint8_least loopi;

	IntSecure_Start();

	/* save the aplication mode */
	ApplicationMode = Mode;

	/* StartOs_Arch */
	StartOs_Arch();


	/* init every task */
   for( loopi = 0; loopi < TASKS_COUNT; loopi++)
	{
		/* \req OSEK_SYS_3.1.2-2/3 The operating system shall ensure that the task
		 ** code is being executed from the first statement. */
		SetEntryPoint(loopi); /* set task entry point */
	}

	/* add to ready the corresponding tasks for this
    * Application Mode */
	for (loopi = 0; loopi < AutoStart[Mode].TotalTasks; loopi++)
	{
		/* Add Tasks to the ready list */
		AddReady(AutoStart[Mode].TasksRef[loopi]);
	}

	for (loopi = 0; loopi < ALARM_AUTOSTART_COUNT; loopi++)
	{
		if (AutoStartAlarm[loopi].Mode == Mode)
		{
			(void)SetRelAlarm(AutoStartAlarm[loopi].Alarm, AutoStartAlarm[loopi].AlarmTime, AutoStartAlarm[loopi].AlarmCycleTime);
		}
	}

	/* set actual task to invalid task */
	SetRunningTask(INVALID_TASK);

	/* set task context, in other case the call
    * to schedule may return with error */
	SetActualContext(CONTEXT_TASK);

#if (HOOK_STARTUPHOOK == ENABLE)
	StartupHook();
#endif

	IntSecure_End();

	/* enable all OS interrupts */
	EnableOSInterrupts();

	/* enable interrupts */
	EnableInterrupts();
	

	/* call Scheduler */
	(void)Schedule();

	/* this function shall never return */
	while(1);
}

/** @} doxygen end group definition */
/** @} doxygen endVar group definition */
/*==================[end of file]============================================*/

