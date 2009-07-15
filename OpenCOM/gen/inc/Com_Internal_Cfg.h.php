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
/** \brief OpenCOM File to be Generated
 **
 ** \file Com_Internal_Cfg.h.php
 **
 **/
?>

#ifndef _COM_INTERNAL_CFG_H_
#define _COM_INTERNAL_CFG_H_
/** \brief OpenCOM Generated Configuration Header File
 **
 ** This file contents the generated configuration of OpenCOM
 **
 ** \file Com_Internal_Cfg.h
 **
 **/

/** \addtogroup OpenCOM
 ** @{ */ 
/** \addtogroup OpenCOM_Internal
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
/** \brief Error Checking Type */
/** TODO */
#define ERROR_CHECKING_TYPE ERROR_CHECKING_STANDARD

/*------------------[Message Objects macros declarations]---------------------*/
#define COM_MSG_PROP_TX_STAT_INT		0U
#define COM_MSG_PROP_TX_STAT_EXT		1U
#define COM_MSG_PROP_TX_ZERO_INT		2U
#define COM_MSG_PROP_TX_ZERO_EXT		3U
#define COM_MSG_PROP_RX_STAT_INT		4U
#define COM_MSG_PROP_RX_STAT_EXT		5U
#define COM_MSG_PROP_RX_ZERO_INT		6U
#define COM_MSG_PROP_RX_ZERO_EXT		7U

#define COM_MSG_TPROP_TRIGGERED		0U
#define COM_MSG_TPROP_PENDING			1U
#define COM_MSG_TPROP_AUTO				2U

#define COM_MSG_NOTIF_NONE				0U
#define COM_MSG_NOTIF_ATASK			1U
#define COM_MSG_NOTIF_SEVENT			2U
#define COM_MSG_NOTIF_CBACK			3U
#define COM_MSG_NOTIF_FLAG				4U

/*------------------[Network Message Objects macros declarations]-------------*/
/*------------------[PDU Message Objects macros declarations]-----------------*/
#define COM_TX_PDU_PERIODIC			0U
#define COM_TX_PDU_DIRECT				1U
#define COM_TX_PDU_MIXED				2U
#define COM_RX_PDU						3U

/*------------------[Lower Layers macros declarations]------------------------*/

/*==================[typedef]================================================*/
/*------------------[Identifier type definitions]----------------------------*/
/** \brief Network Message Identifier type definition */
typedef uint8 Com_NetMsgType;

/** \brief I-PDU type definition */
/** TODO uint8 or uint16 has to depend on the account of messages */
typedef uint8 Com_IPDUType;

/*------------------[Message Objects type definitions]----------------------*/
/** \brief Message Flags type definition
 **
 ** \param MsgProp indicates the message properties, valid values are:
 **			- COM_MSG_PROP_TX_STAT_INT
 **			- COM_MSG_PROP_TX_STAT_EXT
 **			- COM_MSG_PROP_TX_ZERO_INT
 **			- COM_MSG_PROP_TX_ZERO_EXT
 **			- COM_MSG_PROP_RX_STAT_INT
 **			- COM_MSG_PROP_RX_STAT_EXT
 **			- COM_MSG_PROP_RX_ZERO_INT
 **			- COM_MSG_PROP_RX_ZERO_EXT
 ** \param Type is the type fo the message valid values are:
 **			- COM_MSG_TPROP_TRIGGERED
 **			- COM_MSG_TPROP_PENDING
 **			- COM_MSG_TPROP_AUTO
 ** \param CType indicates the callback type
 **			- COM_MSH_NOTIF_NONE
 **			- COM_MSH_NOTIF_ATASK
 **			- COM_MSH_NOTIF_SEVENT
 **			- COM_MSH_NOTIF_CBACK
 **			- COM_MSH_NOTIF_FLAG
 **/
typedef struct {
	uint16 MsgProp : 3;
	uint16 TProp : 2;
	uint16 CType : 3;
} Com_MsgFlagsType;

/** \brief Transmit Message Object Const type definition
 **
 ** \param Flags	Transmit Flags, for more details see Com_MsgFlagsType type
 **					definition
 ** \param NetMsg indicates on which network the message will be transmitted,
 **					only used on external communication.
 ** \param Msg		indicates the related message, only used on internal
 **					communication
 **/
typedef struct {
	Com_MsgFlagsType Flags;
	Com_NetMsgType NetMsg;
	MessageIdentifier Msg;
	/* init value TODO */
} Com_TxMessageObjectConstType;

/** \brief Receive Message Object Const type definition
 **
 ** \param Flags	Receive Flags, for more details see Com_MsgFlagsType type
 **					definition
 **/
typedef struct {
	Com_MsgFlagsType Flags;
	/** TODO */
} Com_RxMessageObjectConstType;

/*------------------[Network Message Objects type definitions]--------------*/
/** \brief Network Message Flags type definition
 **
 ** \param Prop 		network message properties, valid valuesa are:
 **							- COM_NM_PROP_STATIC
 **							- COM_NM_PROP_DYNAMIC
 **							- COM_NM_PROP_ZERO
 ** \param BitOrd		bit ordering, valid values are:
 **							- COM_NM_BO_BIGENDIAN
 **							- COM_NM_BO_LITTLEENDIAN
 ** \param DataInt	network message data interpretation
 **							- COM_NM_DI_UNSIGNEDINTEGER
 **							- COM_NM_DI_BYTEARRAY
 ** \param Direction	network message data direction
 **							- COM_NM_DIR_RX
 **							- COM_NM_DIR_TX_TRIGGERED
 **							- COM_NM_DIR_TX_PENDING
 **							- COM_NM_DIR_TX_AUTO
 **/
typedef struct {
	uint16 Prop : 2;
	uint16 BitOrd : 1;
	uint16 DataInt : 1;
	uint16 Direction : 2;
} Com_NetMsgFlagsType;

/** \brief Transmit Network Message Const type definition
 **
 ** \param Flags	Network Message Flags, for more detailes see
 **					Com_NMsgFlagsType type definition
 ** \param Size	Size of the network message in bits
 ** \param Offset	Offset of the network message on the PDU
 ** \param IPDU	IPDU for this network message
 **/
typedef struct {
	Com_NetMsgFlagsType Flags;
	uint16 Size;
	uint16 Offset;
	Com_IPDUType IPDU;
} Com_TxNetworkMessageConstType;

/** \brief Receive Network Message Const type definition
 **
 ** \param Flags	Network Message Flags, for more detailes see
 **					Com_NMsgFlagsType type definition
 ** \param Size	Size of the network message in bits
 ** \param Offset	Offset of the network message on the PDU
 ** \param IPDU	IPDU for this network message
 **/
typedef struct {
	Com_NetMsgFlagsType	Flags;
	uint16 Size;
	uint16 Offset;
	Com_IPDUType IPDU;
} Com_RxNetworkMessageConstType;

/*------------------[PDU Message Objects type definitions]------------------*/
/** \brief IPDU Flags type definition
 **
 ** \param Prop is the property of the IPDU valid values are:
 **			- COM_TX_PDU_PERIODIC
 **			- COM_TX_PDU_DIRECT
 **			- COM_TX_PDU_MIXED
 **			- COM_RX_PDU
 **/
typedef struct {
	uint16 Prop : 2;
} Com_IPDUFlagsType;

/** \brief Transmit IPDU Object Const type definition
 **
 ** \param Size size in bits of the IPDU
 ** \param Flags IPDU flags, see Com_IPDUFlagsType type definition
 **/
typedef struct {
	uint16 Size;
	Com_IPDUFlagsType Flags;
	uint16 TimePeriod;
	uint16 TimeOffset;
	uint16 MinDelay;
	uint16 Timeout;
	uint8 Layer;
	uint16 LayerPDU;
} Com_TxPduObjectsConstType;

/** \brief Reception IPDU Object Const type definition
 **
 ** \param Flags IPDU flags, see Com_IPDUFlagsType type definition
 **/
typedef struct {
	Com_IPDUFlagsType Flags;
} Com_RxPduObjectsConstType;

/*------------------[Lower Layers type definitions]-------------------------*/
/** \brief Low Layer Tx Trigger Functions */
typedef void (*Com_TxTriggerType)(uint16 IPDU);

/*==================[external data declaration]==============================*/
/*------------------[Message Objects declarations]---------------------------*/
/** \brief Constants for the Message Receive Objects */
Com_RxMessageObjectConstType Com_RxMessageObjectsConst[];

/** \brief Constants for the Message Transmission Objects */
Com_TxMessageObjectConstType Com_TxMessageObjectsConst[];

/*------------------[Network Message Objects declarations]-------------------*/
/** \brief Constant for the Network Message Transmission */
Com_TxNetworkMessageConstType Com_TxNetworkMessageConst[];

/** \brief Constant for the Network Message Reception */
Com_RxNetworkMessageConstType Com_RxNetworkMessageConst[];

/*------------------[PDU Message Objects declarations]-----------------------*/
/** \brief Constants for the PDU Transmited */
Com_TxPduObjectsConstType Com_TxPduObjectsConst[];

/** \brief Constants for the PDU Received */
Com_RxPduObjectsConstType Com_RxPduObjectsConst[];

/*------------------[Lower Layers declarations]------------------------------*/
/** \brief Lower Layer array */
Com_TxTriggerType Com_TxTrigger[];

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_INTERNAL_CFG_H_ */

