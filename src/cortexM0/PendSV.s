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

/** \brief Cortex-M PendSV Interrupt Handler, used for context switch.
 **
 ** \file cortexM0/PendSV.s
 ** \arch cortexM0
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

   .thumb_func
   .syntax unified

   .global PendSV_Handler
   .extern Osek_OldTaskPtr_Arch,Osek_NewTaskPtr_Arch,CheckTerminatingTask_Arch

/* Pendable Service Call, used for context-switching in all Cortex-M processors */
PendSV_Handler:

   /*
    * Read the comments in InitStack_Arch() to better understand the
    * structure of the context data stored on the stack.
    *
    * At the start of the execution of this handler the registers
    * in BLOCK 1 have already been stored on the stack by the CPU
    * by the exception entry sequence.
    *
    * */

   /*
    * Disable interrupts to handle context data atomically.
    * */

   cpsid f

   /*
    * Check if the currently active task is being removed. If it is,
    * reset the task's context data block.
    *
    * This is done in an external C routine.
    *
    * */

   mov r0,lr
   push {r0}
   bl CheckTerminatingTask_Arch
   pop {r0}
   mov lr,r0

   /*
    * Use MSP to store context.
    * */

   mrs r0,msp

   /*
    * Save the integer registers in BLOCK 2: R4-R11, and the exception
    * return value currently stored in LR.
    * */

   /* Store LR in the stack */
   subs r0,4
   mov r1,lr
   str r1,[r0]

   /* Store R4 in the stack */
   subs r0,4
   str r4,[r0]

   /* Store R5 in the stack */
   subs r0,4
   str r5,[r0]

   /* Store R6 in the stack */
   subs r0,4
   str r6,[r0]

   /* Store R7 in the stack */
   subs r0,4
   str r7,[r0]

   /* Move the registers in R8-R11 to R4-R7.
    * This is because not all thumb instructions
    * can access the registers R8-R15. */
   mov r4,r8
   mov r5,r9
   mov r6,r10
   mov r7,r11

   /* Store R8 in the stack */
   subs r0,4
   str r4,[r0]

   /* Store R9 in the stack */
   subs r0,4
   str r5,[r0]

   /* Store R10 in the stack */
   subs r0,4
   str r6,[r0]

   /* Store R11 in the stack */
   subs r0,4
   str r7,[r0]

   /*
    * Store the task stack pointer on the task context block.
    *
    * If there was no currently active task, the exiting
    * task context block pointer may be null. In that case
    * do nothing.
    *
    * FIXME In this case we shouldn't even have written the state
    * of the register set on the stack, because we may be
    * overwriting the initial task state that was built by
    * CheckTerminatingTask_Arch at the start of the handler.
    */

   ldr r1,=Osek_OldTaskPtr_Arch
   ldr r1,[r1]
   cmp r1,0
   beq dont_save_current_context
   str r0,[r1]
dont_save_current_context:

   /*
    * Load the stack pointer of the task being activated from that task's
    * task context block.
    *
    * This pointer is never null, since this handler is never invoked unless
    * some task needs to be activated.
    * */

   ldr r1,=Osek_NewTaskPtr_Arch
   ldr r1,[r1]
   ldr r0,[r1]

   /* Restore the value of R11 to an auxiliary register. */
   ldr r7,[r0]
   adds r0,4

   /* Restore the value of R10 to an auxiliary register. */
   ldr r6,[r0]
   adds r0,4

   /* Restore the value of R9 to an auxiliary register. */
   ldr r5,[r0]
   adds r0,4

   /* Restore the value of R8 to an auxiliary register. */
   ldr r4,[r0]
   adds r0,4

   /* Move the values in R4-R7 to R8-R11. */
   mov r11,r7
   mov r10,r6
   mov r9,r5
   mov r8,r4

   /* Restore the value of R7. */
   ldr r7,[r0]
   adds r0,4

   /* Restore the value of R6. */
   ldr r6,[r0]
   adds r0,4

   /* Restore the value of R5. */
   ldr r5,[r0]
   adds r0,4

   /* Restore the value of R4. */
   ldr r4,[r0]
   adds r0,4

   /* Restore the return value of the exception. */
   ldr r1,[r0]
   mov lr,r1
   adds r0,4

   /* Update the value of the stack pointer, MSP. */
   msr msp,r0

   /*
    * End of the critical section.
    *
    * From here on the code interuptible again, even before going back to the task, and those
    * interrupts might activate this handler again.
    *
    * TODO Check if this can result on some unexpected execution path or task context data
    * corruption.
    */

   cpsie f

   /*
    * Return from the PensSV exception handler.
    */
   bx lr

   .end
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
