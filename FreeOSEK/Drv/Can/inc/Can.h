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

#ifndef _CAN_H_
#define _CAN_H_
/** \brief FreeOEK CAN Header File
 **
 ** This file shall be included by all files using any OpenDRV CAN API.
 **
 ** \file Can.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Can Control Area Network
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
  * 20090426 v0.1.0 MaCe initial version
 */  

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Can_Cfg.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/** \brief CAN Config Type
 **
  ** This type is used to pass the CAN configuration.
  ** \param ConfigArch contents the hardware dependent CAN configuration
 **/
typedef struct {
	Can_ConfigArchType ConfigArch;
} Can_ConfigType;

/** \brief CAN Controller Configuration Type
 **
  ** This type is used to pass the CAN Controller configuration
  ** \param ControllerConfigArch contents the hardware dependent CAN Controller configuration
 **/
typedef struct {
	Can_ControllerConfigArchType ControllerConfigArch;
} Can_ControllerConfigType;

/** \brief CAN ID Type
 **
 ** This type is used to represent the CAN ID type
 **/
#if ( CAN_ID_TYPE == CAN_ID_STANDARD )
typedef uint16 Can_IdType;
#elif ( CAN_ID_TYPE == CAN_ID_EXTENDED )
typedef uint32 Can_IdType;
#else
#error CAN_ID_TYPE not defined to CAN_ID_STANDARD neither to CAN_ID_EXTENDED.
#endif

/** \brief CAN PDU type
 **
 ** This type is used to 
 **/
typedef struct {
	uint8* sdu;
	Can_IdType id;
	PduIdType swPduHandle;
	uint8 length;
} Can_PduType;

typedef enum {
	CAN_T_START = 0,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WEEKUP
} Can_StateTransitionType;

typedef enum {
	CAN_OK = 0,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief CAN driver init service
 **
 ** This CAN driver service shall be called to initialize the CAN driver. Calls
 ** to any other CAN driver service before initialization is not allowed.
 **
 ** \param[in] Config pointer to the CAN driver configuration
 **/
extern void Can_Init(const Can_ConfigType* Config);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CAN_H_ */


