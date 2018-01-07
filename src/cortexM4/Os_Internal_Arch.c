/* Copyright 2014, Pablo Ridolfi (UTN-FRBA)
 * Copyright 2017, Gerardo Puga (UNLP)
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

/** \brief FreeOSEK Os Internal Arch Implementation File
 **
 ** \file cortexM4/Os_Internal_Arch.c
 ** \arch cortexM4
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */



/*==================[inclusions]=============================================*/



#include "Os_Internal.h"



/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/



TaskType cortexM4TerminatedTaskID = INVALID_TASK;

TaskContextType cortexM4NullContext;

TaskContextRefType cortexM4ActiveContextPtr = &cortexM4NullContext;



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/



void cortexM4ReturnHook(void)
{
   /*
    * Tasks shouldn't return here...
    *
    * This is a security net for runaway tasks that reach the end of
    * their main body code without terminating their execution
    * properly using TerminateTask or something of the kind.
    *
    * */

   while(1)
   {
      osekpause();
   }
}



/* Task Stack Initialization */
void cortexM4ResetTaskContext(uint8 TaskID)
{
   uint32 *taskStackRegionPtr;
   sint32 taskStackSizeWords;

   taskStackRegionPtr = (uint32 *)TasksConst[TaskID].StackPtr;

   taskStackSizeWords = TasksConst[TaskID].StackSize / 4;

   /*
    * Build an initial task context block information on the stack such that
    * the task can be kick-started using a simple task context switch to
    * activate it.
    *
    * During context switches, the task's context data (made up of the values
    * of all of the cpu registers) is stored/recovered on/from the task's
    * stack.
    *
    * Once the register values are stored on the stack, the task context
    * can be reduced to a pointer to the top of the stack, a single
    * 32 bit word that is stored on the operating system's administrative
    * data structures.
    *
    * The structure of the context information that is stored on the stack
    * during a context switch is composed of:
    *
    *  * Integer register values (R0-R15).
    *  * Floating point register values (S0-S31).
    *  * Special registers (xPSR), FP status register.
    *  * Other task state items: exception return value (Contains task CPU
    *    Mode/Stack/FPU info).
    *
    * This context information can be divided in four blocks:
    *
    * * [BLOCK 1] Automatically saved Floating Point registers.
    * * [BLOCK 2] Automatically saved Integer Registers.
    * * [BLOCK 3] Manually saved Floating Point Registers.
    * * [BLOCK 4] Manually saved Integer Registers.
    *
    * The registers in BLOCK 1 and BLOCK 2 are automatically saved/recovered during the PendSV
    * exception entry/exit sequence, while the ones in BLOCK 3 and BLOCK 4 are manually
    * saved/recovered by the exception handler's code.
    *
    * The floating point registers (BLOCK 1 and BLOCK 3) are not always used: these
    * registers are only stored if the system detects that the floating point unit is in use.
    * On the CortexM architecture this detection is performed automatically CPU when
    * the FPU is enabled by the application's initialization code.
    *
    * */

   /* **********************************************
    *
    * Manufacture task context information on the
    * initial stack
    *
    * */

   /*
    *  BLOCK 1
    *  -------
    *
    * [ BLOCK 1 / INDEX 01 / OFFSET -00 ] FTSCR
    * [ BLOCK 1 / INDEX 02 / OFFSET -04 ] S15
    * [ BLOCK 1 / INDEX 03 / OFFSET -08 ] S14
    *           ... so on...
    * [ BLOCK 1 / INDEX 14 / OFFSET -52 ] S2
    * [ BLOCK 1 / INDEX 15 / OFFSET -56 ] S1
    * [ BLOCK 1 / INDEX 16 / OFFSET -60 ] S0
    *
    * */

   /*
    * ABSENT BLOCK. INITIAL CONTEXT DATA DOES NOT CONTAIN
    * FLOATING POINT DATA
    *
    * */

   /*
    *  BLOCK 2
    *  -------
    *
    * [ BLOCK 2 / INDEX 01 / OFFSET -00 ] xPSR
    * [ BLOCK 2 / INDEX 02 / OFFSET -04 ] PC (R15)
    * [ BLOCK 2 / INDEX 03 / OFFSET -08 ] LR (R14)
    * [ BLOCK 2 / INDEX 04 / OFFSET -12 ] R12
    * [ BLOCK 2 / INDEX 05 / OFFSET -16 ] R3
    * [ BLOCK 2 / INDEX 06 / OFFSET -20 ] R2
    * [ BLOCK 2 / INDEX 07 / OFFSET -24 ] R1
    * [ BLOCK 2 / INDEX 08 / OFFSET -28 ] R0
    *
    * */

   taskStackRegionPtr[taskStackSizeWords - 1] = (uint32) (1 << 24);                       /* xPSR.T = 1 */
   taskStackRegionPtr[taskStackSizeWords - 2] = (uint32) TasksConst[TaskID].EntryPoint;   /* initial PC */
   taskStackRegionPtr[taskStackSizeWords - 3] = (uint32) cortexM4ReturnHook;              /* Stacked LR */

   /*
    *  BLOCK 3
    *  -------
    *
    * [ BLOCK 3 / INDEX 01 / OFFSET -04 ] S31
    * [ BLOCK 3 / INDEX 02 / OFFSET -08 ] S30
    *           ... so on...
    * [ BLOCK 3 / INDEX 15 / OFFSET -52 ] S17
    * [ BLOCK 3 / INDEX 16 / OFFSET -56 ] S16
    *
    * */

   /*
    * ABSENT BLOCK. INITIAL CONTEXT DATA DOES NOT CONTAIN
    * FLOATING POINT DATA
    *
    * */


   /*
    *  BLOCK 4
    *  -------
    *
    * [ BLOCK 4 / INDEX 01 / OFFSET -00 ] Exception Return Value (Contains task CPU Mode/Stack/FPU info)
    * [ BLOCK 4 / INDEX 02 / OFFSET -04 ] R11
    * [ BLOCK 4 / INDEX 03 / OFFSET -08 ] R10
    * [ BLOCK 4 / INDEX 04 / OFFSET -12 ] R9
    * [ BLOCK 4 / INDEX 05 / OFFSET -16 ] R8
    * [ BLOCK 4 / INDEX 06 / OFFSET -20 ] R7
    * [ BLOCK 4 / INDEX 07 / OFFSET -24 ] R6
    * [ BLOCK 4 / INDEX 08 / OFFSET -28 ] R5
    * [ BLOCK 4 / INDEX 08 / OFFSET -28 ] R4
    *
    * */

   /*
    * Exception return value:
    *
    *  * Back to thread mode.
    *  * Return using PSP.
    *  * Set bit 4 to 1, to indicate that this is base stack frame (no FP data).
    *
    * */

   taskStackRegionPtr[taskStackSizeWords - 9] = 0xFFFFFFFD;


   /* **********************************************
    *
    * Initial task context block data
    *
    * */

   /*
    * Initial context block data
    *
    * The context block data is made up of a single pointer to the top
    * of the task stack.
    *
    */

   TasksConst[TaskID].TaskContext->stackTopPointer   = &(taskStackRegionPtr[taskStackSizeWords - 17]);
}



void cortexM4UpdateActiveTaskContextPtr()
{
   if (cortexM4TerminatedTaskID != INVALID_TASK)
   {
      cortexM4ResetTaskContext(cortexM4TerminatedTaskID);

      cortexM4TerminatedTaskID = INVALID_TASK;
   }

   cortexM4ActiveContextPtr = TasksConst[RunningTask].TaskContext;
}



/* Periodic Interrupt Timer, included in all Cortex-M4 processors */
void SysTick_Handler(void)
{
   /* Store the calling context in a variable. */
   ContextType actualContext = GetCallingContext();

   /* Set ISR2 context. */
   SetActualContext(CONTEXT_ISR2);

#if (ALARMS_COUNT != 0)

   /* Counter increment. */
   static CounterIncrementType CounterIncrement = 1; /* TODO remove me. */

   (void)CounterIncrement; /* This avoids a compiler warning because the variable is not being used. */

   /*
    * Enter critical section.
    * */
   IntSecure_Start();

   /*
    * The the RTOS counter increment handler.
    * */
   CounterIncrement = IncrementCounter(0, 1 /* CounterIncrement */); /* TODO FIXME */

   /*
    * Exit the critical section.
    * */
   IntSecure_End();

#endif /* #if (ALARMS_COUNT != 0) */

   /* reset context */
   SetActualContext(actualContext);

#if (NON_PREEMPTIVE == OSEK_DISABLE)

   /*
    * Check if the currently active task is preemptive;
    * if it is, call schedule().
    * */

   if ( ( CONTEXT_TASK == actualContext ) &&
         ( TasksConst[GetRunningTask()].ConstFlags.Preemtive ) )
   {
      /* This shall force a call to the scheduler. */
      PostIsr2_Arch(isr);
   }

#endif /* #if (NON_PREEMPTIVE == OSEK_DISABLE) */
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

