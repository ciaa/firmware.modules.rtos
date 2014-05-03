/*********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALLY*
 *********************************************************/

/* Copyright 2011 Tamas Kenderes
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

/** \brief FreeOSEK Driver Dio Arch Header File to be Generated
 **
 ** \file Dio_Arch_Cfg.h.php
 **/

#ifndef _DIO_ARCH_CFG_H_
#define _DIO_ARCH_CFG_H_
/** \brief FreeOSEK Driver Dio Arch Generated Configuration Header File
 **
 ** This file contents the generated configuration of the Dio Driver
 **
 ** \file Dio_Arch_Cfg.h
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
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.6 KT	initial version
 */

/*==================[cpu macros]=============================================*/
/** \brief at91sam7x cpu definition */
#define at91sam7x128	1
/** \brief at91sam7x cpu definition */
#define at91sam7x256	2
/** \brief at91sam7x cpu definition */
#define at91sam7x512	3

/*==================[inclusions]=============================================*/
#ifndef CPU
#error No CPU defined
#elif (CPU == at91sam7x128)
#include "AT91SAM7X128.h"
#elif (CPU == at91sam7x256)
#include "AT91SAM7X256.h"
#elif (CPU == at91sam7x512)
#include "AT91SAM7X512.h"
#else
#error Wrong CPU defined
#endif

/*==================[macros]=================================================*/
<?php
foreach($diochannels as $dioc)
{
	$name = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "NAME");
	$port_txt = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PORT");
	$port = ord(strtoupper($port_txt[0])) - ord('A');
	$pin = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PIN");
	$dir = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "DIRECTION");
	if (($port < 0) || ($port > 1))
	{
		error("Invalid port number in Dio channel " . $dioc);
	}
	elseif($pin > 30)
	{
		error("Invalid pin number in Dio channel " . $dioc);
	}
	elseif( ($dir != "INPUT") &&
			($dir != "OUTPUT"))
	{
		error("Invalid direction in Dio channel " . $dioc);
	}
	else
	{
		if($dir == "OUTPUT")
		{
			print "#define Dio_WriteChannel_Arch_" . ($port * 32 + $pin) . "(value) \\\n";
			print "	((value) == DIO_LOW) ? ( *AT91C_PIO" . $port_txt . "_CODR = (1 << " . $pin . ") ) : ( *AT91C_PIO" . $port_txt . "_SODR = (1 << " . $pin . ") )\n\n";
		}
		else
		{
			print "#define Dio_ReadChannel_Arch_" . ($port * 32 + $pin) . "() \\\n";
			print "	( ( PIO" . $port . "_PDSR >> " . $pin . " ) & 1 )\n\n";
		}
	}
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
#endif /* #ifndef _DIO_ARCH_CFG_H_ */

