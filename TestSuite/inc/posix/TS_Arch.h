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

#ifndef _TS_ARCH_H_
#define _TS_ARCH_H_
/** \brief TestSuite Architecture Header File
 **
 ** \file posix/TS_Arch.h
 **/

/** \addtogroup TestSuite
 ** @{ */
/** \addtogroup TestSuite_Global TestSuite Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081117 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#define ASSERT_ARCH(cond)	\
	{							\
		printf("Error the condition \"" # cond "\" in File: %s, in Line: %d is true.\n",__FILE__, __LINE__);  \
	}

#define TS_PrintResult_Arch(ts, result)   \
   {                                    	\
      printf("Test: %4d Result: ",(ts));	\
      switch(result)                      \
      {                                   \
         case TS_OK:                      \
            printf("OK\n");               \
            break;                        \
         case TS_FAILED:                  \
            printf("FAILED\n");           \
            break;                        \
         case TS_USER:                    \
            printf("USER\n");             \
            break;                        \
         case TS_NOTRUN:                  \
            printf("NOTRUN\n");           \
            break;                        \
         default:                         \
            printf("ERROR RESULT\n");     \
            break;                        \
      }												\
	}


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TS_ARCH_H_ */

