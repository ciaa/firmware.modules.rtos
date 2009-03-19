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

#ifndef _ETH_ARCH_H_
#define _ETH_ARCH_H_
/** \brief OpenDRV Ethernet Arch Header File
 **
 ** \file Eth_Arch.h
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
 * v0.1.0 20090317 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "lpc2468.h"	/* include processor header file */

/*==================[macros]=================================================*/
/** \brief Ethernet block power/clock control bit */
#define PCENET_MASK 0x40000000

#define RECEIVE_ENABLE_MASK					0x00000001
#define PASS_ALL_RECEIVED_FRAMES_MASK		0x00000002
#define RX_FLOW_CONTROL_MASK					0x00000004
#define TX_FLOW_CONTROL_MASK					0x00000008
#define LOOPBACK_MASK							0x00000010
#define RESET_TX_MASK							0x00000100
#define RESET_MCS_TX_MASK						0x00000200
#define RESET_RX_MASK							0x00000400
#define RESET_MCS_RX_MASK						0x00000800
#define SIMULATION_RESET_MASK					0x00004000
#define SOFT_RESET_MASK							0x00008000

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
void Eht_Init_Arch(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ETH_ARCH_H_ */

