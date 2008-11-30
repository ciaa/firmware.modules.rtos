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

/** \brief OpenDRV Ethernet Main Function
 **
 ** This file implements the Ethernet Main Function service
 **
 ** \file Eth_MainFunction.c
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
void Eth_MainFunction
(
	void
)
{

	while (Eth_Var.Flags.TX_Data > 0)
	{
		Eth_Var.TX_Data--;
		Eth_Receive;
	}

	/* check if new data was received by the driver */
	while (Eth_Var.RX_Data > 0)
	{
		if(BUF->type == HTONS(UIP_ETHTYPE_IP))
		{
			uip_arp_ipin();
			uip_input();
			if (uip_len > 0)
			{
				uip_arp_out();
				Eth_Transmit();
			}
		}
		else if (BUF->type == HTONS(UIP_ETHTYPE_ARP))
		{
			uip_arp_arpin();
			if (uip_len > 0)
			{
				Eth_Transmit();
			}
		}
		else
		{
			
		}
		
		Eth_Var.RX_Data--;
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

