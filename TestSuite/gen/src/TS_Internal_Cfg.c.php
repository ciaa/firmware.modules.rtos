/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

/** \brief Test Suite Configuration Implementation File
 **
 ** \file TS_Internal_Cfg.c
 **/

/** \addtogroup TestSuite
 ** @{ */
/** \addtogroup Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080907 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "TS_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
const TestCase_Type TestCases[TS_TESTS_COUNT] = {
<?php
$testnames = $config->getList("/TESTSUITE","*");
$count = 0;
foreach ($testnames as $name)
{
	if ($count++ != 0)
	{
		print ",\n";
	}
	print "	TEST_$name";
}
print "\n";
?>
};

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

