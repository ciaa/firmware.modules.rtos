/* Copyright 2016, Franco Bucafusco
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

/** \brief Start the system counter
 **
 ** This file includes the function to start the system counter
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160222 v0.1.0 FB   initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal_Arch_Cpu.h"
#include "ciaaPlatforms.h"

#if (CPU == msp430f5529)
#include "msp430.h"
#include "driverlib.h"
#endif

/*==================[macros and definitions]=================================*/

#define SVMH_FULL_PERF()  PMMCTL0_H = 0xA5; SVSMLCTL |= (SVMLFP); PMMCTL0_H = 0x00;



#define WORKING_FREQUENCY_KHZ       (unsigned long)(WORKING_FREQUENCY_MHZ*1e3)  // en KHZ
#define WORKING_FREQUENCY_HZ        (unsigned long)(WORKING_FREQUENCY_MHZ*1e6)  // en Hz

#define XT1_XT2_PORT_DIR            P5DIR
#define XT1_XT2_PORT_OUT            P5OUT
#define XT1_XT2_PORT_SEL            P5SEL
#define XT1_ENABLE                  (BIT4 + BIT5)
#define XT2_ENABLE                  (BIT2 + BIT3)

#define VALOR_MS(A)  (unsigned short)( ( ( ( unsigned long )A*REF_FREQUENCY_HZ)/1000 ) )

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
const Timer_A_initUpModeParam tick_timer_init_params =
{
   .clockSource                              = TIMER_A_CLOCKSOURCE_ACLK,
   .clockSourceDivider                       = TIMER_A_CLOCKSOURCE_DIVIDER_1,
   .timerPeriod                              = VALOR_MS( TIC_PERIOD ) ,
   .timerInterruptEnable_TAIE                = TIMER_A_TAIE_INTERRUPT_DISABLE,
   .captureCompareInterruptEnable_CCR0_CCIE  = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
   .timerClear                               = TIMER_A_SKIP_CLEAR,
   .startTimer                               = true,
};

const Timer_A_initCaptureModeParam swi_init_params =
{
   .captureRegister           = TIMER_A_CAPTURECOMPARE_REGISTER_1,
   .captureMode               = TIMER_A_CAPTUREMODE_NO_CAPTURE, //FUNCIONA? SI NO, PROBAR CON TIMER_A_CAPTUREMODE_RISING_EDGE
   .captureInputSelect        = TIMER_A_CAPTURE_INPUTSELECT_GND,
   .synchronizeCaptureSource  = TIMER_A_CAPTURE_ASYNCHRONOUS,
   .captureInterruptEnable    = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,
   .captureOutputMode         = TIMER_A_OUTPUTMODE_OUTBITVALUE, /* this is set for completion of the structure, but no needed*/
};

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
Initializes the main system clock
ACLK = REF_FREQUENCY_HZ
MCLK = SMCLK = 14.7456Mhz
*/
void StartOs_Arch_System()
{
   UCS_turnOffXT1();

   XT1_XT2_PORT_SEL |= XT1_ENABLE + XT2_ENABLE;    // Setup XT1 and XT2

   PMM_setVCore( 3 );                              // Set Vcore to accomodate for max. allowed system speed

   UCS_turnOnLFXT1( UCS_XT1_DRIVE_0 ,   UCS_XCAP_1  );   // Use 32.768kHz XTAL as reference

   UCS_initClockSignal( UCS_FLLREF ,  UCS_XT1CLK_SELECT ,   UCS_CLOCK_DIVIDER_1  );

   UCS_initFLLSettle( WORKING_FREQUENCY_KHZ,  ( WORKING_FREQUENCY_HZ/REF_FREQUENCY_HZ )  );

   /*
   ESTA LINEAS SON PARA ESTABLECER LA CONFIGURACION DEL MODULO PMM PARA QUE ESTE EN FULL PERFORMACN Y FAST WAKE UP MODE.
   SI NO ESTA CONFIGURADO ASI, AL DESPERTARSE DE UN LPM, EL ARRANQUE DEL DCO NO ES AGIL Y PARA EL CASO DE LA RECEPCION DE LA
   UART Y SE PIERDE EL PRIMER uint8_t DE DATOS.
   ESTO ES, PORQUE EL TIEMPO DE ENCENDIDO ES MAYOR QUE UN BIT DE LA COMUNICACION.
   */
   PMM_enableSvsLInLPMFastWake();   // SVSL_ENABLED_IN_LPM_FAST_WAKE();
   PMM_enableSvsHInLPMFullPerf();   // SVSH_ENABLED_IN_LPM_FULL_PERF() ;

   PMM_optimizeSvsLInLPMFastWake(); //   SVSL_OPTIMIZED_IN_LPM_FAST_WAKE();
   PMM_optimizeSvsHInLPMFullPerf(); //   SVSH_OPTIMIZED_IN_LPM_FULL_PERF();

   SVMH_FULL_PERF();

   PMM_disableSvsL();//  DISABLE_SVSL() ;
}

void StartOs_Arch_SystemTick(void)
{
   /* Activate SystemTick */
   Timer_A_initUpMode( TIMER_A2_BASE , (Timer_A_initUpModeParam*) &tick_timer_init_params);

   /* Configuration of the channel 1 to simulate the PendSV IRQ from cortex arquitecture.*/
   Timer_A_initCaptureMode( TIMER_A2_BASE ,(Timer_A_initCaptureModeParam*) &swi_init_params );

}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
