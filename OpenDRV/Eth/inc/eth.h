/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
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

#ifndef _ETH_H_
#define _ETH_H_
/** \brief OpenDRV Ethernet Header File
 **
 ** This file shall be included by all files using any OpenDRV Ethernet API.
 **
 ** \file eth.h
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
#include "Gen_Types.h"
#include "Eth_Cfg.h"
#include "Eth_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void Eth_ipchksum(void);

extern void Eth_tcpchksum(void);

extern void Eth_add32(void);

extern void Eth_Send(void);

extern void Eth_Receive(void);

extern void Eth_Transmit(void);

extern void Eth_MainFunction(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ETH_H_ */

