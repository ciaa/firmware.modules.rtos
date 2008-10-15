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

#ifndef _OSEK_INTERNAL_ARCH_H_
#define _OSEK_INTERNAL_ARCH_H_
/** \brief OpenSEK Internal Architecture Dependent Header File
 **
 ** \file posix/Osek_Internal_Arch.h
 ** \arch posix
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup Internal
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080725 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "ucontext.h"	/* used to task changes */
#include "mqueue.h"		/* used to simulate interrupts */
#include "errno.h"		/* used to read errno */
#include "stdio.h"		/* used to print debug information */
#include "signal.h"		/* used to simulate interrupts */
#include "unistd.h"		/* used to create a fork to poll the interrupts */
#include "stdlib.h"		/* used to call exit to terminate the process */
#include "time.h"			/* used to simulate the hardware timer */

/*==================[macros]=================================================*/
/** \brief Interrupt Secure Start Macro
 **
 ** This macro shall be used to disable the interrupts
 **/
#define IntSecure_Start() SuspendAllInterrupts()

/** \brief Interrupt Secure End Macro
 **
 ** This macro shall be used to restore the interrupts
 **/
#define IntSecure_End() ResumeAllInterrupts()

/** \brief osekpause
 **
 **/
#define osekpause()	{ (void)usleep(1); }

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define CallTask(task)															\
	{																					\
		uint8 jmp = 1;																\
		(void)getcontext(TasksConst[GetRunningTask()].TaskContext);	\
		jmp--;																		\
		if (jmp == 0)																\
		{																				\
			/* set as running task */											\
			SetRunningTask(task);												\
			(void)setcontext(TasksConst[(task)].TaskContext);			\
		}																				\
	}

/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define JmpTask(task)   { (void)setcontext(TasksConst[(task)].TaskContext); }

/** \brief Save context */
#define SaveContext(task) { (void)getcontext(TasksConst[(task)].TaskContext); }

/** \brief Set the entry point for a task */
#define SetEntryPoint(task)   { (void)makecontext(TasksConst[(task)].TaskContext, TasksConst[(task)].EntryPoint, 0); }

/** \brief */
#define ResetStack(task)																													\
	{																																				\
		TasksConst[loopi].TaskContext->uc_stack.ss_sp = TasksConst[loopi].StackPtr;      /* set stack pointer */	\
		TasksConst[loopi].TaskContext->uc_stack.ss_size = TasksConst[loopi].StackSize;   /* set stack size */		\
		TasksConst[loopi].TaskContext->uc_stack.ss_flags = 0;																		\
   }

#define ISR_NMI      0
#define ISR_CTR      1
#define ISR_CANRX    2
#define ISR_CANTX    3

#define EnableOSInterrupts()															\
	{																							\
		InterruptMask &= (InterruptFlagsType)~(OSEK_OS_INTERRUPT_MASK);	\
	}

#define EnableInterrupts()		\
	{									\
		InterruptState = 1;		\
	}

/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the counter
 **
 ** \param[in] CounterID id of the counter to be readed
 ** \return Actual value of the counter
 **/
#define GetCounter_Arch(CounterID) (CountersVar[CounterID].Time)

/*==================[typedef]================================================*/
/** \brief uint8 type definition */
typedef unsigned char uint8;

/** \brief sint8 type definition */
typedef signed char sint8;

/** \brief uint16 type definition */
typedef unsigned short uint16;

/** \brief sint16 type definition */
typedef signed short sint16;

/** \brief uint32 type definition */
typedef unsigned int uint32;

/** \brief sint32 type definition */
typedef signed int sint32;

/** \brief uint8_least type definition */
typedef unsigned int uint8_least;

/** \brief sint8_least type definition */
typedef signed int sint8_least;

/** \brief uint16_least type definition */
typedef unsigned int uint16_least;

/** \brief sint16_least type definition */
typedef signed int sint16_least;

/** \brief uint32_least type definition */
typedef unsigned int uint32_least;

/** \brief sint32_least type definition */
typedef signed int sint32_least;

/** \brief falg type definition */
typedef unsigned char flag;

/*==================[external data declaration]==============================*/
/** \brief Interrupt Falg
 **
 ** This variable indicate the state of the posix interrupts. If bit 0 is set
 ** interrupt 0 has been activated, if bit 1 is set interrupt 1 has been
 ** activated, and so on.
 **/
extern InterruptFlagsType InterruptFlag;

/** \brief Message Queue
 **/
extern mqd_t MessageQueue;

/** \brief Message Queue Attributes
 **/
extern struct mq_attr MessageQueueAttr;

/** \brief Message Signal
 **/
extern struct sigaction MessageSignal;

/** \brief Kill Signal
 **/
extern struct sigaction KillSignal;

/** \brief Signal Event
 **/
extern struct sigevent SignalEvent;

/** \brief Osek Hardware Timer 0
 **/
extern uint32 OsekHWTimer0;

/*==================[external functions declaration]=========================*/
/** \brief Posix Interrupt Handler
 **
 ** This function is called every time when a interrupt message is received.
 **/
extern void PosixInterruptHandler(int status);

extern void HWTimerFork(uint8 timer);

extern void OsekKillSigHandler(int status);

extern void OSEK_ISR_HWTimer0(void);

extern void OSEK_ISR_HWTimer1(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_H_ */

