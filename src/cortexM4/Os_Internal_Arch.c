/* Copyright 2014, Pablo Ridolfi (UTN-FRBA)
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



void* Osek_NewTaskPtr_Arch;

void* Osek_OldTaskPtr_Arch;



/*==================[internal data definition]===============================*/



TaskType TerminatingTask = INVALID_TASK;

TaskType WaitingTask = INVALID_TASK;



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/



void ReturnHook_Arch(void)
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



void CheckTerminatingTask_Arch(void)
{
   /*
    * If there is task being terminated, destroy its context information and
    * reset its state so that the next time that the task is activated it
    * starts its execution on the first instruction of the task body.
    * */

   if(TerminatingTask != INVALID_TASK)
   {
      InitStack_Arch(TerminatingTask);
   }

   TerminatingTask = INVALID_TASK;
}



/* Task Stack Initialization */
void InitStack_Arch(uint8 TaskID)
{
   uint32_t *taskStackRegionPtr;
   int32_t taskStackSizeWords;

   taskStackRegionPtr = (uint32 *)TasksConst[TaskID].StackPtr;

   taskStackSizeWords = TasksConst[TaskID].StackSize / 4;

   /*
    * Build an initial task context block information on the stack such that
    * the task can be kick-started using a simple task context switch to
    * activate it.
    *
    * The cpu context information (register values) is stored on the top
    * of the task stack while the task is not being executed on the processor.
    *
    * The context data block stored on the OS administrative data structures
    * is made up of only a single 32 bits pointer to the top of the task stack.
    *
    * The CortexM task context block is made of three sections:
    *
    *  * Automatically stacked interrupt return context, made up of the registers
    *    that are automatically stacked by the processor during the PendSV exception
    *    entry sequence.
    *
    *  * Floating point context, made up of floating point registers and status
    *    registers. This section is OPTIONAL, and is only stored for certain types of
    *    tasks when the floating point unit is active.
    *
    *  * Integer context, made of the rest of the general purpose registers that
    *    where not included in the first section. The return value of the PendSV
    *    exception is also stored here, in order to protect from the context change
    *    the information about the type of stack being used by the task and the state
    *    of the floating point unit.
    */

   /* **********************************************
    *
    * Manufacture task context information on the
    * initial stack
    *
    * */

   /*
    * CortexM Task Context map:
    *
    * PendSV Interrupt Frame Stack (automatically stacked):
    *
    * [ 1: StackTop -  04] xPSR
    * [ 2: StackTop -  08] PC (R15)
    * [ 3: StackTop -  12] LR (R13)
    * [ 4: StackTop -  16] R12
    * [ 5: StackTop -  20] R3
    * [ 6: StackTop -  24] R2
    * [ 7: StackTop -  28] R1
    * [ 8: StackTop -  32] R0
    *
    */

   taskStackRegionPtr[taskStackSizeWords - 1] = (uint32) (1 << 24);                       /* xPSR.T = 1 */
   taskStackRegionPtr[taskStackSizeWords - 2] = (uint32) TasksConst[TaskID].EntryPoint;   /* initial PC */
   taskStackRegionPtr[taskStackSizeWords - 3] = (uint32) ReturnHook_Arch;                 /* Stacked LR */

   /*
    * PendSV Handler Additional Context Data (stacked by the handler):
    *
    * [ 9: StackTop -  36] S16 (floating point, optional)
    * [10: StackTop -  40] S17 (floating point, optional)
    * [11: StackTop -  44] S18 (floating point, optional)
    * [12: StackTop -  48] S19 (floating point, optional)
    * [13: StackTop -  52] S20 (floating point, optional)
    * [14: StackTop -  56] S21 (floating point, optional)
    * [15: StackTop -  60] S22 (floating point, optional)
    * [16: StackTop -  64] S23 (floating point, optional)
    * [17: StackTop -  68] S24 (floating point, optional)
    * [18: StackTop -  72] S25 (floating point, optional)
    * [19: StackTop -  76] S26 (floating point, optional)
    * [20: StackTop -  80] S27 (floating point, optional)
    * [21: StackTop -  84] S28 (floating point, optional)
    * [22: StackTop -  88] S29 (floating point, optional)
    * [23: StackTop -  92] S30 (floating point, optional)
    * [24: StackTop -  96] S31 (floating point, optional)
    *
    * */

   /*
    * Currently no task uses the floating point unit
    * */

   /*
    * [25: StackTop - 100] Exception Return Value (Contains task CPU Mode/Stack/FPU info)
    * [26: StackTop - 104] R11 (integer context)
    * [27: StackTop - 108] R10 (integer context)
    * [28: StackTop - 112] R9 (integer context)
    * [29: StackTop - 116] R8 (integer context)
    * [30: StackTop - 120] R7 (integer context)
    * [31: StackTop - 124] R6 (integer context)
    * [32: StackTop - 128] R5 (integer context)
    * [33: StackTop - 132] R4 (integer context)
    *
    */

   taskStackRegionPtr[taskStackSizeWords - 9] = 0xFFFFFFFD; /* Exception return value: return using PSP */

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

   *(TasksConst[TaskID].TaskContext) = &(taskStackRegionPtr[taskStackSizeWords - 17]);
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

