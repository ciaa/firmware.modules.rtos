/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/*
 * Copyright 2016 Franco Bucafusco
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

/** \brief FreeOSEK Os Support File for MSP430 Architectures.
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

<?php

/** \brief Handlers used by OSEK */
switch ($definitions["CPU"])
{
   case "msp430f5529":
      /* Interrupt sources for msp430f5529
       * See externals/drivers/msp430/inc/msp430f5529.h.
       * Names in this array are set without the trailing "_VECTOR" string
       */
      $intList = array (
                  0 => "RTC",
                  1 => "PORT2",
                  2 => "TIMER2_A1",
                  3 => "TIMER2_A0",
                  4 => "USCI_B1",
                  5 => "USCI_A1",
                  6 => "PORT1",
                  7 => "TIMER1_A1",
                  8 => "TIMER1_A0",
                  9 => "DMA",
                  10 => "USB_UBM",
                  11 => "TIMER0_A1",
                  12 => "TIMER0_A0",
                  13 => "ADC12",
                  14 => "USCI_B0",
                  15 => "USCI_A0",
                  16 => "WDT",
                  17 => "TIMER0_B1",
                  18 => "TIMER0_B0",
                  19 => "COMP_B",
                  20 => "UNMI",
                  21 => "SYSNMI",
                  22 => "RESET",
      );
      break;

   default:
      error("the CPU " . $definitions["CPU"] . " is not supported.");
      break;
}

$MAX_INT_COUNT = max(array_keys($intList))+1;

?>
