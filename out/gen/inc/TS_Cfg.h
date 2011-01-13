/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _TS_CFG_H_
#define _TS_CFG_H_
/** \brief Test Suite Configuration Header File
 **
 ** \file TS_Cfg.h
 **/

/** \addtogroup TestSuite
 ** @{ */
/** \addtogroup TestSuite_Global
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
 * 20080830 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
/** \brief TS_MEMMAP definition (DISABLE MemMap is not used, ENABLE MemMap is
 ** used) */
#define TS_MEMMAP DISABLE

#define TS_TESTS_COUNT 23

#define OS_0001 0

#define OS_0002 1

#define OS_0003 2

#define OS_0004 3

#define OS_0005 4

#define OS_0006 5

#define OS_0007 6

#define OS_0008 7

#define OS_0009 8

#define OS_0010 9

#define OS_0011 10

#define OS_0012 11

#define OS_0013 12

#define OS_0014 13

#define OS_0015 14

#define OS_0016 15

#define OS_0017 16

#define OS_0018 17

#define OS_0019 18

#define OS_0020 19

#define OS_0021 20

#define OS_0022 21

#define OS_0023 22


/*==================[typedef]================================================*/
/** \brief Type definition of TestResult */
typedef unsigned char TS_ResultType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#if (TS_MEMMAP == ENABLE)
#define TestSuite_START_SEC_CODE
#include "MemMap.h"
#endif

/** \brief Test OS_0001
 **
 ** Test description
 **/
TS_ResultType TEST_OS_0001(void)  ATTRIBUTES();

/** \brief Test OS_0002
 **
 ** Test ActivateTask interface
 **/
TS_ResultType TEST_OS_0002(void)  ATTRIBUTES();

/** \brief Test OS_0003
 **
 ** Test TerminateTask interface
 **/
TS_ResultType TEST_OS_0003(void)  ATTRIBUTES();

/** \brief Test OS_0004
 **
 ** Test ChainTask interface
 **/
TS_ResultType TEST_OS_0004(void)  ATTRIBUTES();

/** \brief Test OS_0005
 **
 ** Test Schedule interface
 **/
TS_ResultType TEST_OS_0005(void)  ATTRIBUTES();

/** \brief Test OS_0006
 **
 ** Test GetTaskID interface
 **/
TS_ResultType TEST_OS_0006(void)  ATTRIBUTES();

/** \brief Test OS_0007
 **
 ** Test GetTaskState interface
 **/
TS_ResultType TEST_OS_0007(void)  ATTRIBUTES();

/** \brief Test OS_0008
 **
 ** Test EnableAllInterrupts interface
 **/
TS_ResultType TEST_OS_0008(void)  ATTRIBUTES();

/** \brief Test OS_0009
 **
 ** Test DisableAllInterrupts interface
 **/
TS_ResultType TEST_OS_0009(void)  ATTRIBUTES();

/** \brief Test OS_0010
 **
 ** Test ResumeAllInterrupts interface
 **/
TS_ResultType TEST_OS_0010(void)  ATTRIBUTES();

/** \brief Test OS_0011
 **
 ** Test SuspendAllInterrupts interface
 **/
TS_ResultType TEST_OS_0011(void)  ATTRIBUTES();

/** \brief Test OS_0012
 **
 ** Test ResumeOSInterrupts interface
 **/
TS_ResultType TEST_OS_0012(void)  ATTRIBUTES();

/** \brief Test OS_0013
 **
 ** Test SuspendOSInterrupts interface
 **/
TS_ResultType TEST_OS_0013(void)  ATTRIBUTES();

/** \brief Test OS_0014
 **
 ** Test GetResource interface
 **/
TS_ResultType TEST_OS_0014(void)  ATTRIBUTES();

/** \brief Test OS_0015
 **
 ** Test ReleaseResource interface
 **/
TS_ResultType TEST_OS_0015(void)  ATTRIBUTES();

/** \brief Test OS_0016
 **
 ** Test SetEvent interface
 **/
TS_ResultType TEST_OS_0016(void)  ATTRIBUTES();

/** \brief Test OS_0017
 **
 ** Test ClearEvent interface
 **/
TS_ResultType TEST_OS_0017(void)  ATTRIBUTES();

/** \brief Test OS_0018
 **
 ** Test WaitEvent interface
 **/
TS_ResultType TEST_OS_0018(void)  ATTRIBUTES();

/** \brief Test OS_0019
 **
 ** Test GetAlarmBase interface
 **/
TS_ResultType TEST_OS_0019(void)  ATTRIBUTES();

/** \brief Test OS_0020
 **
 ** Test GetAlarm interface
 **/
TS_ResultType TEST_OS_0020(void)  ATTRIBUTES();

/** \brief Test OS_0021
 **
 ** Test SetRelAlarm interface
 **/
TS_ResultType TEST_OS_0021(void)  ATTRIBUTES();

/** \brief Test OS_0022
 **
 ** Test SetAbsAlarm interface
 **/
TS_ResultType TEST_OS_0022(void)  ATTRIBUTES();

/** \brief Test OS_0023
 **
 ** Test CancelAlarm interface
 **/
TS_ResultType TEST_OS_0023(void)  ATTRIBUTES();


#if (TS_MEMMAP == ENABLE)
#define TestSuite_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TS_CFG_H_ */

