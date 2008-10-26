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

/** \brief OpenSEK Internal Arch Implementation File
 **
 ** \file posix/Osek_Internal_Arch.c
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
 * 20080713 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8	InterruptState;

mqd_t MessageQueue;

struct mq_attr MessageQueueAttr;

struct sigaction MessageSignal;

struct sigaction KillSignal;

pid_t OsekProcessID;

struct sigevent SignalEvent;

uint32 OsekHWTimer0;

InterruptFlagsType InterruptFlag;

uint32 PosixStack;

uint32 OsekStack;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void CounterInterrupt(CounterType CounterID)
{
	uint8_least loopi;
	AlarmType AlarmID;

	/* increment counter */
	CountersVar[CounterID].Time = ( CountersVar[CounterID].Time + 1 ) % CountersConst[CounterID].MaxAllowedValue;

	/* for alarms on this counter */
	for(loopi = 0; loopi < CountersConst[CounterID].AlarmsCount; loopi++)
	{
		/* get alarm id */
		AlarmID = CountersConst[CounterID].AlarmRef[loopi];

		/* check if the alarm is eanble */
		if (AlarmsVar[AlarmID].AlarmState == 1)
		{
			/* decrement alarm time */
			AlarmsVar[AlarmID].AlarmTime--;

			/* check if alarm time was reached */
			if (AlarmsVar[AlarmID].AlarmTime == 0)
			{
				/* check if new alarm time has to be set */
				if(AlarmsVar[AlarmID].AlarmCycleTime == 0)
				{
					/* disable alarm if no cycle was configured */
					AlarmsVar[AlarmID].AlarmState = 0;
				}
				else
				{
					/* set new alarm cycle */
					AlarmsVar[AlarmID].AlarmTime = AlarmsVar[AlarmID].AlarmCycleTime;
				}

				/* check the alarm action */
				switch(AlarmsConst[AlarmID].AlarmAction)
				{
					case INCREMENT:
						/* call counter function */
						CounterInterrupt(AlarmsConst[AlarmID].AlarmActionInfo.Counter);
						break;
					case ACTIVATETASK:
						/* activate task */
						ActivateTask(AlarmsConst[AlarmID].AlarmActionInfo.TaskID);
						break;
					case ALARMCALLBACK:
						/* callback */
						if(AlarmsConst[AlarmID].AlarmActionInfo.CallbackFunction != NULL)
						{
							AlarmsConst[AlarmID].AlarmActionInfo.CallbackFunction();
						}
						break;
					case SETEVENT:
						/* set event */
						SetEvent(AlarmsConst[AlarmID].AlarmActionInfo.TaskID, AlarmsConst[AlarmID].AlarmActionInfo.Event);
						break;
					default:
						/* some error ? */
						break;
				}
			}
		}
	}
}

void OSEK_ISR_HWTimer0(void)
{
	CounterInterrupt(0);
}

void OSEK_ISR_HWTimer1(void)
{
	CounterInterrupt(1);
}

void PosixInterruptHandler(int status)
{
	uint8 msg[10];
	ssize_t mq_ret;

	mq_ret = mq_receive(MessageQueue, (char*)msg, sizeof(msg), NULL);
	if (mq_ret > 0)
	{
		if (msg[0] < 32)
		{
			/* printf("Interrupt: %d\n",msg[0]); */
			if ( (InterruptState) &&
				  ( (InterruptMask & (1 << msg[0] ) )  == 0 ) )
			{
				InterruptTable[msg[0]]();
			}
			else
			{
				InterruptFlag |= 1 << msg[0];
			}
		}

	}
	else
	{
		switch(errno)
		{
			case EAGAIN:
				printf("Queue Empty\n");
				break;
			case EBADF:
				printf("Not valued queue descriptor\n");
				break;
			case EMSGSIZE:
				printf("Message buffer to small\n");
				break;
			case EINTR:
				printf("Reception interrupted by a signal\n");
				break;
			default:
				printf("other error\n");
				break;
		}
		printf("Error by reading the Message Queue, returned value: %d, error number: %d\n",mq_ret,errno);
	}

	if (mq_notify(MessageQueue, &SignalEvent) == -1)
	{
		printf("Error: Message Notification can not be activated, error: %d.\n",errno);
		sleep(3);
	}
}

void HWTimerFork(uint8 timer)
{
	int mq_ret;
	char msg;
	struct timespec rqtp;

	if (timer <= 2)
	{
		msg = timer + 4;

		rqtp.tv_sec=0;
   	rqtp.tv_nsec=1000000;

		while(1)
		{
			mq_ret = mq_send(MessageQueue, &msg, sizeof(msg), 0);
			if (mq_ret < 0)
			{
				/* printf("Error HW Timer can not generate an interrupt\n"); */
			}
			nanosleep(&rqtp,NULL);
		}
	}

	exit(0);
}

void OsekKillSigHandler(int status)
{
	PreCallService();
	mq_unlink("/OpenSEK");
	exit(0);
	PostCallService();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

