<?php
/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, 2015 Pablo Ridolfi
 * Copyright 2015, Alejandro Permingeat
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

/** \brief FreeOSEK Os Support File for cortexM0 Architectures.
 **
 ** \file Os_Internal_Defs.php
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/** \brief Handlers used by OSEK */

switch ($this->definitions["CPU"])
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
      $this->log->error("the CPU " . $this->definitions["CPU"] . " is not supported.");
      break;
}


?>
