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

#ifndef _CLK_ARCH_H_
#define _CLK_ARCH_H_
/** \brief Clk Arch Header File
 **
 ** Clk Arch Header File
 **
 ** \file Clk_Arch.h
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
 * v0.1.0 20090125 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "clk.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef struct {
	uint8 Config;
} Clk_ConfigArchType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CLK_ARCH_H_ */

