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
