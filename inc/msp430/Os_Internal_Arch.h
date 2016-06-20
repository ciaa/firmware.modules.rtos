/* Copyright 2016, Franco Bucafusco
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

#ifndef _OS_INTERNAL_ARCH_H_
#define _OS_INTERNAL_ARCH_H_

/** \brief FreeOSEK Internal Architecture Dependent Header File
 **
 ** \file msp430/Os_Internal_Arch.h
 ** \arch msp430
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
  * FBUC         Franco Bucafusco
  *
  */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160222 v0.1.0 FBUC   initial version
 */

/*==================[inclusions]=============================================*/
#include "msp430.h"
#include "driverlib.h"

/*==================[macros]=================================================*/

/** \brief Default Value for Status Register
 **
 ** Enable GIE in SR so that the WDT never stops when we go to user task
 ** Enable SCG0 for 25MHZ CPU execution
 **/
#define DEFAULT_SR ((uint16)0x0048)

/** \brief Extra size reserved for each stack
 **
 ** This macro shall be set to the amount of extra stack needed for each task
 ** in the simulation of the rtos in systems like windows/linux. In real
 ** embedded hw this macro shall be set to 0.
 **
 ** TASK_STAC_ADDITIONAL_STACK bytes of extra stack are reserver for each task
 ** running on the system.
 **/
#define TASK_STACK_ADDITIONAL_SIZE      0

/** \brief Osek_Internal_Arch_Cpu.h inclusion needed macro
 **
 ** This define makes the Osek_Internal.h file to include the
 ** Osek_Internal_Arch_Cpu file which is not standard for all architectures.
 ** If for the actual architecture no Osek_Internal_Arch_Cpu.h is needed
 ** remove the macro and this comment.
 **/
#define OSEK_INLCUDE_INTERNAL_ARCH_CPU

extern void *Osek_OldTaskPtr_Arch;
extern void *Osek_NewTaskPtr_Arch;

extern TaskType TerminatingTask;


/** \brief Define common objects for using IntSecure_Start and IntSecure_End-
 **
 ** This macro will be used internaly by the OS in any part of code that
 ** has to be executed atomic. It should be placed before IntSecure_Start or IntSecure_End is called
 **/
#define IntSecure_Common()    unsigned short SR_BACK___;


/** \brief Interrupt Secure Start Macro
 **
 ** This macro will be used internaly by the OS in any part of code that
 ** has to be executed atomic.
 **/
#define IntSecure_Start() SR_BACK___ = _get_SR_register(); \
                                     _disable_interrupts() ; \
                                     __asm__ __volatile__ ("nop");

/** \brief Interrupt Secure End Macro
 **
 ** This macro is the countra part of IntSecure_Start()
 **/
#define IntSecure_End() if( SR_BACK___ & GIE )      \
                        {                           \
                           _enable_interrupts() ;   \
                        }                           \

/** \brief osekpause
 **
 ** This macro is called by the scheduler when not task has to be executed.
 ** If a background task is configured by the user (a full preemptive task
 ** with lower priority and which never ends) this macro will never be called.
 ** In other case the macro will be called any time that the OS has nothing
 ** else to execute. The macro may sleep the cpu for a short time to avoid
 ** overheating and full power consumption or may halt the processor always
 ** that all wakeup reasons are right configured. If nothing is running
 ** nothing my activate any task so we
 **/
#define osekpause() asm volatile("nop")	//TODO revisar los low power modes

/** \brief SAVE_CONTEXT
 **
 ** This macro is called by the context switch routine.
 **
 **/
#define SAVE_CONTEXT()        \
  asm volatile ( "push r4\n\t"\
                 "push r5\n\t"\
                 "push r6\n\t"\
                 "push r7\n\t"\
                 "push r8\n\t"\
                 "push r9\n\t"\
                 "push r10\n\t"\
                 "push r11\n\t"\
                 "push r12\n\t"\
                 "push r13\n\t"\
                 "push r14\n\t"\
                 "push r15\n\t"\
               );

#define RESTORE_CONTEXT()     \
  asm volatile ( "pop r15\n\t"\
                 "pop r14\n\t"\
                 "pop r13\n\t"\
                 "pop r12\n\t"\
                 "pop r11\n\t"\
                 "pop r10\n\t"\
                 "pop r9\n\t"\
                 "pop r8\n\t"\
                 "pop r7\n\t"\
                 "pop r6\n\t"\
                 "pop r5\n\t"\
                 "pop r4\n\t"\
               );

#define RETURN_FROM_NAKED_ISR()  asm volatile ("reti    \n\t");

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define CallTask(actualtask, nexttask)                                     \
{                                                                          \
   Osek_OldTaskPtr_Arch = (void*) (TasksConst[(actualtask)].TaskContext); \
   Osek_NewTaskPtr_Arch = (void*) (TasksConst[(nexttask)].TaskContext);   \
   /* next action will trigger assigned IRQ for the SWI */                 \
   HWREG16(TIMER_A2_BASE + TIMER_A_CAPTURECOMPARE_REGISTER_1) |= (CCIFG|CCIE);    \
}

/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define JmpTask(task)                                                      \
{                                                                          \
   extern TaskType WaitingTask;                                            \
   if(WaitingTask != INVALID_TASK)                                         \
   {                                                                       \
      Osek_OldTaskPtr_Arch = (void*) (TasksConst[WaitingTask].TaskContext);\
      WaitingTask = INVALID_TASK;                                          \
   }                                                                       \
   else                                                                    \
   {                                                                       \
      Osek_OldTaskPtr_Arch = (void*)0;                                     \
   }                                                                       \
   Osek_NewTaskPtr_Arch = (void*) (TasksConst[(task)].TaskContext);       \
   /* next action will trigger assigned IRQ for the SWI */                 \
   HWREG16(TIMER_A2_BASE + TIMER_A_CAPTURECOMPARE_REGISTER_1) |= (CCIFG|CCIE); \
}



/** \brief Save context */
#define SaveContext(task)                                                  \
{                                                                          \
   extern TaskType WaitingTask;                                            \
   if(TasksVar[GetRunningTask()].Flags.State == TASK_ST_WAITING)           \
   {                                                                       \
      WaitingTask = GetRunningTask();                                      \
   }                                                                       \
   flag = 0;                                                               \
   /* remove of the Ready List */                                          \
   RemoveTask(GetRunningTask());                                           \
   /* set system context */                                                \
   SetActualContext(CONTEXT_SYS);                                          \
   /* set running task to invalid */                                       \
   SetRunningTask(INVALID_TASK);                                           \
   /* finish cirtical code */                                              \
   IntSecure_End();                                                        \
   /* call scheduler */                                                    \
   Schedule();                                                             \
   /* add this call in order to maintain counter balance when returning */ \
   IntSecure_Start();                                                      \
}

/** \brief */
#define ResetStack(task)       \
{                              \
   TerminatingTask = (task);   \
}

/** \brief Set the entry point for a task */
#define SetEntryPoint(task)    \
{                              \
   TerminatingTask = (task);   \
}

/** \brief Enable OS Interruptions
 **
 ** Enable OS configured interrupts (ISR1 and ISR2). This macro
 ** is called only ones in StartUp.c function.
 **/
#define EnableOSInterrupts() _enable_interrupts();




/** \brief Enable Interruptions
 **
 ** Enable not OS configured interrupts (ISR1 and ISR2). This macro
 ** is called only ones in StartUp.c function.
 **
 ** This macro may be empty. Maybe will be removed on the future,
 ** please use it only if necessary, in other case use EnableOSInterrupts.
 **/
#define EnableInterrupts() EnableOSInterrupts()


/** \brief Disable OS Interruptions
 **
 ** Disable OS configured interrupts (ISR1 and ISR2).
 ** NOTE: the nop operation after the dint instruction was inserted
 **         to workarround the hw bug cpu39 described in slaz314h.pdf
 **/
#define DisableOSInterrupts()  _disable_interrupts(); __asm__ __volatile__ ("nop");



/** \brief Disable Interruptions
 **
 ** Disable not OS configured interrupts (ISR1 and ISR2). This macro
 ** is called only ones in StartUp.c function.
 **
 ** This macro may be empty. Maybe will be removed on the future,
 ** please use it only if necessary, in other case use DisableOSInterrupts.
 **/
#define DisableInterrupts() DisableOSInterrupts()

/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the a counter
 **
 ** \param[in] CounterID id of the counter to be readed
 ** \return Actual value of the counter
 **/
#define GetCounter_Arch(CounterID) (CountersVar[CounterID].Time)


/** \brief Pre ISR1 Macro
 **
 ** This macro is called every time that an ISR Cat 1 is started
 **/
#define PreIsr1_Arch(isr)


/** \brief Post ISR1 Macro
 **
 ** This macro is called every time that an ISR Cat 1 is finished
 **/
#define PostIsr1_Arch(isr) ClearPendingIRQ_Arch(isr)

/** \brief Pre ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is started
 **/
#define PreIsr2_Arch(isr)

/** \brief Post ISR2 Macro
 **
 ** This macro is called every time that an ISR Cat 2 is finished
 **/
#define PostIsr2_Arch(isr) ClearPendingIRQ_Arch(isr)

/** \brief ShutdownOs Arch service
 **
 ** This macro is called on the ShutdownOS to perform the architecture
 ** dependent shutdown actions.
 **/
#define ShutdownOs_Arch()

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
void InitStack_Arch(uint8 TaskID);
void ClearPendingIRQ_Arch(unsigned short irQ_number);
void MSP430_EnableIRQ(unsigned char irQ_number);
void MSP430_DisableIRQ(unsigned char irQ_number);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */
