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

/** \brief FreeOSEK Driver Etherner lpc2468 Internal Service
 **
 ** This file implements the Ethernet lpc2468 Internal Service
 **
 ** \file lpc2468/Eth_Internal_Arch.c
 ** \arch lpc2468
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Eth
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Eth_Internal Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090323 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Eth_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
/** \brief PHY timeout for reading and writing of registers */
static uint32 Eth_PhyTimeout;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
extern Eth_ReturnType Eth_PhySetTimeout
(
	uint32 timeout
)
{
	/* set the timeout */
	Eth_PhyTimeout = timeout;
}

extern Eth_ReturnType Eth_PhyWrite
(
	uint8 phy,
	uint8 add,
	uint16 val
)
{
	Eth_ReturnType ret = E_OK;
	uint32 timeout = 0;

	/* start write */
	MAC_MCMD = 0;

	/* select phy addresse and register address to be written */
	MAC_MADR = ( ( ( phy & 0x1f ) << 8 ) | ( (add & 0x1f ) << 0 ) );

	/* set value to be written */
	MAC_MWTD = val;

	/* wait until the value was written or timeout */
	while ( ( MAC_MIND & BUSY_MASK != 0 ) &&
			  ( timeout < Eth_PhyTimeout ) )
	{
		/* increment timeout */
		timeout++;
	}

	/* if still busy it was a timeout */
	if ( MAC_MIND & BUSY_MASK != 0 )
	{
		/* set timeout error */
		ret = E_ETH_TIMEOUT;
	}

	return ret;	
}

extern Eth_ReturnType Eth_PhyRead
(
	uint8 phy,
	uint8 add,
	uint16* val
)
{
	Eth_ReturnType ret = E_OK;
	uint32 timeout = 0;

	/* start read */
	MAC_MCMD = 1;

	/* select phy addresse and register addresse to be readed */
	MAC_MADR = ( ( ( phy & 0x1f ) << 8 ) | ( (add & 0x1f ) << 0 ) );

	/* wait until the value was readed or a timeout occurs */
	while ( ( MAC_MIND & BUSY_MASK != 0 ) &&
			  ( timeout < Eth_PhyTimeout ) )
	{
		/* increment timeout */
		timeout++;
	}

	/* if still busy it was a timeout */
	if ( MAC_MIND & BUSY_MASK != 0 )
	{
		/* set timeout error */
		ret = E_ETH_TIMEOUT;
	}
	else
	{
		/* get the value */
		*val = (uint16) MAC_MRDD;
	}

	return ret;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

