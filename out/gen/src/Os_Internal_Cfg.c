/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief FreeOSEK Os Generated Internal Configuration Implementation File
 **
 ** \file Os_Internal_Cfg.c
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090719 v0.1.2 MaCe rename file to Os_
 * 20090128 v0.1.1 MaCe add OSEK_MEMMAP check
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
/** \brief InitTask stack */
uint8 StackTaskInitTask[128];
/** \brief LedsTask stack */
uint8 StackTaskLedsTask[64];
/** \brief ButtonsTask stack */
uint8 StackTaskButtonsTask[64];

/** \brief InitTask context */
TaskContextType ContextTaskInitTask;
/** \brief LedsTask context */
TaskContextType ContextTaskLedsTask;
/** \brief ButtonsTask context */
TaskContextType ContextTaskButtonsTask;

/** \brief Ready List for Priority 2 */
TaskType ReadyList2[1];

/** \brief Ready List for Priority 1 */
TaskType ReadyList1[1];

/** \brief Ready List for Priority 0 */
TaskType ReadyList0[1];

const AlarmType OSEK_ALARMLIST_HardwareCounter[1] = {
	IncrementSWCounter, /* this alarm has to be incremented with this counter */
};

const AlarmType OSEK_ALARMLIST_SoftwareCounter[2] = {
	ActivateLedsTask, /* this alarm has to be incremented with this counter */
	ActivateButtonsTask, /* this alarm has to be incremented with this counter */
};


/*==================[external data definition]===============================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_DATA
#include "MemMap.h"
#endif

/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.			Osek P.
 * 3					2
 * 2					1
 * 1					0
 */

const TaskConstType TasksConst[TASKS_COUNT] = {
	/* Task InitTask */
	{
 		OSEK_TASK_InitTask,	/* task entry point */
		&ContextTaskInitTask, /* pointer to task context */
		StackTaskInitTask, /* pointer stack memory */
		128, /* stack size */
		0, /* task priority */
		1, /* task max activations */
		{
			1, /* extended task */
			0, /* non preemtive task */
			0
		}, /* task const flags */
		0 , /* events mask */
		0 /* resources mask */
	},
	/* Task LedsTask */
	{
 		OSEK_TASK_LedsTask,	/* task entry point */
		&ContextTaskLedsTask, /* pointer to task context */
		StackTaskLedsTask, /* pointer stack memory */
		64, /* stack size */
		1, /* task priority */
		1, /* task max activations */
		{
			0, /* basic task */
			0, /* non preemtive task */
			0
		}, /* task const flags */
		0 , /* events mask */
		0 /* resources mask */
	},
	/* Task ButtonsTask */
	{
 		OSEK_TASK_ButtonsTask,	/* task entry point */
		&ContextTaskButtonsTask, /* pointer to task context */
		StackTaskButtonsTask, /* pointer stack memory */
		64, /* stack size */
		2, /* task priority */
		1, /* task max activations */
		{
			0, /* basic task */
			0, /* non preemtive task */
			0
		}, /* task const flags */
		0 , /* events mask */
		0 /* resources mask */
	}
};

/** \brief TaskVar Array */
TaskVariableType TasksVar[TASKS_COUNT];

/** \brief List of Auto Start Tasks in Application Mode AppMode1 */
const TaskType TasksAppModeAppMode1[1]  ATTRIBUTES() = {
	InitTask
};
/** \brief AutoStart Array */
const AutoStartType AutoStart[1]  ATTRIBUTES() = {
	/* Application Mode AppMode1 */
	{
		1, /* Total Auto Start Tasks in this Application Mode */
		(TaskRefType)TasksAppModeAppMode1 /* Pointer to the list of Auto Start Stacks on this Application Mode */
	}
};

const ReadyConstType ReadyConst[3] = { 
	{
		1, /* Length of this ready list */
		ReadyList2 /* Pointer to the Ready List */
	},
	{
		1, /* Length of this ready list */
		ReadyList1 /* Pointer to the Ready List */
	},
	{
		1, /* Length of this ready list */
		ReadyList0 /* Pointer to the Ready List */
	}
};

/** TODO replace next line with: 
 ** ReadyVarType ReadyVar[3]  ATTRIBUTES(); */
ReadyVarType ReadyVar[3];

/** \brief Resources Priorities */
const TaskPriorityType ResourcesPriority[0]  ATTRIBUTES() = {

};
/** TODO replace next line with: 
 ** AlarmVarType AlarmsVar[3] ATTRIBUTES(); */
AlarmVarType AlarmsVar[3];

const AlarmConstType AlarmsConst[3]  ATTRIBUTES() = {
	{
		OSEK_COUNTER_HardwareCounter, /* Counter */
		INCREMENT, /* Alarm action */
		{
			NULL, /* no callback */
			0, /* no task id */
			0, /* no event */
			OSEK_COUNTER_SoftwareCounter /* counter */
		},
	},
	{
		OSEK_COUNTER_SoftwareCounter, /* Counter */
		ACTIVATETASK, /* Alarm action */
		{
			NULL, /* no callback */
			LedsTask, /* TaskID */
			0, /* no event */
			0 /* no counter */
		},
	},
	{
		OSEK_COUNTER_SoftwareCounter, /* Counter */
		ACTIVATETASK, /* Alarm action */
		{
			NULL, /* no callback */
			ButtonsTask, /* TaskID */
			0, /* no event */
			0 /* no counter */
		},
	}
};

const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {
  {
		AppMode1, /* Application Mode */
		IncrementSWCounter, /* Alarms */
		1, /* Alarm Time */
		1 /* Alarm Time */
	}
};

CounterVarType CountersVar[2];

const CounterConstType CountersConst[2] = {
	{
		1, /* quantity of alarms for this counter */
		(AlarmType*)OSEK_ALARMLIST_HardwareCounter, /* alarms list */
		100000, /* max allowed value */
		1, /* min cycle */
		1000 /* ticks per base */
	},
	{
		2, /* quantity of alarms for this counter */
		(AlarmType*)OSEK_ALARMLIST_SoftwareCounter, /* alarms list */
		100000, /* max allowed value */
		1, /* min cycle */
		100 /* ticks per base */
	}
};


/** TODO replace the next line with 
 ** uint8 ApplicationMode ATTRIBUTES(); */
uint8 ApplicationMode;

/** TODO replace the next line with
 ** uint8 ErrorHookRunning ATTRIBUTES(); */
uint8 ErrorHookRunning;

#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_DATA
#include "MemMap.h"
#endif

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_CODE
#include "MemMap.h"
#endif


#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

