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

#define COM_RX_MSG_NORMAL		0U
#define COM_RX_MSG_TRIGGERED	1U
#define COM_RX_MSG_PENDING		2U
#define COM_TX_MSG_NORMAL		3U
#define COM_TX_MSG_TRIGGERED	4U
#define COM_TX_MSG_PENDING		5U

/*==================[typedef]================================================*/
/** \brief I-PDU type definition */
/** TODO uint8 or uint16 has to depend on the account of messages */
typedef uint8 Com_IPDUType;

typedef struct {
	uint16 Type : 3;
} Com_MsgFlagsType;

typedef struct {
	Com_MsgFlagsType Flags;
} Com_TxMessageObjectConstType;

typedef struct {
	Com_MsgFlagsType Flags;
} Com_RxMessageObjectConstType;

/*==================[external data declaration]==============================*/
Com_RxMessageObjectConstType Com_RxMessageObjectsConst[];

Com_TxMessageObjectConstType Com_TxMessageObjectsConst[];

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_INTERNAL_CFG_H_ */

