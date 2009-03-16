/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

<?php
/** \brief OpenDRV DIO Arch Header File to be Generated
 **
 ** \file Dio_Arch_Cfg.h.php
 **/
?>

#ifndef _DIO_ARCH_CFG_H_
#define _DIO_ARCH_CFG_H_
/** \brief OpenDRV DIO Arch Generated Configuration Header File
 **
 ** This file contents the generated configuration of the IO Driver
 **
 ** \file Dio_Arch_Cfg.h
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
 * 20090316 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
<?php
foreach($diochannels as $dioc)
{
	$name = $config->getValue("/OpenDRV/Dio/" . $dioconfig[0] . "/" . $dioc, "NAME");
	$port = $config->getValue("/OpenDRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PORT");
	$pin = $config->getValue("/OpenDRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PIN");
	$dir = $config->getValue("/OpenDRV/Dio/" . $dioconfig[0] . "/" . $dioc, "DIRECTION");
	if ($port > 4)
	{
		error("Invalid port number in Dio channel " . $dioc);
	}
	elseif($pin > 31)
	{
		error("Invalid pin number on Dio channel " . $dioc);	
	}
	elseif( ($dir != "INPUT") &&
			  ($dir != "OUTPUT"))
	{
		error("Invalid direction on Dio channel " . $dioc);
	}
	else
	{
		if($dir == "OUTPUT")
		{
			print "#define Dio_WriteChannel_Arch_" . ($port * 32 + $pin) . "(value) \\\n";
			print "				((value) == DIO_LOW) ? ( FIO" . $port . "CLR = 1 << " . $pin . " ) : ( FIO" . $port . "SET = 1 << " . $pin . " )\n\n";
		}
		else
		{
			print "#define Dio_ReadChannel_Arch_" . ($port * 32 + $pin) . "() \\\n";
			print "				( ( FIO" . $port . "PIN >> " . $pin . " ) & 1 )\n\n";
		}
	}
}

?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_ARCH_CFG_H_ */

