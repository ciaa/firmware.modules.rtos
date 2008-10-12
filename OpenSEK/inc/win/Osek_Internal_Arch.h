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
 ** \file Osek_Internal_Arch.h
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
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "unistd.h"
#include "signal.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "errno.h"

/*==================[macros]=================================================*/
/** \brief Lenght of the Message Queue */
#define MESSAGE_QUEUE_LENGTH  32

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

/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define JmpTask(task) \
   {                                                                                            \
      __asm__ __volatile__ ("movl %0, %%esp;" \
         "movl %2, %%eax;" \
         "movl %1, %%ebp;" \
         "jmp *%%eax;" \
         : :  "g" (TasksConst[(task)].TaskContext->tss_esp), "g" (TasksConst[(task)].TaskContext->tss_ebp) , "g" (TasksConst[(task)].TaskContext->tss_eip) : "%eax"); \
   }

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
/* #define CallTask(task)															\
	{																					\
		SaveContext(GetRunningTask());                              \
      *//* set as running task *//*											   \
		SetRunningTask(task);												   \
	   JmpTask(task);                                              \
		RestoreContext();                                           \
	}*/

/** \brief Save context */
#define SaveContext(task) \
   {                                   \
      /* save actual esp */            \
      __asm__ __volatile__ ("movl %%esp, %%eax; movl %%eax, %0;" : "=g" (TasksConst[(task)].TaskContext->tss_esp) : : "%eax" ); \
                                       \
      /* save actual ebp */            \
      __asm__ __volatile__ ("movl %%ebp, %%eax; movl %%eax, %0;" : "=g" (TasksConst[(task)].TaskContext->tss_ebp) : : "%eax" );  \
                                       \
      /* save return eip */            \
      __asm__ __volatile__ ("movl $_next, %%eax; movl %%eax, %0;" : "=g" (TasksConst[(task)].TaskContext->tss_eip) : : "%eax"); \
      __asm__ __volatile__ ("_next:"); \
   }

/** \brief Set the entry point for a task */
#define SetEntryPoint(task)   { TasksConst[(task)].TaskContext->tss_eip = (uint32)TasksConst[(task)].EntryPoint; }

/** \brief */
#define ResetStack(task)																													      \
	{																																				      \
		TasksConst[loopi].TaskContext->tss_esp = (uint32)( TasksConst[loopi].StackPtr + TasksConst[loopi].StackSize - 4);  \
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

/** \brief Message Queue type definition */
typedef struct {
   uint8 Lock;
   uint8 Buffer[MESSAGE_QUEUE_LENGTH];
   uint8 Last;
   uint8 First;
   uint8 Count;
} MessageQueueType;

/*==================[external data declaration]==============================*/
/** \brief Interrupt Falg
 **
 ** This variable indicate the state of the posix interrupts. If bit 0 is set
 ** interrupt 0 has been activated, if bit 1 is set interrupt 1 has been
 ** activated, and so on.
 **/
extern InterruptFlagsType InterruptFlag;

/** \brief Message Signal
 **/
extern struct sigaction MessageSignal;

/** \brief Signal Event
 **/
/* extern struct sigevent SignalEvent; */

/** \brief Osek Hardware Timer 0
 **/
/* extern uint32 OsekHWTimer0; */

extern MessageQueueType *MessageQueue;

extern int SharedMemory;

/*==================[external functions declaration]=========================*/
extern void CallTask(TaskType NewTask);

extern StatusType SetEvent(TaskType TaskID, EventMaskType Mask);

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

