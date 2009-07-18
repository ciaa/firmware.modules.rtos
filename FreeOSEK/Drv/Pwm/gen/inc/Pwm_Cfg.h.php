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
/** \brief OpenDRV File to be Generated
 **
 ** \file Pwm_Cfg.h.php
 **/
?>

#ifndef _PWM_CFG_H_
#define _PWM_CFG_H_
/** \brief OpenDRV PWM Generated Configuration Header File
 **
 ** This file contents the generated configuration of the PWM Driver
 **
 ** \file Pwm_Cfg.h
 **/

/** \addtogroup OpenDRV
 ** @{ */ 
/** \addtogroup OpenDRV_Pwm
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
 * 20090522 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Pwm Development Error Detection Macro */
/* \req Pwm071 The PwmDevErrorDetect enables the development error detection.
 * (ENABLE the development error detection is enable, DISABLE the development
 * error detection is disable)
 */
/* \dev The PwmDevErrorDetect macro can be ENABLE or DISABLE, this is not
 * conform to the specification */
<?php

$Pwmgen = $config->getList("/OpenDRV/Pwm","GENERAL");
if (count($Pwmgen)!=1)
{
	error("Wrong count of Pwm Driver GENERAL parameters on the configuration, only one is allowed");
}
else
{
	$Pwmdet = $config->getValue("/OpenDRV/Pwm/" . $Pwmgen[0],"DET");
	if($Pwmdet == "")
	{
		warning("DET not configured for Pwm Driver taking ENABLE as default");
		$Pwmdet = "TRUE";
	}
	if($Pwmdet == "FALSE")
	{
		print "#define PwmDevErrorDetect DISABLE\n\n";
	}
	elseif($Pwmdet == "TRUE")
	{
		print "#define PwmDevErrorDetect ENABLE\n\n";
	}
	else
	{
		error("Wrong DET configuration of the PWM Driver");
	}
}


$pwmconfig = $config->getList("/OpenDRV/Pwm","CONFIG");

if(count($pwmconfig)!=1)
{
	error("Wrong count of Pwm Driver configurations, at the moment only 1 config is allowed for the Pwm driver");
}

$pwmchannels = $config->getList("/OpenDRV/Pwm/" . $pwmconfig[0],"CHANNEL");

foreach($pwmchannels as $pwmc)
{
	$name = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_NAME");
	$channel = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL");
	print "/** \brief Channel definition for PWM $pwmc */\n";
	print "#define $name $channel\n\n";
}


?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _PWM_CFG_H_ */

