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

#ifndef _OSEK_INTERNAL_H_
#define _OSEK_INTERNAL_H_
/** \brief OpenSEK Internal Header File
 **
 ** OpenSEK Internal Header File
 **
 ** \file Osek_Internal.h
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */ 

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080713 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "os.h"
#include "Osek_Internal_Arch.h"
#include "Osek_Internal_Arch_Cfg.h"
#include "Osek_Internal_Cfg.h"

/*==================[macros]=================================================*/
/** \brief Invalid Task */
#define INVALID_TASK  ((TaskType)~0)

/** \brief State for Suspended Tasks */
#define TASK_ST_SUSPENDED	SUSPENDED

/** \brief State for Ready Tasks */
#define TASK_ST_READY		READY

/** \brief State for Running Task */
#define TASK_ST_RUNNING		RUNNING

/** \brief State for Wating Tasks */
#define TASK_ST_WAITING 	WAITING

/** \brief Invalid Task State */
#define TASK_ST_INVALID		((TaskStateType)~0)

/** \brief Error Checking Standard */
#define ERROR_CHECKING_STANDARD   1

/** \brief Error Checking Extended */
#define ERROR_CHECKING_EXTENDED   2

/** \brief Definition of FALSE */
#define FALSE 0

/** \brief Definiton of TRUE */
#define TRUE 1

/** \brief Release Internal Resources
 **
 ** This interface release the internal resources of the actual task
 **/
#define ReleaseInternalResources()							\
	{																	\
		/* set the priority to the normal value */		\
		TasksVar[GetRunningTask()].ActualPriority =		\
		TasksConst[GetRunningTask()].StaticPriority;		\
	}

/** \brief Invalid Context */
#define CONTEXT_INVALID ((ContextType)0U)
/** \brief Task Context */
#define CONTEXT_TASK ((ContextType)1U)
/** \brief ISR Category 1 Context */
#define CONTEXT_ISR1 ((ContextType)2U)
/** \brief ISR Category 2 Context */
#define CONTEXT_ISR2 ((ContextType)3U)

/** \brief Get Context at Calling point
 **
 ** This macro returns the actual context
 **
 ** \returns the actual context
 **/
#define GetCallingContext()   (ActualContext)

/** \brief Set Context
 **
 ** Set the context
 **
 ** \param[in] newcontext valid values are:
 **               - CONTEXT_INVALID
 **               - CONTEXT_TASK
 **               - CONTEXT_ISR1
 **               - CONTEXT_ISR2
 **/
#define SetActualContext(newcontext)   \
	{												\
		ActualContext = (newcontext);		\
	}

/** \brief Get Running Task
 **
 ** This macro returns the actual running task
 **
 ** \returns the actual running task
 **/
#define GetRunningTask()   (RunningTask)

/** \brief Set Running Task
 **
 ** This interface set the actual running task variable. Only
 ** the variable will be set, no task context changes are performed
 **
 ** \param[in] newtask new task
 **/
#define SetRunningTask(newtask)  (RunningTask = (newtask) )

/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the counter
 **
 ** \param[in] CounterID id of the counter to be readed
 ** \return Actual value of the counter
 **/
#define GetCounter(CounterID) GetCounter_Arch(CounterID)

/*==================[typedef]================================================*/
/** \brief ContextType
 **
 ** Type used to represent the actual context
 **/
typedef uint8 ContextType;

/*==================[external data declaration]==============================*/
/** \brief ActualContext
 **
 ** This variable saves the actual context
 **/
extern ContextType ActualContext;

/** \brief RunningTask variable */
extern TaskType RunningTask;

/*==================[external functions declaration]=========================*/
/** \brief Architecture Dependnece Start Os function
 **
 ** This function is called from the StartOs function
 **/
extern void StartOs_Arch(void);

/** \brief Get Next Task
 **
 ** This functions returns the next task that shall be executed
 ** in order of the task activation and priority
 **
 ** \return next task to be executed
 **/
extern TaskType GetNextTask(void);

/** \brief Remove Task of the Ready List
 **
 ** This function will remove the first task on the
 ** ready list with priority equal to the static
 ** priority of the given TaskID
 **
 ** \param[in] TaskID TaskID
 **/
void RemoveTask(TaskType TaskID);

/** \brief Add Task to the scheduler list
 **
 ** This function add the indicated task in the
 ** scheduler list
 **
 ** \param[in] TaskID task to be add to the ready list
 **/
extern void AddReady(TaskType TaskID);

/** \brief No Handled Interrupt Handler
 **
 ** This is an interrupt handler used for all not handled interrupts.
 **/ 
extern void OSEK_ISR_NoHandler(void);

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_H_ */

