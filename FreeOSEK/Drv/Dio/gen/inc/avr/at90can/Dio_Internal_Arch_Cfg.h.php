/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2011, Mariano Cerdeiro
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
/** \brief FreeOSEK Driver DIO Internal Arch Header File to be Generated
 **
 ** \file Dio_Internal_Arch_Cfg.h.php
 **/
?>

#ifndef _DIO_INTERNAL_ARCH_CFG_H_
#define _DIO_INTERNAL_ARCH_CFG_H_
/** \brief DRV DIO Internal Arch Generated Configuration Header File
 **
 ** This file contents the generated configuration of the IO Driver
 **
 ** \file Dio_Internal_Arch_Cfg.h
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20110113 v0.1.0 MaCe	initial version
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
<?php
$port_mask = array_fill(0, 5, 0);
$port_dir = array_fill(0, 5, 0);

foreach($diochannels as $dioc)
{
	$name = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "NAME");
	$port = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PORT");
	$pin = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "PIN");
	$dir = $config->getValue("/DRV/Dio/" . $dioconfig[0] . "/" . $dioc, "DIRECTION");
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
		$port_mask[$port] |= 1 << $pin;
		if($dir == "OUTPUT")
		{
			$port_dir[$port] |= 1 << $pin;
		}
	}
}

$count = 0;
foreach($port_mask as $pm)
{
	print "/** \brief Dio Port $count state\n";
	print " **\n";
	print " ** if ENABLE the port will be used in Dio Driver\n";
	print " ** if DISABLE the port will not be used in Dio Driver\n";
	print " **/\n";
	if($pm != 0)
	{
		print "#define DIO_PORT" . $count . "_STATE	ENABLE\n\n";
	}
	else
	{
		print "#define DIO_PORT" . $count . "_STATE	DISABLE\n\n";
	}
	$count++;
}

$count = 0;
foreach($port_mask as $pm)
{
	print "/** \brief Mask of the Dio Port $count\n";
	print " **\n";
	print " ** bit n 0 indicate the bit of the port $count is not used\n";
	print " ** bit n 1 indicate the bit of the port $count is used\n";
	print " **/\n";
	print "#define DIO_PORT" . $count . "_MASK	0x" . dechex($pm) . "\n\n";
	$count++;
}
$count = 0;
foreach($port_dir as $pd)
{
	print "/** \brief Direction of the Dio Port $count\n";
	print " **\n";
	print " ** bit n 0 indicate the bit of the port $count is an input\n";
	print " ** bit n 1 indicate the bit of the port $count is an output\n";
	print " **/\n";
	print "#define DIO_PORT" . $count . "_DIR	0x" . dechex($pd) . "\n\n";
	$count++;
}
?>

/** \brief Init value for Port 0 */
#define DIO_PORT0_INIT	0

/** \brief Init value for Port 1 */
#define DIO_PORT1_INIT	0

/** \brief Init value for Port 2 */
#define DIO_PORT2_INIT	0

/** \brief Init value for Port 3 */
#define DIO_PORT3_INIT	0

/** \brief Init value for Port 4 */
#define DIO_PORT4_INIT	0

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_INTERNAL_ARCH_CFG_H_ */

