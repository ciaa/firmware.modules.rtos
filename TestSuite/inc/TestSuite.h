/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking OpenSEK statically or dynamically with other modules is making a
 * combined work based on OpenSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of OpenSEK give
 * you permission to combine OpenSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with OpenSEK solely through the OpenSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for OpenSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of OpenSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
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

#ifndef _TESTSUITE_H_
#define _TESTSUITE_H_
/** \brief TestSuite Header File
 **
 ** \file TestSuite.h
 **/

/** \addtogroup TestSuite
 ** @{ */
/** \addtogroup TestSuite_Global TestSuite Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090129 v0.1.1 MaCe add TS_MEMMAP check
 * 20080713 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "Types.h"		/* include types */
#include "TS_Cfg.h"		/* include configuration */
#include "TS_Arch.h"

/*==================[macros]=================================================*/
/** \brief TEST macro definition
 **
 ** This macro shall be used to define all tests cases.
 **
 ** \param[in] name name of the test.
 **/
#define TEST(name)	TS_ResultType TEST_ ## name(void)

#define TS_NOTRUN					0
#define TS_FAILED					1
#define TS_USER					2
#define TS_OK						3

#define RunTest(name)		TS_RunTest( TS_TEST_## name, TS_TESTID_ ## name)

#define ASSERT(cond)																												\
	{																																	\
		if (cond)																													\
		{																																\
			ASSERT_ARCH(cond);																									\
			return TS_FAILED;																										\
		}																																\
	}

/*==================[typedef]================================================*/
typedef int TS_ConditionType;

typedef unsigned int TS_TestIDType;

typedef unsigned int TS_ChecksumType;

/*==================[external data declaration]==============================*/
extern TS_ResultType TS_TestResults[(TS_TESTS_COUNT+(sizeof(TS_ResultType)*4)-1)/((sizeof(TS_ResultType)*4))];
extern TS_ChecksumType TS_Checksum;

/*==================[external functions declaration]=========================*/
#if (TS_MEMMAP == ENABLE)
#define TestSuite_START_SEC_CODE
#include "MemMap.h"
#endif

/** \brief TS_RunTestSuite
 **
 ** This api runs the test suite
 **/
extern void TS_RunTestSuite(void) ATTRIBUTES();

extern TS_ResultType TS_GetTestResult(TS_TestIDType TestID) ATTRIBUTES();

extern void TS_PrintResult(unsigned int tc, unsigned char result) ATTRIBUTES();

#if (TS_MEMMAP == ENABLE)
#define TestSuite_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_H_ */

