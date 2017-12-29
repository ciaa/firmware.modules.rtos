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
   .extern Osek_OldTaskPtr_Arch,Osek_NewTaskPtr_Arch,CheckTerminatingTask_Arch

   /*
    * Pendable Service Call, used for context-switching in all Cortex-M processors
    */

PendSV_Handler:

   /*
    * Read the comments in InitStack_Arch() to better understand the
    * structure of the context data stored on the stack.
    *
    * At the start of the execution of this handler part of the calling
    * task's CPU context has already been stored on the task's stack
    * by the exception entry sequence.
    *
    * This includes, in stacking order, BLOCK 1 and BLOCK 2. as
    * described in InitStack_Arch().
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
    * Check if the currently active task is being removed. If it is,
    * reset the task's context data block.
    *
    * This is done in an external C routine.
    *
    * */

   push {lr}
   bl CheckTerminatingTask_Arch
   pop {lr}

   /*
    * Determine which stack is in use in the calling context: MSP o PSP.
    *
    * System code, and initialization code (first call to schedule())
    * use the master stack (MSP), while tasks use the alternative
    * stack (PSP).
    *
    * The information about the stack in use in the calling context
    * is stored in the exception return value that is stored by
    * the CPU on the LR registers during the exception entry sequence.
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
    * Save the integer registers in BLOCK 4: R5-R11, and the exception
    * return value currently stored in LR.
    * */

   stmdb r0!,{r4-r11,lr}

   /*
    * Restituyo MSP, por si existen irqs anidadas
    *
    * TODO Find out under which scenario this is needed.
    */

   tst   lr,0x04
   it    eq
   msreq msp,r0

   /*
    * Store the task stack pointer on the task context block.
    *
    * If there there was no currently active task, the exiting
    * task context block pointer may be null. In that case do nothing.
    *
    * FIXME In this case we shouldn't even have written the state of the register set on the
    * stack, because we may be overwriting the initial task state that was built by
    * CheckTerminatingTask_Arch at the start of the handler. */

   ldr   r1,=Osek_OldTaskPtr_Arch
   ldr   r1,[r1]
   cmp   r1,0
   it    ne
   strne r0,[r1]

   /*
    * Load the stack pointer of the task being activated from that task's
    * task context block.
    *
    * This pointer is never null, since this handler is never invoked unless
    * some task needs to be activated.
    * */

   ldr   r1,=Osek_NewTaskPtr_Arch
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

   /* FIXME and ISB instruction is needed here to ensure the full effect of the
    * modification on the register upon then next few instructions.
    */

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
