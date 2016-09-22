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
#include "Os_Internal_Arch.h"
#include "Os_Internal_Arch_Cfg.h"
#include "Sparc_Arch.h"


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/


TaskType TerminatingTask = INVALID_TASK;

TaskType WaitingTask = INVALID_TASK;


TaskContextType *sparcNewContextPtr;

TaskContextType *sparcOldContextPtr;


/*==================[external data definition]===============================*/


uint32 *active_thread_context_stack_pointer;

uint32 system_in_interrupt_context = 0;


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


void sparcSetTaskContextSWTrapHandler()
{
   /* This routine implements the software trap handler that performs the JmpTask()
    * system call function.
    *
    * This replaces the current context stack pointer with a new one without
    * saving the previous one, which is supposed to be disposable (because there
    * is not a currently active running task, or because the currently running
    * task has been terminated).
    *
    * */
   active_thread_context_stack_pointer = sparcNewContextPtr->stackBottomPtr;
}


void sparcReplaceTaskContextSWTrapHandler()
{
   /* This routine implements the software trap handler that performs the CallTask()
    * system call function.
    *
    * Basically this replaces the current context stack pointer with a new one, after
    * having saved the previously active task's context information for future retrieval.     *
    * */
   sparcOldContextPtr->stackBottomPtr = active_thread_context_stack_pointer;
   active_thread_context_stack_pointer = sparcNewContextPtr->stackBottomPtr;
}


/*==================[external functions definition]==========================*/


void SaveContext(TaskType runningTask)
{
   if(TasksVar[runningTask].Flags.State == TASK_ST_WAITING)
   {
      WaitingTask = runningTask;
   }
}


void CallTask(TaskType currentTask, TaskType newTask)
{
   sparcOldContextPtr = &TasksConst[(currentTask)].TaskContext;
   sparcNewContextPtr = &TasksConst[(newTask)].TaskContext;

   sparcSystemServiceTriggerReplaceTaskContext();
}


void JmpTask(TaskType newTask)
{
   sparcNewContextPtr = &TasksConst[(newTask)].TaskContext;

   if(WaitingTask != INVALID_TASK)
   {
      sparcOldContextPtr = &TasksConst[(WaitingTask)].TaskContext;
      WaitingTask = INVALID_TASK;

      sparcSystemServiceTriggerReplaceTaskContext();
   }
   else
   {
      sparcSystemServiceTriggerSetTaskContext();
   }
}


void SetEntryPoint(TaskType TaskID)
{
   uint32 *stackStartPointer;
   uint32 *stackPointer;
   uint32 *framePointer;
   uint32 effectiveStackTop;

   stackStartPointer = (uint32 *)TasksConst[TaskID].StackPtr;

   /* the ABI requires that all stack frames start at double word
    * aligned addresses.
    *
    * While this can be enforced by (a) using compiler
    * directives to force the compiler to create stack memory
    * spaces that always start on double word aligned addresses
    * and (b) using always stack sizes that are multiples of 8,
    * I can't enforce either of those restrictions because
    * the stack memory spaces are created on generated code that
    * is outside of the scope of the SPARC port (in Os_Internal_Cfg.c.php)
    * and because stack sizes are configured by the user for each task in the
    * OIL file without any kind of restriction on their value.
    *
    * So, instead of trying to address both those issues, I prefer to select
    * the "effective" top of the stack to be the highest double word aligned
    * address that lies within the stack memory space reserved for the task.
    */
   effectiveStackTop = (((uint32)stackStartPointer) + TasksConst[TaskID].StackSize) & 0xfffffff8;

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

   framePointer = (uint32 *)effectiveStackTop;
   stackPointer = framePointer - SPARC_STACK_BARE_MINIMUM_STACK_FRAME_RESERVATION_SIZE / 4;

   /*
    * other fields required in the ABI */
   *(stackPointer + 22) = 0x00; /* incoming argument 5 */
   *(stackPointer + 21) = 0x00; /* incoming argument 4 */
   *(stackPointer + 20) = 0x00; /* incoming argument 3 */
   *(stackPointer + 19) = 0x00; /* incoming argument 2 */
   *(stackPointer + 18) = 0x00; /* incoming argument 1 */
   *(stackPointer + 17) = 0x00; /* incoming argument 0 */
   *(stackPointer + 16) = 0x00; /* struct/union return pointer */

   /*
    * initial value of the task's function input registers */
   *(stackPointer + 15) = 0x00000000; /* %i7 register = return address */
   *(stackPointer + 14) = (uint32) framePointer; /* i6 register = frame pointer */
   *(stackPointer + 13) = 0x00; /* %i5 register */
   *(stackPointer + 12) = 0x00; /* %i4 register */
   *(stackPointer + 11) = 0x00; /* %i3 register */
   *(stackPointer + 10) = 0x00; /* %i2 register */
   *(stackPointer +  9) = 0x00; /* %i1 register */
   *(stackPointer +  8) = 0x00; /* %i0 register */

   /*
    * initial value of the task's function local registers */
   *(stackPointer +  7) = 0x00; /* %l7 register */
   *(stackPointer +  6) = 0x00; /* %l6 register */
   *(stackPointer +  5) = 0x00; /* %l5 register */
   *(stackPointer +  4) = 0x00; /* %l4 register */
   *(stackPointer +  3) = 0x00; /* %l3 register */
   *(stackPointer +  2) = 0x00; /* %l2 register */
   *(stackPointer +  1) = 0x00; /* %l1 register */
   *(stackPointer +  0) = 0x00; /* %l0 register */

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

   framePointer = stackPointer;
   stackPointer = framePointer - SPARC_STACK_BASE_CONTEXT_RESERVATION_SIZE / 4;

   /*
    * padding required to ensure that the stack pointer is always a multiples of size of a double-word */
   *(stackPointer + 19) = 0x00; /* Padding */

   /*
    * Start address of the task function */
   *(stackPointer + 18) = (uint32) TasksConst[TaskID].EntryPoint + 0x04; /* nPC, task function second instruction */
   *(stackPointer + 17) = (uint32) TasksConst[TaskID].EntryPoint + 0x00; /* PC, task function first instruction */

   /*
    * Y register */
   *(stackPointer + 16) = 0x00; /* %y register */

   /*
    * trap input registers = initial value of the task's function output registers */
   *(stackPointer + 15) = (uint32) taskReturnSafetyNet; /* %i7 register, return address of the task function */
   *(stackPointer + 14) = (uint32) framePointer; /* %i6 register, trap frame pointer */
   *(stackPointer + 13) = 0x00; /* %i5 register */
   *(stackPointer + 12) = 0x00; /* %i4 register */
   *(stackPointer + 11) = 0x00; /* %i3 register */
   *(stackPointer + 10) = 0x00; /* %i2 register */
   *(stackPointer +  9) = 0x00; /* %i1 register */
   *(stackPointer +  8) = 0x00; /* %i0 register */

   /*
    * initial value of the task's global registers*/
   *(stackPointer +  7) = 0x00; /* %g7 register */
   *(stackPointer +  6) = 0x00; /* %g6 register */
   *(stackPointer +  5) = 0x00; /* %g5 register */
   *(stackPointer +  4) = 0x00; /* %g4 register */
   *(stackPointer +  3) = 0x00; /* %g3 register */
   *(stackPointer +  2) = 0x00; /* %g2 register */
   *(stackPointer +  1) = 0x00; /* %g1 register */

   /*
    * initial value of the task's Processor Status Register */
   *(stackPointer +  0) = 0x00; /* %psr register */

   /*
    * Save the initial task context pointer */
   TasksConst[TaskID].TaskContext->stackBottomPtr = stackPointer;
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
