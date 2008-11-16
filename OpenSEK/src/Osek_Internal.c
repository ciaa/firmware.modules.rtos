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

/** \brief OpenSEK Internal Implementation File
 **
 ** \file Osek_Internal.c
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Internal
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
#define OpenSEK_START_SEC_VAR
#include "MemMap.h"

TaskType RunningTask;

ContextType ActualContext;

#define OpenSEK_STOP_SEC_VAR
#include "MemMap.h"

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"

void AddReady(TaskType TaskID)
{
	TaskPriorityType priority;
	TaskRefType readylist;
	TaskTotalType maxtasks;
	TaskTotalType position;

	/* get task priority */
	priority = TasksConst[TaskID].StaticPriority;
	/* conver the priority to the array index */
	/* do not remove the -1 is needed. for example if READYLIST_COUNT is 4
	 * the valida entries for this array are between 0 and 3, so the -1 is needed
	 * since the lower priority is 0.
	 */
	priority = (READYLISTS_COUNT-1)-priority;
	
	/* get ready list */
	readylist = ReadyConst[priority].TaskRef;
	/* get max number of entries */
	maxtasks = ReadyConst[priority].ListLength;

	/* get pincrementtion */
	position = ( ReadyVar[priority].ListStart + ReadyVar[priority].ListCount ) % maxtasks;
	/* set the task id in ready the list */
	readylist[position] = TaskID;
	/* increment the list counter */
	ReadyVar[priority].ListCount++;
}

void RemoveTask
(
	TaskType TaskID
)
{
	TaskPriorityType priority;
	TaskRefType readylist;
	TaskTotalType maxtasks;

	/* get task priority */
	priority = TasksConst[TaskID].StaticPriority;
	/* conver the priority to the array index */
	/* do not remove the -1 is needed. for example if READYLIST_COUNT is 4
	 * the valida entries for this array are between 0 and 3, so the -1 is needed
	 * since the lower priority is 0.
	 */
	priority = (READYLISTS_COUNT-1)-priority;

	/* get ready list */
	readylist = ReadyConst[priority].TaskRef;
	/* get max number of entries */
	maxtasks = ReadyConst[priority].ListLength;
	/* increment the ListStart */
	ReadyVar[priority].ListStart= ( ReadyVar[priority].ListStart + 1 )  % maxtasks;
	/* decrement the count of ready tasks */
	ReadyVar[priority].ListCount--;
}

TaskType GetNextTask
(
	void
)
{
	uint8_least loopi;
	flag found = FALSE;
	TaskType ret = INVALID_TASK;

	/* check in all ready lists */
	for (loopi = 0; ( loopi < READYLISTS_COUNT ) && (!found) ; loopi++)
	{
		/* if one or more tasks are ready */
		if (ReadyVar[loopi].ListCount > 0)
		{
			/* return the first ready task */
			ret = ReadyConst[loopi].TaskRef[ReadyVar[loopi].ListStart];

			/* set found true */
			found = TRUE;
		}
	}

	return ret;
}

void OSEK_ISR_NoHandler(void)
{
	while(1);
}

#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

