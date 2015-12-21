/* Copyright 2008, 2009, 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _OS_INTERNAL_H_
#define _OS_INTERNAL_H_
/** \brief FreeOSEK Os Internal Header File
 **
 ** FreeOSEK Os Internal Header File
 **
 ** \file Os_Internal.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal Internal
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
 * 20150619 v0.1.5 MaCe fix issue #279
 * 20090719 v0.1.4 MaCe rename file to Os_
 * 20090329 v0.1.3 MaCe add TASK_MAX_PRIORITY macro
 * 20090130 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20081113 v0.1.1 KLi  Added memory layout attribute macros
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "os.h"
#include "Os_Internal_Arch.h"
#ifdef OSEK_INLCUDE_INTERNAL_ARCH_CPU
/** Os_Internal_Arch_Cpu.h is only included if the macro
 ** OSEK_INCLUDE_INTERNAL_ARCH_CPU is defined on
 ** Os_Internal_Arch.h **/
#include "Os_Internal_Arch_Cpu.h"
#endif /* #ifdef OSEK_INLCUDE_INTERNAL_ARCH_CPU */
#include "Os_Internal_Arch_Cfg.h"
#include "Os_Internal_Cfg.h"
#include "ciaaPlatforms.h"
#if (OSEK_MULTICORE == OSEK_ENABLE)
#include "ciaaMulticore.h"
#endif

/*==================[macros]=================================================*/
/** \brief Invalid Task */
#define INVALID_TASK  ((TaskType)~0)

/** \brief State for Suspended Tasks */
#define TASK_ST_SUSPENDED   SUSPENDED

/** \brief State for Ready Tasks */
#define TASK_ST_READY       READY

/** \brief State for Running Task */
#define TASK_ST_RUNNING     RUNNING

/** \brief State for Wating Tasks */
#define TASK_ST_WAITING     WAITING

/** \brief Invalid Task State */
#define TASK_ST_INVALID     ((TaskStateType)~0)

/** \brief Task Maximal Priority */
#define TASK_MAX_PRIORITY ((TaskPriorityType)~0)

/** \brief Error Checking Standard */
#define ERROR_CHECKING_STANDARD   1

/** \brief Error Checking Extended */
#define ERROR_CHECKING_EXTENDED   2

/** \brief Release Internal Resources
 **
 ** This interface release the internal resources of the actual task
 **/
#define ReleaseInternalResources()                     \
{                                                      \
}

/** \brief Invalid Context */
#define CONTEXT_INVALID ((ContextType)0U)
/** \brief Task Context */
#define CONTEXT_TASK ((ContextType)1U)
/** \brief ISR Category 1 Context */
#define CONTEXT_ISR1 ((ContextType)2U)
/** \brief ISR Category 2 Context */
#define CONTEXT_ISR2 ((ContextType)3U)
/** \brief SYS Context */
#define CONTEXT_SYS  ((ContextType)4U)
/** \brief DBG Context */
#define CONTEXT_DBG  ((ContextType)5U)

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
#define SetActualContext(newcontext)  \
   do {                               \
      ActualContext = (newcontext);   \
   } while(0)

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

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
/** \brief Schedule the Task running after the ISR ends if a higher
 **        priority Task is Active
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used internally by the system.
 **
 ** \remarks This interfaces calls the Scheduler and indicate it to avoid
 **          any checks regarding the context where it has been called, or
 **          the use of resources. This interface is only for internal use
 **          and shall not be used by the rtos user.
 **
 ** \return E_OK
 **/
#define Schedule_WOChecks() Schedule_Int(FALSE)
#elif (ERROR_CHECKING_TYPE == ERROR_CHECKING_STANDARD)
/* if standard error checking is used, the scheduler does not perform any check
 * and cann be called irectly */
#define Schedule_WOChecks() Schedule()
#endif

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
 ** This function is called from the StartOS function
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

/** \brief Increment Counter Service
 **
 ** This service is called to increment a specific counter an Increment amount
 ** of times.
 **
 ** \param[in] CounterID id of the counter to be incremented
 ** \param[in] Increment amount of times to increment the counter
 ** \return after how many increments of the CounterID the function has to be
 ** called. If the function is called again later as should with a grater
 ** increment some events may be executed together.
 **/
extern CounterIncrementType IncrementCounter(CounterType CounterID, CounterIncrementType Increment);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_H_ */

