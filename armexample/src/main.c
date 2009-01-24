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

#define	STAT1	0x01
#define	STAT2	0x02

#define	LED_OFF		0x01
#define	LED_ON		0x02
#define	LED_TOGGLE	0x03

#define TRUE	1
#define	FALSE	0

void SetLed(int led, int state);
void InitLeds(void);

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

void Delay(void)
{
	int j;
	for (j = 0; j < 10000; j++ );
}

/* return TRUE if the RTC is OK */
int TestRTC(void)
{
	int timeout = 1000000;
	RTC_CCR = 0;
	RTC_SEC = 0x00;
	RTC_CCR = 1<<1; /* clear the counter */
	RTC_CCR = 1<<0 | 1<<4; /* enable the clock using the external xtal */
	
	while (timeout--);
	timeout = RTC_CTC;
	
	if ((1550 < timeout) & (timeout < 1600)) return TRUE;
	
	return FALSE;
}

int	main (void) {
	
	int	j;										// loop counter (stack variable)
	InitPLL();
	
	SCS |= 1<<0; /* enable fast IO on ports 0&1 */
	
	InitLeds();
	
	SetLed(STAT1, LED_OFF);
	if (TestRTC() == TRUE) 
	{
		SetLed(STAT2, LED_OFF);
		SetLed(STAT1, LED_ON);
	}
	else 
	{
		SetLed(STAT2, LED_ON);
	}
		
	for (j = 0; j < 200000; j++);
	
	// endless loop to toggle the green led
	while (1) {
		
		for (j = 0; j < 5000; j++ )
		{
			if (But2Pressed() == TRUE) SetLed(STAT2, LED_ON);
			if (But1Pressed() == TRUE) SetLed(STAT2, LED_OFF);
		}
		
		SetLed(STAT1, LED_TOGGLE);
	}
}


#define PLL_MValue	11
#define PLL_NValue	0
#define CCLKDivValue	4
#define USBCLKDivValue	5

void InitPLL(void)  
{

	volatile unsigned long MValue;
	volatile unsigned long NValue;

	if ( PLLSTAT & (1 << 25) )
	{
		PLLCON = 1;			/* Enable PLL, disconnected */
		PLLFEED = 0xaa;
		PLLFEED = 0x55;
	}

	PLLCON = 0;				/* Disable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
    
	SCS |= 0x20;			/* Enable main OSC */
	while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

	CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

	PLLCFG = PLL_MValue | (PLL_NValue << 16);
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
      
	PLLCON = 1;				/* Enable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;

	CCLKCFG = CCLKDivValue;	/* Set clock divider */

	while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
	MValue = PLLSTAT & 0x00007FFF;
	NValue = (PLLSTAT & 0x00FF0000) >> 16;
	while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

	PLLCON = 3;				/* enable and connect */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Check connect bit status */
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

void InitLeds(void)
{
	SetLed(STAT1, LED_OFF);
	SetLed(STAT2, LED_OFF);
	
	FIO4DIR |= 1<<17; /* STAT1&2 as out */
	FIO4DIR |= 1<<16; 
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
