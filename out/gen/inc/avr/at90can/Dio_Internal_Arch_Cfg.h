/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2011, Mariano Cerdeiro
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


#ifndef _DIO_INTERNAL_ARCH_CFG_H_
#define _DIO_INTERNAL_ARCH_CFG_H_
/** \brief DRV DIO Internal Arch Generated Configuration Header File
 **
 ** This file contents the generated configuration of the IO Driver
 **
 ** \file Dio_Internal_Arch_Cfg.h
 **/

/** \addtogroup FreeOSEK
 ** @{ */ 
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20110113 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Dio Port 0 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT0_STATE	DISABLE

/** \brief Dio Port 1 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT1_STATE	DISABLE

/** \brief Dio Port 2 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT2_STATE	ENABLE

/** \brief Dio Port 3 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT3_STATE	DISABLE

/** \brief Dio Port 4 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT4_STATE	DISABLE

/** \brief Dio Port 5 state
 **
 ** if ENABLE the port will be used in Dio Driver
 ** if DISABLE the port will not be used in Dio Driver
 **/
#define DIO_PORT5_STATE	ENABLE

/** \brief Mask of the Dio Port 0
 **
 ** bit n 0 indicate the bit of the port 0 is not used
 ** bit n 1 indicate the bit of the port 0 is used
 **/
#define DIO_PORT0_MASK	0x0

/** \brief Mask of the Dio Port 1
 **
 ** bit n 0 indicate the bit of the port 1 is not used
 ** bit n 1 indicate the bit of the port 1 is used
 **/
#define DIO_PORT1_MASK	0x0

/** \brief Mask of the Dio Port 2
 **
 ** bit n 0 indicate the bit of the port 2 is not used
 ** bit n 1 indicate the bit of the port 2 is used
 **/
#define DIO_PORT2_MASK	0x18

/** \brief Mask of the Dio Port 3
 **
 ** bit n 0 indicate the bit of the port 3 is not used
 ** bit n 1 indicate the bit of the port 3 is used
 **/
#define DIO_PORT3_MASK	0x0

/** \brief Mask of the Dio Port 4
 **
 ** bit n 0 indicate the bit of the port 4 is not used
 ** bit n 1 indicate the bit of the port 4 is used
 **/
#define DIO_PORT4_MASK	0x0

/** \brief Mask of the Dio Port 5
 **
 ** bit n 0 indicate the bit of the port 5 is not used
 ** bit n 1 indicate the bit of the port 5 is used
 **/
#define DIO_PORT5_MASK	0x6

/** \brief Direction of the Dio Port 0
 **
 ** bit n 0 indicate the bit of the port 0 is an input
 ** bit n 1 indicate the bit of the port 0 is an output
 **/
#define DIO_PORT0_DIR	0x0

/** \brief Direction of the Dio Port 1
 **
 ** bit n 0 indicate the bit of the port 1 is an input
 ** bit n 1 indicate the bit of the port 1 is an output
 **/
#define DIO_PORT1_DIR	0x0

/** \brief Direction of the Dio Port 2
 **
 ** bit n 0 indicate the bit of the port 2 is an input
 ** bit n 1 indicate the bit of the port 2 is an output
 **/
#define DIO_PORT2_DIR	0x0

/** \brief Direction of the Dio Port 3
 **
 ** bit n 0 indicate the bit of the port 3 is an input
 ** bit n 1 indicate the bit of the port 3 is an output
 **/
#define DIO_PORT3_DIR	0x0

/** \brief Direction of the Dio Port 4
 **
 ** bit n 0 indicate the bit of the port 4 is an input
 ** bit n 1 indicate the bit of the port 4 is an output
 **/
#define DIO_PORT4_DIR	0x0

/** \brief Direction of the Dio Port 5
 **
 ** bit n 0 indicate the bit of the port 5 is an input
 ** bit n 1 indicate the bit of the port 5 is an output
 **/
#define DIO_PORT5_DIR	0x6


/** \brief Init value for Port 0 */
#define DIO_PORT0_INIT	0

/** \brief Init value for Port 1 */
#define DIO_PORT1_INIT	0

/** \brief Init value for Port 2 */
#define DIO_PORT2_INIT	0

/** \brief Init value for Port 3 */
#define DIO_PORT3_INIT	0

/** \brief Init value for Port 4 */
#define DIO_PORT4_INIT	0

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_INTERNAL_ARCH_CFG_H_ */

