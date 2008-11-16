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

#ifndef _MEMMAP_ARCH_H_
#define _MEMMAP_ARCH_H_
/** \brief OpenSEK Posix Memory Mapping Header File
 **
 ** \file posix/MemMap_Arch.h
 **
 **/

/** \addtogroup OpenGEN
 ** @{ */
/** \addtogroup OpenGEN_Global
 ** \ingroup OpenGEN
 ** @{ */

/*
 * Initials	  Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081114 MaCe	initial version
 */

#ifdef OpenSEK_START_SEC_CODE
	#define START_SECTION_CODE
	#undef OpenSEK_START_SEC_CODE
#endif

#ifdef OpenSEK_STOP_SEC_CODE
	#define STOP_SECTION_CODE
	#undef OpenSEK_STOP_SEC_CODE
#endif

#ifdef OpenSEK_START_SEC_VAR
	#define START_SECTION_VAR
	#undef OpenSEK_START_SEC_VAR
#endif

#ifdef OpenSEK_STOP_SEC_VAR
	#define STOP_SECTION_VAR
	#undef OpenSEK_STOP_SEC_VAR
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MEMMAP_H_ */

