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

/** \brief Blinking main
 **
 ** This file implements the Blinking example
 **
 ** \file CarCombi/src/main.c
 **
 **/

/** \addtogroup Examples Examples
 ** @{ */
/** \addtogroup CarCombi Car Combi
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 200902522 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "os.h"		/* OSEK header file */
#include "Mcu.h"		/* MCU Driver header file */
#include "Dio.h"		/* DIO Driver header file */
#include "Pwm.h"		/* PWM Driver header file */
#include "Adc.h"		/* ADC Driver header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief main function
 **
 ** Project main function. This function is called after the c conformance
 ** initialisation. This function shall call the StartOS in the right
 ** Application Mode. The StartOS API shall never return.
 **
 **/
int main
(
	void
)
{	
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
	/* init MCU Driver */
	Mcu_Init((Mcu_ConfigRefType)NULL);

	/* init Clock */
	(void)Mcu_InitClock((Mcu_ClockType)NULL);

	/* init DIO Driver */
	(void)Dio_Init((Dio_ConfigType*)NULL);

	/* init PWM Driver */
	Pwm_Init((Pwm_ConfigType*)NULL);
	
	/* init ADC Driver */
	Adc_Init((Adc_ConfigType*)NULL);

	/* Task Activations oder:
	 *
	 * Task are activated at the indicated time frames to try to avoid the
	 * activation of two or more task at the same moment, avoidong
	 * latency time between the task activation and execution. 
	 *
	 * CarSimulationTask:	5ms, 15ms, 25ms, 35ms, ... , 65ms, 75ms, ... , 245ms, 255ms, ... , 455ms, 505ms, ...
	 * CombiTask:				20ms, 70ms, 120ms, 170ms, 220ms, 270ms, ..., 220ms, 270ms, ... , 470ms, 520ms, ...
	 * BlinkingLedsTask:		250ms, 500ms, 
	 */

	/* start cyclic alarm to activate task BlinkingLedsTask every 250ms */
	SetRelAlarm(ActivateBlinkingLedsTask, 250, 250);

	/* start cyclic alarm to activate task CombiTask every 50ms */
	/* first time will be called after 25ms to avoid tasks
		to be activated on the same moment */
	SetRelAlarm(ActivateCombiTask, 20, 50);

	/* start cyclic alarm to activate task CarSimulationTask every 10ms */
	/* first time will be called after 5ms to avoid tasks
		to be activated on the same moment */
	SetRelAlarm(ActivateCarSimulationTask, 5, 10);

	/* Terminate Init Task */
	TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

