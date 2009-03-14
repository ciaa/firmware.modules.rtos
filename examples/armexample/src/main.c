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

/** \brief OpenSEK CancelAlarm Implementation File
 **
 ** This file implements the CancelAlarm API
 **
 ** \file CancelAlarm.c
 **
 **/

/** \addtogroup Examples Examples
 ** @{ */
/** \addtogroup ARMExample ARM Example
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
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
	Dio_Init((Dio_ConfigRefType)NULL);

	/* start cyclic alarm to activate task LedsTask */
	SetRelAlarm(ActivateLedsTask, 10, 10);

	/* start cyclic alarm to activate task ButtonsTask */
	SetRelAlarm(ActivateButtonsTask, 5, 10);

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

	switch (led0) {
		case 0:
			SET_LED0(0);
			led0 = 1;
			break;
		case 1:
			SET_LED0(1);
			led0 = 0;
			break;
		default:
			break;
	}

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
	if ( GET_BUT0() == DIO_HIGH )
	{
		led1 = 1;
	}
	if ( GET_BUT1() == DIO_HIGH )
	{
		led1 = 0;
	}

	/* Terminate Buttons Task */
	TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

