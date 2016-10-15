/* Copyright 2016, Gerardo Puga (UNLP)
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

/** \brief SPARC V8 System Calls service funcions
 **
 ** \file sparc/syscallservices.s
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */


#include "sparcassembly.h"


   !
   ! This file provides a number of functions that provide access to a set of system
   ! services.
   !
   ! Some of this services are provded locally (e.g. enable traps) while some others are
   ! actually provided by the syscall system software trap.
   !

   ! Entry assumptions: none. This functions are called using the usual function calling scheme. Unless explicitely stated
   ! these functions take no input arguments and return no return values.
   !


   ! **************************************************
   !
   ! void sparcSystemServiceTriggerCallTask();
   !
   ! ***

   .global sparcSystemServiceTriggerReplaceTaskContext
   .type   sparcSystemServiceTriggerReplaceTaskContext, #function

sparcSystemServiceTriggerReplaceTaskContext:

   ta      SPARC_REPLACE_TASK_CONTEXT_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceTriggerCallTask();
   !
   ! ***

   .global sparcSystemServiceTriggerSetTaskContext
   .type   sparcSystemServiceTriggerSetTaskContext, #function

sparcSystemServiceTriggerSetTaskContext:

   ta      SPARC_SET_TASK_CONTEXT_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceEnableTraps();
   !
   ! ***

   .global sparcSystemServiceEnableTraps
   .type   sparcSystemServiceEnableTraps, #function

sparcSystemServiceEnableTraps:

   !
   ! Get the value of the PSR register
   mov     %psr, %g1

   !
   ! check wheter the ET bit is already set
   andcc   %g1, SPARC_PSR_ET_MASK, %g0
   bnz     traps_are_already_enabled

   !
   ! enable traps
   or     %g1, SPARC_PSR_ET_MASK, %g1
   mov    %g1, %psr
   ! three delay cycles needed after writing on the PSR register
   nop
   nop
   nop

traps_are_already_enabled:

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceDisableTraps();
   !
   ! ***

   .global sparcSystemServiceDisableTraps
   .type   sparcSystemServiceDisableTraps, #function

sparcSystemServiceDisableTraps:

   mov     SPARC_SYSCALL_ID_DISABLE_TRAPS, %g1
   ta      SPARC_SYSCALL_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceMaskInterrupts();
   !
   ! ***

   .global sparcSystemServiceMaskInterrupts
   .type   sparcSystemServiceMaskInterrupts, #function

sparcSystemServiceMaskInterrupts:

   mov     SPARC_SYSCALL_ID_MASK_INTERRUPTS, %g1
   ta      SPARC_SYSCALL_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceUnMaskInterrupts();
   !
   ! ***

   .global sparcSystemServiceUnMaskInterrupts
   .type   sparcSystemServiceUnMaskInterrupts, #function

sparcSystemServiceUnMaskInterrupts:

   mov     SPARC_SYSCALL_ID_UNMASK_INTERRUPTS, %g1
   ta      SPARC_SYSCALL_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceRebootSystem();
   !
   ! ***

   .global sparcSystemServiceRebootSystem
   .type   sparcSystemServiceRebootSystem, #function

sparcSystemServiceRebootSystem:

   mov     SPARC_SYSCALL_ID_REBOOT_SYSTEM, %g1
   ta      SPARC_SYSCALL_SERVICE_SW_TRAP_NUMBER

   retl
   nop


   ! **************************************************
   !
   ! void sparcSystemServiceCallDebugger();
   !
   ! ***

   .global sparcSystemServiceCallDebugger
   .type   sparcSystemServiceCallDebugger, #function

sparcSystemServiceCallDebugger:

   !
   ! Invoke the software trap that is used by GDB/GRMON to indicate the
   ! presence of a breakpoint.
   ta      SPARC_CALL_DEBUGGER_SW_TRAP_NUMBER

   retl
   nop

