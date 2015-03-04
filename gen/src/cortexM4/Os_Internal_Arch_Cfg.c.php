/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, Mariano Cerdeiro
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

/** \brief FreeOSEK Os Generated Internal Achitecture Configuration Implementation File
 **
 ** \file cortexM4/Os_Internal_Arch_Cfg.c
 ** \arch cortexM4
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
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.3 20150303 Apermingeat added K60_120 interrupt sources
 * v0.1.2 20141130 PR   Added ISR cat. 2 enabling and disabling functions.
 * v0.1.1 20141115 PR   added LPC43xx interrupt sources, spelling mistake fixed
 * v0.1.0 20141115 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

#if (CPU == mk60fx512vlq15)
  #include "Cpu.h"
/* __thumb_startup is defined in startup.c */
  void __thumb_startup( void );

  extern uint32_t __SP_INIT;

#else

/* ResetISR is defined in cr_startup_lpc43xx.c */
extern void ResetISR(void);

/** \brief External declaration for the pointer to the stack top from the Linker Script */
extern void _vStackTop(void);

#endif

/** \brief Handlers used by OSEK */
extern void SysTick_Handler(void);
extern void PendSV_Handler(void);

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
void MemManage_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void) {
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
/* Interrupt sources for MK60F15.
 * See externals/platforms/cortexM4/k60_120/inc/MK60F15.h.
 */
$intList_k60_120 = array (
   0 => "Initial_Stack_Pointer",
   1 => "Initial_Program_Counter",
   2 => "NMI",
   3 => "Hard_Fault",
   4 => "Mem_Manage_Fault",
   5 => "Bus_Fault",
   6 => "Usage_Fault",
   7 => "Reserved7",
   8 => "Reserved8",
   9 => "Reserved9",
   10 => "Reserved10",
   11 => "SVCall",
   12 => "DebugMonitor",
   13 => "Reserved13",
   14 => "PendableSrvReq",
   15 => "SysTick",
   16 => "DMA0_DMA16",
   17 => "DMA1_DMA17",
   18 => "DMA2_DMA18",
   19 => "DMA3_DMA19",
   20 => "DMA4_DMA20",
   21 => "DMA5_DMA21",
   22 => "DMA6_DMA22",
   23 => "DMA7_DMA23",
   24 => "DMA8_DMA24",
   25 => "DMA9_DMA25",
   26 => "DMA10_DMA26",
   27 => "DMA11_DMA27",
   28 => "DMA12_DMA28",
   29 => "DMA13_DMA29",
   30 => "DMA14_DMA30",
   31 => "DMA15_DMA31",
   32 => "DMA_Error",
   33 => "MCM",
   34 => "FTFE",
   35 => "Read_Collision",
   36 => "LVD_LVW",
   37 => "LLW",
   38 => "Watchdog",
   39 => "RNG",
   40 => "I2C0",
   41 => "I2C1",
   42 => "SPI0",
   43 => "SPI1",
   44 => "SPI2",
   45 => "CAN0_ORed_Message_buffer",
   46 => "CAN0_Bus_Off",
   47 => "CAN0_Error",
   48 => "CAN0_Tx_Warning",
   49 => "CAN0_Rx_Warning",
   50 => "CAN0_Wake_Up",
   51 => "I2S0_Tx",
   52 => "I2S0_Rx",
   53 => "CAN1_ORed_Message_buffer",
   54 => "CAN1_Bus_Off",
   55 => "CAN1_Error",
   56 => "CAN1_Tx_Warning",
   57 => "CAN1_Rx_Warning",
   58 => "CAN1_Wake_Up",
   59 => "Reserved59",
   60 => "UART0_LON",
   61 => "UART0_RX_TX",
   62 => "UART0_ERR",
   63 => "UART1_RX_TX",
   64 => "UART1_ERR",
   65 => "UART2_RX_TX",
   66 => "UART2_ERR",
   67 => "UART3_RX_TX",
   68 => "UART3_ERR",
   69 => "UART4_RX_TX",
   70 => "UART4_ERR",
   71 => "UART5_RX_TX",
   72 => "UART5_ERR",
   73 => "ADC0",
   74 => "ADC1",
   75 => "CMP0",
   76 => "CMP1",
   77 => "CMP2",
   78 => "FTM0",
   79 => "FTM1",
   80 => "FTM2",
   81 => "CMT",
   82 => "RTC",
   83 => "RTC_Seconds",
   84 => "PIT0",
   85 => "PIT1",
   86 => "PIT2",
   87 => "PIT3",
   88 => "PDB0",
   89 => "USB0",
   90 => "USBDCD",
   91 => "ENET_1588_Timer",
   92 => "ENET_Transmit",
   93 => "ENET_Receive",
   94 => "ENET_Error",
   95 => "Reserved95",
   96 => "SDHC",
   97 => "DAC0",
   98 => "DAC1",
   99 => "TSI0",
   100 => "MCG",
   101 => "LPTimer",
   102 => "Reserved102",
   103 => "PORTA",
   104 => "PORTB",
   105 => "PORTC",
   106 => "PORTD",
   107 => "PORTE",
   108 => "PORTF",
   109 => "Reserved109",
   110 => "SWI",
   111 => "NFC",
   112 => "USBHS",
   113 => "Reserved113",
   114 => "CMP3",
   115 => "Reserved115",
   116 => "Reserved116",
   117 => "FTM3",
   118 => "ADC2",
   119 => "ADC3",
   120 => "I2S1_Tx",
   121 => "I2S1_Rx",

);

$MAX_INT_COUNT_k60_120 = max(array_keys($intList_k60_120))+1;
?>




#if (CPU == mk60fx512vlq15)
/** \brief mk60fx512vlq15 Interrupt vector */
__attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */
  
    /* ISR name                             No. Address      Pri Name                           Description */
    &__SP_INIT,                        /* 0x00  0x00000000   -   ivINT_Initial_Stack_Pointer    used by PE */
    {
    (tIsrFunc)&__thumb_startup,        /* 0x01  0x00000004   -   ivINT_Initial_Program_Counter  used by PE */
    (tIsrFunc)&Cpu_INT_NMIInterrupt,   /* 0x02  0x00000008   -2   ivINT_NMI                      used by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x03  0x0000000C   -1   ivINT_Hard_Fault               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x04  0x00000010   -   ivINT_Mem_Manage_Fault         unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x05  0x00000014   -   ivINT_Bus_Fault                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x06  0x00000018   -   ivINT_Usage_Fault              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x07  0x0000001C   -   ivINT_Reserved7                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x08  0x00000020   -   ivINT_Reserved8                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x09  0x00000024   -   ivINT_Reserved9                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0A  0x00000028   -   ivINT_Reserved10               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0B  0x0000002C   -   ivINT_SVCall                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0C  0x00000030   -   ivINT_DebugMonitor             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0D  0x00000034   -   ivINT_Reserved13               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0E  0x00000038   -   ivINT_PendableSrvReq           unused by PE */
    (tIsrFunc)&SysTick_Handler,        /* 0x0F  0x0000003C   -   ivINT_SysTick                  unused by PE */
<?php

/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");

for($i=16; $i < $MAX_INT_COUNT_k60_120; $i++)
{
   $src_found = 0;
   foreach ($intnames as $int)
   {
      $intcat = $config->getValue("/OSEK/" . $int,"CATEGORY");
      $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");

      if($intList_k60_120[$i] == $source)
      {
         if ($intcat == 2)
         {
            print "    (tIsrFunc)&OSEK_ISR2_$int,          /* 0x".dechex($i)."  0x00000".strtoupper(dechex($i*4))." ISR for " . $intList_k60_120[$i] . " (IRQ $i) Category 2 */\n";
            $src_found = 1;
         } elseif ($intcat == 1)
         {
            print "    (tIsrFunc)&OSEK_ISR_$int,          /* 0x".dechex($i)."  0x00000".strtoupper(dechex($i*4))."  ISR for " . $intList_k60_120[$i] . " (IRQ $i) Category 1 */\n";
            $src_found = 1;
         } else
         {
            error("Interrupt $int type $inttype has an invalid category $intcat");
         }
      }
   }
   if($src_found == 0)
   {
      print "    (tIsrFunc)&OSEK_ISR_NoHandler,     /* 0x".dechex($i)."  0x00000".strtoupper(dechex($i*4))."   -   No Handler set for ISR " . $intList_k60_120[$i] . " (IRQ $i) */\n";
   }
}
?>
	}
  };

#else

<?php
/* Interrupt sources for LPC43xx.
 * See externals/platforms/cortexM4/lpc43xx/inc/cmsis_43xx.h.
 */
$intList = array (
   0 => "DAC",
   1 => "M0APP",
   2 => "DMA",
   3 => "RESERVED1",
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
   44 => "RESERVED6",
   45 => "ADCHS",
   46 => "ATIMER",
   47 => "RTC",
   48 => "RESERVED8",
   49 => "WDT",
   50 => "M0SUB",
   51 => "CAN0",
   52 => "QEI"
);

$MAX_INT_COUNT = max(array_keys($intList))+1;
?>

/** \brief LPC4337 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* Core Level - CM4 */
   &_vStackTop,                    /* The initial stack pointer  */
   ResetISR,                       /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   MemManage_Handler,              /* The MPU fault handler      */
   BusFault_Handler,               /* The bus fault handler      */
   UsageFault_Handler,             /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   DebugMon_Handler,               /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   SysTick_Handler,                /* The SysTick handler        */

   /* Chip Level - LPC43xx (M4 core) */
<?php

/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");

for($i=0; $i < $MAX_INT_COUNT; $i++)
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
            print "   OSEK_ISR2_$int, /* ISR for " . $intList[$i] . " (IRQ $i) Category 2 */\n";
            $src_found = 1;
         } elseif ($intcat == 1)
         {
            print "   OSEK_ISR_$int, /* ISR for " . $intList[$i] . " (IRQ $i) Category 1 */\n";
            $src_found = 1;
         } else
         {
            error("Interrupt $int type $inttype has an invalid category $intcat");
         }
      }
   }
   if($src_found == 0)
   {
      print "   OSEK_ISR_NoHandler, /* No Handler set for ISR " . $intList[$i] . " (IRQ $i) */\n";
   }
}
?>
};
#endif

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

