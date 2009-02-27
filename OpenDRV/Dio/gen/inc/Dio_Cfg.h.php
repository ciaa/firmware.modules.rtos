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

<?php
/** \brief OpenDRV File to be Generated
 **
 ** \file Dio_Cfg.h.php
 **/
?>

#ifndef _DIO_CFG_H_
#define _DIO_CFG_H_
/** \brief OpenDRV DIO Generated Configuration Header File
 **
 ** This file contents the generated configuration of the IO Driver
 **
 ** \file Dio_Cfg.h
 **/

/** \addtogroup OpenDRV
 ** @{ */ 
/** \addtogroup OpenDRV_Dio
 ** \ingroup OpenDRV
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
/** TODO this has to be a configurable parameter in function of the Dio oil
 ** configuration. */
#define DioDevErrorDetect ENABLE

<?php

$dioconfig = $config->getList("/OpenDRV/Dio","CONFIG");

if(count($dioconfig)!=1)
{
	error("Wront count of Dio Driver configurations, at the moment only 1 config is allowed for the Dio driver");
}

$diochannels = $config->getList("/OpenDRV/Dio/" . $dioconfig[0],"CHANNEL");
$count = 0;
foreach($diochannels as $dioc)
{
	print "#define " . $dioc . " " . $count . "\n";
	$count++;
}

?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_CFG_H_ */

