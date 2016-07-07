/* Copyright 2016, Franco Bucafusco
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Os Internal Arch Implementation File
 **
 ** \file msp430/Os_Internal_Arch.c
 ** \arch msp430
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void * Osek_NewTaskPtr_Arch;
void * Osek_OldTaskPtr_Arch;

/*==================[internal data definition]===============================*/

TaskType TerminatingTask   = INVALID_TASK;
TaskType WaitingTask       = INVALID_TASK;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void ReturnHook_Arch(void)
{
   /* Tasks shouldn't return here... */
   while(1)
   {
      osekpause();
   }
}

void CheckTerminatingTask_Arch(void)
{
   if( INVALID_TASK != TerminatingTask )
   {
      InitStack_Arch( TerminatingTask );
   }
   TerminatingTask = INVALID_TASK;
}

/* Task Stack Initialization */
void InitStack_Arch(uint8 TaskID)
{
   uint16 * taskStack     = (uint16 *)TasksConst[TaskID].StackPtr;  /* stack bottom */

   int taskStackSizeWords = TasksConst[TaskID].StackSize/2;            /* calculation of the size of the stack in words units (16bits) */

   taskStack[taskStackSizeWords-1] = (uint16) TasksConst[TaskID].EntryPoint;    /*PC*/
   taskStack[taskStackSizeWords-2] = DEFAULT_SR;                             /*SP*/

   /* la ubicacion, reservando 13 registro para el cambio de contexto
   */
   *(TasksConst[TaskID].TaskContext) = &(taskStack[taskStackSizeWords - 14]);
}


void TickProcess()
{
   /* TODO this could be improved by accesing directly to the registers. remember that this handlers should be as fast as possible.*/
   Timer_A_clearCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_0);

   /* store the calling context in a variable */
   ContextType actualContext = GetCallingContext();

   /* set isr 2 context */
   SetActualContext(CONTEXT_ISR2);

#if (ALARMS_COUNT != 0)
   /* counter increment */
   static CounterIncrementType CounterIncrement = 1;
   (void)CounterIncrement; /* TODO remove me */

#if 0
   /* increment the disable interrupt conter to avoid enable the interrupts.
      Disabled because MSP430 AUTOMATICALLY DISABLES GLOBAL IRQ AT IRQ HANDLERS */
   IntSecure_Start();
#endif

   /* call counter interrupt handler */
   CounterIncrement = IncrementCounter(0, TIC_PERIOD );

#if 0
   /* set the disable interrupt counter back.
      Disabled because MSP430 AUTOMATICALLY DISABLES GLOBAL IRQ AT IRQ HANDLERS */
   IntSecure_End();
#endif

#endif /* #if (ALARMS_COUNT != 0) */

   /* reset context */
   SetActualContext(actualContext);

   AfterIsr2_Schedule();
}

/**
OSEK periodic interrupt is implemented using TimerA_2 timer module.
*/
interrupt_vec(TIMER2_A0_VECTOR) __attribute__((naked))
void OSEK_ISR_TIMER2_A0_VECTOR(void)
{
   /*
   It's not necessary to disable global irqs.
   It is done automatically when the SP is cleared.
   */
   /*  This handler service the periodic interrupt.
   */
   /* Clear the IRQ flag*/
   TickProcess();

   /*
   This handler calls TickProcess because it is defined as naked, and therefore the compiler do not save regiters.
   The same happens with the RETI instruction that is inserted in the last macro.
   Calling the function, the compiler saves the neede registers.
   */

   RETURN_FROM_NAKED_ISR(); /*return from Tick ISR */
}

/**   OSEK_ISR_TIMER2_A1_VECTOR
 **   The Pendable Service Call is implementad by using and nonused Timer Channel (1)
 **   Is is triggered by setting the IE and IFG lines within the same line in CallTask
 **   and JmpTask.
 **   Note 1: It's not necessary to disable global irqs.
 **           It is done automatically when the SP is cleared by HW
**/
interrupt_vec(TIMER2_A1_VECTOR) __attribute__((naked))
void OSEK_ISR_TIMER2_A1_VECTOR(void)
{
   register unsigned short local_taiv = TA2IV;

   if( local_taiv & TA2IV_TACCR1)  //
   {
      /* Clear the IRQ flag*/
      /* TODO this could be improved by accesing directly to the registers. remember that this handlers should be as fast as possible.*/
      Timer_A_disableCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_1 );
      Timer_A_clearCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_1);

      /* reinicio el stack de la tarea que termino */
      CheckTerminatingTask_Arch();

      /* Context save r4 to r15
         r0 = PC  automatically saved by HW when handler is serviced
       r1 = SP
       r2 = SR  automatically saved by HW when handler is serviced
       r3 = CG  doesn't care
      */
      SAVE_CONTEXT();

      /* exchange stack pointers */
      if( NULL != Osek_OldTaskPtr_Arch )
      {
         asm volatile ( "mov &Osek_OldTaskPtr_Arch,  r6 \n\t"  );
         asm volatile ( "mov SP,  @r6 \n\t"  );
      }
      asm volatile ( "mov &Osek_NewTaskPtr_Arch,  r6 \n\t"  );
      asm volatile ( "mov @r6, SP \n\t"  );

      /*
      Context restore r4 to r15
      It does not Include the reti instruction.
      */
      RESTORE_CONTEXT()
   }

   RETURN_FROM_NAKED_ISR(); /*return from ISR*/
}


/*
MSP430 hasn't a way of dissabling "all the vector" at once, without touching the
individual sub IE flags.
So, when dissable the IRQ handler the system must backup the current available IRQ flags, from
all the possible regiters, to be restored later in the EnableIRQ.
*/
#if( MSP430_ENABLE_RTC_HANDLER== 1)
unsigned char rtcctl0_bck     = 0;
unsigned char rtcps0ctl_bck      = 0;  //the RTCPS0CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char rtcps1ctl_bck      = 0;     //the RTCPS1CTL is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_PORT2_HANDLER== 1)
unsigned char p2ie_bck        = 0;
#endif

#if( MSP430_ENABLE_PORT1_HANDLER==1 )
unsigned char p1ie_bck        = 0;
#endif

#if( MSP430_ENABLE_TIMER2_A1_HANDLER== 1)
unsigned char ta2ctl_bck      = 0;  //the TA2CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta2cctl1_bck    = 0;  //the TA2CCTL1 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta2cctl2_bck    = 0;  //the TA2CCTL2 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_TIMER2_A0_HANDLER==1 )
unsigned char ta2cctl0_bck    = 0;
#endif

#if( MSP430_ENABLE_TIMER1_A0_HANDLER==1 )
unsigned char ta1ctl_bck      = 0;  //the TA1CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta1cctl0_bck    = 0;  //the TA1CCTL0 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta1cctl1_bck    = 0;  //the TA1CCTL1 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta1cctl2_bck    = 0;  //the TA1CCTL2 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_TIMER0_A1_HANDLER==1 )
unsigned char ta0ctl_bck         = 0;  //the TA0CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta0cctl1_bck       = 0;  //the TA0CCTL1 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta0cctl2_bck       = 0;  //the TA0CCTL2 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta0cctl3_bck       = 0;  //the TA0CCTL3 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char ta0cctl4_bck       = 0;  //the TA0CCTL4 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_TIMER0_A0_HANDLER==1 )
unsigned char ta0cctl0_bck       = 0;  //the TA0CCTL0 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_TIMER0_B1_HANDLER==1 )
unsigned char tb0ctl_bck         = 0;    //the TB0CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl1_bck       = 0;    //the TB0CCTL1 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl2_bck       = 0;    //the TB0CCTL2 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl3_bck       = 0;    //the TB0CCTL3 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl4_bck       = 0;    //the TB0CCTL4 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl5_bck       = 0;    //the TB0CCTL5 is 16bit wide, but the IRQ flags are in the lower byte
unsigned char tb0cctl6_bck       = 0;    //the TB0CCTL6 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_TIMER0_B0_HANDLER==1 )
unsigned char tb0cctl0_bck       = 0;    //the TB0CCTL0 is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_DMA_HANDLER==1 )
unsigned char dma0ctl_bck        = 0;  //the DMA0CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char dma1ctl_bck        = 0;  //the DMA1CTL is 16bit wide, but the IRQ flags are in the lower byte
unsigned char dma2ctl_bck        = 0;  //the DMA2CTL is 16bit wide, but the IRQ flags are in the lower byte
#endif

#if( MSP430_ENABLE_USCI_A0_HANDLER==1 )
unsigned char uca1ctl1_bck    = 0;
unsigned char uca1ie_bck      = 0;
#endif

#if( MSP430_ENABLE_USCI_A1_HANDLER==1 )
unsigned char uca0ctl1_bck    = 0;
unsigned char uca0ie_bck      = 0;
#endif


#if( MSP430_ENABLE_USCI_B0_HANDLER==1 )
unsigned char ucb0ie_bck      = 0;
#endif

#if( MSP430_ENABLE_USCI_B1_HANDLER==1 )
unsigned char ucb1ie_bck      = 0;
#endif

#if( MSP430_ENABLE_ADC12_HANDLER==1 )
unsigned char  adc12ctl0_bck  = 0;  //the ADC12CTL0 is 16bit wide, but the IRQ flags are in the lower byte
unsigned short adc12ie_bck    = 0;
#endif

//TODO: OPTIMIZAR SOLO AGREGANDO LOS CASES BASADOS EN LOS ISR QUE DEFINA EL USUARIO EN EL OIL

/**
Enable the backed up IRQ signals (done within MSP430_DisableIRQ).
SEE SLAS590 (TABLE 4)
*/
void MSP430_EnableIRQ(unsigned char irQ_number)
{
   switch( irQ_number )
   {
#if( MSP430_ENABLE_RTC_HANDLER== 1)
      case 0: // => "RTC",
         /* RTCRDYIE, RTCTEVIE, RTCAIE, RT0PSIE, RT1PSIE */
         /**/
         RTCCTL0   |= ( rtcctl0_bck   & (RTCTEVIE|RTCAIE|RTCRDYIE) );
         RTCPS0CTL |= ( rtcps0ctl_bck & RT0PSIE );
         RTCPS1CTL |= ( rtcps1ctl_bck & RT1PSIE );
         break;
#endif

#if( MSP430_ENABLE_PORT2_HANDLER==1)
      case 1 : //=> "PORT2",
         /* P2IE.0 to P2IE.7*/
         P2IE |= p2ie_bck;
         break;
#endif

#if( MSP430_ENABLE_TIMER2_A1_HANDLER==1)
      case 2 : //=> "TIMER2_A1",
         /* TA2CCR1 CCIE1 to TA2CCR2 CCIE2, TA2IE*/
         TA2CTL   |= ( ta2ctl_bck & TAIE );
         TA2CCTL1 |= ( ta2cctl1_bck & CCIE );
         TA2CCTL2 |= ( ta2cctl2_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_TIMER2_A0_HANDLER==1 )
      case 3 : //=> "TIMER2_A0",
         /* TA2CCR0 CCIE0 */
         TA2CCTL0 |= ( ta2cctl0_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_USCI_B1_HANDLER==1 )
      case 4 : //=> "USCI_B1",
         /* UCB1RXIE, UCB1TXIE */
         UCB1IE |= ( ucb1ie_bck & (UCRXIE|UCTXIE) );
         break;
#endif

#if( MSP430_ENABLE_USCI_A1_HANDLER==1 )
      case 5 : //=> "USCI_A1",
         /* UCA1RXIE, UCA1TXIE */
         UCA1IE   |= ( uca1ie_bck & (UCRXIE|UCTXIE) );
         UCA1CTL1 |= ( uca1ctl1_bck & (UCRXEIE|UCBRKIE) );
         break;
#endif

#if( MSP430_ENABLE_PORT1_HANDLER==1 )
      case 6 : //=> "PORT1",
         /* P1IE.0 to P1IE.7  */
         P1IE |= p1ie_bck;
         break;
#endif

#if( MSP430_ENABLE_TIMER1_A1_HANDLER==1 )
      case 7 : //=> "TIMER1_A1",
         /*  TA1CCR1 CCIE1 to TA1CCR2 CCIE2 TA1IE*/
         TA1CTL   |= ( ta1ctl_bck & TAIE );
         TA1CCTL1 |= ( ta1cctl1_bck & CCIE );
         TA1CCTL2 |= ( ta1cctl2_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_TIMER1_A0_HANDLER==1 )
      case 8 : //=> "TIMER1_A0",
         /* TA1CCR0 CCIE0 */
         TA1CCTL0 |= ( ta1cctl0_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_DMA_HANDLER==1 )
      case 9 : //=> "DMA",
         /* DMA0IE, DMA1IE, DMA2IE */
         DMA0CTL |= ( dma0ctl_bck & DMAIE );
         DMA1CTL |= ( dma1ctl_bck & DMAIE );
         DMA2CTL |= ( dma2ctl_bck & DMAIE );
         break;
#endif

#if( MSP430_ENABLE_USB_UBM_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 10: // => "USB_UBM",
         /* USB interrupts */
         USBPWRCTL   |= VBOFFIE|VBONIE|VUOVLIE;
         USBPLLIR    |= USBOORIE|USBLOSIE|USBOOLIE;
         USBIEPCNF_0 |=USBIIE;
         USBOEPCNF_0 |=USBIIE;
         USBIEPIE = 0XFF;
         USBOEPIE = 0XFF;
         USBMAINT    |=UTIE;
         USBIE       |= RSTRIE|SUSRIE|RESRIE|SETUPIE|STPOWIE;

         USBIEPCNF_0 |= USBIIE;
         USBOEPCNF_0 |= USBIIE;

         USBIEPCNF_1 |= USBIIE;
         USBOEPCNF_1 |= USBIIE;
         USBIEPCNF_2 |= USBIIE;
         USBOEPCNF_2 |= USBIIE;
         USBIEPCNF_3 |= USBIIE;
         USBOEPCNF_3 |= USBIIE;
         USBIEPCNF_4 |= USBIIE;
         USBOEPCNF_4 |= USBIIE;
         USBIEPCNF_5 |= USBIIE;
         USBOEPCNF_5 |= USBIIE;
         USBIEPCNF_6 |= USBIIE;
         USBOEPCNF_6 |= USBIIE;
         USBIEPCNF_7 |= USBIIE;
         USBOEPCNF_7 |= USBIIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER0_A1_HANDLER==1 )
      case 11: // => "TIMER0_A1",
         /* TA0CCR1 CCIE1 to TA0CCR4 CCIE4 TA0IE */
         TA0CTL   |= ( ta0ctl_bck & TAIE );
         TA0CCTL1 |= ( ta0cctl1_bck & CCIE );
         TA0CCTL2 |= ( ta0cctl2_bck & CCIE );
         TA0CCTL3 |= ( ta0cctl3_bck & CCIE );
         TA0CCTL4 |= ( ta0cctl4_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_TIMER0_A0_HANDLER==1 )
      case 12: // => "TIMER0_A0",
         /* TA0CCR0 CCIE0 */
         TA0CCTL0 |= ( ta0cctl0_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_ADC12_HANDLER==1 )
      case 13: // => "ADC12",
         /* ADC12IE0 to ADC12IE15 */
         ADC12CTL0 |= ( adc12ctl0_bck & (ADC12OVIE|ADC12TOVIE) );
         ADC12IE = adc12ie_bck;
         break;
#endif

#if( MSP430_ENABLE_USCI_B0_HANDLER==1 )
      case 14: // => "USCI_B0",
         /* UCB0RXIE, UCB0TXIE  */
         UCB0IE |= ( ucb0ie_bck & (UCRXIE|UCTXIE) );
         break;
#endif

#if( MSP430_ENABLE_USCI_A0_HANDLER==1 )
      case 15: // => "USCI_A0",
         /* UCA0RXIE, UCA0TXIE */
         UCA0IE   |= ( uca0ie_bck & (UCRXIE|UCTXIE) );
         UCA0CTL1 |= ( uca0ctl1_bck & (UCRXEIE|UCBRKIE) );
         break;
#endif

#if( MSP430_ENABLE_WDT_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 16: // => "WDT",
         /* WDTIE */
         break;
#endif

#if( MSP430_ENABLE_TIMER0_B1_HANDLER==1 )
      case 17: // => "TIMER0_B1",
         /* TB0CCR1 CCIE1 to TB0CCR6 CCIE6 TB0IE */
         TB0CTL   |= ( tb0ctl_bck & TAIE );
         TB0CCTL1 |= ( tb0cctl1_bck & CCIE );
         TB0CCTL2 |= ( tb0cctl2_bck & CCIE );
         TB0CCTL3 |= ( tb0cctl3_bck & CCIE );
         TB0CCTL4 |= ( tb0cctl4_bck & CCIE );
         TB0CCTL5 |= ( tb0cctl5_bck & CCIE );
         TB0CCTL6 |= ( tb0cctl6_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_TIMER0_B0_HANDLER==1 )
      case 18: // => "TIMER0_B0",
         /* TB0CCR0 CCIE0 */
         TB0CCTL0 |= ( tb0cctl0_bck & CCIE );
         break;
#endif

#if( MSP430_ENABLE_COMP_B_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 19: // => "COMP_B",
         /* Comparator B interrupt flags */
         break;
#endif

#if( MSP430_ENABLE_UNMI_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 20: // => "UNMI",
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 21: // => "SYSNMI",
         /* NMIIE, OFIE, ACCVIE, BUSIE SVMLIE, SVMHIE, DLYLIE, DLYHIE, VLRLIE, VLRHIE, VMAIE, JMBNIE, JMBOUTIE */
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 22: // => "RESET"
         /* WDTIE, KEYV */
         break;
#endif
      default:
         break;
   }
   //TODO: remove system IRQ vectors and OS
   //TODO: FALTA USB
}


/*
for a given irq_number it disables all the interrupts related to that irq vector.
it backups the actual state of the enabled signals for that vector (enabled by the user application)
*/
void MSP430_DisableIRQ(unsigned char irQ_number)
{
   switch(irQ_number)
   {
#if( MSP430_ENABLE_RTC_HANDLER== 1)
      case 0: // => "RTC",
         /* RTCRDYIE, RTCTEVIE, RTCAIE, RT0PSIE, RT1PSIE */

         //backup the register/s
         rtcctl0_bck    = RTCCTL0   ;
         rtcps0ctl_bck  = RTCPS0CTL ;
         rtcps1ctl_bck  = RTCPS1CTL ;

         //clear all flags
         RTCCTL0   &=~( RTCTEVIE|RTCAIE|RTCRDYIE);
         RTCPS0CTL &=~ RT0PSIE;
         RTCPS1CTL &=~ RT1PSIE;
         break;
#endif

#if( MSP430_ENABLE_PORT2_HANDLER== 1)
      case 1 : //=> "PORT2",
         /* P2IE.0 to P2IE.7*/

         //backup the register/s
         p2ie_bck = P2IE;

         //clear all flags
         P2IE = 0x00;
         break;
#endif

#if( MSP430_ENABLE_TIMER2_A1_HANDLER== 1)
      case 2 : //=> "TIMER2_A1",
         /* TA2CCR1 CCIE1 to TA2CCR2 CCIE2, TA2IE*/

         //backup the register/s
         ta2ctl_bck   =   TA2CTL  ;
         ta2cctl1_bck =   TA2CCTL1;
         ta2cctl2_bck =   TA2CCTL2;

         //clear all flags
         TA2CTL   &=~ TAIE;
         TA2CCTL1 &=~ CCIE;
         TA2CCTL2 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER2_A0_HANDLER==1 )
      case 3 : //=> "TIMER2_A0",
         /* TA2CCR0 CCIE0 */

         //backup the register/s
         ta2cctl0_bck = TA2CCTL0;

         //clear all flags
         TA2CCTL0 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_USCI_B1_HANDLER==1 )
      case 4 : //=> "USCI_B1",
         /* UCB1RXIE, UCB1TXIE */

         //backup the register/s
         ucb1ie_bck = UCB1IE;

         //clear all flags
         UCB1IE &=~ (UCRXIE|UCTXIE);
         break;
#endif

#if( MSP430_ENABLE_USCI_A1_HANDLER==1 )
      case 5 : //=> "USCI_A1",
         /* UCA1RXIE, UCA1TXIE */

         //backup the register/s
         uca1ie_bck = UCA1IE;
         uca1ctl1_bck = UCA1CTL1;

         //clear all flags
         UCA1IE &=~ (UCRXIE|UCTXIE);
         UCA1CTL1 &=~ (UCRXEIE|UCBRKIE);
         break;
#endif

#if( MSP430_ENABLE_PORT1_HANDLER== 1)
      case 6 : //=> "PORT1",
         /* P1IE.0 to P1IE.7  */
         //backup the register/s
         p1ie_bck = P1IE;

         //clear all flags
         P1IE = 0x00;
         break;
#endif

#if( MSP430_ENABLE_TIMER1_A1_HANDLER==1 )
      case 7 : //=> "TIMER1_A1",
         /*  TA1CCR1 CCIE1 to TA1CCR2 CCIE2 TA1IE*/

         //backup the register/s
         ta1ctl_bck   = TA1CTL  ;
         ta1cctl1_bck = TA1CCTL1;
         ta1cctl2_bck = TA1CCTL2;

         //clear all flags
         TA1CTL   &=~ TAIE;
         TA1CCTL1 &=~ CCIE;
         TA1CCTL2 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER1_A0_HANDLER==1 )
      case 8 : //=> "TIMER1_A0",
         /* TA1CCR0 CCIE0 */
         //backup the register/s
         ta1cctl0_bck = TA1CCTL0;

         //clear all flags
         TA1CCTL0 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_DMA_HANDLER==1 )
      case 9 : //=> "DMA",
         /* DMA0IE, DMA1IE, DMA2IE */

         //backup the register/s
         dma0ctl_bck = DMA0CTL;
         dma1ctl_bck = DMA1CTL;
         dma2ctl_bck = DMA2CTL;

         //clear all flags
         DMA0CTL &=~  DMAIE;
         DMA1CTL &=~  DMAIE;
         DMA2CTL &=~  DMAIE;
         break;
#endif

#if( MSP430_ENABLE_USB_UBM_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 10: // => "USB_UBM",
         /* USB interrupts */
         USBPWRCTL   &=~ (VBOFFIE|VBONIE|VUOVLIE);
         USBPLLIR    &=~ (USBOORIE|USBLOSIE|USBOOLIE);
         USBIEPCNF_0 &=~ USBIIE;
         USBOEPCNF_0 &=~ USBIIE;
         USBIEPIE = 0XFF;
         USBOEPIE = 0XFF;
         USBMAINT    &=~ UTIE;
         USBIE       &=~ (RSTRIE|SUSRIE|RESRIE|SETUPIE|STPOWIE);

         USBIEPCNF_0 &=~ USBIIE;
         USBOEPCNF_0 &=~ USBIIE;

         USBIEPCNF_1 &=~ USBIIE;
         USBOEPCNF_1 &=~ USBIIE;
         USBIEPCNF_2 &=~ USBIIE;
         USBOEPCNF_2 &=~ USBIIE;
         USBIEPCNF_3 &=~ USBIIE;
         USBOEPCNF_3 &=~ USBIIE;
         USBIEPCNF_4 &=~ USBIIE;
         USBOEPCNF_4 &=~ USBIIE;
         USBIEPCNF_5 &=~ USBIIE;
         USBOEPCNF_5 &=~ USBIIE;
         USBIEPCNF_6 &=~ USBIIE;
         USBOEPCNF_6 &=~ USBIIE;
         USBIEPCNF_7 &=~ USBIIE;
         USBOEPCNF_7 &=~ USBIIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER0_A1_HANDLER==1 )
      case 11: // => "TIMER0_A1",
         /* TA0CCR1 CCIE1 to TA0CCR4 CCIE4 TA0IE */

         //backup the register/s
         ta0ctl_bck= TA0CTL  ;
         ta0cctl1_bck= TA0CCTL1;
         ta0cctl2_bck= TA0CCTL2;
         ta0cctl3_bck= TA0CCTL3;
         ta0cctl4_bck= TA0CCTL4;

         //clear all flags
         TA0CTL   &=~ TAIE;
         TA0CCTL1 &=~ CCIE;
         TA0CCTL2 &=~ CCIE;
         TA0CCTL3 &=~ CCIE;
         TA0CCTL4 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER0_A0_HANDLER==1 )
      case 12: // => "TIMER0_A0",
         /* TA0CCR0 CCIE0 */
         //backup the register/s
         ta0cctl0_bck = TA0CCTL0;

         //clear all flags
         TA0CCTL0 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_ADC12_HANDLER==1 )
      case 13: // => "ADC12",
         /* ADC12IE0 to ADC12IE15 */

         //backup the register/s
         adc12ctl0_bck = ADC12CTL0;
         adc12ie_bck = ADC12IE;

         //clear all flags
         ADC12CTL0 &=~ (ADC12OVIE|ADC12TOVIE);
         ADC12IE = 0x0000;
         break;
#endif

#if( MSP430_ENABLE_USCI_B0_HANDLER==1 )
      case 14: // => "USCI_B0",
         /* UCB0RXIE, UCB0TXIE  */

         //backup the register/s
         ucb0ie_bck = UCB0IEUCB0IE;

         //clear all flags
         UCB0IE &=~ (UCRXIE|UCTXIE);
         break;
#endif

#if( MSP430_ENABLE_USCI_A0_HANDLER==1 )
      case 15: // => "USCI_A0",
         /* UCA0RXIE, UCA0TXIE */

         //backup the register/s
         uca0ie_bck = UCA0IE;
         uca0ctl1_bck = UCA0CTL1;

         //clear all flags
         UCA0IE   &=~ (UCRXIE|UCTXIE);
         UCA0CTL1 &=~ (UCRXEIE|UCBRKIE);
         break;
#endif

#if( MSP430_ENABLE_WDT_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 16: // => "WDT",
         /* WDTIE */
         break;
#endif

#if( MSP430_ENABLE_TIMER0_B1_HANDLER==1 )
      case 17: // => "TIMER0_B1",
         /* TB0CCR1 CCIE1 to TB0CCR6 CCIE6 TB0IE */

         //backup the register/s
         tb0ctl_bck   = TB0CTL   ;
         tb0cctl1_bck = TB0CCTL1 ;
         tb0cctl2_bck = TB0CCTL2 ;
         tb0cctl3_bck = TB0CCTL3 ;
         tb0cctl4_bck = TB0CCTL4 ;
         tb0cctl5_bck = TB0CCTL5 ;
         tb0cctl6_bck = TB0CCTL6 ;

         //clear all flags
         TB0CTL   &=~ TAIE;
         TB0CCTL1 &=~ CCIE;
         TB0CCTL2 &=~ CCIE;
         TB0CCTL3 &=~ CCIE;
         TB0CCTL4 &=~ CCIE;
         TB0CCTL5 &=~ CCIE;
         TB0CCTL6 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_TIMER0_B0_HANDLER==1 )
      case 18: // => "TIMER0_B0",
         /* TB0CCR0 CCIE0 */

         //backup the register/s
         tb0cctl0_bck = TB0CCTL0;

         //clear all flags
         TB0CCTL0 &=~ CCIE;
         break;
#endif

#if( MSP430_ENABLE_COMP_B_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 19: // => "COMP_B",
         /* Comparator B interrupt flags */
         break;
#endif

#if( MSP430_ENABLE_UNMI_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 20: // => "UNMI",
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 21: // => "SYSNMI",
         /* NMIIE, OFIE, ACCVIE, BUSIE SVMLIE, SVMHIE, DLYLIE, DLYHIE, VLRLIE, VLRHIE, VMAIE, JMBNIE, JMBOUTIE */
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 22: // => "RESET"
         /* WDTIE, KEYV */
         break;
#endif

      default:
         break;
   }
}

/*
for a given irq_number it clear the flag that made the handler to be called.
*/
void ClearPendingIRQ_Arch(unsigned short irQ_number)
{
   volatile unsigned char dummy;   //ignore compiling warning

   switch(irQ_number)
   {
#if( MSP430_ENABLE_RTC_HANDLER== 1)
#error TODO: NOT IMPLEMENTED
      case 0: // => "RTC",
         break;
#endif

#if( MSP430_ENABLE_PORT2_HANDLER== 1)
      case 1 : //=> "PORT2",
         dummy = P2IV;
         /* There is no need to clear the flag manually: From MSP430f5529 User manually

         " Any access (read or write) of the P1IV register automatically resets the highest pending interrupt flag. If
         another interrupt flag is set, another interrupt is immediately generated after servicing the initial interrupt "

         */
         break;
#endif

#if( MSP430_ENABLE_TIMER2_A1_HANDLER== 1)
#error TODO: SHOULD NOT BE IMPLEMENTED. THIS IRQ IS RESERVED FOR RTOS FUNCTIONALITY
      case 2 : //=> "TIMER2_A1",

         break;
#endif

#if( MSP430_ENABLE_TIMER2_A0_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 3 : //=> "TIMER2_A0",

         break;
#endif

#if( MSP430_ENABLE_USCI_B1_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 4 : //=> "USCI_B1",

         break;
#endif

#if( MSP430_ENABLE_USCI_A1_HANDLER==1 )
      case 5 : //=> "USCI_A1",
         dummy = UCA1IV;
         break;
#endif

#if( MSP430_ENABLE_PORT1_HANDLER== 1)
      case 6 : //=> "PORT1",
         dummy = P1IV;
         /* There is no need to clear the flag manually: From MSP430f5529 User manually

         " Any access (read or write) of the P1IV register automatically resets the highest pending interrupt flag. If
         another interrupt flag is set, another interrupt is immediately generated after servicing the initial interrupt "

         */
         break;
#endif

#if( MSP430_ENABLE_TIMER1_A1_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 7 : //=> "TIMER1_A1",

         break;
#endif

#if( MSP430_ENABLE_TIMER1_A0_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 8 : //=> "TIMER1_A0",

         break;
#endif

#if( MSP430_ENABLE_DMA_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 9 : //=> "DMA",

         break;
#endif

#if( MSP430_ENABLE_USB_UBM_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 10: // => "USB_UBM",

         break;
#endif

#if( MSP430_ENABLE_TIMER0_A1_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 11: // => "TIMER0_A1",

         break;
#endif

#if( MSP430_ENABLE_TIMER0_A0_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 12: // => "TIMER0_A0",

         break;
#endif

#if( MSP430_ENABLE_ADC12_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 13: // => "ADC12",

         break;
#endif

#if( MSP430_ENABLE_USCI_B0_HANDLER==1 )
      case 14: // => "USCI_B0",

         break;
#endif

#if( MSP430_ENABLE_USCI_A0_HANDLER==1 )
      case 15: // => "USCI_A0",
         dummy = UCA0IV;
         break;
#endif

#if( MSP430_ENABLE_WDT_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 16: // => "WDT",
         /* WDTIE */
         break;
#endif

#if( MSP430_ENABLE_TIMER0_B1_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 17: // => "TIMER0_B1",

         break;
#endif

#if( MSP430_ENABLE_TIMER0_B0_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 18: // => "TIMER0_B0",

         break;
#endif

#if( MSP430_ENABLE_COMP_B_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 19: // => "COMP_B",
         /* Comparator B interrupt flags */
         break;
#endif

#if( MSP430_ENABLE_UNMI_HANDLER==1 )
#error TODO: NOT IMPLEMENTED
      case 20: // => "UNMI",
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 21: // => "SYSNMI",
         /* NMIIE, OFIE, ACCVIE, BUSIE SVMLIE, SVMHIE, DLYLIE, DLYHIE, VLRLIE, VLRHIE, VMAIE, JMBNIE, JMBOUTIE */
         break;
#endif

#if( MSP430_ENABLE_SYSNMI_HANDLER==1 )
#error SHOULD NOT BE IMPLEMENTED
      case 22: // => "RESET"
         /* WDTIE, KEYV */
         break;
#endif
   }
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
