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

        !
        ! Default trap handler, used to be assigned to any trap table entry that does not have a specially customized trap handler. This
        ! may be because the trap is not actually implemented in a given SPARC v8 implementation, or because it is not expected that
        ! the trap will be generated under normal circumstances.
        !
        ! The code assumes the following register arrangement on entry:
        !  %l0 = psr
        !  %l1 = PC
        !  %l2 = nPC
        !  %l3 = trap type, or trap service table index
        !
        .global default_trap_handler
        .type   default_trap_handler, #function

        .extern sparcSystemServiceEnableTraps

default_trap_handler:

        !
        ! Default action: Call the debugger.
        !

        !
        ! Since the debugger is called using a software trap, traps must be reenabled.
        or     %l0, SPARC_PSR_ET_MASK, %l0
        mov    %l0, %psr
        ! three delay cycles needed after writing on the PSR register
        nop
        nop
        nop

        !
        ! Invoke the software trap that is used by GDB/GRMON to indicate the
        ! presence of a breakpoint.
        ta      0x01

        !
        ! Return to the interrupted trap

        ! This universal handler may be used for both interrupting and precise traps.
        ! Interrupting traps must reexecute the instruction where the trap was invoked.
        ! All other trap types are assumed to be precise traps

        cmp     %l3, 0x11
        bl      return_from_a_precise_trap
        nop

        cmp     %l3, 0x1f
        bg      return_from_a_precise_trap
        nop

 return_from_an_interrupting_trap:

        !
        ! Reexecute the instruction where the trap was invoked
        jmp     %l1
        rett    %l2

 return_from_a_precise_trap:

        !
        ! Go back to the instruction located right after the instruction that trapped.
        jmp     %l2
        rett    %l2 + 0x04

