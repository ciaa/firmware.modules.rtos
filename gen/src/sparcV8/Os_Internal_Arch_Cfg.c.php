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
#include "Os_Internal_Arch_Cpu.h"
#include "sparcsyscalls.h"


/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/


<?php
$this->loadHelper("modules/rtos/gen/ginc/Multicore.php");

/*
 * Synchronous trap sources for SPARC processors.
 */
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
		15 => "IRQ15" 
);

$INTERRUPT_NAMES_LIST_LENGTH = max ( array_keys ( $interrupt_names_list ) ) + 1;

/*
 * Synchronous trap sources for SPARC processors.
 */
$hardware_counters_names_list = array (
		0 => "HWCOUNTER0",
		1 => "HWCOUNTER1",
		2 => "HWCOUNTER2",
		3 => "HWCOUNTER3",
		4 => "HWCOUNTER4",
		5 => "HWCOUNTER5",
		6 => "HWCOUNTER6",
		7 => "HWCOUNTER7" 
);

$HARDWARE_COUNTERS_NAMES_LIST_LENGTH = max ( array_keys ( $hardware_counters_names_list ) ) + 1;

?>

void OSEK_COUNTER_GPTIMER0_IRQHandler(void)
{
   /* Store the calling context so that we can
      restore it later */
   ContextType actualContext = GetCallingContext();

   /* Change the execution context to ISR2 */
   SetActualContext(CONTEXT_ISR2);

   /* Check the pending interrupt bit of $counter_id */
   sparcCheckPendingTimerInterrupts();

   /* Restore the previous execution context */
   SetActualContext(actualContext);

#if (NON_PREEMPTIVE == OSEK_DISABLE)
   /* check if the actual task is preemptive */
   if ( ( CONTEXT_TASK == actualContext ) &&
        ( TasksConst[GetRunningTask()].ConstFlags.Preemtive ) )
   {
      /* this shall force a call to the scheduler */
      PostIsr2_Arch(isr);
   }
#endif /* #if (NON_PREEMPTIVE == OSEK_ENABLE) */
}


/** \brief Interrupt enabling and priority setting function */
void sparcSetupUserISRs(void)
{

<?php
/* get ISRs defined by user application */
$interrupt_handlers_list = $this->helper->multicore->getLocalList ( "/OSEK", "ISR" );

for($i = 1; $i < $INTERRUPT_NAMES_LIST_LENGTH; $i ++) {
	$interrupt_source_found = 0;
	
	foreach ( $interrupt_handlers_list as $interrupt_handler ) {
		$interrupt_category = $this->config->getValue ( "/OSEK/" . $interrupt_handler, "CATEGORY" );
		$irq_source = $this->config->getValue ( "/OSEK/" . $interrupt_handler, "INTERRUPT" );
		
		if ($interrupt_names_list [$i] == $irq_source) {
			if ($interrupt_category == 2) {
				
				print "   /* ISR for IRQ source " . $interrupt_names_list [$i] . " Category 2 */\n";
				print "   sparcRegisterISR2Handler(OSEK_ISR2_$interrupt_handler, $i);\n";
				print "\n";
				
				$interrupt_source_found = 1;
			} elseif ($interrupt_category == 1) {
				
				print "   /* ISR for IRQ source " . $interrupt_names_list [$i] . " Category 1 */\n";
				print "   sparcRegisterISR1Handler(OSEK_ISR_$interrupt_handler, $i);\n";
				print "\n";
				
				$interrupt_source_found = 1;
			} else {
				
				$this->log->error ( "Interrupt $interrupt_handler type $inttype has an invalid category $interrupt_category" );
			}
		}
	}
	if ($interrupt_source_found == 0) {
		print "   /* No handler declared for source " . $interrupt_names_list [$i] . " */\n";
		print "\n";
	}
}
?>
}


uint32 sparcGetHardwareTimersInUseMask(void)
{
   uint32 timersInUseMask;

   timersInUseMask = 0;
<?php
$counters_list = $this->helper->multicore->getLocalList ( "/OSEK", "COUNTER" );

for($i = 0; $i < $HARDWARE_COUNTERS_NAMES_LIST_LENGTH; $i ++) {
	
	foreach ( $counters_list as $counter_name ) {
		$counter_type = $this->config->getValue ( "/OSEK/" . $counter_name, "TYPE" );
		$counter_id = $this->config->getValue ( "/OSEK/" . $counter_name, "COUNTER" );
		
		if ($counter_type == "HARDWARE") {
			if ($hardware_counters_names_list [$i] == $counter_id) {
				$counter_index = $i;
				print "\n";
				print "   /* Enable $counter_id */\n";
				print "   timersInUseMask |= (1 << $i);\n";
			}
		}
	}
}
?>

   return timersInUseMask;
}

uint32 sparcGetHardwareTimerID(uint32 hwTimerIndex)
{
   const uint32 hwTimersIds[] = {<?php
$counters_list = $this->helper->multicore->getLocalList ( "/OSEK", "COUNTER" );

for($i = 0; $i < $HARDWARE_COUNTERS_NAMES_LIST_LENGTH; $i++) {
	$counter_index = -1;
	$o = 0;
	
	foreach ( $counters_list as $counter_name ) {
		$counter_type = $this->config->getValue ( "/OSEK/" . $counter_name, "TYPE" );
		$counter_id = $this->config->getValue ( "/OSEK/" . $counter_name, "COUNTER" );
		
		if ($counter_type == "HARDWARE") {
			if ($hardware_counters_names_list [$i] == $counter_id) {
				$counter_index = $o;
			}
		}
		
		$o++;
	}
	
	if ($i > 0) {
		print ", ";
	}
	print "$counter_index";
}
?>};
   
   return hwTimersIds[hwTimerIndex];
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

