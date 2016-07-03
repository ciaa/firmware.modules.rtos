<?php
/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
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

/** \brief FreeOSEK Os Support File for cortexM4 Architectures.
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
   case "mk60fx512vlq15":
      /* Interrupt sources for MK60F12.
       * See externals/platforms/cortexM4/k60_120/inc/device/MK60F12/MK60F12.h.
       */
      $intList = array (
         0 => "DMA0_DMA16",
         1 => "DMA1_DMA17",
         2 => "DMA2_DMA18",
         3 => "DMA3_DMA19",
         4 => "DMA4_DMA20",
         5 => "DMA5_DMA21",
         6 => "DMA6_DMA22",
         7 => "DMA7_DMA23",
         8 => "DMA8_DMA24",
         9 => "DMA9_DMA25",
         10 => "DMA10_DMA26",
         11 => "DMA11_DMA27",
         12 => "DMA12_DMA28",
         13 => "DMA13_DMA29",
         14 => "DMA14_DMA30",
         15 => "DMA15_DMA31",
         16 => "DMA_ERR",
         17 => "MCM",
         18 => "FTFE",
         19 => "Read_Collision",
         20 => "LVD_LVW",
         21 => "LLW",
         22 => "WDG",
         23 => "RNG",
         24 => "I2C0",
         25 => "I2C1",
         26 => "SPI0",
         27 => "SPI1",
         28 => "SPI2",
         29 => "CAN0_READ",
         30 => "CAN0_BOFF",
         31 => "CAN0_ERR",
         32 => "CAN0_TXW",
         33 => "CAN0_RXW",
         34 => "CAN0_WAKEUP",
         35 => "I2S0_TX",
         36 => "I2S0_RR",
         37 => "CAN1_READ",
         38 => "CAN1_BOFF",
         39 => "CAN1_EERROR",
         40 => "CAN1_TXW",
         41 => "CAN1_RXW",
         42 => "CAN1_WAKEUP",
         43 => "RES59",
         44 => "UART0_LON",
         45 => "UART0",
         46 => "UART0_ERR",
         47 => "UART1",
         48 => "UART1_ERR",
         49 => "UART2",
         50 => "UART2_ERR",
         51 => "UART3",
         52 => "UART3_ERR",
         53 => "UART4",
         54 => "UART4_ERR",
         55 => "UART5",
         56 => "UART5_ERR",
         57 => "ADC0",
         58 => "ADC1",
         59 => "CMP0",
         60 => "CMP1",
         61 => "CMP2",
         62 => "FTM0",
         63 => "FTM1",
         64 => "FTM2",
         65 => "CMT",
         66 => "RTC",
         67 => "RTC_SEC",
         68 => "PIT0",
         69 => "PIT1",
         70 => "PIT2",
         71 => "PIT3",
         72 => "PDB0",
         73 => "USB0",
         74 => "USBDCD",
         75 => "ENET_1588_Timer",
         76 => "ENET_TX",
         77 => "ENET_RX",
         78 => "ENET_ERR",
         79 => "RES95",
         80 => "SDHC",
         81 => "DAC0",
         82 => "DAC1",
         83 => "TSI0",
         84 => "MCG",
         85 => "LPTimer",
         86 => "RES102",
         87 => "PORTA",
         88 => "PORTB",
         89 => "PORTC",
         90 => "PORTD",
         91 => "PORTE",
         92 => "PORTF",
         93 => "RES109",
         94 => "SWI",
         95 => "NFC",
         96 => "USBHS",
         97 => "RES113",
         98 => "CMP3",
         99 => "RES115",
         100 => "RES116",
         101 => "FTM3",
         102 => "ADC2",
         103 => "ADC3",
         104 => "I2S1_TX",
         105 => "I2S1_RX",
      );
      break;

   case "lpc4337":
      /* Interrupt sources for LPC43xx.
       * See externals/platforms/cortexM4/lpc43xx/inc/cmsis_43xx.h.
       */
      $intList = array (
         0 => "DAC",
         1 => "M0APP",
         2 => "DMA",
         3 => "RES1",
         4 => "FLASH_EEPROM",
         5 => "ETH",
         6 => "SDIO",
         7 => "LCD",
         8 => "USB0",
         9 => "USB1",
         10 => "SCT",
         11 => "RIT",
         12 => "TIMER0",
         13 => "TIMER1",
         14 => "TIMER2",
         15 => "TIMER3",
         16 => "MCPWM",
         17 => "ADC0",
         18 => "I2C0",
         19 => "I2C1",
         20 => "SPI",
         21 => "ADC1",
         22 => "SSP0",
         23 => "SSP1",
         24 => "UART0",
         25 => "UART1",
         26 => "UART2",
         27 => "UART3",
         28 => "I2S0",
         29 => "I2S1",
         30 => "SPIFI",
         31 => "SGPIO",
         32 => "GPIO0",
         33 => "GPIO1",
         34 => "GPIO2",
         35 => "GPIO3",
         36 => "GPIO4",
         37 => "GPIO5",
         38 => "GPIO6",
         39 => "GPIO7",
         40 => "GINT0",
         41 => "GINT1",
         42 => "EVRT",
         43 => "CAN1",
         44 => "RES6",
         45 => "ADCHS",
         46 => "ATIMER",
         47 => "RTC",
         48 => "RES8",
         49 => "WDT",
         50 => "M0SUB",
         51 => "CAN0",
         52 => "QEI"
      );
      break;

   default:
      $this->log->error("the CPU " . $this->definitions["CPU"] . " is not supported.");
      break;
}


?>
