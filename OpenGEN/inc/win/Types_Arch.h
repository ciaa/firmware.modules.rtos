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

#ifndef _TYPES_ARCH_H_
#define _TYPES_ARCH_H_
/** \brief OpenGEN Architecture Types definition
 **
 ** \file win/Types_Arch.h
 ** \arch win
 **
 **/

/** \addtogroup OpenGEN
 ** @{ */
/** \addtogroup OpenGEN_Global
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090306 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#ifndef TYPES_NULL
#define TYPES_NULL
/** \brief NULL definition */
#define NULL ((void *)0)
#else
#error NULL defined before
#endif

/*==================[typedef]================================================*/
#ifndef TYPES_BOOL
#define TYPES_BOOL
/** \brief bool type type definition */
typedef unsigned char bool;
#else
#error bool defined before
#endif

#ifndef TYPES_UINT8
#define TYPES_UINT8
/** \brief usigned 8 bits integer type definition */
typedef unsigned char uint8;
#else
#error uint8 defined before
#endif

#ifndef TYPES_SINT8
#define TYPES_SINT8
/** \brief signed 8 bits integer type definition */
typedef signed char sint8;
#else
#error sint8 defined before
#endif

#ifndef TYPES_UINT8F
#define TYPES_UINT8F
/** \brief unsigned 8 bits fast integer type definition */
typedef unsigned int uint8f;
#else
#error uint8f defined before
#endif

#ifndef TYPES_SINT8F
#define TYPES_SINT8F
/** \brief signed 8 bits fast integer type definition */
typedef signed int sint8f;
#else
#error sint8f defined before
#endif

#ifndef TYPES_UINT16
#define TYPES_UINT16
/** \brief unsigned 16 bits integer type definition */
typedef unsigned short uint16;
#else
#error uint16 defined before
#endif

#ifndef TYPES_SINT16
#define TYPES_SINT16
/** \brief signed 16 bits integer type definition */
typedef signed short sint16;
#else
#error sint16 defined before
#endif

#ifndef TYPES_UINT16F
#define TYPES_UINT16F
/** \brief unsigned 16 bits fast integer type definition */
typedef unsigned int uint16f;
#else
#error uint16f defined before
#endif

#ifndef TYPES_SINT16F
#define TYPES_SINT16F
/** \brief signed 16 bits fast integer type definition */
typedef signed int sint16f;
#else
#error uint16f defined before
#endif

#ifndef TYPES_UINT32
#define TYPES_UINT32
/** \brief unsigned 32 bits integer type definition */
typedef unsigned int uint32;
#else
#error uint32 defined before
#endif

#ifndef TYPES_SINT32
#define TYPES_SINT32
/** \brief signed 32 bits integer type definition */
typedef signed int sint32;
#else
#error sint32 defined before
#endif      
            
#ifndef TYPES_UINT32F
#define TYPES_UINT32F
/** \brief unsigned 32 bits fast integer type definition */
typedef unsigned int uint32f;
#else
#error uint32f defined before
#endif

#ifndef TYPES_SINT32F
#define TYPES_SINT32F
/** \brief signed 32 bits fast integer type definition */
typedef signed int sint32f;
#else
#error sint32 defined before
#endif

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TYPES_ARCH_H_ */

