/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _MAIN_H_
#define _MAIN_H_
/** \brief Module Test Header File
 **
 ** \file moduletest01/inc/main.h
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Moduletests OpenSEK Module Tests
 ** @{ */
/** \addtogroup OpenSEK_Moduletests_ModuleTest1 OpenSEK Module Test 1
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081205 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#define INVALID_TASK 0xFF

#define INVALID_RESOURCE 0xFF

#define INVALID_ALARM 0xFF

#define mt_GetMark() (mt_StateCounter)

#define mt_SetMark(mark)                                                   \
   {                                                                       \
      if ( (mark) == 0 )                                                   \
      {                                                                    \
         mt_StateCounter = 0;                                              \
      }                                                                    \
      else if ( (mt_StateCounter+1) == (mark) )                            \
      {                                                                    \
         mt_StateCounter++;                                                \
      }                                                                    \
      else                                                                 \
      {                                                                    \
      }                                                                    \
   }

#define mt_SetTaskAssert(state) (mt_TaskAssert = (state) )

#define mt_GetTaskAssert() (mt_TaskAssert)

#define TASKASSERT(cond)                                                                              \
   {                                                                                                  \
      if (cond)                                                                                       \
      {                                                                                               \
         ASSERT_ARCH();                                                                               \
         mt_TaskAssert = TS_FAILED;                                                                   \
      }                                                                                               \
   }

#define mt_SetTestCase(testcase) (mt_TestCase = (testcase))

#define mt_GetTestCase() (mt_TestCase)

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#define TestSuite_START_SEC_CODE
#include "MemMap.h"

/** \brief main function
 **
 ** Project main function. This function is called after the c conformance
 ** initialisation. This function shall call the StartOs in the right
 ** Application Mode. The StartOs API shall never return.
 **
 **/
int main
(
   void
) ATTRIBUTES();

#define TestSuite_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */

