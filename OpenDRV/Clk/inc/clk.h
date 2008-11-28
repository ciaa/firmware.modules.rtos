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

#ifndef _CLK_H_
#define _CLK_H_
/** \brief OpenDRV Clock Header File
 **
 ** This file shall be included by all files using any OpenDRV Clock API.
 **
 ** \file clk.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Clk
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
 * v0.1.0 20081126 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Gen_Types.h"
#include "Clk_Cfg.h"
#include "Clk_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef uint8 Clk_ReturnType;

typedef struct {
	Clk_ConfigArchType Clk_Arch;
} Clk_ConfigType;

typedef Clk_ConfigType* Clk_ConfigRefType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern Clk_ReturnType Clk_Init(Clk_ConfigRefType config);

extern Clk_RetunrType Clk_ReInit(Clk_ConfigRefType config);

extern Clk_ReturnType Clk_DeInit();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CLK_H_ */

