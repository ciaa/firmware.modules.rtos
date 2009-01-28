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

#ifndef _TYPES_H_
#define _TYPES_H_
/** \brief OpenGEN Generic Types definition
 **
 ** \file Types.h
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
 * v0.1.1 20090128 MaCe add DISABLE and ENABLE macros
 * v0.1.0 20081126 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "Compiler.h"
#include "Types_Arch.h"

/*==================[macros]=================================================*/
#ifndef TYPES_NULL
#define TYPES_NULL
/** \brief NULL definition */
#define NULL ((void *)0)
#endif

#ifndef ENABLE
/** \brief ENABLE macro with the value 1 */
#define ENABLE 1
#elif ENABLE != 1
#error ENABLE defined somewhere else with a different value
#endif

#ifndef DISABLE
/** \brief DISABLE macro 2 */
#define DISABLE 2
#elif DISABLE != 2
#error DISABLE defined somewhere else with a different value
#endif

/*==================[typedef]================================================*/
#ifndef TYPES_BOOL
/** \brief bool type type definition */
typedef unsigned char bool;
#endif

#ifndef TYPES_UINT8
#define TYPES_UINT8
/** \brief default usigned 8 bits integer type definition */
typedef unsigned char uint8;
#endif

#ifndef TYPES_SINT8
#define TYPES_SINT8
/** \brief default signed 8 bits integer type definition */
typedef signed char sint8;
#endif

#ifndef TYPES_UINT8F
#define TYPES_UINT8F
/** \brief default unsigned 8 bits fast integer type definition */
typedef unsigned int uint8f;
#endif

#ifndef TYPES_SINT8F
#define TYPES_SINT8F
/** \brief default signed 8 bits fast integer type definition */
typedef signed int sint8f;
#endif

#ifndef TYPES_UINT16
#define TYPES_UINT16
/** \brief default unsigned 16 bits integer type definition */
typedef unsigned short uint16;
#endif

#ifndef TYPES_SINT16
#define TYPES_SINT16
/** \brief default signed 16 bits integer type definition */
typedef signed short sint16;
#endif

#ifndef TYPES_UINT16F
#define TYPES_UINT16F
/** \brief default unsigned 16 bits fast integer type definition */
typedef unsigned int uint16f;
#endif

#ifndef TYPES_SINT16F
#define TYPES_SINT16F
/** \brief default signed 16 bits fast integer type definition */
typedef signed int sint16f;
#endif

#ifndef TYPES_UINT32
#define TYPES_UINT32
/** \brief default unsigned 32 bits integer type definition */
typedef unsigned int uint32;
#endif

#ifndef TYPES_SINT32
#define TYPES_SINT32
/** \brief default signed 32 bits integer type definition */
typedef signed int sint32;
#endif      
            
#ifndef TYPES_UINT32F
#define TYPES_UINT32F
/** \brief default unsigned 32 bits fast integer type definition */
typedef unsigned int uint32f;
#endif

#ifndef TYPES_SINT32F
#define TYPES_SINT32F
/** \brief default signed 32 bits fast integer type definition */
typedef signed int sint32f;
#endif

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TYPES_H_ */

