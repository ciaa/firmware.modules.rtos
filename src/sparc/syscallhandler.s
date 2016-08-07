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

/** \brief SPARC V8 System Calls trap handler.
 **
 ** \file sparc/syscallhandler.s
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

        !
        ! This SysCall handler serves a software interrupt that the system may use to ask
        ! a series of services, like enabling or disabling traps, rebooting the system, etc.
        !
        ! The user causes this interrupt using "ta SYSCALL_TRAP", and indicates which service
        ! is being asked for from the syscall by setting a service id number on the global
        ! register %g1.
        !
        ! Entry assumptions:
        !
        !  %g1 = syscall number (user provided)
        !  %l0 = psr
        !  %l1 = PC
        !  %l2 = nPC
        !  %l3 = trap type, or trap service table index
        !
        .global syscall_handler
        .type   syscall_handler, #function

syscall_chandler:

        !
        ! We have local registers %l4 to %l7 available for use.
        ! The trap window may be the inactive window, therefore we should
        ! not call any function that may perform a save/restore pair, nor use any of
        ! the output registers since they may be the input registers of a register
        ! window that is currently in use.

		!
		! Validate the service id number.
		subcc   %g1, 8, %g0
		bge     invalid_service_id

        !
        ! Calculated the index of the selector, based on the service id,
        ! adding a displacement of four bytes for each service id.
        sll     %g1, 2, %l4

        !
        ! Call the relevant service id handler
        sethi   %hi(assembler_case_selector), %l5
        add     %l4, %l5, %l5
        jmpl    [%lo(assembler_case_selector) + %l5], %g0
        nop

assembler_case_selector:
        ba,a     disable_traps                    ! SYSCALL ID 0x00 = Disable trap
        ba,a     mask_interrupts_service          ! SYSCALL ID 0x01 = Mask all asynchronous interrupts
        ba,a     unmask_interrupts_service        ! SYSCALL ID 0x02 = Unmask all asynchronous interrupts
        ba,a     invalid_service_id               ! SYSCALL ID 0x03 = Still undefined service id.
        ba,a     invalid_service_id               ! SYSCALL ID 0x04 = Still undefined service id.
        ba,a     invalid_service_id               ! SYSCALL ID 0x05 = Still undefined service id.
        ba,a     invalid_service_id               ! SYSCALL ID 0x06 = Still undefined service id.
        ba,a     invalid_service_id               ! SYSCALL ID 0x07 = Still undefined service id.

        ! **************************
        !
        ! "DISABLE TRAPS" SERVICE CODE
        !
disable_traps_service:

		!
		! Traps are already disabled by the time this code gets the chance
		! to be executed, because during trap entry the processor automtically sets
		! the ET bit in the PSR register to 0.
		!
		! In order to complete our action, we have to
		! return to the trap calling code without
		! reactivating the traps. That means that
		! we are not allowed to use RETT.
		!
		! Instead, we must exit the trap doing all of the
		! same actions that a RETT instruction would do,
		! except reactivating ET.
		!
		! According to the SPARC v8 Manual, the actions performed
		! by RETT are:
		! (1) adds 1 to the CWP (modulo NWINDOWS)
		! (2) Causes a delayed control transfer to the target address.
		! (3) Restores the S field of the PSR from the PS field.
		! (4) Sets the ET field of the PSR to 1.

        !
		! Do (3) Restores the S field of the PSR from the PS field.

		! Empty the S bit
		andn    %l0, SPARC_PSR_S_MASK, %l0

		! Check whether the previous value of the S bit was 0
		andcc   %l0, SPARC_PSR_PS_MASK, %g0
        bz      go_back_to_user_mode
        nop

        ! We came from supervisor mode code, so set the S bit on
        ! before going back
        or      %l0, SPARC_PSR_S_MASK, %l0

go_back_to_user_mode:

        mov     %l0, %psr

        ! We'll be releasing the trap window before going back, so
        ! we need to save the return address now. %g1 is the
        ! only global register available.
        mov     %l2, %g1

        !
        ! Do (1) adds 1 to the CWP (modulo NWINDOWS).
        ! Here we will lose sight of the local registers in the trap window.
        restore

        !
        ! Do (2) Causes a delayed control transfer to the target address.
        ! Go back to the trapping code without using RETT
        jmp     %g1
        nop


        ! **************************
        !
        ! "MASK INTERRUPTS" SERVICE CODE
        !
mask_interrupts_service:

        !
        ! Set the PIL field in the PSR register to 15
        or      %l0, SPARC_PSR_PIL_MASK, %l0
        mov     %l0, %psr
        ! three delay cycles are needed after modifying the PSR
        nop
        nop
        nop

        !
        ! processing done, proceed to the exit
        ja      exit_syscall
        nop


        ! **************************
        !
        ! "UNMASK INTERRUPTS" SERVICE CODE
        !
unmask_interrupts_service:

        !
        ! Set the PIL field in the PSR register to 0
        andn    %l0, SPARC_PSR_PIL_MASK, %l0
        mov     %l0, %psr
        ! three delay cycles are needed after modifying the PSR
        nop
        nop
        nop

        ! processing done, proceed to the exit
        ja      exit_syscall
        nop

        ! **************************
        !
        ! "REBOOT SYSTEM" SERVICE CODE
        !
unmask_interrupts_service:

        !
        ! According to the SPARC v8 Manual,
        ! a reset trap can be generated by causing
        ! a processor trap while traps are disabled.
        !
        ! When this code gets to be executed, the processor
        ! is running with the ET bit in the PSR set to 0,
        ! and therefore the following code should cause a
        ! reset trap.
        ta      0  ! the trap number called is irrelevant

        ! If everything worked as intended, the following code should
        ! not get the chance to be executed, but is kept for two reasons:
        !
        ! * One, for the sake of the simetry of the code. This is important for
        !   maintainability.
        ! * Two, defensive programming: reset trap generation when trapping with
        !   traps disabled is not actually REQUIRED by the SPARC v8 Architecture
        !   manual, but only suggested. Therefore some portability issues might
        !   arise with the previous code when used on processors other that LEON 3.
        !
        ! Execute a controlled exit from the trap back to the trapping code.
        ja      exit_syscall
        nop

        ! **************************
        !
        ! INVALID SERVICE ID SERVICE CODE
        !
invalid_service:

        !
        ! TODO What should be done about this case?
        !

        ! done
	    ja,a    exit_syscall

exit_syscall:

        !
        ! All done. Since we are going back from a precise trap, we don't want
        ! to re-execute the trapping instruction.
        jmp     %l2
        rett    %l2 + 0x4
