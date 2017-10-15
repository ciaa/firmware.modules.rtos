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
 ** \file sparcV8/Os_Internal_Arch.c
 ** \arch sparcV8
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
#include "sparcassembly.h"


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/


/**
 * \brief Communication variable between user and trap versions of CallTask and JmpTask.
 *
 * There is potential for race conditions when updating this variable, because the modification and the triggering
 * do not execute as a single atomic operation. */
TaskContextType *sparcNewContextPtr;

/**
 * \brief Auxiliar context data block.
 *
 * This the is an auxiliar data block that is used to store the running context information when context management code needs
 * to store the context status of a non-task-related code fragment.
 *
 * Examples of this is whenever the system enters interrupt mode while there are no ready tasks on the system, and any interrupt
 * service routine executed before the first task of the system is activated.
 */
TaskContextType sparcNullTaskContextData;


/*==================[external data definition]===============================*/


/**
 * \brief Pointer to the currently active task context data block.
 *
 * The block pointed by this pointer is where the context information is saved upon interrupt mode entry, and
 * from where context data is restored when exiting the outermost interrupt handler.
 */
uint32 *active_thread_context_stack_pointer = (uint32 *)&sparcNullTaskContextData;

/** \brief Flag that indicates the low-level context aware trap entry and exit code if the interrupt
 * service request is nested within another interrupt service routine already in execution, or not.
 *
 * This is used to determine whether the context aware trap entry/exit code must save/restore the
 * context information of a userland task (in a context data block) or that of another another interrupt
 * service routine (on the stack).
 */
uint32 system_in_interrupt_context = 0;

/**
 * \brief Number of implemented register windows on the processor.
 *
 * This parameter is detected by the initialization code, and used by the window
 * overflow/underflow and context aware trap entry/exit codes.
 */
uint32 detected_sparc_register_windows = SPARC_DEFAULT_REGISTER_WINDOW_COUNT;


/*==================[internal functions definition]==========================*/


/**
 * \brief Low level function return catcher.
 *
 * Every task's stack is initialized in such a way that if the main body function of the
 * task returns without having called TerminateTask() o ChainTask(), the return address
 * points to the start of this function.
 *
 * This restricts the possible failure modes caused by the runaway task and facilitates
 * debugging.
 *
 * TODO Currently this function does nothing. Alternatives would be:
 * * To reboot the application whenever a task falls here.
 * * To call ErrorHook() somehow.
 * * To trap to the debugger (only useful during the debugging phase.)
 */
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


/*
 * TODO Eliminate this function. This functionality should be incorporated within contextAwareTrapHandler()
 * */
void sparcTaskContextReplacementHandlerCaller(uint32_t serviceId)
{
   sparcAssert(serviceId >= 0, "Invalid index");
   sparcAssert(serviceId <= 1, "Invalid index");

   /* It used to be the case that there were two services, one for JmpTask() and
    * another for CallTask(), but not anymore. */

   IntSecure_Start();

   sparcNewContextPtr = TasksConst[RunningTask].TaskContext;

   active_thread_context_stack_pointer = sparcNewContextPtr->TaskContextData;

   /* unset the frozen-context flag */
   *(active_thread_context_stack_pointer + 19) = 0x00000000;

   IntSecure_End();
}


/**
 * \brief Task state initialization routine.
 *
 * This function initializes the state of a user task, including both the context data block and the task's stack.
 *
 * In SPARC this routine also sets the read-not-write-context flag on the tasks context data.
 *
 * @param TaskID TaskId of the task whose state information must be initialized.
 */
void SetEntryPoint(TaskType TaskID)
{
   uint32 *stackStartPointer;
   uint32 effectiveStackTop;
   uint32 *stackPointer;
   uint32 *framePointer;
   uint32 *contextDataPtr;

   DisableAllInterrupts();

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
   *(stackPointer + 15) = (uint32) TasksConst[TaskID].EntryPoint; /* %i7 register = return address */
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
    * [contextBase - 4C] to [contextBase - 4F] Padding needed to make the context size a double-word multiple size.
    * [contextBase - 48] to [contextBase - 4B] nPC
    * [contextBase - 44] to [contextBase - 47] PC
    * [contextBase - 40] to [contextBase - 43] %y register
    * [contextBase - 3C] to [contextBase - 3F] %i7 register
    * [contextBase - 38] to [contextBase - 3B] %i6 register = frame pointer
    * [contextBase - 34] to [contextBase - 37] %i5 register
    * [contextBase - 30] to [contextBase - 33] %i4 register
    * [contextBase - 2C] to [contextBase - 2F] %i3 register
    * [contextBase - 28] to [contextBase - 2B] %i2 register
    * [contextBase - 24] to [contextBase - 27] %i1 register
    * [contextBase - 20] to [contextBase - 23] %i0 register
    * [contextBase - 1C] to [contextBase - 1F] %g7 register
    * [contextBase - 18] to [contextBase - 1B] %g6 register
    * [contextBase - 14] to [contextBase - 17] %g5 register
    * [contextBase - 10] to [contextBase - 13] %g4 register
    * [contextBase - 0C] to [contextBase - 0F] %g3 register
    * [contextBase - 08] to [contextBase - 0B] %g2 register
    * [contextBase - 04] to [contextBase - 07] %g1 register
    * [contextBase - 00] to [contextBase - 03] %psr register
    */

   /* The task context data needs to be aligned on an 8 byte boundary,
    * for the time being that is being sorted out by using __attribute__
    * on the type definition of TaskContextType, which unlike the stack space
    * structure does fall within the scope of the port and has a perfectly
    * defined constant size. */
   contextDataPtr = TasksConst[TaskID].TaskContext->TaskContextData;

   /*
    *
    * Floating point initial context should be initialized here, if used.
    *
    * */

   /*
    * Flag that tells sparcTaskContextAwareTrapHandler not to overwrite this
    * this information the next time the handler is invoked. */
   *(contextDataPtr + 19) = 0xffffffff; /* read-not-write context flag */

   /*
    * Start address of the task function */
   *(contextDataPtr + 18) = (uint32) TasksConst[TaskID].EntryPoint + 0x04; /* nPC, task function second instruction */
   *(contextDataPtr + 17) = (uint32) TasksConst[TaskID].EntryPoint + 0x00; /* PC, task function first instruction */

   /*
    * Y register */
   *(contextDataPtr + 16) = 0x00; /* %y register */

   /*
    * trap input registers = initial value of the task's function output registers */
   *(contextDataPtr + 15) = (uint32) taskReturnSafetyNet; /* %i7 register, return address of the task function */
   *(contextDataPtr + 14) = (uint32) stackPointer; /* %i6 register, trap frame pointer */
   *(contextDataPtr + 13) = 0x00; /* %i5 register */
   *(contextDataPtr + 12) = 0x00; /* %i4 register */
   *(contextDataPtr + 11) = 0x00; /* %i3 register */
   *(contextDataPtr + 10) = 0x00; /* %i2 register */
   *(contextDataPtr +  9) = 0x00; /* %i1 register */
   *(contextDataPtr +  8) = 0x00; /* %i0 register */

   /*
    * initial value of the task's global registers*/
   *(contextDataPtr +  7) = 0x00; /* %g7 register */
   *(contextDataPtr +  6) = 0x00; /* %g6 register */
   *(contextDataPtr +  5) = 0x00; /* %g5 register */
   *(contextDataPtr +  4) = 0x00; /* %g4 register */
   *(contextDataPtr +  3) = 0x00; /* %g3 register */
   *(contextDataPtr +  2) = 0x00; /* %g2 register */
   *(contextDataPtr +  1) = 0x00; /* %g1 register */

   /*
    * initial value of the task's Processor Status Register */
   *(contextDataPtr +  0) = SPARC_INITIAL_PSR_VALUE_IN_TASK_CONTEXT; /* %psr register */

   EnableAllInterrupts();
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
