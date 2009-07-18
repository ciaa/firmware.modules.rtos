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

#ifndef _OSEK_ARCH_H_
#define _OSEK_ARCH_H_
/** \brief FreeOSEK Architecture Dependent Header File
 **
 ** This file is included form os.h and defines macros
 ** and types which depends on the architecture.
 **
 ** \file arm7/Osek_Arch.h
 ** \arch arm7
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Global
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080725 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Enable All Interrupts Arch */
#define EnableAllInterrupts_Arch()	ResumeAllInterrupts_Arch()

/** \brief Disable All Interrupts Arch */
#define DisableAllInterrupts_Arch() SuspendAllInterrupts_Arch()

/** \brief Resume All Interrupts Arch */
#define ResumeAllInterrupts_Arch()						\
	{																\
		__asm__ __volatile__ (								\
			"mrs r7, CPSR								\t\n"	\
			"and r7, r7, #0xFFFFFF3F				\t\n"	\
			"msr CPSR, r7								\t\n"	\
			: : : "r7"											\
		);															\
	}

/** \brief Suspend All Interrupts Arch */
#define SuspendAllInterrupts_Arch()						\
	{																\
		__asm__ __volatile__ (								\
			"mrs r7, CPSR								\t\n"	\
			"orr r7, r7, #0xC0						\t\n"	\
			"msr CPSR, r7								\t\n"	\
			: : : "r7"											\
		);															\
	}
					\
/** \brief Resume OS Interrupts Arch */
#define ResumeOSInterrupts_Arch()						\
	{																\
	}

/** \brief Suspend OS Interrupts Arch */
#define SuspendOSInterrupts_Arch()					\
	{															\
	}

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
extern void ScheduleInterrupts(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_ARCH_H_ */

