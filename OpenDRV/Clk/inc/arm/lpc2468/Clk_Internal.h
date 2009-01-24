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

#ifndef _CLK_INTERNAL_H_
#define _CLK_INTERNAL_H_
/** \brief Clk Internal Header File
 **
 ** Clk Internal Header File
 **
 ** \file Clk_Internal.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Clk
 ** \ingroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_CLk_Internal
 ** \ingroup OpenDRV_Clk
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20090124 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "clk.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#define OpenDRV_CLK_START_SEC_CODE
#include "MemMap.h"

extern Clk_ReturnType Clk_Init_Arch(Clk_ConfigRefType config) ATTRIBUTE();

#define OpenDRV_CLK_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CLK_INTERNAL_H_ */

