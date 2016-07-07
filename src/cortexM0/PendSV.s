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
   /* disable IRQs */
   cpsid f

   /* Restart terminating task stack. */
   mov r0,lr
   push {r0}
   bl CheckTerminatingTask_Arch
   pop {r0}
   mov lr,r0

   /* Use MSP to store context */
   mrs r0,msp

   /* Integer context saving, including lr */
   subs r0,4
   mov r1,lr
   str r1,[r0]

   subs r0,4
   str r4,[r0]
   subs r0,4
   str r5,[r0]
   subs r0,4
   str r6,[r0]
   subs r0,4
   str r7,[r0]

   mov r4,r8
   mov r5,r9
   mov r6,r10
   mov r7,r11

   subs r0,4
   str r4,[r0]
   subs r0,4
   str r5,[r0]
   subs r0,4
   str r6,[r0]
   subs r0,4
   str r7,[r0]

   /* Check if actual context need to be saved */
   ldr r1,=Osek_OldTaskPtr_Arch
   ldr r1,[r1]
   cmp r1,0
   beq no_guardo
   str r0,[r1]
no_guardo:

   /* Load new context SP */
   ldr r1,=Osek_NewTaskPtr_Arch
   ldr r1,[r1]
   ldr r0,[r1]

   /* Restore registers */
   ldr r7,[r0]
   adds r0,4
   ldr r6,[r0]
   adds r0,4
   ldr r5,[r0]
   adds r0,4
   ldr r4,[r0]
   adds r0,4

   mov r11,r7
   mov r10,r6
   mov r9,r5
   mov r8,r4

   ldr r7,[r0]
   adds r0,4
   ldr r6,[r0]
   adds r0,4
   ldr r5,[r0]
   adds r0,4
   ldr r4,[r0]
   adds r0,4

   ldr r1,[r0]
   mov lr,r1
   adds r0,4

   /* Restore MSP */
   msr msp,r0

   /* Enable IRQs */
   cpsie f

   /* IRQ end */
   bx lr

   .end
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
