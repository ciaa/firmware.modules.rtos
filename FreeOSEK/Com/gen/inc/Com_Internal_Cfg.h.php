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
 ** \file Com_Internal_Cfg.h.php
 **
 **/
?>

#ifndef _COM_INTERNAL_CFG_H_
#define _COM_INTERNAL_CFG_H_
/** \brief FreeOSEK Com Generated Configuration Header File
 **
 ** This file contents the generated configuration of OpenCOM
 **
 ** \file Com_Internal_Cfg.h
 **
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
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20090711 MaCe	initial version
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
<?php
$configs = $config->getList("/COM", "COM");

/* COMSTATUS */
$status = $config->getValue("/COM/" . $configs[0], "COMSTATUS");
print "/** \brief Error Checking Type */\n";
if ( $status == TRUE )
{
	print "#define ERROR_CHECKING_TYPE ERROR_CHECKING_EXTENDED\n\n";
}
elseif ( $status == FALSE )
{
	print "#define ERROR_CHECKING_TYPE ERROR_CHECKING_STANDARD\n\n";
}
else
{
	warning("COMSTATUS not defined, using FALSE as default");
	print "#define ERROR_CHECKING_TYPE ERROR_CHECKING_STANDARD\n\n";
}

/* COMERRORHOOK */
$errorhook = $config->getValue("/COM/" . $configs[0], "COMERRORHOOK");
print "/** \brief ErrorHook  */\n";
if ( $errorhook == TRUE )
{
	print "#define COM_ERRORHOOK ENABLE\n\n";
}
elseif ( $errorhook == FALSE )
{
	print "#define COM_ERRORHOOK DISABLE\n\n";
}
else
{
	warning("COMERRORHOOK not defined, using FALSE as default");
	print "#define COM_ERRORHOOK DISABLE\n\n";
}

/* COMUSEGETSERVICEID */
$getsid = $config->getValue("/COM/" . $configs[0], "COMUSEGETSERVICEID");
print "/** \brief Enable or Disable GetServiceId */\n";
if ( $getsid == TRUE )
{
	print "#define COM_GETSERVICEID ENABLE\n\n";
}
elseif ( $getsid == FALSE )
{
	print "#define COM_GETSERVICEID DISABLE\n\n";
}
else
{
	warning("COMUSEGETSERVICEID not defined, using FALSE as default");
	print "#define COM_GETSERVICEID DISABLE\n\n";
}

/* COMUSEPARAMETERACCESS */
$pa = $config->getValue("/COM/" . $configs[0], "COMUSEPARAMETERACCESS");
print "/** \brief Enable or Disable USEPARAMETERACCESS */\n";
if ( $pa == TRUE )
{
	print "#define COM_USEPARAMETERACCESS ENABLE\n\n";
}
elseif ( $pa == FALSE )
{
	print "#define COM_USEPARAMETERACCESS DISABLE\n\n";
}
else
{
	warning("COMUSEPARAMETERACCESS not defined, using FALSE as default");
	print "#define COM_USEPARAMETERACCESS DISABLE\n\n";
}

/* COMSTARTCOMEXTENSION */
$se = $config->getValue("/COM/" . $configs[0], "COMSTARTCOMEXTENSION");
print "/** \brief Enable or Disable COMSTARTCOMEXTENSION */\n";
if ( $se == TRUE )
{
	print "#define COM_STARTCOMEXTENSION ENABLE\n\n";
}
elseif ( $se == FALSE )
{
	print "#define COM_COMSTARTCOMEXTENSION DISABLE\n\n";
}
else
{
	warning("COMSTARTCOMEXTENSION not defined, using FALSE as default");
	print "#define COM_COMSTARTCOMEXTENSION DISABLE\n\n";
}
?>
/*------------------[Message Objects macros declarations]--------------------*/
/** \brief Description of the Message Properties
 **
 ** bits:
 **    4     3     2     1    0
 ** +-----+-----+-----+-----+---+
 ** | T/R | Q/U | S/D | I/E | Z |
 ** +-----+-----+-----+-----+---+
 **
 ** T/R 0 indicates transmission
 **     1 indicates reception
 ** Q/U 0 indicates unqueued message (always for tx message)
 **     1 indicates queued message
 ** S/D 0 indicates static message length
 **     1 indicates dynamic message length
 ** I/E 0 indicates internal message
 **	  1 indicates external message (or both)
 ** Z	  1 indicates zero message
 **/
#define COM_MSG_PROP_TX						0x00U
#define COM_MSG_PROP_RX						0x10U
#define COM_MSG_PROP_UNQUEUED				0x00U
#define COM_MSG_PROP_QUEUED				0x08U
#define COM_MSG_PROP_STATIC				0x00U
#define COM_MSG_PROP_DYNAMIC				0x04U
#define COM_MSG_PROP_INTERNAL				0x00U
#define COM_MSG_PROP_EXTERNAL				0x02U
#define COM_MSG_PROP_ZERO					0x01U

#define COM_MSG_PROP_TX_STAT_INT			( COM_MSG_PROP_TX | COM_MSG_PROP_STATIC   | COM_MSG_PROP_INTERNAL )
#define COM_MSG_PROP_TX_STAT_EXT			( COM_MSG_PROP_TX | COM_MSG_PROP_STATIC   | COM_MSG_PROP_EXTERNAL )
#define COM_MSG_PROP_TX_DYN_EXT			( COM_MSG_PROP_TX | COM_MSG_PROP_DYNAMIC  | COM_MSG_PROP_EXTERNAL )
#define COM_MSG_PROP_TX_ZERO_INT			( COM_MSG_PROP_TX | COM_MSG_PROP_INTERNAL | COM_MSG_PROP_ZERO )
#define COM_MSG_PROP_TX_ZERO_EXT			( COM_MSG_PROP_TX | COM_MSG_PROP_EXTERNAL | COM_MSG_PROP_ZERO )
#define COM_MSG_PROP_RX_ZERO_INT			( COM_MSG_PROP_RX | COM_MSG_PROP_INTERNAL | COM_MSG_PROP_ZERO )
#define COM_MSG_PROP_RX_ZERO_EXT			( COM_MSG_PROP_RX | COM_MSG_PROP_EXTERNAL | COM_MSG_PROP_ZERO )
#define COM_MSG_PROP_RX_UNQUEUED_INT	( COM_MSG_PROP_RX | COM_MSG_PROP_UNQUEUED | COM_MSG_PROP_INTERNAL )
#define COM_MSG_PROP_RX_UNQUEUED_EXT	( COM_MSG_PROP_RX | COM_MSG_PROP_UNQUEUED | COM_MSG_PROP_EXTERNAL )
#define COM_MSG_PROP_RX_QUEUED_INT		( COM_MSG_PROP_RX | COM_MSG_PROP_QUEUED   | COM_MSG_PROP_INTERNAL )
#define COM_MSG_PROP_RX_QUEUED_EXT		( COM_MSG_PROP_RX | COM_MSG_PROP_QUEUED   | COM_MSG_PROP_EXTERNAL )
#define COM_MSG_PROP_RX_DYN_EXT			( COM_MSG_PROP_RX | COM_MSG_PROP_DYNAMIC  | COM_MSG_PROP_EXTERNAL )
#define COM_MSG_PROP_RX_ZERO				( COM_MSG_PROP_RX | COM_MSG_PROP_INTERNAL | COM_MSG_PROP_ZEROm)

#define COM_MSG_TRANS_TRIGGERED		0U
#define COM_MSG_TRANS_PENDING			1U
#define COM_MSG_TRANS_AUTO				2U

#define COM_MSG_NOTIF_NONE				0U
#define COM_MSG_NOTIF_ATASK			1U
#define COM_MSG_NOTIF_SEVENT			2U
#define COM_MSG_NOTIF_CBACK			3U
#define COM_MSG_NOTIF_FLAG				4U

<?php
print "/** \brief Count of RX Messages */\n";
print "#define COM_TX_MAX_MESSAGE $com_total_tx_msg\n\n";

print "/** \brief Count of RX Messages */\n";
print "#define COM_RX_MAX_MESSAGE $com_total_rx_msg\n\n";

print "/** \brief Enable or Disable ReceiveMessage API */\n";
if ( $com_total_rx_msg == 0 )
{
	print "#define COM_RECEIVEMESSAGE DISABLE\n\n";
}
else
{
	print "#define COM_RECEIVEMESSAGE ENABLE\n\n";
}

print "/** \brief Enable or Disable SendMessage API */\n";
if ( $com_total_tx_msg == 0 )
{
	print "#define COM_SENDMESSAGE DISABLE\n\n";
}
else
{
	print "#define COM_SENDMESSAGE ENABLE\n\n";
}


$timebase = $config->getList("/COM/" . $configs[0], "COMTIMEBASE");
if (count($timebase) != 1)
{
	error("only one COMTIMEBAE shall be defined, " . count($timebase) . " were found");
}
print "/** \brief COM time base macro definition */\n";
print "#define COM_TIMEBASE $timebase\n\n";



?>
/*------------------[Network Message Objects macros declarations]------------*/
#define COM_NM_PROP_STATIC				0
#define COM_NM_PROP_DYNAMIC			1
#define COM_NM_PROP_ZERO				2

#define COM_NM_BO_BIGENDIAN			0
#define COM_NM_BO_LITTLEENDIAN		1

#define COM_NM_DI_UNSIGNEDINTEGER	0
#define COM_NM_DI_BYTEARRAY			1

#define COM_NM_DIR_TX_TRIGGERED		0
#define COM_NM_DIR_TX_PENDING			1
#define COM_NM_DIR_TX_AUTO				2

<?php
$nets = $config->getList("/COM","NETWORKMESSAGE");
$count_tx = 0;
print "/** \brief Definition of all Transmitted Network Messages */\n";
foreach ($nets as $net)
{
	$netmp = $config->getValue("/COM/" . $net,"MESSAGEPROPERTY");
	$netdir = $config->getValue("/COM/" . $net . "/" . $netmp, "DIRECTION");
	if ( $netdir == "SENT" )
	{
		print "/** \brief Net Tx $net */\n";
		print "#define $net " . $count_tx . "U\n\n";
		$count_tx++;
	}
}
$com_total_tx_net = $count_tx;

$count_rx = 0;
print "/** \brief Definition of all Receive Network Messages */\n";
foreach ($nets as $net)
{
	$netmp = $config->getValue("/COM/" . $net,"MESSAGEPROPERTY");
	$netdir = $config->getValue("/COM/" . $net . "/" . $netmp, "DIRECTION");
	if ( $netdir == "RECEIVE" )
	{
		print "/** \brief Net Rx $net */\n";
		print "#define $net " . $count_rx . "U\n\n";
		$count_rx++;
	}
}
$com_total_rx_net = $count_rx;
?>

/*------------------[PDU Message Objects macros declarations]----------------*/
#define COM_TX_PDU_PERIODIC			0U
#define COM_TX_PDU_DIRECT				1U
#define COM_TX_PDU_MIXED				2U
#define COM_RX_PDU						3U

<?php
$pdus = $config->getList("/COM","IPDU");
$count_tx = 0;
print "/** \brief Definition of all Transmitted PDU Messages */\n";
foreach ($pdus as $pdu)
{
	$pduprop = $config->getValue("/COM/" . $pdu,"IPDUPROPERTY");
	if ( $pduprop == "SENT" )
	{
		print "/** \brief PDU Tx $pdu */\n";
		print "#define $pdu " . $count_tx . "U\n\n";
		$count_tx++;
	}
}
$com_total_tx_pdus = $count_tx;

$count_rx = 0;
print "/** \brief Definition of all Receive PDU Messages */\n";
foreach ($pdus as $pdu)
{
	$pduprop = $config->getValue("/COM/" . $pdu,"IPDUPROPERTY");
	if ( $msgprop == "RECEIVE" )
	{
		print "/** \brief PDU Rx $pdu */\n";
		print "#define $pdu " . $count_rx . "U\n\n";
		$count_rx++;
	}
}
$com_total_rx_pdus = $count_rx;
?>

/*------------------[Lower Layers macros declarations]-----------------------*/

/*==================[typedef]================================================*/
/*------------------[Identifier type definitions]----------------------------*/
/** \brief Network Message Identifier type definition */
typedef uint8 Com_NetMsgType;

/** \brief I-PDU type definition */
/** TODO uint8 or uint16 has to depend on the quantity of pdus */
typedef uint8 Com_PDUType;

/** \brief Net type definition */
/** TODO uint8 or uint16 has to depend on the quantity of network messages */
typedef uint8 Com_NetType;

/*------------------[Message Objects type definitions]----------------------*/
/** \brief Message Flags type definition
 **
 ** \param Prop indicates the message properties, valid values are:
 **			- COM_MSG_PROP_TX_STAT_INT
 **			- COM_MSG_PROP_TX_STAT_EXT
 **			- COM_MSG_PROP_TX_DYN_EXT
 **			- COM_MSG_PROP_TX_ZERO_INT
 **			- COM_MSG_PROP_TX_ZERO_EXT
 **			- COM_MSG_PROP_RX_ZERO_INT
 **			- COM_MSG_PROP_RX_ZERO_EXT
 **			- COM_MSG_PROP_RX_UNQUEUED_INT
 **			- COM_MSG_PROP_RX_UNQUEUED_EXT
 **			- COM_MSG_PROP_RX_QUEUED_INT
 **			- COM_MSG_PROP_RX_QUEUED_EXT
 **			- COM_MSG_PROP_RX_DYN_EXT
 **			- COM_MSG_PROP_RX_ZERO
 ** \param Trans is the type fo the message valid values are:
 **			- COM_MSG_TRANS_TRIGGERED
 **			- COM_MSG_TRANS_PENDING
 **			- COM_MSG_TRANS_AUTO
 ** \param Notif indicates the message callback type
 **			- COM_MSG_NOTIF_NONE
 **			- COM_MSG_NOTIF_ATASK
 **			- COM_MSG_NOTIF_SEVENT
 **			- COM_MSG_NOTIF_CBACK
 **			- COM_MSG_NOTIF_FLAG
 **/
typedef struct {
	uint16 Prop : 5;
	uint16 Trans : 2;
	uint16 Notif : 3;
} Com_MsgFlagsType;

/** \brief Transmit Message Object Const type definition
 **
 ** \param Flags	Transmit Flags, for more details see Com_MsgFlagsType type
 **					definition
 ** \param Size	Size of the network message in bits
 ** \param Data	pointer to the memory to stor the data
 ** \param Net		network message
 **/
typedef struct {
	Com_MsgFlagsType Flags;
	uint16 Size;
	uint8* Data;
	Com_NetType Net;
} Com_TxMsgObjCstType;

/** \brief Receive Message (and network) Object Const type definition
 **
 ** \param Flags	Receive Flags, for more details see Com_MsgFlagsType type
 **					definition
 ** \param Size	Size of the network message in bits
 ** \param Data	pointer to the memory to stor the data
 ** \param Net		network message
 **/
typedef struct {
	Com_MsgFlagsType Flags;
	uint16 Size;
	uint8* Data;
	Com_NetType Net;
} Com_RxMsgObjCstType;

/*------------------[Network Message Objects type definitions]--------------*/
/** \brief Network Message Flags type definition
 **
 ** \param Prop network message properties, valid valuesa are:
 **			- COM_NM_PROP_STATIC
 **			- COM_NM_PROP_DYNAMIC
 **			- COM_NM_PROP_ZERO
 ** \param BitOrd network bit ordering, valid values are:
 **			- COM_NM_BO_BIGENDIAN
 **			- COM_NM_BO_LITTLEENDIAN
 ** \param DataInt network message data interpretation
 **			- COM_NM_DI_UNSIGNEDINTEGER
 **			- COM_NM_DI_BYTEARRAY
 ** \param Direction network message data direction
 **			- COM_NM_DIR_RX
 **			- COM_NM_DIR_TX_TRIGGERED
 **			- COM_NM_DIR_TX_PENDING
 **			- COM_NM_DIR_TX_AUTO
 ** \param Offset	offset of the network message on the PDU byte
 **/
typedef struct {
	uint16 Prop : 2;
	uint16 BitOrd : 1;
	uint16 DataInt : 1;
	uint16 Direction : 2;
	uint16 Offset : 3;
} Com_NetFlagsType;

/** \brief Transmit Network Message Object Const type definition
 **
 ** \param Flags	Transmit Flags, for more details see Com_NetFlagsType type
 **					definition
 ** \param Size	Size in bits of the network message
 ** \param PDU		PDU message
 **/
typedef struct {
	Com_NetFlagsType Flags;
	uint16 Size;
	Com_PDUType PDU;
} Com_TxNetObjCstType;

/** \brief Receive Network Message Object Const type definition
 **
 ** \param Flags	Transmit Flags, for more details see Com_NetFlagsType type
 **					definition
 ** \param Net		network message
 **/
typedef struct {
	Com_NetFlagsType Flags;
	Com_PDUType PDU;
} Com_RxNetObjCstType;

/*------------------[PDU Message Objects type definitions]------------------*/
/** \brief PDU Flags type definition
 **
 ** \param Prop is the property of the PDU valid values are:
 **			- COM_TX_PDU_PERIODIC
 **			- COM_TX_PDU_DIRECT
 **			- COM_TX_PDU_MIXED
 **			- COM_RX_PDU
 **/
typedef struct {
	uint16 Prop : 2;
} Com_PDUFlagsType;

/** \brief Transmit PDU Object Const type definition
 **
 ** \param Size size in bits of the PDU
 ** \param Flags PDU flags, see Com_PDUFlagsType type definition
 **/
typedef struct {
	uint16 Size;
	Com_PDUFlagsType Flags;
	uint16 TimePeriod;
	uint16 TimeOffset;
	uint16 MinDelay;
	uint16 Timeout;
	uint8 Layer;
	uint16 LayerPDU;
} Com_TxPduObjCstType;

/** \brief Reception PDU Object Const type definition
 **
 ** \param Flags PDU flags, see Com_PDUFlagsType type definition
 ** \param Msgs pointer to the lisf of messages receiving from this PDU
 ** \param MsgCount amount of message on the Msgs list
 **/
typedef struct {
	Com_PDUFlagsType Flags;
	const MessageIdentifier* Msgs;
	uint8	MsgCount;
} Com_RxPduObjCstType;

/*------------------[Lower Layers type definitions]-------------------------*/
/** \brief Low Layer Tx Trigger Functions */
typedef void (*Com_TxTriggerType)(uint16 PDU);

/*==================[external data declaration]==============================*/
<?php
print "/*------------------[Message Objects declarations]---------------------------*/\n";
if ( $com_total_rx_msg != 0 )
{
	print "/** \brief Constants for the Message Receive Objects */\n";
	print "extern const Com_RxMsgObjCstType Com_RxMsgObjsCst[$com_total_rx_msg];\n\n";
}
else
{
	print "/* No reception Message is defined, Com_RxMsgObjsCst is not declared */\n\n";
}
if ( $com_total_tx_msg != 0 )
{
	print "/** \brief Constants for the Message Transmission Objects */\n";
	print "extern const Com_TxMsgObjCstType Com_TxMsgObjsCst[$com_total_tx_msg];\n\n";
}
else
{
	print "/* No transmission Message is defined, Com_TxMsgObjsCst is not declared */\n\n";
}

print "/*------------------[Network Objects declarations]---------------------------*/\n";
if ( $com_total_rx_net != 0 )
{
	print "/** \brief Constants for the Network Message Received Objects */\n";
	print "extern const Com_RxNetObjCstType Com_RxNetObjsCst[$com_total_rx_net];\n\n";
}
else
{
	print "/* No reception Network Message is defined, Com_TxMsgObjsCst is not declared */\n\n";
}
if ( $com_total_tx_net != 0 )
{
	print "/** \brief Constants for the Network Message Transmission Objects */\n";
	print "extern const Com_TxNetObjCstType Com_TxNetObjsCst[$com_total_tx_net];\n\n";
}
else
{
	print "/* No transmission Network Message is defined, Com_TxMsgObjsCst is not declared */\n\n";
}

print "/*------------------[PDU Objects declarations]-------------------------------*/\n";
if ( $com_total_rx_pdus != 0 )
{
	print "/** \brief Constants for the PDU Receive Objects */\n";
	print "extern const Com_RxPduObjCstType Com_RxPduObjsCst[" . $com_total_rx_pdus . "];\n\n";
}
else
{
	print "/* No reception PDU is defined, Com_RxPduObjsCst is not declared */\n\n";
}

if ( $com_total_tx_pdus != 0 )
{
	print "/** \brief Constants for the PDU Transmit Objects */\n";
	print "extern const Com_TxPduObjCstType Com_TxPduObjsCst[" . $com_total_tx_pdus . "];\n\n";
}
else
{
	print "/* No transmission PDU is defined, Com_TxPduObjectsConst is not declared */\n\n";
}
?>
/*------------------[Lower Layers declarations]------------------------------*/
<?php
$pdus = $config->getList("/COM","IPDU");
$count = 0;
$f = $c = $ti = $ui = $u = 0;
foreach ($pdus as $pdu)
{
	$pduprop = $config->getValue("/COM/" . $pdu,"IPDUPROPERTY");
	if ( $pduprop == "SENT" )
	{
		$layer = $config->getValue("/COM/" . $pdu, "LAYERUSED");
		if ( ( $layer == "TCP") && ( $ti == 0 ) )
		{
			$count++;
			$ti = 1;
		}
		if ( ( $layer == "UDP") && ( $ui == 0 ) )
		{
			$count++;
			$ui = 1;
		}
		if ( ( $layer == "CAN") && ( $c == 0 ) )
		{
			$count++;
			$c = 1;
		}
		if ( ( $layer == "FLRY") && ( $f == 0 ) )
		{
			$count++;
			$f = 1;
		}
		if ( ( $layer == "USB") && ( $u == 0 ) )
		{
			$count++;
			$u = 1;
		}
	}
}
if ( $count != 0 )
{
	print "/** \brief Lower Layer array */\n";
	print "extern const Com_TxTriggerType Com_TxTrigger[$count];\n\n";
}
else
{
	print "/* no Lower Layer is used, Com_TxTrigger is not declared */\n\n";
}

print "/*------------------[Transmit Buffer declarations]---------------------------*/\n";
$msgidp = 0;
foreach ($messages as $msg)
{
	$msgprop = $config->getValue("/COM/" . $msg, "MESSAGEPROPERTY");
	$msgsize = $config->getValue("/COM/" . $msg . "/" . $msgprop, "SIZEINBITS");
	if ( ( strpos($msgprop,"SEND") > -1 ) && ( strpos($msgprop,"INTERNAL") > -1 ) )
	{
		$msgidp += ( ( $msgsize + 7 ) >> 3 );
	}
}

if ( $msgidp != 0 )
{
	print "/** \brief Transmission Internal Message Buffer */\n";
	print "extern uint8 Com_TxMsgIntBuf[$msgidp];\n\n";
}
else
{
	print "/* no internal buffer is needed, Com_TxMsgIntBuf is not defined */\n\n";
}

$pdumsgs = $config->getList("/COM","IPDU");
foreach ($pdumsgs as $pm)
{
	print "/** \brief Transmit External $pm PDU Buffer */\n";
	$pmsize = $config->getValue("/COM/" . $pm , "SIZEINBITS");
	$pmsize = ( ( $pmsize + 7 ) >> 3 );
	print "extern uint8 Com_TxMsgExtBuf_" . $pm . "[" . $pmsize . "];\n\n";
}
?>
/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_INTERNAL_CFG_H_ */

