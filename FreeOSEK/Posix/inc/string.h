/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface.
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 *
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _STRING_H_
#define _STRING_H_
/** \brief Posix String Header File
 **
 ** \file string.h
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Posix
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081112 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Posix.h"
#include "string_Arch.h"

/*==================[macros]=================================================*/
#if (emPOSIX_STRING_MEMCPY == emPOSIX_MACRO)
#define memcpy(s1, s2, n) memcpy_arch(s1, s2, n)
#endif

#if (emPOSIX_STRING_MEMSET == emPOSIX_MACRO)
#define memset(s, c, n) memset_arch(s, c, n)
#endif

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#if (emPOSIX_STRING_MEMCPY == emPOSIX_FUNCTION)
/** \brief This function shall copy n bytes from s2 to s1
 **
 ** The memcpy() function shall copy n bytes from the object pointed to by s2
 ** into the object pointed to by s1. If copying takes place between objects
 ** that overlap, the behavior is undefined.
 **
 ** \return The memcpy() function shall return s1; no return value is reserved
 **			to indicate an error.
 **/
extern void* memcpy
(
	void *RESTRICT s1,
	const void *RESTRICT s2,
	size_t n
);
#endif /* #if (emPOSIX_STRING_MEMCPY == emPOSIX_FUNCTION) */

#if (emPOSIX_STRING_MEMSET == emPOSIX_FUNCTION)
/** \brief This function set bytes in memory
 **
 ** The memset() function shall copy c (converted to an unsigned char) into
 ** each of the first n bytes of the object pointed to by s.
 **
 ** \return The memset() function shall return s; no return value is reserved
 ** 			to indicate an error.
 **/
extern void* memset
(
	void * s,
	int c,
	size_t n
);
#endif /* #if (emPOSIX_STRING_MEMSET == emPOSIX_FUNCTION) */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _STRING_H_ */

