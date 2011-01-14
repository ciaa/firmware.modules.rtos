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

<?php
/** \brief Dio Driver File to be Generated
 **
 ** \file Dio_Cfg.h.php
 **/
?>

#ifndef _DIO_CFG_H_
#define _DIO_CFG_H_
/** \brief Driver DIO Generated Configuration Header File
 **
 ** This file contents the generated configuration of the IO Driver
 **
 ** \file Dio_Cfg.h
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */  
/** \addtogroup FreeOSEK_Drv_Dio
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090213 v0.1.1 MaCe raname Io driver to Dio
 * 20090125 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Dio Development Error Detection Macro */
/* \req DIO071 The DioDevErrorDetect enables the development error detection.
 * (ENABLE the development error detection is enable, DISABLE the development
 * error detection is disable)
 */
/* \dev The DioDevErrorDetect macro can be ENABLE or DISABLE, this is not
 * conform to the specification */
<?php

$diogen = $config->getList("/DRV/Dio","GENERAL");
if (count($diogen)!=1)
{
	error("Wrong count of Dio Driver GENERAL parameters on the configuration, only one is allowed");
}
else
{
	$diodet = $config->getValue("/DRV/Dio/" . $diogen[0],"DET");
	if($diodet == "")
	{
		warning("DET not configured for Dio Driver taking ENABLE as default");
		$diodet = "TRUE";
	}
	if($diodet == "FALSE")
	{
		print "#define DioDevErrorDetect DISABLE\n\n";
	}
	elseif($diodet == "TRUE")
	{
		print "#define DioDevErrorDetect ENABLE\n\n";
	}
	else
	{
		error("Wrong DET configuration of the Dio Driver");
	}
}


$dioconfig = $config->getList("/DRV/Dio","CONFIG");

if(count($dioconfig)!=1)
{
	error("Wrong count of Dio Driver configurations, at the moment only 1 config is allowed for the Dio driver");
}

$diochannels = $config->getList("/DRV/Dio/" . $dioconfig[0],"CHANNEL");
$count = 0;
foreach($diochannels as $dioc)
{
	$name = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "NAME");
	$port = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PORT");
	$pin = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PIN");
	$dir = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "DIRECTION");
	switch ($port)
	{
		case "A":
			$port = 0;
			break;
		case "B":
			$port = 1;
			break;
		case "C":
			$port = 2;
			break;
		case "D":
			$port = 3;
			break;
		case "E":
			$port = 4;
			break;
		case "F":
			$port = 5;
			break;
	}
	print "/** \brief Define Dio Channel $dioc - port: $port - pin: $pin */\n";
	print "#define " . $name . "	" . (($port*32)+$pin) . "\n\n";
	$count++;
}

?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_CFG_H_ */

