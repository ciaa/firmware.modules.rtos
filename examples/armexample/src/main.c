/****************************************************************************
 *  
 * Project: LPC-E2468 blinking led demo
 *
 * Copyright: Ivan Vasilev, Olimex Ltd. All rights reserved.
 * 
 * File: $File main.c $
 * Description: Board-specific USB initialization
 * Developer: Ivan Vasilev, <ivan at l123.org>
 *
 * Last change: $Date: 2008-04-08 09:23:26 +0300 (вторник, 08 Април 2008) $
 * Revision: $Revision: 4 $
 * Id: $Id: main.c 4 2008-04-08 06:23:26Z Ivan $
 * Author: $Author: Ivan $
 *
 *  This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 ****************************************************************************/
 
#include "lpc2468.h"
#include "os.h"
#include "Mcu.h"
#include "Dio.h"

#define	STAT1	0x01
#define	STAT2	0x02

#define	LED_OFF		0x01
#define	LED_ON		0x02
#define	LED_TOGGLE	0x03

#define TRUE	1
#define	FALSE	0

void SetLed(int led, int state);

void InitPLL(void);
void feed(void);

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));


/* return TRUE if the button is pressed */
int But1Pressed(void)
{
	if (FIO2PIN & (1<<13)) return FALSE;
	else return TRUE;
}
int But2Pressed(void)
{
	if (FIO2PIN & (1<<21)) return FALSE;
	else return TRUE;
}

/* void Delay(void)
{
	int j;
	for (j = 0; j < 10000; j++ );
} */

/* return TRUE if the RTC is OK */
/* int TestRTC(void)
{
	int timeout = 1000000;
	RTC_CCR = 0;
	RTC_SEC = 0x00;
	RTC_CCR = 1<<1; clear the counter
	RTC_CCR = 1<<0 | 1<<4; enable the clock using the external xtal
	
	while (timeout--);
	timeout = RTC_CTC;
	
	if ((1550 < timeout) & (timeout < 1600)) return TRUE;
	
	return FALSE;
} */

int	main (void) {
	
	int	j;										// loop counter (stack variable)

	Mcu_Init((Mcu_ConfigRefType)NULL);
	Dio_Init((Dio_ConfigRefType)NULL);
	
	/* SetLed(STAT1, LED_OFF);
	if (TestRTC() == TRUE) 
	{
		SetLed(STAT2, LED_OFF);
		SetLed(STAT1, LED_ON);
	}
	else 
	{
		SetLed(STAT2, LED_ON);
	} */
		
	/* for (j = 0; j < 200000; j++); */
	
	// endless loop to toggle the green led
	StartOs(AppMode1);

	while (1) {
		
		for (j = 0; j < 5000; j++ )
		{
			if (But2Pressed() == TRUE) SetLed(STAT2, LED_ON);
			if (But1Pressed() == TRUE) SetLed(STAT2, LED_OFF);
		}
		
		SetLed(STAT1, LED_TOGGLE);
	}
}

TASK(InitTask)
{
	TerminateTask();
}

TASK(Task_Leds)
{
	TerminateTask();
}

TASK(Task_Keys)
{
	TerminateTask();
}

void SetLed(int led, int state)
{
	if (led == STAT1)
	{
		switch (state)
		{
			case LED_OFF:
				FIO4SET |= 1<<17;
				break;
			
			case LED_ON:
				FIO4CLR |= 1<<17;
				break;
			
			case LED_TOGGLE:
				if (FIO4PIN & (1<<17) )
				{
					SetLed(led, LED_ON);
				}
				else 
				{
					SetLed(led, LED_OFF);
				}
				break;
			default:
				break;
		}
	}
	else if (led == STAT2)
	{
		switch (state)
		{
			case LED_OFF:
				FIO4SET |= 1<<16;
				break;
			
			case LED_ON:
				FIO4CLR |= 1<<16;
				break;
			
			case LED_TOGGLE:
				if (FIO4PIN & (1<<16) )
				{
					SetLed(led, LED_ON);
				}
				else 
				{
					SetLed(led, LED_OFF);
				}
				break;
			default:
				break;
		}
	}
}
/*  Stubs for various interrupts (may be replaced later)  */
/*  ----------------------------------------------------  */

void IRQ_Routine (void) {
	while (1) ;	
}

void FIQ_Routine (void)  {
	while (1) ;	
}


void SWI_Routine (void)  {
	while (1) ;	
}


void UNDEF_Routine (void) {
	while (1) ;	
}
