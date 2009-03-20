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
 * that communicate with FreeOSEK solely through the OpenSEK defined interface. 
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

#ifndef _ETH_INTERNAL_H_
#define _ETH_INTERNAL_H_
/** \brief OpenDRV Ethernet Internal Header File
 **
 ** \file Eth_Internal.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Eth
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
 * v0.1.0 20081129 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Eth_Cfg.h"
#include "Eth_Arch.h"
#include "uip.h"
#include "uip_arp.h"

/*==================[macros]=================================================*/
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/*==================[typedef]================================================*/
typedef struct {
	uint8	TxData;
	uint8 RxData;
} Eth_VarType;
	
/*==================[external data declaration]==============================*/
extern Eth_VarType Eth_Var;

/*==================[external functions declaration]=========================*/
extern void Eth_ipchksum(void);

extern void Eth_tcpchksum(void);

extern void Eth_add32(void);

extern void Eth_Send(void);

extern void Eth_Receive(void);

extern void Eth_Transmit
(
	char const * const msg,
	uint16 length
);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ETH_H_ */

