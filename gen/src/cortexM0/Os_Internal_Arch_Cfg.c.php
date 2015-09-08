/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, 2015 Pablo Ridolfi
 * Copyright 2015, Alejandro Permingeat
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

/** \brief FreeOSEK Os Generated Internal Achitecture Configuration Implementation File
 **
 ** \file cortexM0/Os_Internal_Arch_Cfg.c
 ** \arch cortexM0
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * PR           Pablo Ridolfi
 * Apermingeat  Alejandro Permingeat
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.5 20150831 PR   cortexM0 first version
 * v0.1.4 20150307 MaCe rework port for CIAA-FLS
 * v0.1.3 20150303 Apermingeat added K60_120 interrupt sources
 * v0.1.2 20141130 PR   Added ISR cat. 2 enabling and disabling functions.
 * v0.1.1 20141115 PR   added LPC43xx interrupt sources, spelling mistake fixed
 * v0.1.0 20141115 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#if (CPU == lpc43xx)
/* THIS IS A DIRTY WORKAROUND :( ciaa/Firmware#309*/
#undef FALSE
#undef TRUE
#include "chip.h"
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
#if (CPU == lpc4337)
/* ResetISR is defined in cr_startup_lpc43xx.c */
extern void ResetISR(void);

/** \brief External declaration for the pointer to the stack top from the Linker Script */
extern void _vStackTop(void);
#else
#error Not supported CPU
#endif

/** \brief Handlers used by OSEK */
extern void PendSV_Handler(void);

<?php
if ($definition["ARCH"] == "cortexM0")
{
   echo "extern void RIT_IRQHandler(void);\n";
}
?>

/*==================[internal functions definition]==========================*/
/* Default exception handlers. */
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void) {
    while (1) {
    }
}

/*==================[external functions definition]==========================*/
<?php
switch ($definition["CPU"])
{
   case "lpc4337":
      /* Interrupt sources for LPC43xx (Cortex-M0 core).
       * See externals/platforms/cortexM0/lpc43xx/inc/cmsis_43xx_m0app.h.
       */
      $intList = array (
         0 => "RTC",
         1 => "M4CORE",
         2 => "DMA",
         3 => "RES1",
         4 => "FLASH_EEPROM_ATIMER",
         5 => "ETH",
         6 => "SDIO",
         7 => "LCD",
         8 => "USB0",
         9 => "USB1",
         10 => "SCT",
         11 => "RIT_WWDT",
         12 => "TIMER0",
         13 => "GINT1",
         14 => "PIN_INT4",
         15 => "TIMER3",
         16 => "MCPWM",
         17 => "ADC0",
         18 => "I2C0_I2C1",
         19 => "SGPIO",
         20 => "SPI_DAC",
         21 => "ADC1",
         22 => "SSP0_SSP1",
         23 => "EVENTROUTER",
         24 => "UART0",
         25 => "UART1",
         26 => "UART2_CCAN1",
         27 => "UART3",
         28 => "I2S0_I2S1_QEI",
         29 => "CCAN_0",
         30 => "ADCHS",
         31 => "M0SUB",
      );
      break;

   default:
      error("the CPU " . $definition["CPU"] . " is not supported.");
      break;
}

$MAX_INT_COUNT = max(array_keys($intList))+1;

if ($definition["CPU"] == "lpc4337") : ?>
/** \brief LPC4337 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &_vStackTop,                    /* The initial stack pointer  */
   ResetISR,                       /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   0,                              /* The MPU fault handler      */
   0,                              /* The bus fault handler      */
   0,                              /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   0,                              /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   0,                              /* The SysTick handler        */
<?php else :
      error("Not supported CPU: " . $definition["CPU"]);
   endif;
?>
   /*** User Interrupts ***/
<?php

/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");

for($i=0; $i < $MAX_INT_COUNT; $i++)
{
   /* LPC4337-CortexM0 core uses RIT timer for OSEK periodic interrupt */
   if( ($i==11) && ($definition["ARCH"] == "cortexM0") )
   {
      print "   RIT_IRQHandler,\n";
   }
   else
   {
      $src_found = 0;
      foreach ($intnames as $int)
      {
         $intcat = $config->getValue("/OSEK/" . $int,"CATEGORY");
         $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");

         if($intList[$i] == $source)
         {
            if ($intcat == 2)
            {
               print "   OSEK_ISR2_$int, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." ISR for " . $intList[$i] . " (IRQ $i) Category 2 */\n";
               $src_found = 1;
            } elseif ($intcat == 1)
            {
               print "   OSEK_ISR_$int, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." ISR for " . $intList[$i] . " (IRQ $i) Category 1 */\n";
               $src_found = 1;
            } else
            {
               error("Interrupt $int type $inttype has an invalid category $intcat");
            }
         }
      }
      if($src_found == 0)
      {
         print "   OSEK_ISR_NoHandler, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." - No Handler set for ISR " . $intList[$i] . " (IRQ $i) */\n";
      }
   }
}
?>
};

/** \brief Interrupt enabling and priority setting function */
void Enable_User_ISRs(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $prio = $config->getValue("/OSEK/" . $int,"PRIORITY");

   print "   /* Enabling IRQ $source with priority $prio */\n";
   print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   print "   NVIC_SetPriority(" . array_search($source, $intList) . ", $prio);\n\n";
}
?>
}

/** \brief Enable user defined category 2 ISRs */
void Enable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Enabling IRQ $source */\n";
      print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}

/** \brief Disable user defined category 2 ISRs */
void Disable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Disabling IRQ $source */\n";
      print "   NVIC_DisableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
