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
   .global sparcWindowOverflowTrapHandler
   .type   sparcWindowOverflowTrapHandler, #function

   .extern detected_sparc_register_windows

sparcWindowOverflowTrapHandler:

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
   ! The CWP field is currently pointing at the only invalid window within the register windows set. Since
   ! we will change the validity status of this window in the near future, for the sake of clarity from now
   ! on we will call this window the "trap window", since all of its local registers are available for use by
   ! trap handler exclusively.
   !
   ! From now on we need to do two things:
   ! * Mark the trap window as valid (rewriting the WIM register). No additional work required
   !   here, since the trap window was previously marked as invalid and therefore nothing of any value is stored
   !   there.
   ! * Mark the window below the trap window as invalid (again, rewriting WIM does the trick). Since that window
   !   is currently in use, before invalidating it we must dump its contents to the stack.
   !

   ! Rotate the current WIM value one bit to the right (modulo the number of
   ! windows), in order to generate the updated WIM value (one that will both
   ! mark the trap window as VALID and the one below that as INVALID).

   ! Since we will be moving the CWP one window below the trap window before actually
   ! updating the WIM (for reasons that will be explained below) we will need to take
   ! the new WIM value with us using a global register.
   !
   ! Global registers might be in use by the code that was interrupted by the
   ! window overflow trap, so we must back up the contents of any global that is modified
   ! and restore its value before returning from the trap.

   !
   ! Back up the value of %g1 to %l6
   mov     %g1, %l6

   !
   ! Rotate the old value of WIM (in %lo) one bit to the right, sending the
   ! rightmost bit to the leftmost position...
   srl     %l0, 1, %l5
   sll     %l0, %l4, %l0
   or      %l0, %l5, %g1
   ! It is unnecessary to mask out any extra bits (those beyond the NWINDOWS'th bit) of %g1
   ! because the WIM register ignores any value written to a bit other than those of
   ! the implemented register windows.

   !
   ! Now the new WIM value is stored in %g1, but we can't update the WIM register yet. We
   ! still need to dump the contents of the recently invalidated window to the stack, and that
   ! will require us to execute a SAVE instruction. If we had updated the WIM register now,
   ! when the SAVE instruction was executed it would detect that after execution the CWP would
   ! point to an invalid window and therefore a new WINDOW_OVERFLOW trap would be generated, which is
   ! not only bogus but also dangerous: this code is executing with traps disabled so that any
   ! synchronous trap would throw the processor into error mode.
   !
   ! For similar reasons we need to update the WIM register BEFORE moving back to the trap window.

   ! Move one window below
   save

   ! Store in's and local's to the stack. For the sake of performance, we store registers two at
   ! a time using STD.
   std     %l0, [%sp]         ! %sp is double word aligned
   std     %l2, [%sp + 8]
   std     %l4, [%sp + 16]
   std     %l6, [%sp + 24]
   std     %i0, [%sp + 32]
   std     %i2, [%sp + 40]
   std     %i4, [%sp + 48]
   std     %i6, [%sp + 56]

   ! Update the WIM
   mov     %g1, %wim

   ! The behavior of instructions that read or write the WIM register during the
   ! first three cycles after a write operation has been performed on it is
   ! undefined (implementation dependent) so we play safe and burn those cycles away...
   nop
   nop
   nop

   ! Return to the trap window
   restore

   !
   ! Restore the value of the global register that we modified
   mov     %l6, %g1

   !
   ! All done.  Return from the trap, making sure that the instruction that caused the trap is
   ! executed again.
   jmp     %l1
   rett    %l2

