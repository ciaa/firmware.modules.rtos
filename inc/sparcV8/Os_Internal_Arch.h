/* Copyright 2016, Gerardo Puga (UNLP)
 *
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
 ** \file sparcV8/Os_Internal_Arch.h
 ** \arch sparcV8
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/


#include "os.h"
#include "Os_Arch.h"
#include "Os_Internal_Arch_Cpu.h"


/*==================[macros]=================================================*/


/** \brief Extra size reserved for each stack
 **
 ** This macro shall be set to the amount of extra stack needed for each task
 ** in the simulation of the rtos in systems like windows/linux. In real
 ** embedded hw this macro shall be set to 0.
 **
 ** TASK_STACK_ADDITIONAL_STACK bytes of extra stack are reserved for each task
 ** running on the system.
 **/
#define TASK_STACK_ADDITIONAL_SIZE 0


/** \brief Osek_Internal_Arch_Cpu.h inclusion needed macro
 **
 ** This define makes the Osek_Internal.h file to include the
 ** Osek_Internal_Arch_Cpu file which is not standard for all architectures.
 ** If for the actual architecture no Osek_Internal_Arch_Cpu.h is needed
 ** remove the macro and this comment.
 **
 ** The typo must be preserved because this is how the macro is called on the
 ** FreeOSEK source code.
 **/
#define OSEK_INLCUDE_INTERNAL_ARCH_CPU


/** \brief Interrupt Secure Start Macro
 **
 ** This macro will be used internally by the OS whenever it
 ** needs to get into a critical region and execute code
 ** atomically.
 **/
#define IntSecure_Start() { SuspendAllInterrupts(); }


/** \brief Interrupt Secure End Macro
 **
 ** This macro complements of IntSecure_Start(). It re-enables
 ** interrupts, signaling the end of the critical region.
 **/
#define IntSecure_End() { ResumeAllInterrupts(); }


/** \brief Enable OS Interruptions
 **
 ** Enable OS configured interrupts (ISR1 and ISR2). This macro
 ** is called only at the end of the StartOS() function.
 **/
#define EnableOSInterrupts() { sparcEnableAllInterrupts(); }


/** \brief Enable Interruptions
 **
 ** Enable not OS configured interrupts (ISR1 and ISR2). This macro
 ** is called only from StartUp.c
 **
 ** This macro may be empty. Maybe will be removed on the future,
 ** please use it only if necessary, in other case use EnableOSInterrupts.
 **/
#define EnableInterrupts()


/** \brief Disable OS Interruptions
 **
 ** Disable OS configured interrupts (ISR1 and ISR2). This macro is currently never
 ** called from anywhere in the code.
 **
 **/
#define DisableOSInterrupts() { sparcEnableAllInterrupts(); }


/** \brief Disable Interruptions
 **
 ** Disable not OS configured interrupts (ISR1 and ISR2). This macro is currently never
 ** called from anywhere in the code.
 **
 ** This macro may be empty. Maybe will be removed on the future,
 ** please use it only if necessary, in other case use DisableOSInterrupts.
 **/
#define DisableInterrupts()


/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the a counter
 **
 ** \param[in] CounterID id of the counter to be read
 ** \return Actual value of the counter
 **/
#define GetCounter_Arch(CounterID) (CountersVar[CounterID].Time)


/** \brief Pre ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is started
 **/
#define PreIsr2_Arch(isr)


/** \brief Post ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is finished
 **/
#define PostIsr2_Arch(isr) Schedule_WOChecks()


/** \brief ShutdownOs Arch service
 **
 ** This macro is called on the ShutdownOS to perform the architecture
 ** dependent shutdown actions.
 **/
#define ShutdownOs_Arch()


/** \brief osekpause
 **
 ** This macro is called by the scheduler when there are no tasks available
 ** for execution. If a background task is configured by the user (a full
 ** preemptive task with lower priority and which never ends) this macro will
 ** never be called. Otherwise this macro will be called any time that the
 ** OS has nothing else to execute. The macro may sleep the cpu for a short time
 ** to avoid over heating and full power consumption, or may halt the processor
 ** until an event wakes it up again (for example, an external interrupt).
 **
 **/
#define osekpause() { sparcOsekPause(); }


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/


extern TaskType TerminatingTask;

extern uint32 detected_sparc_register_windows;


/*==================[external functions declaration]=========================*/



void SaveContext(TaskType task);


void CallTask(TaskType actualtask, TaskType nexttask);


void JmpTask(TaskType task);


void SetEntryPoint(TaskType task);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */

