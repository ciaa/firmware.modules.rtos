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
 ** \file posix/StartOs_Arch.c
 ** \arch posix
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
	uint8_least loopi;

	/* init every task */
	for( loopi = 0; loopi < TASKS_COUNT; loopi++)
	{
		/* init stack */
		TasksConst[loopi].TaskContext->uc_stack.ss_sp = TasksConst[loopi].StackPtr;		/* set stack pointer */
		TasksConst[loopi].TaskContext->uc_stack.ss_size = TasksConst[loopi].StackSize;	/* set stack size */
		TasksConst[loopi].TaskContext->uc_stack.ss_flags = 0;										/* clear stack flags */

		/* create task context */
		(void)getcontext(TasksConst[loopi].TaskContext);	/* get actual context as start point */
	}

	/* set message queue attributes */
	
	MessageQueueAttr.mq_flags = O_NONBLOCK;
	MessageQueueAttr.mq_maxmsg = 10;
	MessageQueueAttr.mq_msgsize = 8;
	MessageQueueAttr.mq_curmsgs = 0;

	/* init interrupts queue*/
	/* open the Queue with followings options:
 	 *		- name as defined in the compiler macro PROJECT
 	 *		- queue is read only
 	 *		- create the queue
 	 *		- if the queue exists return an error
 	 *		- 
 	 */
	MessageQueue = mq_open("/OpenSEK", O_RDWR | O_CREAT | O_EXCL | O_NONBLOCK, 0666, &MessageQueueAttr);
	if (MessageQueue == (mqd_t)-1)
	{
		switch (errno)
		{
			case EINVAL:
				printf ("Error: Invalid argument\n");
				break;
			default:
				break;
		}
		printf ("Error: Message Queue for interrupts can not be configured, error number: %d\n",errno);
		sleep(2);
	}

	if (mq_getattr(MessageQueue, &MessageQueueAttr) == -1)
	{
		printf ("Error: Get Attribte error, error number: %d\n",errno);
      sleep(2);
	}
	else
	{
		//printf("Maxmsg: %d, Msgsize: %d, Curmsg: %d, Flags: %d\n", MessageQueueAttr.mq_maxmsg, MessageQueueAttr.mq_msgsize, MessageQueueAttr.mq_curmsgs, MessageQueueAttr.mq_flags);
		//sleep(2);
	}

	KillSignal.sa_handler = OsekKillSigHandler;
	sigemptyset(&KillSignal.sa_mask);
	KillSignal.sa_flags = 0;

	if (sigaction(SIGINT, &KillSignal, NULL) == -1)
	{
		printf("Error: SIGKILL can not be configured, error number: %d\n",errno);
	}

	MessageSignal.sa_handler = PosixInterruptHandler;
	(void)sigemptyset(&MessageSignal.sa_mask);
	MessageSignal.sa_flags = 0;

	if (sigaction(SIGUSR1, &MessageSignal, NULL) == -1)
	{
		printf("Error: SIGUSR1 can not be configured, error number: %d\n", errno);
	}

	SignalEvent.sigev_notify = SIGEV_SIGNAL;
	SignalEvent.sigev_signo = SIGUSR1;
	SignalEvent.sigev_value.sival_int = MessageQueue;
	SignalEvent.sigev_notify_function = NULL;
	SignalEvent.sigev_notify_attributes = NULL;

	if (mq_notify(MessageQueue, &SignalEvent) == -1)
	{
		printf("Error: Message Notification can not be activated, error: %d.\n",errno);
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
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

