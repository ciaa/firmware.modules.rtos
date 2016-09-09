/* Copyright 2016, Gerardo Puga (UNLP)
 * Copyright 2014, Pablo Ridolfi (UTN-FRBA)
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
 ** \file sparc/Os_Internal_Arch.c
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/

#include "Os_Internal_Arch.h"
#include "Os_Internal_Arch_Cpu.h"
#include "Os_Internal_Arch_Cfg.h"
#include "grlib.h"

/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/


grDeviceAddress grIRQMBaseAddress;

uint32 sparcISR1HandlersMask = 0x00;

uint32 sparcISR2HandlersMask = 0x00;

uint32 sparcCurrentInterruptMask = 0x0;

sparcIrqHandlerRef sparcUniversalTrapHandlersTable[15] = {
        /*
         * External Interrupt handlers
         * */
        0x00, /* Index 00, IRQ 1 */
        0x00, /* Index 01, IRQ 2 */
        0x00, /* Index 02, IRQ 3 */
        0x00, /* Index 03, IRQ 4 */
        0x00, /* Index 05, IRQ 5 */
        0x00, /* Index 06, IRQ 6 */
        0x00, /* Index 07, IRQ 7 */
        0x00, /* Index 08, IRQ 8 */
        0x00, /* Index 09, IRQ 9 */
        0x00, /* Index 10, IRQ 10 */
        0x00, /* Index 11, IRQ 11 */
        0x00, /* Index 12, IRQ 12 */
        0x00, /* Index 13, IRQ 13 */
        0x00, /* Index 14, IRQ 14 */
        0x00, /* Index 15, IRQ 15 */
        /*
         * Software trap handlers
         * */
        sparcSetTaskContextSWTrapHandler, /* Index 16, set task context handler */
        sparcReplaceTaskContextSWTrapHandler /* Index 17, Replace task context handler */
};


/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/


void sparcOsekPause()
{

   /* According to aeroflex Gaisler LEON 3 documentation, the LEON 3
    * implementation of the SPARC Architecture will enter into a power
    * down mode by executing a WRASR instruction to the %asr19 register.
    * In this power-down mode, the processor halts the pipeline, freezing
    * code execution and cache changes until the next interrupt comes along.
    * */
   asm("wrasr %g0, %asr19");

}


void sparcRegisterISR1Handler(sparcIrqHandlerRef newHandler, sparcIrqNumber irq)
{
    uint32 newInterruptMask;

    newInterruptMask = (1 << irq);

    grRegisterWrite(grIRQMBaseAddress, IRQMP_INTERRUPT_CLEAR_REGISTER, newInterruptMask);

   sparcISR1HandlersMask |= newInterruptMask;

   sparcIRQHandlersTable[irq - 1] = newHandler;
}


void sparcRegisterISR2Handler(sparcIrqHandlerRef newHandler, sparcIrqNumber irq)
{
   uint32 newInterruptMask;

   newInterruptMask = (1 << irq);

   grRegisterWrite(grIRQMBaseAddress, IRQMP_INTERRUPT_CLEAR_REGISTER, newInterruptMask);

   sparcISR2HandlersMask |= newInterruptMask;

   sparcIRQHandlersTable[irq - 1] = newHandler;
}


void sparcEnableAllInterrupts(void)
{

    sparcCurrentInterruptMask = sparcCurrentInterruptMask | (sparcISR1HandlersMask | sparcISR2HandlersMask);

    grRegisterWrite(grDeviceAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);
}


void sparcDisableAllInterrupts(void)
{
    sparcCurrentInterruptMask = sparcCurrentInterruptMask & (~(sparcISR1HandlersMask | sparcISR2HandlersMask));

    grRegisterWrite(grDeviceAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);
}


void sparcEnableISR2Interrupts(void)
{
    sparcCurrentInterruptMask = sparcCurrentInterruptMask | (sparcISR2HandlersMask);

    grRegisterWrite(grDeviceAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);
}


void sparcDisableISR2Interrupts(void)
{
    sparcCurrentInterruptMask = sparcCurrentInterruptMask & (~(sparcISR2HandlersMask));

    grRegisterWrite(grDeviceAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);
}


void StartOs_Arch_Cpu(void)
{
   /* Enable caches.
    *
    * After reset, the caches are disabled and a flush
    * operation must be performed to initialize the tags and valid bits
    * in them bits. */
    __asm__ ("flush\n\t"
             "set 0x81000f, %g1\n\t"
             "sta %g1, [%g0] 2\n\t"
             :
             :
             : /* no output registers */
             : /* no input registers */
             : "%g1" /* clobbered registers */
            );


   /*
    * Setup application interrupts. This routine is automatically generated by the OSEK
    * OS generator. */
   sparcSetupUserISRs();

   /*
    * Setup the timer interrupt
    * */
   sparcSetupSystemISRs();
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

