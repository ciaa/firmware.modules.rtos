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

/** \brief OpenSEK Generated Internal Achitecture Configuration Implementation File
 **
 ** \file Osek_Internal_Arch_Cfg.c
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20080713 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
<?php
foreach ($tasks as $task)
{
	print "/** \brief $task context */\n";
	print "TaskContextType TaskContext" . $task . ";\n";
}
print "\n";

?>

InterruptType InterruptTable[INTERUPTS_COUNT] =
{
<?php
$intnames = $config->getList("/OSEK","ISR");
for ($loopi = 0; $loopi < 32; $loopi++)
{
	if ($loopi<8)
	{
		switch($loopi)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				print "	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt $loopi */\n";
				break;
			case 4:
				print "	OSEK_ISR_HWTimer0, /* HW Timer 0 Interrupt handler */\n";
				break;
			case 5:
				print "	OSEK_ISR_HWTimer1, /* HW Timer 1 Interrupt handler */\n";
				break;
			case 6:
			case 7:
				print "	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt $loopi */\n";
				break;
		}
	}
	else
	{
		$flag = false;
		foreach ($intnames as $int)
		{
			$inttype = $config->getValue("/OSEK/" . $int,"INTERRUPT");
			$intcat = $config->getValue("/OSEK/" . $int,"CATEGORY");
			switch($inttype)
			{
				case "INT_CANRX":
					if($loopi == 8)
					{
						if($intcat == "1")
						{
							print "	OSEK_ISR_$int, /* interrupt handler $loopi */\n";
							$flag = true;
						}
						elseif($intcat == "2")
						{
							print "	OSEK_ISR2_$int, /* interrupt handler $loopi */\n";
							$flag = true;
						}
						else
						{
							error("Interrupt $int type $inttype has an invalid category $intcat");
						}
					}
					break;
				case "INT_CANTX":
					if($loopi == 9)
					{
						if($intcat == "1")
						{
							print "	OSEK_ISR_$int, /* interrupt handler $loopi */\n";
							$flag = true;
						}
						elseif($intcat == "2")
						{
							print "	OSEK_ISR2_$int, /* interrupt handler $loopi */\n";
							$flag = true;
						}
						else
						{
							error("Interrupt $int type $inttype has an invalid category $intcat");
						}
					}
					break;
			}
		}
		if ($flag == false)
		{
			print "	OSEK_ISR_NoHandler, /* no interrupt handler for interrupt $loopi */\n";
		}
	}
}
?>
};

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

