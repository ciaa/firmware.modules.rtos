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

/** \brief SPARC V8 Default trap handler.
 **
 ** \file sparc/defaulthandler.s
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
   ! Default trap handler.
   ! This handler is used to for any trap table entry that does
   ! not have its own customized trap handler, which may happen
   ! if the trap is not actually implemented in a given SPARC v8
   ! implementation, or because it is not expected that
   ! the trap will be generated under normal circumstances.
   !
   ! The code assumes the following register values on entry:
   !  %l0 = psr
   !  %l1 = PC
   !  %l2 = nPC
   !  %l3 = trap type, or trap service table index
   !
   .global sparcDefaultTrapHandler
   .type   sparcDefaultTrapHandler, #function

sparcDefaultTrapHandler:

   !
   ! Default action: Call the debugger.
   !

   !
   ! Since the debugger is called using a software trap,
   ! traps must be reenabled.
   or     %l0, SPARC_PSR_ET_MASK, %l0
   mov    %l0, %psr
   ! After each write to the PSR register we must avoid 
   ! operations that can read/write its value for at least
   ! the next three cycles.
   nop
   nop
   nop

   !
   ! Invoke the software trap that is used by GDB/GRMON
   ! to indicate the presence of a breakpoint.
   ta      SPARC_CALL_DEBUGGER_SW_TRAP_NUMBER

   !
   ! Return to the interrupted trap
   !
   ! This is probably not going to get executed, since we called the 
   ! debugger, but just for completeness...

   ! Precise trap. Go back to the instruction located right after
   ! the instruction that trapped.
   jmp     %l2
   rett    %l2 + 0x04

