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

/** \brief FreeOSEK Memory Mapping Header File
 **
 ** \file MemMap.h
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

/* MEMMAP_ERROR definition */
#define MEMMAP_ERROR

/* include user configurated memory mapping */
#include "MemMap_Cfg.h"

/* include arhcitecture dependent user configurated memory mapping */
#include "MemMap_Arch_Cfg.h"

#if (MEMMAP_GEN_MEMMAP_ARCH == MEMMAP_ENABLE)
/* include generic architecture dependent memory mapping */
#include "MemMap_Arch.h"
#endif

/* include user configurated section mapping */
#include "MemMap_Section_Cfg.h"

/* include architecture dependent user section mapping */
#include "MemMap_Section_Arch_Cfg.h"

#if (MEMMAP_GEN_SECTION_COMPILER == MEMMAP_ENABLE)
/* include compiler dependent section mapping */
#include "MemMap_Section_Compiler.h"
#endif

/* if MEMMAP_ERROR is still defined a compiler error shall be generated */
#ifdef MEMMAP_ERROR
#error Error the memory class was not found.
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

