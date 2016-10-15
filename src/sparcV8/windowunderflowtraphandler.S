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

/** \brief SPARC V8 Window overflow trap handler.
 **
 ** \file sparc/trapwindowoveflowhandler.s
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
   ! ***
   !
   ! This routine is based on the SPARC window management examples that can be found on the text
   ! "SPARC traps under SunOS" by Jim Moore (SunSoft, Sun Microsystems Inc.), with minor code
   ! modifications and heavily commented for the sake of clarity.
   !
   ! ***
   !

   !
   ! The code assumes the following register arrangement on entry:
   !  %l1 = PC
   !  %l2 = nPC
   !
   .global sparcWindowUnderflowTrapHandler
   .type   sparcWindowUnderflowTrapHandler, #function

   .extern detected_sparc_register_windows

sparcWindowUnderflowTrapHandler:

   !
   ! Read the current WIM value and store it locally
   mov     %wim, %l0

   !
   ! Keep the number of windows minus one in a register, it will be useful later
   ! when updating the Window Invalid Mask.
   sethi   %hi(detected_sparc_register_windows), %l4
   ld      [%lo(detected_sparc_register_windows) + %l4], %l4
   sub     %l4, 1, %l4

   !
   ! The window underflow trap is caused by a RESTORE or RETT instruction when the WIM register bit asociated
   ! with the UPDATED (incremented) CWP value is marked as invalid. When this happens the CWP is NOT updated
   ! and a window underflow trap is generated.
   !
   ! Since as part of the trap entry sequence the processor will automatically DECREMENT the CWP in order to
   ! give the trap routine a fresh set of registers to work with, by the time we enter the window underflow
   ! trap handler the CWP is pointing two register windows BELOW the one marked as invalid. This is ok, since
   ! this window is valid but currently unused.
   !
   ! From now on we will call this register window the "trap window".
   !
   ! In the rest of the trap handler we need to perform the following operations:
   !
   ! * Mark the invalid window as valid (rewriting the WIM register), and read its contents back from the stack.
   ! * Mark the window above the invalid window as invalid. Since that window is currently unused no further
   !   work is required here.
   !

   ! Rotate the old value of WIM (in %lo) one bit to the left, sending the
   ! rightmost bit to the leftmost position...
   sll     %l0, 1, %l5
   srl     %l0, %l4, %l0   ! Notice here that the mask stored in %l4 is also NWINDOWS-1... beautiful.
   or      %l0, %l5, %l5
   ! It is unnecessary to mask out any extra bits (those beyond the NWINDOWS'th bit) of %l5
   ! because the WIM register ignores any value written to a bit other than those of
   ! the implemented register windows.

   ! Update the WIM. This step needs to be performed before entering the invalid window (see below)
   ! so that the RESTORE instruction does not throw the processor into error mode for having caused a
   ! synchronous trap (a nested undeflow trap) while the ET (enable traps) bit is disabled.
   mov     %l5, %wim
   ! The behavior of instructions that read or write the WIM register during the
   ! first three cycles after a write operation has been performed on it is
   ! undefined (implementation dependent) so we play safe and burn those cycles away...
   nop
   nop
   nop

   !
   ! Restore twice to get into the window that was previously marked as INVALID, so
   ! that we can restore the register values from the stack.
   restore
   restore

   ! Read the register values from the stack
   ldd     [%sp], %l0
   ldd     [%sp + 8], %l2
   ldd     [%sp + 16], %l4
   ldd     [%sp + 24], %l6
   ldd     [%sp + 32], %i0
   ldd     [%sp + 40], %i2
   ldd     [%sp + 48], %i4
   ldd     [%sp + 56], %i6

   ! Go back to the trap window before exiting the trap
   save
   save

   !
   ! All done.  Return from the trap, making sure that the instruction that caused the trap is
   ! executed again.
   jmp     %l1
   rett    %l2

