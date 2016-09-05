/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2016, Gerardo Puga (UNLP)
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
 ** \file sparc/Os_Internal_Arch_Cfg.c
 ** \arch sparc
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



/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/


<?php

/* 
 * Synchronous trap sources for SPARC processors. 
 * */
$interrupt_names_list = array (
   1 => "IRQ1",
   2 => "IRQ2",
   3 => "IRQ3",
   4 => "IRQ4",
   5 => "IRQ5",
   6 => "IRQ6",
   7 => "IRQ7",
   8 => "IRQ8",
   9 => "IRQ9",
   10 => "IRQ10",
   11 => "IRQ11",
   12 => "IRQ12",
   13 => "IRQ13",
   14 => "IRQ14",
   15 => "IRQ15",
   );

$MAX_INT_COUNT = max(array_keys($interrupt_names_list))+1;

?>

/** \brief Interrupt enabling and priority setting function */
void sparcSetupUserISRs(void)
{
   
<?php
$this->loadHelper("modules/rtos/gen/ginc/Multicore.php");

/* get ISRs defined by user application */
$interrupt_handlers_list = $this->helper->multicore->getLocalList("/OSEK", "ISR");

for($i = 1; $i < $MAX_INT_COUNT; $i++)
{
   $interrupt_source_found = 0;
   
   foreach ($interrupt_handlers_list as $interrupt_handler)
   {
      $interrupt_category = $this->config->getValue("/OSEK/" . $interrupt_handler,"CATEGORY");
      $irq_source = $this->config->getValue("/OSEK/" . $interrupt_handler,"INTERRUPT");
      
      if($interrupt_names_list[$i] == $irq_source)
      {
         if ($interrupt_category == 2)
         {
            
            print "   /* ISR for IRQ source " . $interrupt_names_list[$i] . " Category 2 */\n";
            print "   sparcRegisterISR2Handler(OSEK_ISR2_$interrupt_handler, $i);\n";
            print "   \n";
            
            $interrupt_source_found = 1;
            
         } elseif ($interrupt_category == 1) {
            
         	print "   /* ISR for IRQ source " . $interrupt_names_list[$i] . " Category 1 */\n";
            print "   sparcRegisterISR1Handler(OSEK_ISR_$interrupt_handler, $i);\n";
            print "   \n";
            
            $interrupt_source_found = 1;
            
         } else {
            
            $this->log->error("Interrupt $interrupt_handler type $inttype has an invalid category $interrupt_category");
            
         }
      }
   }
   if($interrupt_source_found == 0)
   {
      print "   /* No handler declared for source " . $interrupt_names_list[$i] . " */\n";
      print "   \n";
   }
}
?>
};


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

