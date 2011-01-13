/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

#ifndef _OS_CFG_H_
#define _OS_CFG_H_
/** \brief FreeOSEK Os Generated Configuration Header File
 **
 ** This file contents the generated configuration of FreeOSEK Os
 **
 ** \file Os_Cfg.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090719 v0.1.3 MaCe rename file to Os_
 * 20090424 v0.1.2 MaCe add counters defines
 * 20090128 v0.1.1 MaCe add MEMMAP off configuration
 * 20080810 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Definition of the  DeclareTask Macro */
#define DeclareTask(name)	void OSEK_TASK_ ## name (void)

#define OSEK_OS_INTERRUPT_MASK ((InterruptFlagsType)0xFFFFFFFFU)

/** \brief Task Definition */
#define InitTask 0
/** \brief Task Definition */
#define LedsTask 1
/** \brief Task Definition */
#define ButtonsTask 2

/** \brief Definition of the Application Mode AppMode1 */
#define AppMode1 0



/** \brief Definition of the Alarm IncrementSWCounter */
#define IncrementSWCounter 0
/** \brief Definition of the Alarm ActivateLedsTask */
#define ActivateLedsTask 1
/** \brief Definition of the Alarm ActivateButtonsTask */
#define ActivateButtonsTask 2

/** \brief Definition of the Counter HardwareCounter */
#define HardwareCounter 0
/** \brief Definition of the Counter SoftwareCounter */
#define SoftwareCounter 1

/** \brief OSEK_MEMMAP macro (DISABLE not MemMap is used for FreeOSEK, ENABLE
 ** MemMap is used for FreeOSEK) */
#define OSEK_MEMMAP DISABLE

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_DATA
#include "MemMap.h"
#endif


#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_DATA
#include "MemMap.h"
#endif

/*==================[external functions declaration]=========================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_CODE
#include "MemMap.h"
#endif
/** \brief Task Declaration of Task InitTask */
DeclareTask(InitTask) ATTRIBUTES();
/** \brief Task Declaration of Task LedsTask */
DeclareTask(LedsTask) ATTRIBUTES();
/** \brief Task Declaration of Task ButtonsTask */
DeclareTask(ButtonsTask) ATTRIBUTES();




#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_CFG_H_ */

