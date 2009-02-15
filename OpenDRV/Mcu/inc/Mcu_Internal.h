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

#ifndef _MCU_INTERNAL_H_
#define _MCU_INTERNAL_H_
/** \brief Mcu Internal Header File
 **
 ** Mcu Internal Header File
 **
 ** \file Mcu_Internal.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu
 ** \ingroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu_Internal
 ** \ingroup OpenDRV_Mcu
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090215 v0.1.1 MaCe	raname the driver to Mcu
 * 20090124 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "lpc2468.h"
#include "Mcu.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** TODO */
/* #define OpenDRV_MCU_START_SEC_CODE
 * #include "MemMap.h" */

extern Mcu_ReturnType Mcu_Init_Arch(Mcu_ConfigRefType Config);

/** TODO */
/* #define OpenDRV_MCU_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MCU_INTERNAL_H_ */

