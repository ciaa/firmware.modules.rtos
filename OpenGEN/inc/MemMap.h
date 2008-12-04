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

/** \brief OpenSEK Memory Mapping Header File
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

