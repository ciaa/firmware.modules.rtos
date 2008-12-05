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
 * v0.1.0 20080830 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
#define TS_TESTS_COUNT <?php echo $config->getCount("/TESTSUITE","*"); ?>


<?php
$testnames = $config->getList("/TESTSUITE","*");
$count = 0;
foreach ($testnames as $name)
{
   print "#define $name $count\n\n";
	$count++;
}

?>

/*==================[typedef]================================================*/
/** \brief Type definition of TestResult */
typedef unsigned char TS_ResultType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#define TestSuite_START_SEC_CODE
#include "MemMap.h"

<?php
$testnames = $config->getList("/TESTSUITE","*");

foreach ($testnames as $name)
{
	$desc = $config->getValue("/TESTSUITE/" . $name,"DESCRIPTION");
	print "/** \brief Test $name\n";
	print " **\n";
	print " ** $desc\n";
	print " **/\n";
	print "TS_ResultType TEST_$name(void)  ATTRIBUTES();\n\n";
}
?>

#define TestSuite_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TS_CFG_H_ */
