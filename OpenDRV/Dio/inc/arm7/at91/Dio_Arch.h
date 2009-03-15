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

#ifndef _DIO_ARCH_H_
#define _DIO_ARCH_H_
/** \brief DIO Arch Header File
 **
 ** DIO Arch Header File
 **
 ** \file Dio_Arch.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Dio
 ** \ingroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Dio_Internal
 ** \ingroup OpenDRV_Dio
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090219 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "at91rm92.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef struct {
	uint8 Config;
} Dio_ConfigArchType;

/** \brief Channel type definition */
/* \req DIO015 Parameters of type Dio_ChannelType contain the numeric ID of a
 * DIO channel. The mapping of the ID is implementation specific but not
 * configurable. */
typedef uint8 Dio_ChannelType;

/** \brief Port type definition */
/* \req DIO018 Parameters of type Dio_PortType contain the numeric ID of a DIO
 * port. The mapping of ID is implementation specific but not configurable. */
typedef uint8 Dio_PortType;

/** \brief Channel Group type definition */
/* \req DIO021 Dio_ChannelGroupType is the type for the definition of a channel
 * group, which consists of several adjoining channels within a port. */
typedef uint8 Dio_ChannelGroupType;

/** \brief Level type definition */
/* \req  DIO023 Dio_LevelType is the type for the possible levels that a DIO
 * channel can have (input or output). */
typedef uint8 Dio_LevelType;

/** \brief Port Level type definition */
/* \req DIO024 Dio_PortLevelType is the type for the value of a DIO port. */
typedef uint32 Dio_PortLevelType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_ARCH_H_ */

