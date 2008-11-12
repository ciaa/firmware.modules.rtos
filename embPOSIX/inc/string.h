/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of embPOSIX.
 *
 * embPOSIX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * embPOSIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with embPOSIX. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _STRING_H_
#define _STRING_H_
/** \brief Posix String Header File
 **
 ** \file string.h
 **/

/** \addtogroup embPOSIX embPOSIX
 ** @{ */
/** \addtogroup embPOSIX_string embPOSIX string
 ** \ingroup embPOSIX
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
#include "string_Cfg.h"

/*==================[macros]=================================================*/
#ifndef (emPOSIX_STRING_MEMCPY == emPOSIX_MACRO)
#define memcpy(s1, s2, n) memcpy_arch(s1, s2, n)
#endif

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#ifdef (emPOSIX_STRING_MEMCPY == emPOSIX_FUNCTION)
/** \brief This function shall copy n bytes from s2 to s1
 **
 ** The memcpy() function shall copy n bytes from the object pointed to by s2
 ** into the object pointed to by s1. If copying takes place between objects
 ** that overlap, the behavior is undefined.
 **
 ** \return The memcpy() function shall return s1; no return value is reserved
 **			to indicate an error.
 **/
extern void *memcpy
(
	void *restrict s1,
	const void *restrict s2,
	size_t n
);
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _STRING_H_ */

