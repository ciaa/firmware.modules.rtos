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

#ifndef _ETH_INTERNAL_ARCH_H_
#define _ETH_INTERNAL_ARCH_H_
/** \brief OpenDRV Ethernet Internal Arch Header File
 **
 ** \file Eth_Internal_Arch.h
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

/** \brief Mask values for MAC1 register */
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

/** \brief Mask values for MAC2 register */
#define FULL_DUPLEX_MASK						0x00000001
#define FRAME_LENGTH_CHECHKING_MASK			0x00000002
#define HUGE_FRAME_ENABLE_MASK				0x00000004
#define DELAY_CRC_MASK							0x00000008
#define CRC_ENABLE_MASK							0x00000010
#define PAD_CRC_ENABLE_MASK					0x00000020
#define VLAN_PAD_ENABLE_MASK					0x00000040
#define AUTO_DETECT_PAD_ENABLE_MASK			0x00000080
#define PURE_PREAMBLE_ENFORCEMENT_MASK		0x00000100
#define LONG_PREAMBLE_ENFORCEMENT_MASK		0x00000200
#define NO_BACKOFF_MASK							0x00001000
#define BACK_PRESSURE_NO_BACKOFF_MASK		0x00002000
#define EXCESS_DEFER_MASK						0x00004000

/** \brief Mask values for MIND register */
#define BUSY_MASK									0x00000001

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Ethernet Driver Init Service
 **
 ** This service shall be called from the Eth_Init service to perform the
 ** architecture dependent initialisations.
 **
 ** This is an internal function, called only by the driver.
 **/
extern void Eth_Init_Arch
(
	void
);

/** \brief Set PHY read and write timeout
 **
 ** This service set the PHY timeout used for reading and writting.
 ** The time out is not in second neither other time unit also in
 ** status read unit.
 **
 ** This is an internal function, called only by the driver.
 **
 ** \param[in] timeout timeout to be set
 ** \return E_OK this interface returns always E_OK
 **/
extern Eth_ReturnType Eth_PhySetTimeout
(
	uint32 timeout
);

/** \brief Write PHY register
 **
 ** This service write the indicated value (val) into the indicated PHY
 ** address (phy) and register (add).
 **
 ** This is an internal function, called only by the driver.
 **
 ** \param[in] phy physical address
 ** \param[in] add register address
 ** \param[in] val value to be written
 ** \return E_OK if no error occurs
 **			E_ETH_TIMEOUT if a timeout occurs
 **/
extern Eth_ReturnType Eth_PhyWrite
(
	uint8 phy,
	uint8 add,
	uint16 val
);

/** \brief Read PHY register
 **
 ** This service read into value (val) from the indicated PHY
 ** address (phy) and register (add).
 **
 ** This is an internal function, called only by the driver.
 **
 ** \param[in] phy physical address
 ** \param[in] add register address
 ** \param[in] val pointer to save the readed data
 ** \return E_OK if no error occurs
 **			E_ETH_TIMEOUT if a timeout occurs
 **/
extern Eth_ReturnType Eth_PhyRead
(
	uint8 phy,
	uint8 add,
	uint16* val
);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ETH_INTERNAL_ARCH_H_ */

