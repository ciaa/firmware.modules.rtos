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

/** \brief FreeOSEK Os Conformance Test for the Task Managment, Test Sequence 1
 **
 ** \file FreeOSEK/Os/tst/ctest/src/ctest_tm_01.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_TM Task Management
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_TM_01 Test Sequence 1
 ** @{ */

/*==================[inclusions]=============================================*/
#include "os.h"            /* include os header file */
#include "ctest_tm_01.h"   /* include test header file */
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
   TaskStateType State;

   Sequence(0);
   /* enable interrupts ISR2 and ISR3 */
   /* nothing to do */

   Sequence(1);
   /* \treq TM_01 nmf B1B2E1E2 e Call ActivateTask() from a task level with
    * an invalid task ID (task doesn't exist)
    *
    * \result Service returns E_OS_ID
    */
   ret = ActivateTask(INVALID_TASK);
   ASSERT(TM_01, ret != E_OS_ID);

   Sequence(2);
   /* \treq TM_40 nmf B1B2E1E2 e Call GetTaskState() with an invalid task ID
    * (task doesn't exist)
    *
    * \result Service returns E_OS_ID
    */
   ret = GetTaskState(INVALID_TASK, &State);
   ASSERT(TM_40, ret != E_OS_ID);

   Sequence(3);
   /* \treq TM_24 nmf B1B2E1E2 e Call ChainTask() from task level. Task-ID is
    * invalid (does not exist).
    *
    * \result Service returns E_OS_ID
    */
   ret = ChainTask(INVALID_TASK);
   ASSERT(TM_24, ret != E_OS_ID);

   /* activate task 2 */
   Sequence(4);
   ret = ActivateTask(Task2);
   ASSERT(OTHER, ret != E_OK);

#if (CT_SCHEDULING_Task1 == CT_NON_PREEMPTIVE)
   /* force scheduling */
   Schedule();
#endif /* #if (CT_SCHEDULING_TASK1 == CT_NON_PREEMPTIVE) */

   Sequence(9);
   /* get scheduler resource */
   ret = GetResource(RES_SCHEDULER);
   ASSERT(OTHER, ret != E_OK);

   Sequence(10);
   /* \treq TM_22 nmf B1B2E1E2 e Call TerminateTask() while still occuping a
    * resource
    *
    * \result Running task is not terminated. Service returns E_OS_RESOURCE
    */
   ret = TerminateTask();
   ASSERT(TM_22, ret != E_OS_RESOURCE);

   Sequence(11);
   /* \treq TM_27 nmf B1B2E1E2 e Call ChainTask() while still occuping a
    * resource
    *
    * \result Running task is not terminated. Service returns E_OS_RESOURCE
    */
   ret = ChainTask(Task2);
   ASSERT(TM_27, ret != E_OS_RESOURCE);

   Sequence(12);
   ret = ReleaseResource(RES_SCHEDULER);
   ASSERT(OTHER, ret != E_OK);

   Sequence(13);
   /*  trigger ISR 2 */
   TriggerISR2();

#if ( ISR_CATEGORY_3 == OSEK_ENABLE )
   /* trigger ISR 3 */
   TriggerISR3();
#endif /* #if ( ISR_CATEGORY_3 == OSEK_ENABLE ) */

   Sequence(18);
   /* evaluate conformance tests */
   ConfTestEvaluation();

   /* finish the conformance test */
   ConfTestFinish();
}

TASK(Task2)
{
   StatusType ret;

   Sequence(5);
   /* \treq TM_10 nmf B1B2E1E2 e Call ActivateTask() on ready basic task which
    * has reached max. number of activations.
    *
    * \result Service returns E_OS_LIMIT
    */
   ret = ActivateTask(Task1);
   ASSERT(TM_10, ret != E_OS_LIMIT);

   Sequence(6);
   /* \treq TM_15 nmf B1B2E1E2 e Call ActivateTask() on running basic task
    * which has reached max. number of activations
    *
    * \result Service returns E_OS_LIMIT
    */
   ret = ActivateTask(Task2);
   ASSERT(TM_15, ret != E_OS_LIMIT);

   Sequence(7);
   /* \treq TM_30 nmf B1B2E1E2 e Call ChainTask() on ready basic task which has
    * reached max. number of activations
    *
    * \result Running task is not terminated. Service returns E_OS_LIMIT
    */
   ret = ChainTask(Task1);
   ASSERT(TM_30, ret != E_OS_LIMIT);

   Sequence(8);
   TerminateTask();
}

ISR(VN_ISR2)
{
   StatusType ret;
   TaskType TaskID;

   Sequence(14);
   /* \treq TM_20 nmf B1B2E1E2 e Call TerminateTask() from ISR category 2
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = TerminateTask();
   ASSERT(TM_20, ret != E_OS_CALLEVEL);

   Sequence(15);
   /* \treq TM_25 nmf B1B2E1E2 e Call ChainTask() from ISR category 2
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = ChainTask(Task2);
   ASSERT(TM_25, ret != E_OS_CALLEVEL);

   Sequence(16);
   /* \treq TM_35 nmf B1B2E1E2 e Call Schedule() from ISR category 2
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = Schedule();
   ASSERT(TM_35, ret != E_OS_CALLEVEL);

   Sequence(17);
   /* \treq TM_37 nmf B1B2E1E2 e Call GetTaskID() from ISR category 2
    *
    * \result Service returns E_OS_CALLEVEL
    */
    /* This test case has been adpated, is an error in OSEK Testplan
     * see #38 Issue in TestPlan TM_37 Call GetTaskID() from ISR category 2 */
   ret = GetTaskID(&TaskID);
   ASSERT(TM_37, (ret != E_OK) || (TaskID != Task1) );
}

#if ( ISR_CATEGORY_3 == OSEK_ENABLE )
ISR(VN_ISR3)
{
   StatusType ret;

   EnterISR();

   /* \treq TM_21 nmf B1B2E1E2 e Call TerminateTask() from ISR category 3
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = TerminateTask();
   ASSERT(TM_21, ret != E_OS_CALLEVEL);

   /* \treq TM_26 nmf B1B2E1E2 e Call ChainTask() from ISR category 3
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = ChainTask(Task2);
   ASSERT(TM_26, ret != E_OS_CALLEVEL);

   /* \treq TM_36 nmf B1B2E1E2 e Call Schedule() from ISR category 3
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = Schedule();
   ASSERT(TM_36, ret != E_OS_CALLEVEL);

   /* \treq TM_38 nmf B1B2E1E2 e Call GetTaskID() from ISR category 3
    *
    * \result Service returns E_OS_CALLEVEL
    */
   ret = GetTaskID();
   ASSERT(TM_38, ret != E_OS_CALLEVEL);

   LeaveISR();

}
#endif /* #if ( ISR_CATEGORY_3 == OSEK_ENABLE ) */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
