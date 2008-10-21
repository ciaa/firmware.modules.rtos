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

#ifndef _TS_INTERNAL_H_
#define _TS_INTERNAL_H_
/** \brief TestSuite Internal Header File
 **
 ** \file TS_Internal.h
 **/

/** \addtogroup TestSuite
 ** @{ */ 
/** \addtogroup TestSuite_Internal
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
#include "TestSuite.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef TS_ResultType (*TestCase_Type)(void);

/*==================[external data declaration]==============================*/
extern const TestCase_Type TestCases[TS_TESTS_COUNT];

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TS_INTERNAL_H_ */

