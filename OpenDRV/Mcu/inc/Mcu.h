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

#ifndef _MCU_H_
#define _MCU_H_
/** \brief OpenDRV Mcu Header File
 **
 ** This file shall be included by all files using any OpenDRV Mcu API.
 **
 ** \file Mcu.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu
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
 * 20090215 v0.1.1 MaCe	raname the driver to Mcu
 * 20081126 v0.1.0 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Mcu_Cfg.h"
#include "Mcu_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef uint8 Mcu_ReturnType;

typedef struct {
	Mcu_ConfigArchType Mcu_Arch;
} Mcu_ConfigType;

typedef Mcu_ConfigType* Mcu_ConfigRefType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern Mcu_ReturnType Mcu_Init(Mcu_ConfigRefType Config);

extern Mcu_ReturnType Mcu_DeInit();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MCU_H_ */

