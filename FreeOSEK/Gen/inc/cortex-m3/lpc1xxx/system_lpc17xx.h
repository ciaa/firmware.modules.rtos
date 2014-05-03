/******************************************************************************
 * @file:    system_LPC17xx.h
 * @purpose: CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 *           for the NXP LPC17xx Device Series
 * @version: V1.0
 * @date:    25. Nov. 2008
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2008 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __SYSTEM_LPC17xx_H
#define __SYSTEM_LPC17xx_H


//added to match freeosek calling convention with my .h file
#define FIO4CLR GPIO4->FIOCLR
#define FIO4SET GPIO4->FIOSET
#define FIO4PIN GPIO4->FIOPIN
#define FIO4DIR GPIO4->FIODIR
#define FIO4MASK GPIO4->FIOMASK

#define FIO3CLR GPIO3->FIOCLR
#define FIO3SET GPIO3->FIOSET
#define FIO3PIN GPIO3->FIOPIN
#define FIO3DIR GPIO3->FIODIR
#define FIO3MASK GPIO3->FIOMASK

#define FIO2CLR GPIO2->FIOCLR
#define FIO2SET GPIO2->FIOSET
#define FIO2PIN GPIO2->FIOPIN
#define FIO2DIR GPIO2->FIODIR
#define FIO2MASK GPIO2->FIOMASK

#define FIO1CLR GPIO1->FIOCLR
#define FIO1SET GPIO1->FIOSET
#define FIO1PIN GPIO1->FIOPIN
#define FIO1DIR GPIO1->FIODIR
#define FIO1MASK GPIO1->FIOMASK

#define FIO0CLR GPIO0->FIOCLR
#define FIO0SET GPIO0->FIOSET
#define FIO0PIN GPIO0->FIOPIN
#define FIO0DIR GPIO0->FIODIR
#define FIO0MASK GPIO0->FIOMASK


//extern uint32_t SystemFrequency;    /*!< System Clock Frequency (Core Clock)  */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
//extern void SystemInit (void);
#endif
