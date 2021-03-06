/* Copyright 2008, 2009 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
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

/** \brief FreeOSEK Os Conformance Test for the Alarms, Test Sequence 6
 **
 ** \file FreeOSEK/Os/tst/ctest/src/ctest_al_06.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_AL Alarms
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_AL_06 Test Sequence 6
 ** @{ */


/*==================[inclusions]=============================================*/
#include "os.h"            /* include os header file */
#include "ctest_al_06.h"   /* include test header file */
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
   /* start OS in AppMode 1 */
   StartOS(AppMode1);

   /* shall never return */
   while(1);

   return 0;
}

TASK(Task1)
{
   StatusType ret;
   EventMaskType EventMask;
   TaskStateType TaskState;

   Sequence(0);
   ret = ActivateTask(Task2);
   ASSERT(OTHER, ret != E_OK);

   Sequence(1);
   ret = SetRelAlarm(Alarm1, 1, 0);
   ASSERT(OTHER, ret != E_OK);

   Sequence(2);
   /* \treq AL_33 nm B1B2E1E2 se Expiration of alarm wich sets an event
    * while running task is non-preemptive. Task which owns the event is not
    * waiting for this event and not suspended
    *
    * \result Event is set
    */
   IncAlarmCounter();
   ASSERT(AL_33, 0);

   Sequence(3);
   ret = GetEvent(Task2, &EventMask);
   ASSERT(OTHER, ret != E_OK);
   ASSERT(OTHER, EventMask != Event1);

   Sequence(4);
   ret = Schedule();
   ASSERT(OTHER, ret != E_OK);

   Sequence(7);
   ret = SetRelAlarm(Alarm1, 1, 0);
   ASSERT(OTHER, ret != E_OK);

   Sequence(8);
   /* \treq AL_34 nm B1B2E1E2 se Expiration of alarm wich sets an event
    * while running task is non-preemptive. Task which owns the event is
    * waiting for this event
    *
    * \result Event is set. Task which is owner of the event becomes ready.
    * No preemption of running task
    */
   IncAlarmCounter();
   ASSERT(AL_34, 0);

   Sequence(9);
   ret = GetTaskState(Task2, &TaskState);
   ASSERT(OTHER, ret != E_OK);
   ASSERT(OTHER, TaskState != READY);

   Sequence(10);
   TerminateTask();
}

TASK(Task2)
{
   StatusType ret;

   Sequence(5);
   ret = ClearEvent(Event1);
   ASSERT(OTHER, ret != E_OK);

   Sequence(6);
   ret = WaitEvent(Event1);
   ASSERT(OTHER, ret != E_OK);

   Sequence(11);

   /* evaluate conformance tests */
   ConfTestEvaluation();

   /* finish the conformance test */
   ConfTestFinish();
}

/* This task is not used, only to change the scheduling police */
TASK(Task3)
{
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

