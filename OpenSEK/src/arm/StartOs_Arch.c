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

/** \brief OpenSEK StartOs Architecture Dependece Implementation File
 **
 ** This file implements the StartOs Arch API
 **
 ** \file arm/StartOs_Arch.c
 ** \arch ARM
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081116 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void StartOs_Arch(void)
{
	uint8f loopi;

	/* init every task */
	for( loopi = 0; loopi < TASKS_COUNT; loopi++)
	{
		/* init stack */
		TasksConst[loopi].TaskContext->reg_r13 = (uint32)TasksConst[loopi].StackPtr + TasksConst[loopi].StackSize;

		/* init entry point */
		TasksConst[loopi].TaskContext->reg_r15 = (uint32) TasksConst[loopi].EntryPoint;

		/* init program status register */
		TasksConst[loopi].TaskContext->reg_cpsr = 0x000000d3; /** ?? TODO */

		/* init all registers to 0 */
		TasksConst[loopi].TaskContext->reg_r0 = 0;
		TasksConst[loopi].TaskContext->reg_r1 = 0;
		TasksConst[loopi].TaskContext->reg_r2 = 0;
		TasksConst[loopi].TaskContext->reg_r3 = 0;
		TasksConst[loopi].TaskContext->reg_r4 = 0;
		TasksConst[loopi].TaskContext->reg_r5 = 0;
		TasksConst[loopi].TaskContext->reg_r6 = 0;
		TasksConst[loopi].TaskContext->reg_r7 = 0;
		TasksConst[loopi].TaskContext->reg_r8 = 0;
		TasksConst[loopi].TaskContext->reg_r9 = 0;
		TasksConst[loopi].TaskContext->reg_r10 = 0;
		TasksConst[loopi].TaskContext->reg_r11 = 0;
		TasksConst[loopi].TaskContext->reg_r12 = 0;
		TasksConst[loopi].TaskContext->reg_r14 = 0;
	}

	/* call CPU dependent initialisation */
	StartOs_Arch_Cpu();

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

