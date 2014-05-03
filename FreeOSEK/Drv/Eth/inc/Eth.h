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

#ifndef _ETH_H_
#define _ETH_H_
/** \brief FreeOSEK Driver Ethernet Header File
 **
 ** This file shall be included by all files using any FreeOSEK Driver Ethernet API.
 **
 ** \file Eth.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Eth Ethernet
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Eth_Global Global
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

/*==================[macros]=================================================*/
/** \brief E_OK definition */
#ifndef E_OK
#define E_OK						0
#endif

/** \brief Eth timeout error definition */
#define E_ETH_TIMEOUT			1

/*==================[typedef]================================================*/
typedef uint8f Eth_ReturnType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Ethernet Driver main function
 **
 ** This function shall be called cyclicaly to process all Driver data.
 **/
extern void Eth_MainFunction(void);

/** \brief Ethernet Driver Init Service
 **
 ** This service shall be called before any other Eth Driver service to perform
 ** the Ethernet Driver initialisation. Calling any other Ethernet Driver
 ** service before this one can generate unexpected behaviours.
 **/
extern void Eth_Init(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ETH_H_ */

