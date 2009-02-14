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

/** \brief Project Main Entry Point
 **
 ** main function implementation file
 **
 ** \file example01/src/main.c
 **
 **/

/** \addtogroup Examples Examples
 ** @{ */
/** \addtogroup Example1 Example 1
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20080812 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "os.h"
#include "stdio.h"

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
 ** initialisation. This function shall call the StartOs in the right
 ** Application Mode. The StartOs API shall never return.
 **
 **/
int main
(
	void
)
{
	StartOs(AppMode1);

	/* shall never return */
	while(1);

	return 0;
}

void ErrorHook(void)
{
	printf("ErrorHook was called\n");
	printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
	ShutdownOs(0);
}

ISR(CanRx)
{
}

ISR(CanTx)
{
}

ISR(NMI)
{
}

TASK(InitTask)
{
	/* init */

	/* ... */

	/* end init */

	ActivateTask(TaskA);
	TerminateTask();
}

TASK(TaskA)
{
	printf("TaskA is running\n");
	ChainTask(TaskB);
}

TASK(TaskB)
{
	printf("TaskB is running\n");
	ChainTask(TaskC);
}

TASK(TaskC)
{
	printf("TaskC is running\n");
	ChainTask(TaskA);
}

TASK(TaskD)
{
	TerminateTask();
}

TASK(TaskE)
{
	TerminateTask();
}

ALARMCALLBACK(AlarmCallback)
{

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

