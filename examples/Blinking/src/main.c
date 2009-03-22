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
 * that communicate with FreeOSEK solely through the OpenSEK defined interface. 
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

/** \brief Blinking main
 **
 ** This file implements the Blinking example
 **
 ** \file main.c
 **
 **/

/** \addtogroup Examples Examples
 ** @{ */
/** \addtogroup Blinking Blinking
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090322 v0.1.1 MaCe correct comments of the file
 * 20090227 v0.1.0 MaCe initial version based on an LPC-E2468 blinking led demo
 */

/*==================[inclusions]=============================================*/
#include "os.h"		/* OSEK header file */
#include "Mcu.h"		/* MCU Driver header file */
#include "Dio.h"		/* DIO Driver header file */

/*==================[macros and definitions]=================================*/
#define SET_LED0(val)	Dio_WriteChannel(LED0, (val == 0 ) ? DIO_LOW : DIO_HIGH)
#define SET_LED1(val)	Dio_WriteChannel(LED1, (val == 0 ) ? DIO_LOW : DIO_HIGH)

#define GET_BUT0()		Dio_ReadChannel(BUT0)
#define GET_BUT1()		Dio_ReadChannel(BUT1)

/*==================[internal data declaration]==============================*/
uint8 led1;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief main function
 **
 ** Project main function. This function is called after the c conformance
 ** initialisation. This function shall call the StartOs in the right
 ** Application Mode. The StartOs API shall never return.
 **
 **/
int main
(
	void
)
{	
	/* Start OSEK */
	StartOs(AppMode1);
}

/** \brief Init Task
 **
 ** This task is called one time after every reset and takes care of
 ** the system initialization.
 **/
TASK(InitTask)
{
	/* init MCU Driver */
	Mcu_Init((Mcu_ConfigRefType)NULL);

	/* init Clock */
	(void)Mcu_InitClock((Mcu_ClockType)0);

	/* init DIO Driver */
	(void)Dio_Init((Dio_ConfigRefType)NULL);

	/* start cyclic alarm to activate task LedsTask every 250ms */
	SetRelAlarm(ActivateLedsTask, 250, 250);

	/* start cyclic alarm to activate task ButtonsTask every 250ms */
	/* first time will be called after 125ms to avoid both tasks
		to be activated on the same moment */
	SetRelAlarm(ActivateButtonsTask, 125, 250);

	/* Terminate Init Task */
	TerminateTask();
}

/** \brief Led Task
 **
 ** This task set the Board Leds:
 **  LED0 will blink every time the task is started
 **  LED1 can be turned on or of with the board buttons
 **/
TASK(LedsTask)
{
	static uint8 led0 = 0;
	
	/* check actual state of the led */
	switch (led0) {
		case 0:
			/* set the led off */
			SET_LED0(0);
			/* save led 0 status */
			led0 = 1;
			break;
		case 1:
			/* set the led on */
			SET_LED0(1);
			/* save led 0 status */
			led0 = 0;
			break;
		default:
			/* shall never happens */
			break;
	}

	/* set or clear the led1 depending on led1 variable */
	/* led1 variable will be set on the ButtonsTask Task */
	SET_LED1(led1);

	/* Terminate Leds Task */
	TerminateTask();
}

/** \brief Button Task
 **
 ** This task get the status of the 2 Buttons of the board.
 **/
TASK(ButtonsTask)
{

	/* check if Button 0 is low */
	if ( GET_BUT0() == DIO_LOW )
	{
		/* turn off the led */
		led1 = 1;
	}
	/* check if Button 1 is low */
	if ( GET_BUT1() == DIO_LOW )
	{
		/* turn on the led */
		led1 = 0;
	}

	/* Terminate Buttons Task */
	TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

