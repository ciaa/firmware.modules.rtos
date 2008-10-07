/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

/** \brief OpenSEK Generated Configuration Implementation File
 **
 ** \file Osek_Cfg.c
 **/

/** \addtogroup OpenSEK
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20080909 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
<?php
$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
?>
unsigned int Osek_ErrorApi;

unsigned int Osek_ErrorParam1;

unsigned int Osek_ErrorParam2;

unsigned int Osek_ErrorParam3;

unsigned int Osek_ErrorRet;

<?php
}
?>

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */ /** @} doxygen end group definition */
/*==================[end of file]============================================*/

