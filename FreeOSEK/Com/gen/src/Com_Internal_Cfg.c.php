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

/** \brief FreeOSEK Com Generated Configuration Implementation File
 **
 ** \file Com_Internal_Cfg.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Com
 ** @{ */
/** \addtogroup FreeOSEK_Com_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090708 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Com_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
/*------------------[Message Objects declarations]---------------------------*/
<?php
$messages = $config->getList("/COM","MESSAGE");
$count = 0;
$msgidp = 0;
print "/** \brief Constants for the Message Transmitted Objects definition */\n";
print "const Com_TxMsgObjCstType Com_TxMsgObjsCst[$com_total_tx_msg] =\n";
print "{\n";
$messages = $config->getList("/COM","MESSAGE");
$netmsgs = $config->getList("/COM","NETWORKMESSAGE");
$pdumsgs = $config->getList("/COM","IPDU");
foreach ($messages as $msg)
{
	$msgprop = $config->getValue("/COM/" . $msg, "MESSAGEPROPERTY");
	$msgtrans = $config->getValue("/COM/" . $msg . "/" . $msgprop, "TRANSFERPROPERTY");
	$msgnotif = $config->getValue("/COM/" . $msg . "/" . $msgprop, "NOTIFICATION");
	$msgsize = $config->getValue("/COM/" . $msg . "/" . $msgprop, "SIZEINBITS");
	$msgnet = $config->getValue("/COM/" . $msg . "/" . $msgprop, "NETWORKMESSAGE");
	$msge = false;
	if ( strpos($msgprop,"SEND") > -1 )
	{
		/* add , */
		if ($count > 0)
		{
			print ",\n";
		}
		print "	/* Transmit Message Object: $msg */\n";
		print "	{\n";
		print "		/* flags */\n";
		print "		{\n";
		switch ($msgprop)
		{
			case "SEND_STATIC_INTERNAL" :
				print "			COM_MSG_PROP_TX_STAT_INT";
				break;
			case "SEND_STATIC_EXTERNAL" :
				print "			COM_MSG_PROP_TX_STAT_EXT";
				$msge = true;
				break;
			case "SEND_ZERO_INTERNAL" :
				print "			COM_MSG_PROP_TX_ZERO_INT";
				break;
			case "SEND_ZERO_EXTERNAL" :
				print "			COM_MSG_PROP_TX_ZERO_EXT";
				$msge = true;
				break;
			case "RECEIVE_ZERO_INTERNAL" :
				print "			COM_MSG_PROP_RX_ZERO_INT";
				break;
			case "RECEIVE_ZERO_EXTERNAL" :
				print "			COM_MSG_PROP_RX_ZERO_EXT";
				$msge = true;
				break;
			case "RECEIVE_UNQUEUED_INTERNAL" :
				print "			COM_MSG_PROP_RX_STAT_INT";
				break;
			case "RECEIVE_UNQUEUED_EXTERNAL" :
				print "			COM_MSG_PROP_RX_STAT_EXT";
				$msge = true;
				break;
			default :
				error("the MESSAGEPROPERTY of the message $msg is set to $msgprop what is invalid or not supported");
				break;
		}
		print ", /* message properties */\n";
		switch ($msgtrans)
		{
			case "TRIGGERED" :
				print "			COM_MSG_TRANS_TRIGGERED";
				break;
			case "PENDING" :
				print "			COM_MSG_TRANS_PENDING";
				break;
			case "AUTO" :
				print "			COM_MSG_TRANS_AUTO";
				break;
			default :
				error("the TRANSFERPROPERTY of the message of the message $msg  is set to $msgtrans what is invalid or not supported");
				break;
		}
		print ", /* message transfer property */\n";
		switch ($msgnotif)
		{
			case "NONE" :
				print "			COM_MSG_NOTIF_NONE";
				break;
			case "ACTIVATETASK" :
				print "			COM_MSG_NOTIF_ATASK";
				break;
			case "SETEVENT" :
				print "			COM_MSG_NOTIF_SEVENT";
				break;
			case "COMCALLBACK" :
				print "			COM_MSG_NOTIF_CBACK";
				break;
			case "FLAG" :
				print "			COM_MSG_NOTIF_FLAG";
				break;
			default :
				error("the NOTIFICATION of the message $msg is set to $msgnotif what is invalid or not supported");
				break;
		}
		print ", /* message callback type */\n";
		print "		},\n";
		print "		" . $msgsize . ", /* size */\n";
		$offset = 0;
		foreach ($netmsgs as $nm)
		{
			if ( $msgnet == $nm )
			{
				$nmmp = $config->getValue("/COM/" . $nm, "MESSAGEPROPERTY");
				$offset = $config->getValue("/COM/" . $nm . "/" . $nmmp, "BITPOSITION");
				$offset >>= 3;	/* only byte offset is used for the data pointer - see bit position in network message */
			}
		}
		if ( $msge == true )
		{
			/* external message */
			$msgpdu = $config->getValue("/COM/" . $msgnet, "IPDU");		/* get pdu for the net message */
			print "		&Com_TxMsgExtBuf_" . $msgpdu . "[" . $offset . "], /* external communication data pointer */\n";
		}
		else
		{
			/* internal message */
			print "		&Com_TxMsgIntBuf[$msgidp], /* internal communication data pointer */\n";
			$msgidp += ( ( $msgsize + 7 ) >> 3 );
		}
		print "		" . $msgnet . " /* network message */\n";
		print "	}";
		$count++;
	}
}
print "\n};\n";

print "/*------------------[Network Objects declarations]---------------------------*/\n";
$count = 0;
print "/** \brief Constants for the Network Message Transmitted Objects definition */\n";
print "const Com_TxNetObjCstType Com_TxNetObjsCst[$com_total_tx_net] =\n";
print "{\n";
foreach ($netmsgs as $nm)
{
	$nmpdu = $config->getValue("/COM/" . $nm, "IPDU");
	$nmmp = $config->getValue("/COM/" . $nm, "MESSAGEPROPERTY");
	$nmsize = $config->getValue("/COM/" . $nm . "/" . $nmmp, "SIZEINBITS");
	$nmbo = $config->getValue("/COM/" . $nm . "/" . $nmmp, "BITORDERING");
	$nmbp = $config->getValue("/COM/" . $nm . "/" . $nmmp, "BITPOSITION");
	$nmbp &= 7; /* only the byte position is used - see data pointer in message object */
	$nmdi = $config->getValue("/COM/" . $nm . "/" . $nmmp, "DATAINTERPRETATION");
	$nmiv = $config->getValue("/COM/" . $nm . "/" . $nmmp, "INITIALVALUE");
	$nmdir = $config->getValue("/COM/" . $nm . "/" . $nmmp, "DIRECTION");
	$nmtp = $config->getValue("/COM/" . $nm . "/" . $nmmp . "/" . $nmdir, "TRANSFERPROPERTY");
	if ( $nmdir == "SENT" )
	{
		/* add , */
		if ($count > 0)
		{
			print ",\n";
		}
		$count++;
		print "	/* Transmit Network Message Object: $nm */\n";
		print "	{\n";
		print "		/* flags */\n";
		print "		{\n";
		switch ($nmmp)
		{
			case "STATIC" :
				print "			COM_NM_PROP_STATIC, /* network property */\n";
				break;
			case "DYNAMIC" :
				print "			COM_NM_PROP_DYNAMIC, /* network property */\n";
				break;
			case "ZERO" :
				print "			COM_NM_PROP_ZERO, /* network property */\n";
				break;
			default :
				error("$nmmp is not a valid network message property on network message $nm");
				print "			0, /* network properties */\n";
				break;
		}
		switch ($nmbo)
		{
			case "BIGENDIAN" :
				print "			COM_NM_BO_BIGENDIAN, /* network bitorder */\n";
				break;
			case "LITTLEENDIAN" :
				print "			COM_NM_BO_LITTLEENDIAN, /* network bitorder */\n";
				break;
			default :
				error("$nmbo is not a valid bit ordering on network message $nm");
				break;
		}
		switch ($nmdi)
		{
			case "UNSIGNEDINTEGER" :
				print "			COM_NM_DI_UNSIGNEDINTEGER, /* network data interpretation */\n";
				break;
			case "BYTEARRAY" :
				print "			COM_NM_DI_BYTEARRAY, /* network data interpretation */\n";
				break;
			default :
				error("$nmdi is not a valid data interpretation on network message $nm");
				break;
		}
		switch ($nmdir)
		{
			case "SENT" :
				$nmdirprop = $config->getValue("/COM/" . $nm . "/" . $nmmp . "/" . $nmdir, "TRANSFERPROPERTY");
				switch ($nmdirprop)
				{
					case "TRIGGERED" :
						print "			COM_NM_DIR_TX_TRIGGERED, /* network direction */\n";
						break;
					case "PENDING" :
						print "			COM_NM_DIR_TX_PENDING, /* network direction */\n";
						break;
					case "AUTO" :
						print "			COM_NM_DIR_TX_AUTO, /* network direction */\n";
						break;
					default :
						error("$nmdirprop is not a valid transfer property on network message $nm");
						break;
				}
				break;
			case "RECEIVED" :
				print "			COM_NM_DIR_RX, /* network direction */\n";
				break;
			default :
				error("$nmdir is not a valid direction on network message $nm");
				break;
		}
		print "			" . $nmbp . " /* offset on the PDU byte */\n";
		print "		},\n";
		print "		" . $nmsize . ", /* size */\n";
		print "		" . $nmpdu . ", /* PDU */\n";
		print "	}";
	}
}
print "\n};\n\n";

print "/*------------------[Transmit Buffer definition]-----------------------------*/\n";
if ( $msgidp != 0 )
{
	print "/** \brief Transmission Internal Message Buffer */\n";
	print "uint8 Com_TxMsgIntBuf[$msgidp];\n\n";
}
else
{
	print "/* no internal buffer is needed, Com_TxMsgIntBuf is not defined */\n\n";
}

foreach ($pdumsgs as $pm)
{
	print "/** \brief Transmit External $pm PDU Buffer */\n";
	$pmsize = $config->getValue("/COM/" . $pm , "SIZEINBITS");
	$pmsize = ( ( $pmsize + 7 ) >> 3 );
	print "uint8 Com_TxMsgExtBuf_" . $pm . "[" . $pmsize . "];\n";
}
?>

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

