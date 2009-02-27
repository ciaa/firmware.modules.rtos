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

#ifndef _OSEK_INTERNAL_ARCH_CPU_H_
#define _OSEK_INTERNAL_ARCH_CPU_H_
/** \brief OpenSEK Internal Architecture Cpu Dependent Header File
 **
 ** \file arm/Osek_Internal_Arch_Cpu.h
 ** \arch arm/lpc2xxx
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20090227 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "lpc2468.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void StartOs_Arch_Cpu(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_CPU_H_ */

