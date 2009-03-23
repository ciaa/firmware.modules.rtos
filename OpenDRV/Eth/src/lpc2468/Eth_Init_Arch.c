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

/** \brief OpenDRV Etherner lpc24xx Init Service
 **
 ** This file implements the Ethernet lpc24xx Init Service
 **
 ** \file lpc24xx/Eth_Init.c
 ** \arch lpc24xx
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Ethernet
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081130 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Eth_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void Eth_Init_Arch
(
	void
)
{
	/* power on ethernet hardware */
	PCONP |= PCENET_MASK;

	/* remove soft reset condition from the MAC */
	MAC_MAC1 &= (uint32)~SOFT_RESET_MASK;

	MAC_MAC1	= 	RECEIVE_ENABLE_MASK |
					PASS_ALL_RECEIVED_FRAMES_MASK;

	MAC_MAC2 =	CRC_ENABLE_MASK |
					PAD_CRC_ENABLE_MASK |
					VLAN_PAD_ENABLE_MASK;
					

	

	/* configure phy via MIIM interface of the MAC */
	
	/* select RMII or MII mode */
	/* configure transmit and receive DMA */
	/* configure MAC1, MAC2 etc. */
	/* Enable the receive and transmit dataphats */
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

