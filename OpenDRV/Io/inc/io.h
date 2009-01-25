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

#ifndef _IO_H_
#define _IO_H_
/** \brief Io Header File
 **
 ** Io Header File
 **
 ** \file io.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Io
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
 * v0.1.0 20090125 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Io_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef uint8f Io_ReturnType;

typedef struct {
   Io_ConfigArchType Io_Arch;
} Io_ConfigType;

typedef Io_ConfigType* Io_ConfigRefType;


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** TODO */
/* #define OpenDRV_IO_START_SEC_CODE
 * #include "MemMap.h" */

Io_ReturnType Io_Init(Io_ConfigRefType config);

/** TODO */
/* #define OpenDRV_IO_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _IO_H_ */

