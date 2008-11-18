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
 * v0.1.0 20080713 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "TS_Cfg.h"	/* include configuration */
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
#define TS_OK						1
#define TS_FAILED					2
#define TS_USER					3

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
extern TS_ResultType TS_TestResults[(TS_TESTS_COUNT)/4];
extern TS_ChecksumType TS_Checksum;

/*==================[external functions declaration]=========================*/
/** \brief TS_RunTestSuite
 **
 ** This api runs the test suite
 **/
extern void TS_RunTestSuite(void);

extern TS_ResultType TS_GetTestResult(TS_TestIDType TestID);

extern void TS_PrintResult(unsigned int tc, unsigned char result);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_H_ */

