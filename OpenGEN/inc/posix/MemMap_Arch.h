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
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081114 MaCe	initial version
 */

/*==================[OpenSEK OS memory section definiton]====================*/
#ifdef OPENSEK_START_SEC_CODE
	#define START_SECTION_CODE
	#undef OPENSEK_START_SEC_CODE
#endif

#ifdef OPENSEK_END_SEC_CODE
	#define END_SECTION_CODE
	#undef OPENSEK_END_SEC_CODE
#endif

#ifdef OPENSEK_START_SEC_VAR_NOINIT_BOOLEAN
	#define START_SECTION_NOINIT_VAR
	#undef OPENSEK_START_SEC_VAR_NOINIT_BOOLEAN
#endif

#ifdef OPENSEK_END_SEC_VAR_NOINIT_BOOLEAN
	#define END_SECTION_VAR_NOINIT
	#undef OPENSEK_END_SEC_VAR_NOINIT_BOOLEAN
#endif

#ifdef OPENSEK_START_SEC_VAR_NOINIT_8BIT
	#define START_SECTION_NOINIT_VAR
	#undef OPENSEK_START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_NOINIT_8BIT
	#define END_SECTION_VAR_NOINIT
	#undef OPENSEK_END_SEC_VAR_NOINIT_8BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_NOINIT_16BIT
	#define START_SECTION_NOINIT_VAR
	#undef OPENSEK_START_SEC_VAR_NOINIT_16BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_NOINIT_16BIT
	#define END_SECTION_VAR_NOINIT
	#undef OPENSEK_END_SEC_VAR_NOINIT_16BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_NOINIT_32BIT
	#define START_SECTION_NOINIT_VAR
	#undef OPENSEK_START_SEC_VAR_NOINIT_32BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_NOINIT_32BIT
	#define END_SECTION_VAR_NOINIT
	#undef OPENSEK_END_SEC_VAR_NOINIT_32BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SECTION_NOINIT_VAR
	#undef OPENSEK_START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef OPENSEK_END_SEC_VAR_NOINIT_UNSPECIFIED
	#define END_SECTION_VAR_NOINIT
	#undef OPENSEK_END_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef OPENSEK_END_SEC_VAR_POWER_ON_INIT_BOOLEAN
   #define END_SECTION_VAR_POWER_ON_INIT
   #undef OPENSEK_END_SEC_VAR_POWER_ON_INIT_BOOLEAN
#endif

#ifdef OPENSEK_START_SEC_VAR_POWER_ON_INIT_8BIT
   #define START_SECTION_POWER_ON_INIT_VAR
   #undef OPENSEK_START_SEC_VAR_POWER_ON_INIT_8BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_POWER_ON_INIT_8BIT
   #define END_SECTION_VAR_POWER_ON_INIT
   #undef OPENSEK_END_SEC_VAR_POWER_ON_INIT_8BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_POWER_ON_INIT_16BIT
   #define START_SECTION_POWER_ON_INIT_VAR
   #undef OPENSEK_START_SEC_VAR_POWER_ON_INIT_16BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_POWER_ON_INIT_16BIT
   #define END_SECTION_VAR_POWER_ON_INIT
   #undef OPENSEK_END_SEC_VAR_POWER_ON_INIT_16BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_POWER_ON_INIT_32BIT
   #define START_SECTION_POWER_ON_INIT_VAR
   #undef OPENSEK_START_SEC_VAR_POWER_ON_INIT_32BIT
#endif

#ifdef OPENSEK_END_SEC_VAR_POWER_ON_INIT_32BIT
   #define END_SECTION_VAR_POWER_ON_INIT
   #undef OPENSEK_END_SEC_VAR_POWER_ON_INIT_32BIT
#endif

#ifdef OPENSEK_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define START_SECTION_POWER_ON_INIT_VAR
   #undef OPENSEK_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#endif

#ifdef OPENSEK_END_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define END_SECTION_VAR_POWER_ON_INIT
   #undef OPENSEK_END_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MEMMAP_H_ */

