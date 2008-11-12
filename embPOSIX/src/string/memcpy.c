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

/** \brief memcpy implementation file
 **
 ** This file implements the memcpy posix service.
 **
 ** \file memcpy.c
 **
 **/

/** \addtogroup embPOSIX
 ** @{ */
/** \addtogroup embPOSIX_string
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20081112 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "string.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#if (emPOSIX_STRING_MEMCPY == emPOSIX_FUNCTION)
void *memcpy
(
   void *restrict s1,
   const void *restrict s2,
   size_t n
)
{
	unsigned char *s = s2;
	unsigned char *d = s1;
	size_t count;

	/** TODO this function has to be replaced with a architecture specific macro */
	for(count = 0; count < n; count++)
	{
		d[count] = s[count];
	}

	return (void * )s1;
}
#endif /* #if (emPOSIX_STRING_MEMCPY == emPOSIX_FUNCTION) */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

