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

#ifndef _MEMMAP_SECTION_ARCH_H_
#define _MEMMAP_SECTION_ARCH_H_
/** \brief OpenSEK Posix Section Mapping Header File
 **
 ** \file win/MemMap_Section_Arch.h
 ** \arch win
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
 * 20090306 v0.1.0 MaCe	initial version
 */

#ifdef START_SECTION_CODE
	__attribute__ ((section ("SEC_CODE"));
	#undef START_SECTION_CODE
	#undef MEMMAP_ERROR
#endif

#ifdef STOP_SECTION_CODE
	__attribute__ ((section ("SEC_INVALID"));
	#undef STOP_SECTION_CODE
	#undef MEMMAP_ERROR
#endif

#ifdef START_SECTION_VAR
   #undef START_SECTION_VAR
   #undef MEMMAP_ERROR
#endif

#ifdef STOP_SECTION_VAR
   #undef STOP_SECTION_VAR
   #undef MEMMAP_ERROR
#endif


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MEMMAP_H_ */

