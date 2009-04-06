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

/** \brief Free OSEK Conformance Test Result
 **
 ** \file FreeOSEK/tst/ctest/src/ctest_rst_tm_01.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_CT_TM Task Management
 ** @{ */
/** \addtogroup FreeOSEK_CT_TM_01 Test Sequence 1
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090406 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "ctest.h"		/* include ctest header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8 TestResults[35];


const uint8 TestResultsOk[35] =
	{
#if (defined CT_TM_01)
	  ( OK << 0 )			/* CT_TM_01 */
#else
	  ( INIT << 0 )		/* CT_TM_01 */
#endif
	| ( INIT << 2 )		/* CT_TM_02 */
	| ( INIT << 4 )		/* CT_TM_03 */
	| ( INIT << 6 ),		/* CT_TM_04 */
	  ( INIT << 0 )		/* CT_TM_05 */
	| ( INIT << 2 )		/* CT_TM_06 */
	| ( INIT << 4 )		/* CT_TM_07 */
	| ( INIT << 6 ),		/* CT_TM_08 */
	  ( INIT << 0 )		/* CT_TM_09 */
#if (defined CT_TM_01)
	| ( OK << 2 )			/* CT_TM_10 */
#else
	| ( INIT << 2 )		/* CT_TM_10 */
#endif
	| ( INIT << 4 )		/* CT_TM_11 */
	| ( INIT << 6 ),		/* CT_TM_12 */
	  ( INIT << 0 )		/* CT_TM_13 */
	| ( INIT << 2 )		/* CT_TM_14 */
#if (defined CT_TM_01)
	| ( OK << 4 )			/* CT_TM_15 */
#else
	| ( INIT << 4 )		/* CT_TM_15 */
#endif
	| ( INIT << 6 ),		/* CT_TM_16 */
	  ( INIT << 0 )		/* CT_TM_17 */
	| ( INIT << 2 )		/* CT_TM_18 */
	| ( INIT << 4 )		/* CT_TM_19 */
	| ( INIT << 6 ),		/* CT_TM_20 */
#if ( (defined CT_TM_01) && (ISR_CATEGORY_3 == ENABLE) )
	  ( OK << 0 )			/* CT_TM_21 */
#else
	  ( INIT << 0 )		/* CT_TM_21 */
#endif
#if (defined CT_TM_01)
	| ( OK << 2 )			/* CT_TM_22 */
#else
	| ( INIT << 2 )		/* CT_TM_22 */
#endif
	| ( INIT << 4 )		/* CT_TM_23 */
#if (defined CT_TM_01)
	| ( OK << 6 ),			/* CT_TM_24 */
#else
	| ( INIT << 6 ),		/* CT_TM_24 */
#endif
	  ( INIT << 0 )		/* CT_TM_25 */
#if ( (defined CT_TM_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 2 )				/* CT_TM_26 */
#else
	| ( INIT << 2 )			/* CT_TM_26 */
#endif

#if (defined CT_TM_01)
	| ( OK << 4 )			/* CT_TM_27 */
#else
	| ( INIT << 4 )		/* CT_TM_27 */
#endif
	| ( INIT << 6 ),		/* CT_TM_28 */
	  ( INIT << 0 )		/* CT_TM_29 */
#if (defined CT_TM_01)
	| ( OK << 2 )			/* CT_TM_30 */
#else
	| ( INIT << 2 )		/* CT_TM_30 */
#endif
	| ( INIT << 4 )		/* CT_TM_31 */
	| ( INIT << 6 ),		/* CT_TM_32 */
	  ( INIT << 0 )		/* CT_TM_33 */
	| ( INIT << 2 )		/* CT_TM_34 */
	| ( INIT << 4 )		/* CT_TM_35 */
#if ( (defined CT_TM_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 6 ),			/* CT_TM_36 */
#else
	| ( INIT << 6 ),		/* CT_TM_36 */
#endif
	  ( INIT << 0 )		/* CT_TM_37 */
#if ( (defined CT_TM_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 2 )			/* CT_TM_38 */
#else
	| ( INIT << 2 )		/* CT_TM_38 */
#endif
	| ( INIT << 4 )		/* CT_TM_39 */
#if (defined CT_TM_01)
	| ( OK << 6 ),			/* CT_TM_40 */
#else
	| ( INIT << 6 ),		/* CT_TM_40 */
#endif
	  ( INIT << 0 )		/* CT_TM_41 */
	| ( INIT << 2 )		/* CT_IP_01 */
	| ( INIT << 4 )		/* CT_IP_02 */
	| ( INIT << 6 ),		/* CT_IP_03 */
	};

uint8 ConfTestResult;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void ConfTestEvaluation
(
	void
)
{
	uint32f loopi;
	boolean testok = TRUE;

	for( loopi = 0; loopi < 35; loopi++)
	{
		if ( TestResultsOk[loopi] != TestResults[loopi] )
		{
			testok = FALSE;
		}
	}

	if ( testok == TRUE )
	{
		ConfTestResult = 255;
	}

	if ( testok == FALSE )
	{
		ConfTestResult = 128;
	}

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

