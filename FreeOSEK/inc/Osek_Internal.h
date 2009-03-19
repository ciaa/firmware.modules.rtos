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
 * that communicate with FreeOSEK solely through the OpenSEK defined interface. 
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

#ifndef _OSEK_INTERNAL_H_
#define _OSEK_INTERNAL_H_
/** \brief FreeOSEK Internal Header File
 **
 ** FreeOSEK Internal Header File
 **
 ** \file Osek_Internal.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Internal OpenSEK Internal
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 * KLi           Kang Li
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090130 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20081113 v0.1.1 KLi  Added memory layout attribute macros
 * 20080713 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "os.h"
#include "Osek_Internal_Arch.h"
#ifdef OSEK_INLCUDE_INTERNAL_ARCH_CPU
/** Osek_Internal_Arch_Cpu.h is only included if the macro
 ** OSEK_INCLUDE_INTERNAL_ARCH_CPU is defined on
 ** Osek_Internal_Arch.h **/
#include "Osek_Internal_Arch_Cpu.h"
#endif /* #ifdef OSEK_INLCUDE_INTERNAL_ARCH_CPU */
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

/** \brief Pre ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is started
 **/
#define PreIsr2(isr)	PreIsr2_Arch(isr)

/** \brief Post ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is finished
 **/
#define PostIsr2(isr) PostIsr2_Arch(isr)

/*==================[typedef]================================================*/
/** \brief ContextType
 **
 ** Type used to represent the actual context
 **/
typedef uint8 ContextType;

/*==================[external data declaration]==============================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_DATA
#include "MemMap.h"
#endif

/** \brief ActualContext
 **
 ** This variable saves the actual context
 **/
extern ContextType ActualContext;

/** \brief RunningTask variable */
extern TaskType RunningTask;

#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_DATA
#include "MemMap.h"
#endif

/*==================[external functions declaration]=========================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_CODE
#include "MemMap.h"
#endif

/** \brief Architecture Dependnece Start Os function
 **
 ** This function is called from the StartOs function
 **/
extern void StartOs_Arch(void) ATTRIBUTES();

/** \brief Get Next Task
 **
 ** This functions returns the next task that shall be executed
 ** in order of the task activation and priority
 **
 ** \return next task to be executed
 **/
extern TaskType GetNextTask(void) ATTRIBUTES();

/** \brief Remove Task of the Ready List
 **
 ** This function will remove the first task on the
 ** ready list with priority equal to the static
 ** priority of the given TaskID
 **
 ** \param[in] TaskID TaskID
 **/
void RemoveTask(TaskType TaskID) ATTRIBUTES();

/** \brief Add Task to the scheduler list
 **
 ** This function add the indicated task in the
 ** scheduler list
 **
 ** \param[in] TaskID task to be add to the ready list
 **/
extern void AddReady(TaskType TaskID) ATTRIBUTES();

/** \brief No Handled Interrupt Handler
 **
 ** This is an interrupt handler used for all not handled interrupts.
 **/ 
extern void OSEK_ISR_NoHandler(void) ATTRIBUTES();

#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_H_ */

