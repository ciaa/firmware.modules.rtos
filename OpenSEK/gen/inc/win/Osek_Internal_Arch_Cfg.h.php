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
 * v0.1.0 20080713 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#define INTERUPTS_COUNT		32

/*==================[typedef]================================================*/
/** \brief Task Context Type */
typedef struct {
	uint32 tss_esp;
	uint32 tss_ebp;
   uint32 tss_eip;
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
