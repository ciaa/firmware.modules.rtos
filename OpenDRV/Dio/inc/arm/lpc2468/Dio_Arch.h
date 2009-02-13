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

#ifndef _DIO_ARCH_H_
#define _IO_ARCH_H_
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
 * 20090213 v0.1.1 MaCe raname Io driver to Dio
 * 20090125 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#define IO_PORT_BITS_WIDTH	8

/*==================[typedef]================================================*/
typedef struct {
	uint8 Config;
} Io_ConfigArchType;

/** \brief Channel type definition */
typedef uint8 Io_PinType;

/** \brief Port type definition */
typedef uint8 Io_PortType;

/** \brief Port Group type definition */
typedef uint32 Io_PortGroupType;

/** \brief Level type definition */
typedef uint8 Io_PinLevelType;

/** \brief Port Level type definition */
typedef uint8 Io_PortLevelType;

/** \brief Port Group Value type definition */
typedef uint32 Io_PortGroupValueType;

/** \brief Port Group Value Reference type definition */
typedef Io_PortGroupValueType* Io_PortGroupValueRefType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_ARCH_H_ */

