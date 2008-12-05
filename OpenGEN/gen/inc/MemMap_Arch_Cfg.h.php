/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/** TODO in the future this file has to be generated from
 *  the configuration
 */


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

/** \brief OpenSEK Architecture Configurated Memory Mapping Header File
 **
 ** \file MemMap_Arch_Cfg.h
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

<?php

$mappings = $config->getList("/OpenGEN/MemMap","Mapping");

foreach ($mappings as $map)
{
	$name = $config->getValue("/OpenGEN/MemMap/" . $map, "NAME");
	$mapping = $config->getValue("/OpenGEN/MemMap/" . $map, "MAPPING");
	$section = $config->getValue("/OpenGEN/MemMap/" . $map, "SECTION");
	print "/* Mapping of $name */\n";
	print "#ifdef $mapping\n";
	print "	#define $section\n";
	print "	#undef $mapping\n";
	print "#endif\n\n";
}
	
?>

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

