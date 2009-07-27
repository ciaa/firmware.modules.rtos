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
/** \brief FreeOSEK Com File to be Generated
 **
 ** \file Com_Cfg.h.php
 **
 **/
?>

#ifndef _COM_CFG_H_
#define _COM_CFG_H_
/** \brief FreeOSEK Com Generated Configuration Header File
 **
 ** This file contents the generated configuration of OpenCOM
 **
 ** \file Com_Cfg.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Com
 ** @{ */
/** \addtogroup FreeOSEK_Com_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.1 20090705 MaCe implement first COM Module
 * v0.1.0 20090322 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
<?php
$configs = $config->getList("/COM", "COM");
if (count($configs)!=1)
{
	error("not least and no more than 1 COM configuration shall be available, " . count($configs) . " were found");
}

$applmode = $config->getList("/COM/" . $configs[0], "COMAPPMODE");
if (count($applmode)<1)
{
	error("at least one COMAPPMODE shall be defined");
}

$count = 0;
foreach ($applmode as $am)
{
	print "/** \brief Communication Application Mode: $am */\n";
	print "#define $am " . $count . "U\n\n";	
	$count++;
}

$messages = $config->getList("/COM","MESSAGE");
$count = 0;
print "/** \brief Definition of all Send Messages */\n";
foreach ($messages as $msg)
{
	$msgprop = $config->getValue("/COM/" . $msg,"MESSAGEPROPERTY");
	if ( strpos($msgprop,"SEND") > -1 )
	{
		print "/** \brief Send Message $msg */\n";
		print "#define $msg " . $count . "U\n\n";
		$count++;
	}
}
$com_total_tx_msg = $count;

print "/** \brief Definition of all Receive Messages */\n";
foreach ($messages as $msg)
{
	$msgprop = $config->getValue("/COM/" . $msg,"MESSAGEPROPERTY");
	if ( strpos($msgprop,"RECEIVE") > -1 )
	{
		print "/** \brief Receive Message $msg */\n";
		print "#define $msg " . $count . "U\n\n";
		$count++;
	}
}
$com_total_rx_msg = $count - $com_total_tx_msg;

?>

/*==================[typedef]================================================*/
/** \brief Message Identifier data definition */
<?php
if ( ( $com_total_tx_msg + $com_total_rx_msg ) < 256 )
{
	print "typedef uint8 MessageIdentifier;\n";
}
elseif ( ( $com_total_tx_msg + $com_total_rx_msg ) < 65536 )
{
	print "typedef uint16 MessageIdentifier;\n";
}
else
{
	error("up to 65536 messages are allowed on the COM module, " . ( $com_total_tx_msg + $com_total_rx_msg ) . " are defined");
}
?>

/** \brief Communication Lenght type definition */
/* TODO this type has to be configurable */
typedef uint8 COMLengthType;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_CFG_H_ */

