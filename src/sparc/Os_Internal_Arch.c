/* Copyright 2016, Gerardo Puga (UNLP)
 * Copyright 2014, Pablo Ridolfi (UTN-FRBA)
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
 ** \file sparc/Os_Internal_Arch.c
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/

#include "Os_Internal.h"
#include "Sparc_Arch.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/


void *active_thread_context_stack_pointer;


TaskType TerminatingTask = INVALID_TASK;


TaskType WaitingTask = INVALID_TASK;


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


void taskReturnSafetyNet(void)
{
   /* Tasks shouldn't return here, but if they do this should act
    * as a dead end to contain the damage.
    * */
   while(1)
   {
      osekpause();
   }
}


/*==================[external functions definition]==========================*/


void SaveContext(TaskType runningTask)
{
   if(TasksVar[runningTask].Flags.State == TASK_ST_WAITING)
   {
      WaitingTask = runningTask;
   }
}


void CallTask(TaskType actualtask, TaskType nexttask)
{
   Osek_OldTaskPtr_Arch = (void*)TasksConst[(actualtask)].TaskContext;
   Osek_NewTaskPtr_Arch = (void*)TasksConst[(nexttask)].TaskContext;

   sparcSystemServiceTriggerCallTask();
}


void JmpTask(TaskType task)
{
   extern TaskType WaitingTask;

   Osek_NewTaskPtr_Arch = (void*)TasksConst[(task)].TaskContext;

   if(WaitingTask != INVALID_TASK)
   {
      Osek_OldTaskPtr_Arch = (void*)TasksConst[WaitingTask].TaskContext;
      WaitingTask = INVALID_TASK;

      sparcSystemServiceTriggerCallTask();
   }
   else
   {
      Osek_OldTaskPtr_Arch = (void*)0;

      sparcSystemServiceTriggerJmpTask();
   }
}


void SetEntryPoint(TaskType TaskID)
{
   uint32 *taskStack;
   int stackPointerInWords;
   int framePointerInWords;

   taskStack = (uint32 *)TasksConst[TaskID].StackPtr;

   framePointerInWords = TasksConst[TaskID].StackSize / 4;

   /*
    * STACK-TOP INITIALIZATION STACK FRAME
    * ------------------------------------
    *
    * This is a bare minimum stack frame, with only the fields required per SPARC ABI.
    *
    * [sp - 58] to [sp - 5B] incoming argument 5 (mandatory even when not used)
    * [sp - 54] to [sp - 57] incoming argument 4 (mandatory even when not used)
    * [sp - 50] to [sp - 53] incoming argument 3 (mandatory even when not used)
    * [sp - 4C] to [sp - 4F] incoming argument 2 (mandatory even when not used)
    * [sp - 48] to [sp - 4B] incoming argument 1 (mandatory even when not used)
    * [sp - 44] to [sp - 47] incoming argument 0 (mandatory even when not used)
    * [sp - 40] to [sp - 43] struct/union return pointer (mandatory even when not used)
    * [sp - 3C] to [sp - 3F] %i7 register
    * [sp - 38] to [sp - 3B] %i6 register = frame pointer
    * [sp - 34] to [sp - 37] %i5 register
    * [sp - 30] to [sp - 33] %i4 register
    * [sp - 2C] to [sp - 2F] %i3 register
    * [sp - 28] to [sp - 2B] %i2 register
    * [sp - 24] to [sp - 27] %i1 register
    * [sp - 20] to [sp - 23] %i0 register
    * [sp - 1C] to [sp - 1F] %l7 register
    * [sp - 18] to [sp - 1B] %l6 register
    * [sp - 14] to [sp - 17] %l5 register
    * [sp - 10] to [sp - 13] %l4 register
    * [sp - 0C] to [sp - 0F] %l3 register
    * [sp - 08] to [sp - 0B] %l2 register
    * [sp - 04] to [sp - 07] %l1 register
    * [sp - 00] to [sp - 03] %l0 register
    */

   stackPointerInWords = framePointerInWords - SPARC_STACK_BARE_MINIMUM_STACK_FRAME_RESERVATION_SIZE / 4;

   /*
    * other fields required in the ABI */
   taskStack[stackPointerInWords + 22] = 0x00; /* incoming argument 5 */
   taskStack[stackPointerInWords + 21] = 0x00; /* incoming argument 4 */
   taskStack[stackPointerInWords + 20] = 0x00; /* incoming argument 3 */
   taskStack[stackPointerInWords + 19] = 0x00; /* incoming argument 2 */
   taskStack[stackPointerInWords + 18] = 0x00; /* incoming argument 1 */
   taskStack[stackPointerInWords + 17] = 0x00; /* incoming argument 0 */
   taskStack[stackPointerInWords + 16] = 0x00; /* struct/union return pointer */

   /*
    * initial value of the task's function input registers */
   taskStack[stackPointerInWords + 15] = 0x00000000; /* %i7 register = return address */
   taskStack[stackPointerInWords + 14] = &(taskStack[framePointerInWords]); /* i6 register = frame pointer */
   taskStack[stackPointerInWords + 13] = 0x00; /* %i5 register */
   taskStack[stackPointerInWords + 12] = 0x00; /* %i4 register */
   taskStack[stackPointerInWords + 11] = 0x00; /* %i3 register */
   taskStack[stackPointerInWords + 10] = 0x00; /* %i2 register */
   taskStack[stackPointerInWords +  9] = 0x00; /* %i1 register */
   taskStack[stackPointerInWords +  8] = 0x00; /* %i0 register */

   /*
    * initial value of the task's function local registers */
   taskStack[stackPointerInWords +  7] = 0x00; /* %l7 register */
   taskStack[stackPointerInWords +  6] = 0x00; /* %l6 register */
   taskStack[stackPointerInWords +  5] = 0x00; /* %l5 register */
   taskStack[stackPointerInWords +  4] = 0x00; /* %l4 register */
   taskStack[stackPointerInWords +  3] = 0x00; /* %l3 register */
   taskStack[stackPointerInWords +  2] = 0x00; /* %l2 register */
   taskStack[stackPointerInWords +  1] = 0x00; /* %l1 register */
   taskStack[stackPointerInWords +  0] = 0x00; /* %l0 register */


   /*
    * INITIAL TASK CONTEXT DATA
    * -------------------------------
    *
    * [sp - 4C] to [sp - 4F] Padding needed to make the context size a double-word multiple size.
    * [sp - 48] to [sp - 4B] nPC
    * [sp - 44] to [sp - 47] PC
    * [sp - 40] to [sp - 43] %y register
    * [sp - 3C] to [sp - 3F] %i7 register
    * [sp - 38] to [sp - 3B] %i6 register = frame pointer
    * [sp - 34] to [sp - 37] %i5 register
    * [sp - 30] to [sp - 33] %i4 register
    * [sp - 2C] to [sp - 2F] %i3 register
    * [sp - 28] to [sp - 2B] %i2 register
    * [sp - 24] to [sp - 27] %i1 register
    * [sp - 20] to [sp - 23] %i0 register
    * [sp - 1C] to [sp - 1F] %g7 register
    * [sp - 18] to [sp - 1B] %g6 register
    * [sp - 14] to [sp - 17] %g5 register
    * [sp - 10] to [sp - 13] %g4 register
    * [sp - 0C] to [sp - 0F] %g3 register
    * [sp - 08] to [sp - 0B] %g2 register
    * [sp - 04] to [sp - 07] %g1 register
    * [sp - 00] to [sp - 03] %psr register
    */


   framePointerInWords = stackPointerInWords;
   stackPointerInWords = framePointerInWords - SPARC_STACK_BASE_CONTEXT_RESERVATION_SIZE / 4;

   /*
    * padding required to ensure that the stack pointer is always a multiples of size of a double-word */
   taskStack[stackPointerInWords + 19] = 0x00; /* Padding */

   /*
    * Start address of the task function */
   taskStack[stackPointerInWords + 18] = (uint32) TasksConst[TaskID].EntryPoint + 0x04; /* nPC, task function second instruction */
   taskStack[stackPointerInWords + 17] = (uint32) TasksConst[TaskID].EntryPoint + 0x00; /* PC, task function first instruction */

   /*
    * Y register */
   taskStack[stackPointerInWords + 16] = 0x00; /* %y register */

   /*
    * trap input registers = initial value of the task's function output registers */
   taskStack[stackPointerInWords + 15] = (uint32) taskReturnSafetyNet; /* %i7 register, return address of the task function */
   taskStack[stackPointerInWords + 14] = (uint32) &(taskStack[framePointerInWords]); /* %i6 register, trap frame pointer */
   taskStack[stackPointerInWords + 13] = 0x00; /* %i5 register */
   taskStack[stackPointerInWords + 12] = 0x00; /* %i4 register */
   taskStack[stackPointerInWords + 11] = 0x00; /* %i3 register */
   taskStack[stackPointerInWords + 10] = 0x00; /* %i2 register */
   taskStack[stackPointerInWords +  9] = 0x00; /* %i1 register */
   taskStack[stackPointerInWords +  8] = 0x00; /* %i0 register */

   /*
    * initial value of the task's global registers*/
   taskStack[stackPointerInWords +  7] = 0x00; /* %g7 register */
   taskStack[stackPointerInWords +  6] = 0x00; /* %g6 register */
   taskStack[stackPointerInWords +  5] = 0x00; /* %g5 register */
   taskStack[stackPointerInWords +  4] = 0x00; /* %g4 register */
   taskStack[stackPointerInWords +  3] = 0x00; /* %g3 register */
   taskStack[stackPointerInWords +  2] = 0x00; /* %g2 register */
   taskStack[stackPointerInWords +  1] = 0x00; /* %g1 register */

   /*
    * initial value of the task's Processor Status Register */
   taskStack[stackPointerInWords +  0] = 0x00; /* %psr register */


   /*
    * Save the initial task context pointer */
   *(TasksConst[TaskID].TaskContext) = &(taskStack[stackPointerInWords]);
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

