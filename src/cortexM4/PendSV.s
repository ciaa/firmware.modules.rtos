/* Copyright 2014, Pablo Ridolfi (UTN-FRBA)
 * Copyright 2017, Gerardo Puga (UNLP)
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
 ** \file cortexM4/PendSV.s
 ** \arch cortexM4
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

   .thumb_func
   .syntax unified

    /* .section .after_vectors */

   .global PendSV_Handler
   .extern cortexM4ActiveContextPtr,cortexM4UpdateActiveTaskContextPtr

   /*
    * Pendable Service Call, used for context-switching in all Cortex-M processors
    */
PendSV_Handler:

   /*
    * Read the comments in cortexM4ResetTaskContext() to better understand the
    * structure of the context data stored on the stack.
    *
    * At the start of the execution of this handler part of the calling
    * task's CPU context has already been stored on the task's stack
    * by the exception entry sequence.
    *
    * This includes, in stacking order, BLOCK 1 and BLOCK 2. as
    * described in cortexM4ResetTaskContext().
    *
    * The CPU will have only stored the registers of BLOCK 1
    * if the interrupted task has been using the FPU. BLOCK 2
    * Is always saved during the exception entry sequence.
    *
    * Notice that by default the CortexM architecture uses a
    * lazy strategy for saving the FP registers in BLOCK 1. In
    * practice this mean that the processor allocates space on the
    * stack for the registers, but does not store their values
    * there. Only if the exception handler contains a FP
    * instruction does the CPU actually store the
    * values of the registers in BLOCK 1 (S0 to S15, and FPSCR)
    * to the previously allocated stack space. See "Cortex-M4(F)
    * Lazy Stacking and Context Switching", Application Note 298.
    *
    * */

   /*
    * Disable interrupts to handle context data atomically.
    * */

   cpsid f

   /*
    * Determine which stack is in use in the calling context: MSP o PSP.
    *
    * System code, and initialization code (first call to schedule())
    * use the master stack (MSP), while tasks use the alternative
    * stack (PSP).
    *
    * Determining the active stack is done by checking the fourth bit
    * of the return value of the exception, which can be found on the
    * LR register.
    *
    * Since the PendSV exception is the lowest level interrupt that
    * can be invoked, the MSR stack is only used when it is invoked
    * from the context of the first Schedule() function call, in
    * StartOS().
    * */

   tst   lr,0x04
   ite   eq
   mrseq r0,msp
   mrsne r0,psp

   /*
    * Determine whether we need to store the floating point
    * context registers of BLOCK 3.
    *
    * This is indicated in LR[4], which indicates whether
    * the stack frame created during the exception entry
    * sequence includes FP info or not.
    *
    * When using the FP lazy stacking strategy, the vstmdb
    * instruction below forces the processor the dump the register
    * in BLOCK 1 to be written to the stack before continuing.
    * */

   tst   lr,0x10
   it    eq
   vstmdbeq r0!,{s16-s31}

   /*
    * Save the integer registers in BLOCK 4: R4-R11, and the exception
    * return value currently stored in LR.
    * */

   stmdb r0!,{r4-r11,lr}

   /*
    * If the MSP stack is in use, update the MSP register value.
    *
    * FIXME I suspect this is not needed, since all of the possible
    * use cases for this are probably safe anyway without performing
    * this update.
    */

   tst   lr,0x04
   it    eq
   msreq msp,r0

   /*
    * Update the pointer to the top of the stack in the
    * task context block.
    *
    */

   ldr   r1,=cortexM4ActiveContextPtr
   ldr   r2,[r1]           /* Load the address of the stack pointer.    */
   str   r0,[r2]           /* Store the updated value of the stack ptr. */


   /* ************************************* */
   /* ************************************* */
   /* ************************************* */


   /*
    * Update the pointer to the context data of the
    * currently active task.
    *
    * This is done in an external C routine.
    * */

   push {lr}

   bl cortexM4UpdateActiveTaskContextPtr

   pop {lr}

   /* ************************************* */
   /* ************************************* */
   /* ************************************* */

   /*
    * Load the stack pointer of the task being activated from its
    * task context block.
    * */

   ldr   r1,=cortexM4ActiveContextPtr
   ldr   r1,[r1]
   ldr   r0,[r1]

   /*
    * Recover the values of the registers in BLOCK 4.
    */

   ldmia r0!,{r4-r11,lr}

   /*
    * Recover the values of the floating point registers
    * in BLOCK 3, but only if the task being recovered has
    * floating point context data (extended exception stack
    * frame).
    * */

   tst   lr,0x10
   it    eq
   vldmiaeq r0!,{s16-s31}

   /*
    * The values of the registers on BLOCK 2 (integer) and
    * BLOCK 1 (floating point) are left on the stack, and
    * will be recovered by the CPU during the exception
    * exit sequence.
    */

   /*
    * Determine the execution mode and operational stack of the
    * activated task, and update the CONTROL register accordingly.
    */

   mrs   r1,control

  /*
   * FIXME the following code assumes that bit 1 of the control register can be modified,
   * but handler code is ignored when writing to that bit; only supervisor thread code
   * can modify that bit.
   */

   tst   lr,0x04
   ittee eq
   biceq r1,0x03  /* Task uses MSP - CONTROL = thread mode uses MSP and is privileged. */
   msreq msp,r0   /* Task uses MSP - Update MSP with task stack pointer. */
   orrne r1,0x02  /* Task uses PSP - CONTROL =  thread mode uses PSP. Privilege mode stays the same. */
   msrne psp,r0   /* Task uses PSP - Update PSP with task stack pointer. */

   msr   control,r1

   /*
    * The Architecture Reference Manual of the CortexM4 recommends to use this
    * synchronization instruction aftet writing a new value to the CONTROL
    * register.
    */
   isb

   /*
    * End of the critical section.
    */

   cpsie f

   /*
    * Return from the PensSV exception handler.
    */

   bx lr
