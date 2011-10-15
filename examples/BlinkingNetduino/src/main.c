/* Copyright 2011 Tamas Kenderes
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

/** \brief BlinkingNetduino main
 **
 ** This file implements the BlinkingNetduino example
 **
 ** \file BlinkingNetduino/src/main.c
 **
 **/

/** \addtogroup Examples Examples
 ** @{ */
/** \addtogroup BlinkingNetduino BlinkingNetduino
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.0 KT	initial version based on the FreeOSEK Blinking example
 */

/*==================[inclusions]=============================================*/
#include "os.h"		/* OSEK header file */
#include "Mcu.h"		/* MCU Driver header file */
#include "Dio.h"		/* DIO Driver header file */

/*==================[macros and definitions]=================================*/
#define SET_LED0(val)	Dio_WriteChannel(LED0, (val == 0) ? DIO_LOW : DIO_HIGH)

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief main function
 **
 ** Project main function. This function is called after the C conformance
 ** initialization. This function shall call the StartOS() in the right
 ** Application Mode. The function StartOS() shall never return.
 **
 **/
int main
(
	void
)
{
	/* init MCU Driver */
	Mcu_Init((Mcu_ConfigRefType)NULL);

	/* init Clock */
	(void)Mcu_InitClock((Mcu_ClockType)0);

	/* init DIO Driver */
	(void)Dio_Init((Dio_ConfigRefType)NULL);

	/* Start OSEK */
	StartOS(AppMode1);
}

/** \brief Init Task
 **
 ** This task is called one time after every reset and takes care of
 ** the system initialization.
 **/
TASK(InitTask)
{
	/* Insert code here */

	/* Terminate Init Task */
	TerminateTask();
}

/** \brief LED Task
 **
 ** This task toggles the LED.
 **/
TASK(LedTask)
{
	static uint8 led0 = 0;
	
	/* check actual state of the LED */
	switch (led0) {
		case 0:
			/* turn off the LED */
			SET_LED0(1);
			/* save LED status */
			led0 = 1;
			break;
		case 1:
			/* turn on the LED */
			SET_LED0(0);
			/* save LED status */
			led0 = 0;
			break;
		default:
			/* shall never happen */
			break;
	}

	/* Terminate Leds Task */
	TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

