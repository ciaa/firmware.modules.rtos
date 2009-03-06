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

/** \brief OpenSEK StartOs Architecture Dependece Implementation File
 **
 ** This file implements the StartOs Arch API
 **
 ** \file win/StartOs_Arch.c
 ** \arch win
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
 * 20080810 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void StartOs_Arch(void)
{
	uint8f loopi;
	   
	/* init every task */
	for( loopi = 0; loopi < TASKS_COUNT; loopi++)
	{
		/* init stack */
		ResetStack(loopi);

		/* set entry point */
      SetEntryPoint(loopi)
	}

	/* set event */
	MessageSignal.sa_handler = PosixInterruptHandler;
	(void)sigemptyset(&MessageSignal.sa_mask);
	MessageSignal.sa_flags = 0;

	if (sigaction(SIGUSR1, &MessageSignal, NULL) == -1)
	{
		printf("Error: SIGUSR1 can not be configured, error number: %d\n", errno);
	}
	
	/* create shared memory */
   if ((SharedMemory = shmget(1, sizeof(MessageQueueType), IPC_CREAT | 0666)) < 0) {
      printf("shmget error\n");
      exit(1);
   }
    
   /* atach to the segment */
   MessageQueue = (MessageQueueType*) shmat(SharedMemory, NULL, 0);
   if (MessageQueue == (MessageQueueType *) -1)
   {
      printf("shmat error\n");
      exit(1);
   }

	if (fork() == 0)
	{
		HWTimerFork(0);
	}

	if (fork() == 0)
	{
		HWTimerFork(1);
	}

	/* enable interrupts */
	InterruptState = 1;

	/* enable timer interrupt */
	InterruptMask = 16;
	
	SaveWinStack();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

