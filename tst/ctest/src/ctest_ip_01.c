/* Copyright 2008, 2009, 2014 Mariano Cerdeiro
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 * Copyright 2016, Franco Bucafusco
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

/** \brief FreeOSEK Os Conformance Test for the Interrupt processing, Test Sequence 1
 **
 ** \file FreeOSEK/Os/tst/ctest/src/ctest_ip_01.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_IP  Interrupt processing
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_IP_01 Test Sequence 1
 ** @{ */

/*==================[inclusions]=============================================*/
#include "os.h"            /* include os header file */
#include "ctest_ip_01.h"   /* include test header file */
#include "ctest.h"         /* include ctest header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
const uint32f SequenceCounterOk = MAX_SEQUENCE;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main
(
   void
)
{
   EnableISR1();
   EnableISR2();

   /* start OS in AppMode 1 */
   StartOS(AppMode1);

   /* shall never return */
   while(1);

   return 0;
}

TASK(Task1)
{
   Sequence(0);
   /* enable interrupts ISR1 */
   ResumeAllInterrupts();

   Sequence(1);
   /* disable interrupts ISR1 */
   SuspendAllInterrupts();
   ASSERT(IP_03, 0);

   Sequence(2);
   /* trigger ISR 1...pending IRQ */
   TriggerISR1();

   Sequence(3);
   /* enable interrupts ISR1 */
   ResumeAllInterrupts();
   ASSERT(IP_01, 0);
   /*
      This is a deviation from standard, when Resume the interrupts
      there is a pending IRQ which will trigger the ISR
   */

   Sequence(5);
   /* trigger ISR 1 */
   TriggerISR1();
   ASSERT(IP_06, 0);

   Sequence(7);
   /* enable interrupts ISR2 */
   ResumeOSInterrupts();

   Sequence(8);
   /* disable interrupts ISR2 */
   SuspendOSInterrupts();
   ASSERT(IP_03, 0);

   Sequence(9);
   /* trigger ISR 2...pending IRQ */
   TriggerISR2();

   Sequence(10);
   /* enable interrupts ISR2 */
   ResumeOSInterrupts();
   ASSERT(IP_01, 0);
   /*
      This is a deviation from standard, when Resume the interrupts
      there is a pending IRQ which will trigger the ISR
   */

   Sequence(12);
   /* trigger ISR 2 */
   TriggerISR2();
   ASSERT(IP_06, 0);

   Sequence(14);
   /* evaluate conformance tests */
   ConfTestEvaluation();

   /* finish the conformance test */
   ConfTestFinish();
}

ISR(VN_ISR1)
{
   static uint8 ISR1_Trigger_Number = 0;

   switch(ISR1_Trigger_Number)
   {
      case 0:
         Sequence(4);
         ISR1_Trigger_Number++;
         ASSERT(OTHER, 0);
         break;
      case 1:
         Sequence(6);
         ISR1_Trigger_Number++;
         ASSERT(OTHER, 0);
         break;
      default:
         /* throw an ASSERT */
         ASSERT(OTHER, 1);
         break;
   }
}

ISR(VN_ISR2)
{
   static uint8 ISR2_Trigger_Number = 0;

   switch(ISR2_Trigger_Number)
   {
      case 0:
         Sequence(11);
         ISR2_Trigger_Number++;
         ASSERT(OTHER, 0);
         break;
      case 1:
         Sequence(13);
         ISR2_Trigger_Number++;
         ASSERT(OTHER, 0);
         break;
      default:
         /* throw an ASSERT */
         ASSERT(OTHER, 1);
         break;
   }
}

/* This task is not used, only to change the scheduling police */
TASK(Task2)
{
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
