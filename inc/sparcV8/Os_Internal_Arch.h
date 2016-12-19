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
#include "sparcsyscalls.h"


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
 ** According to Aeroflex Gaisler LEON 3 documentation, the LEON 3
 ** implementation of the SPARC Architecture will enter into a power
 ** down mode by executing a WRASR instruction to the %asr19 register.
 ** In this power-down mode, the processor halts the pipeline, freezing
 ** code execution and cache changes until the next interrupt comes along.
 ** */
#define osekpause() {  asm("wr %g0, %asr19"); }


/**
 * \brief SPARC implementation of the OSEK low-level interface routine SaveContext().
 *
 * The context saving/restoring code of the SPARC port does not need to use this function, so
 * it is declared here only a place holder.
 *
 * \param[in] runningTask TaskId of the task whose context must be saved.
 */
#define SaveContext(runningTask) { /* nop */ }

/**
 * \brief SPARC implementation of the OSEK low-level interface routine CallTask().
 *
 * \param[in] currentTask Currently running task's id, whose context needs to be retired from the cpu.
 * \param[in] newTask TaskId of the task whose context needs to be installed on the cpu.
 */
#define CallTask(currentTask, newTask) { sparcSystemServiceTriggerReplaceTaskContext(); }


/**
 * \brief SPARC implementation of the OSEK low-level interface routine JmpTask().
 *
 * \param[in] newTask TaskId of the task whose context needs to be installed on the cpu.
 */
#define JmpTask(newTask) { sparcSystemServiceTriggerSetTaskContext(); }


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/


extern TaskType TerminatingTask;

extern uint32 detected_sparc_register_windows;


/*==================[external functions declaration]=========================*/


void SetEntryPoint(TaskType task);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */

