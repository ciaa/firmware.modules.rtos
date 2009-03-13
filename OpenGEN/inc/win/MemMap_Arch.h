/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking OpenSEK statically or dynamically with other modules is making a
 * combined work based on OpenSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of OpenSEK give
 * you permission to combine OpenSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with OpenSEK solely through the OpenSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for OpenSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of OpenSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
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
 ** \file win/MemMap_Arch.h
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

