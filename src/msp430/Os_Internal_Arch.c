/* Copyright 2016, Franco Bucafusco
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

/** \brief FreeOSEK Os Internal Arch Implementation File
 **
 ** \file msp430/Os_Internal_Arch.c
 ** \arch msp430
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160222 v0.1.0 FB   initial version for msp430 processors
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void * Osek_NewTaskPtr_Arch;
void * Osek_OldTaskPtr_Arch;

/*==================[internal data definition]===============================*/

TaskType TerminatingTask	= INVALID_TASK;
TaskType WaitingTask 		= INVALID_TASK;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void ReturnHook_Arch(void)
{
	/* Tasks shouldn't return here... */
	while(1)
	{
		osekpause();
	}
}

void CheckTerminatingTask_Arch(void)
{
	if( TerminatingTask != INVALID_TASK )
	{
		InitStack_Arch( TerminatingTask );
	}
	TerminatingTask = INVALID_TASK;
}

/* Task Stack Initialization */
void InitStack_Arch(uint8 TaskID)
{
 	uint16 * taskStack     = (uint16 *)TasksConst[TaskID].StackPtr;	/* stack bottom */

	int taskStackSizeWords = TasksConst[TaskID].StackSize/2;				/* calculation of the size of the stack in words units (16bits) */

	taskStack[taskStackSizeWords-1] = (uint32) TasksConst[TaskID].EntryPoint; 	/*PC*/
	taskStack[taskStackSizeWords-2] = DEFAULT_SR; 							       	/*SP*/

 	/* la ubicacion, reservando 13 registro para el cambio de contexto
	*/
	*(TasksConst[TaskID].TaskContext) = &(taskStack[taskStackSizeWords - 14]);
}


/**
 OSEK periodic interrupt is implemented using TimerA_2 timer module.
*/
__attribute__( (__interrupt__(TIMER2_A0_VECTOR),naked))
void OSEK_ISR_TIMER2_A0_VECTOR(void)
{
   /*
   It's not necessary to disable global irqs.
   It is done automatically when the SP is cleared.
   */
	/*  This handler service the periodic interrupt.
	*/
	/* Clear the IRQ flag*/
	Timer_A_clearCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_0);

	/* store the calling context in a variable */
	ContextType actualContext = GetCallingContext();

	/* set isr 2 context */
	SetActualContext(CONTEXT_ISR2);

#if (ALARMS_COUNT != 0)
	/* counter increment */
	static CounterIncrementType CounterIncrement = 1;
	(void)CounterIncrement; /* TODO remove me */

	/* increment the disable interrupt conter to avoid enable the interrupts */
	IntSecure_Start();

	/* call counter interrupt handler */
	CounterIncrement = IncrementCounter(0, TIC_PERIOD );

	/* set the disable interrupt counter back */
	IntSecure_End();
#endif /* #if (ALARMS_COUNT != 0) */

	/* reset context */
	SetActualContext(actualContext);

#if (NON_PREEMPTIVE == OSEK_DISABLE)
	/* check if the actual task is preemptive */
	if ( ( CONTEXT_TASK == actualContext ) &&  ( TasksConst[GetRunningTask()].ConstFlags.Preemtive ) )
	{
		/* this shall force a call to the scheduler */
		PostIsr2_Arch(isr);
	}
#endif /* #if (NON_PREEMPTIVE == OSEK_DISABLE) */

	RETURN_FROM_NAKED_ISR(); /*return from Tick ISR */
}

/*
otros CCIFG (1 2 o 3)
*/
__attribute__( (__interrupt__(TIMER2_A1_VECTOR),naked))
void OSEK_ISR_TIMER2_A1_VECTOR(void)
{
	/*
	It's not necessary to disable global irqs.
	It is done automatically when the SP is cleared.
	*/

	//swi handler
   //ver de hacerla en asm o en c.
   //basicamente es la funcion del context switch. similar al pendSV

	/* Clear the IRQ flag*/	//VERIFICAR TAIV PORQUE LA IRQ PUEDE HABER SURGIDO DE OTRO CCRX
	unsigned short local_taiv = TA2IV;

	if( local_taiv & TA2IV_TACCR1)	//
	{
		Timer_A_disableCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_1 );
		Timer_A_clearCaptureCompareInterrupt( TIMER_A2_BASE , TIMER_A_CAPTURECOMPARE_REGISTER_1);

		/* reinicio el stack de la tarea que termino */
		CheckTerminatingTask_Arch();

		SAVE_CONTEXT();

		/* exchange stack pointers */
		if( Osek_OldTaskPtr_Arch != NULL )
		{
			asm volatile ( "mov SP,  Osek_OldTaskPtr_Arch \n\t"  );
		}

		asm volatile ( "mov Osek_NewTaskPtr_Arch, SP \n\t"  );

		RESTORE_CONTEXT()
	}

	RETURN_FROM_NAKED_ISR();
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
