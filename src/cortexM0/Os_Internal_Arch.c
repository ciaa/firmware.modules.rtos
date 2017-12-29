/* Copyright 2015, Pablo Ridolfi (UTN-FRBA)
 * All rights reserved.
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
 ** \file cortexM0/Os_Internal_Arch.c
 ** \arch cortexM0
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */



/*==================[inclusions]=============================================*/



#include "chip.h"
#include "Os_Internal.h"




/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



void *Osek_NewTaskPtr_Arch;
void *Osek_OldTaskPtr_Arch;



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

   uint32 * taskStack = (uint32 *)TasksConst[TaskID].StackPtr;
   int taskStackSizeWords = TasksConst[TaskID].StackSize/4;

   taskStack[taskStackSizeWords-1] = 1<<24; /* xPSR.T = 1 */
   taskStack[taskStackSizeWords-2] = (uint32) TasksConst[TaskID].EntryPoint; /*PC*/
   taskStack[taskStackSizeWords-3] = (uint32) ReturnHook_Arch; /* stacked LR */
   taskStack[taskStackSizeWords-9] = 0xFFFFFFF9; /* current LR, return using MSP */

   *(TasksConst[TaskID].TaskContext) = &(taskStack[taskStackSizeWords - 17]);

}



/* Cortex-M0 core of LPC4337 uses RIT Timer for periodic IRQ */
void RIT_IRQHandler(void)
{
   if(Chip_RIT_GetIntStatus(LPC_RITIMER) == SET)
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

      Chip_RIT_ClearInt(LPC_RITIMER);

      NVIC_ClearPendingIRQ(RITIMER_IRQn);
   }
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
