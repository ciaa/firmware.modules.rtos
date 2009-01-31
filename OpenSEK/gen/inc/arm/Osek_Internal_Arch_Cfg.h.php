/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

#ifndef _OSEK_INTERNAL_ARCH_CFG_H_
#define _OSEK_INTERNAL_ARCH_CFG_H_
/** \brief OpenSEK Generated Internal Architecture Configuration Header File
 **
 ** This file content the internal generated architecture dependent
 ** configuration of OpenSEK.
 **
 ** \file Osek_Internal_Arch_Cfg.h
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
 * v0.1.0 20081116 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
/** TODO */
#define INTERUPTS_COUNT		32

/*==================[typedef]================================================*/
/** \brief Task Context Type */
typedef struct {
	uint32 reg_r0;
	uint32 reg_r1;
	uint32 reg_r2;
	uint32 reg_r3;
	uint32 reg_r4;
	uint32 reg_r5;
	uint32 reg_r6;
	uint32 reg_r7;
	uint32 reg_r8;
	uint32 reg_r9;
	uint32 reg_r10;
	uint32 reg_r11;
	uint32 reg_r12;
	uint32 reg_r13; /* stack pointer */
	uint32 reg_r14; /* link register */
	uint32 reg_r15; /* program counter */
	uint32 reg_cpsr; /* current program status register */
} TaskContextType;

/** \brief Task Context Type */
typedef TaskContextType* TaskContextRefType;

/** \brief InterruptType Type definition */
typedef void (*InterruptType)(void);

/*==================[external data declaration]==============================*/
extern InterruptType InterruptTable[INTERUPTS_COUNT];

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_CFG_H_ */
