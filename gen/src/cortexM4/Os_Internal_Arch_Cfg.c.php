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
  //extern uint32_t __SP_INIT;

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
    (tIsrFunc)&Cpu_Interrupt,          /* 0x10  0x00000040   -   ivINT_DMA0_DMA16               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x11  0x00000044   -   ivINT_DMA1_DMA17               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x12  0x00000048   -   ivINT_DMA2_DMA18               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x13  0x0000004C   -   ivINT_DMA3_DMA19               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x14  0x00000050   -   ivINT_DMA4_DMA20               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x15  0x00000054   -   ivINT_DMA5_DMA21               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x16  0x00000058   -   ivINT_DMA6_DMA22               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x17  0x0000005C   -   ivINT_DMA7_DMA23               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x18  0x00000060   -   ivINT_DMA8_DMA24               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x19  0x00000064   -   ivINT_DMA9_DMA25               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1A  0x00000068   -   ivINT_DMA10_DMA26              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1B  0x0000006C   -   ivINT_DMA11_DMA27              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1C  0x00000070   -   ivINT_DMA12_DMA28              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1D  0x00000074   -   ivINT_DMA13_DMA29              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1E  0x00000078   -   ivINT_DMA14_DMA30              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1F  0x0000007C   -   ivINT_DMA15_DMA31              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x20  0x00000080   -   ivINT_DMA_Error                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x21  0x00000084   -   ivINT_MCM                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x22  0x00000088   -   ivINT_FTFE                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x23  0x0000008C   -   ivINT_Read_Collision           unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x24  0x00000090   -   ivINT_LVD_LVW                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x25  0x00000094   -   ivINT_LLW                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x26  0x00000098   -   ivINT_Watchdog                 unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x27  0x0000009C   -   ivINT_RNG                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x28  0x000000A0   -   ivINT_I2C0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x29  0x000000A4   -   ivINT_I2C1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2A  0x000000A8   -   ivINT_SPI0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2B  0x000000AC   -   ivINT_SPI1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2C  0x000000B0   -   ivINT_SPI2                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2D  0x000000B4   -   ivINT_CAN0_ORed_Message_buffer unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2E  0x000000B8   -   ivINT_CAN0_Bus_Off             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2F  0x000000BC   -   ivINT_CAN0_Error               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x30  0x000000C0   -   ivINT_CAN0_Tx_Warning          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x31  0x000000C4   -   ivINT_CAN0_Rx_Warning          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x32  0x000000C8   -   ivINT_CAN0_Wake_Up             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x33  0x000000CC   -   ivINT_I2S0_Tx                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x34  0x000000D0   -   ivINT_I2S0_Rx                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x35  0x000000D4   -   ivINT_CAN1_ORed_Message_buffer unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x36  0x000000D8   -   ivINT_CAN1_Bus_Off             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x37  0x000000DC   -   ivINT_CAN1_Error               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x38  0x000000E0   -   ivINT_CAN1_Tx_Warning          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x39  0x000000E4   -   ivINT_CAN1_Rx_Warning          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3A  0x000000E8   -   ivINT_CAN1_Wake_Up             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3B  0x000000EC   -   ivINT_Reserved59               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3C  0x000000F0   -   ivINT_UART0_LON                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3D  0x000000F4   -   ivINT_UART0_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3E  0x000000F8   -   ivINT_UART0_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3F  0x000000FC   -   ivINT_UART1_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x40  0x00000100   -   ivINT_UART1_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x41  0x00000104   -   ivINT_UART2_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x42  0x00000108   -   ivINT_UART2_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x43  0x0000010C   -   ivINT_UART3_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x44  0x00000110   -   ivINT_UART3_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x45  0x00000114   -   ivINT_UART4_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x46  0x00000118   -   ivINT_UART4_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x47  0x0000011C   -   ivINT_UART5_RX_TX              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x48  0x00000120   -   ivINT_UART5_ERR                unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x49  0x00000124   -   ivINT_ADC0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4A  0x00000128   -   ivINT_ADC1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4B  0x0000012C   -   ivINT_CMP0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4C  0x00000130   -   ivINT_CMP1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4D  0x00000134   -   ivINT_CMP2                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4E  0x00000138   -   ivINT_FTM0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4F  0x0000013C   -   ivINT_FTM1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x50  0x00000140   -   ivINT_FTM2                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x51  0x00000144   -   ivINT_CMT                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x52  0x00000148   -   ivINT_RTC                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x53  0x0000014C   -   ivINT_RTC_Seconds              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x54  0x00000150   -   ivINT_PIT0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x55  0x00000154   -   ivINT_PIT1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x56  0x00000158   -   ivINT_PIT2                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x57  0x0000015C   -   ivINT_PIT3                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x58  0x00000160   -   ivINT_PDB0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x59  0x00000164   -   ivINT_USB0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5A  0x00000168   -   ivINT_USBDCD                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5B  0x0000016C   -   ivINT_ENET_1588_Timer          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5C  0x00000170   -   ivINT_ENET_Transmit            unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5D  0x00000174   -   ivINT_ENET_Receive             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5E  0x00000178   -   ivINT_ENET_Error               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5F  0x0000017C   -   ivINT_Reserved95               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x60  0x00000180   -   ivINT_SDHC                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x61  0x00000184   -   ivINT_DAC0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x62  0x00000188   -   ivINT_DAC1                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x63  0x0000018C   -   ivINT_TSI0                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x64  0x00000190   -   ivINT_MCG                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x65  0x00000194   -   ivINT_LPTimer                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x66  0x00000198   -   ivINT_Reserved102              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x67  0x0000019C   -   ivINT_PORTA                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x68  0x000001A0   -   ivINT_PORTB                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x69  0x000001A4   -   ivINT_PORTC                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6A  0x000001A8   -   ivINT_PORTD                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6B  0x000001AC   -   ivINT_PORTE                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6C  0x000001B0   -   ivINT_PORTF                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6D  0x000001B4   -   ivINT_Reserved109              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6E  0x000001B8   -   ivINT_SWI                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6F  0x000001BC   -   ivINT_NFC                      unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x70  0x000001C0   -   ivINT_USBHS                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x71  0x000001C4   -   ivINT_Reserved113              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x72  0x000001C8   -   ivINT_CMP3                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x73  0x000001CC   -   ivINT_Reserved115              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x74  0x000001D0   -   ivINT_Reserved116              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x75  0x000001D4   -   ivINT_FTM3                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x76  0x000001D8   -   ivINT_ADC2                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x77  0x000001DC   -   ivINT_ADC3                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x78  0x000001E0   -   ivINT_I2S1_Tx                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt           /* 0x79  0x000001E4   -   ivINT_I2S1_Rx                  unused by PE */
    }
  };

#else

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

