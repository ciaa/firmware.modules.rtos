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
 ** \file sparcV8/Os_Internal_Arch.c
 ** \arch sparcV8
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
#include "Os_Internal.h"
#include "grlib.h"
#include "sparcsyscalls.h"


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/


/**
 * \brief Base address of the MPIRQ interrupt controller of the system.
 *
 * This value is automatically detected during initialization.
 */
grDeviceAddress sparcIRQMPBaseAddress;

/**
 * \brief System clock frequency.
 *
 * This value is automatically detected during initialization.
 */
uint32_t sparcSystemFrequencyHz;

/**
 * \brief Base address of the system timer.
 *
 * This value is automatically detected during initialization.
 */
grDeviceAddress sparcGPTIMER0BaseAddress;

/**
 * \brief IRQ number of the system timer.
 *
 * This value is automatically detected during initialization.
 */
uint32_t sparcGPTIMER0IRQNumber;

/**
 * \brief Bit mask of the IRQ numbers with a registered ISR1 interrupt service handler routine. */
uint32_t sparcISR1HandlersMask = 0x00;

/**
 * \brief Bit mask of the IRQ numbers with a registered ISR2 interrupt service handler routine. */
uint32_t sparcISR2HandlersMask = 0x00;

/**
 * \brief Bit mask of the currently enabled interrupt sources.
 *
 * This value shadows the value on the IRQ Enable register on the IRQMP module.
 */
uint32_t sparcCurrentInterruptMask = 0x00;

/**
 * \brief Registered user interrupt handlers table.
 *
 * This table is populated by sparcRegisterISR1Handler() and sparcRegisterISR2Handler() during
 * system initialization.
 * */
sparcIrqHandlerRef sparcIRQHandlersTable[15] = {
      0x00, /* Index 00, IRQ 1 */
      0x00, /* Index 01, IRQ 2 */
      0x00, /* Index 02, IRQ 3 */
      0x00, /* Index 03, IRQ 4 */
      0x00, /* Index 04, IRQ 5 */
      0x00, /* Index 05, IRQ 6 */
      0x00, /* Index 06, IRQ 7 */
      0x00, /* Index 07, IRQ 8 */
      0x00, /* Index 08, IRQ 9 */
      0x00, /* Index 09, IRQ 10 */
      0x00, /* Index 10, IRQ 11 */
      0x00, /* Index 11, IRQ 12 */
      0x00, /* Index 12, IRQ 13 */
      0x00, /* Index 13, IRQ 14 */
      0x00  /* Index 14, IRQ 15 */
};


/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/


/**
 * \brief Executes the user interrupt handler associated with a given IRQ number.
 *
 * @param irqNumber IRQ number of the requested handler.
 */
void sparcInterruptHandlerCaller(uint32_t irqNumber)
{
   sparcIrqHandlerRef irqHandler;

   sparcAssert(irqNumber > 0,   "Invalid IRQ number");
   sparcAssert(irqNumber <= 15, "Invalid IRQ number");

   /* Call every interrupt handler associated to this IRQ number
    *
    * Clearly, if you wanted to implement IRQ multiplexing, this is
    * the place to do it... just saying... *wink* *wink*  ;)
    * */

   irqHandler = sparcIRQHandlersTable[irqNumber - 1];

   sparcAssert(irqHandler != NULL,   "Undefined IRQ handler");

   (*irqHandler)();

   /* Clear the interrupt flag on the IRQMP
    * controller */
   sparcClearInterrupt(irqNumber);
}


/**
 * \brief Configures the GPTIMER module to generate interrupts once every tick. */
void sparcSetModularTimerConfiguration()
{
   uint32_t timersInUseMask;
   uint32_t configurationRegisterValue;
   uint32_t timerNReloadRegister;
   uint32_t timerNControlRegister;
   uint32_t numberOfImplementedTimers;
   uint32_t timerIndex;

   /* At this point we can assume that MKPROM/GRMON has already configured the scaler of the
    * first GPTIMER instance on the bus so that the scaler output ticks at 1MHz. We can build
    * on that, leaving the scaler unchanged.
    * */

   /* Find out which of the timers are actually being used
    * in the system */
   timersInUseMask = sparcGetHardwareTimersInUseMask();

   /* Determine the number of implemented timers within the GPTIMER core */
   configurationRegisterValue = grRegisterRead(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_CONFIGURATION_REGISTER);

   numberOfImplementedTimers = configurationRegisterValue & 0x07;

   /* Make sure that the system configuration is not using more timers than those that
    * are present in GPTIMER0 */
   sparcAssert((timersInUseMask & (~((1 << numberOfImplementedTimers) - 1))) == 0, "Attempted to configure more timers than those that are actually present in the hardware.");

   /* Enable all the implemented timer control registers so that we can configure them next. */
   configurationRegisterValue = 0x00
         | 0x00 << 23  /* Reserved bits. Write 0x00. */
         | ((1 << numberOfImplementedTimers) - 1) << 16  /* Enable bits for each timer's control register. */
         | 0x00 << 14  /* Reserved bits. Write 0x00. */
         | 0x00 << 13  /* External Events bit */
         | 0x00 << 12  /* Enable Set bit */
         | 0x00 << 11  /* Enable latching */
         | 0x00 << 10  /* Enable external clock source */
         | 0x00 <<  9  /* Disable timer freeze bit */
         | 0x00 <<  8  /* Separate interrupts bit. Read only, write 0x00. */
         | 0x00 <<  3  /* APB interrupt. Read only, write 0x00. */
         | 0X00 <<  0; /* Number of implemented timers. Read only, write 0x00. */

   grRegisterWrite(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_CONFIGURATION_REGISTER, configurationRegisterValue);

   /* Configure each individual timer. */
   for (timerIndex = 0; timerIndex < numberOfImplementedTimers; timerIndex++)
   {
      timerNReloadRegister = 0;

      /* Set the reload value first, so that we can force a reload next.
       * The period of each of the timers depends on timer's index number.
       * */
      switch (timerIndex) {
      case 0 : timerNReloadRegister =    10000 - 1; break; /*    10 ms */
      case 1 : timerNReloadRegister =    50000 - 1; break; /*    50 ms */
      case 2 : timerNReloadRegister =   100000 - 1; break; /*   100 ms */
      case 3 : timerNReloadRegister =   500000 - 1; break; /*   500 ms */
      case 4 : timerNReloadRegister =  1000000 - 1; break; /*  1000 ms */
      case 5 : timerNReloadRegister =  5000000 - 1; break; /*  5000 ms */
      case 6 : timerNReloadRegister = 10000000 - 1; break; /* 10000 ms */
      default: timerNReloadRegister = 50000000 - 1; break; /* 50000 ms */
      }

      grRegisterWrite(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_RELOAD_VALUE_REGISTER(timerIndex), timerNReloadRegister);

      /* Check whether this particular timer is in use by the current system
       * configuration */
      if ((timersInUseMask & (1 << timerIndex)) != 0)
      {
         /* The timer is in use, configure and enable it. While at it, force a reload and
          * clean any pending interrupt to make sure that we get a clean start. */
         timerNControlRegister = 0x00
               | 0x00 << 16  /* Reload value for the watchdog window counter. */
               | 0x00 <<  9  /* Reserved. Write 0x00. */
               | 0x01 <<  8  /* Disable watchdog output bit.*/
               | 0x00 <<  7  /* Enable watchdog NMI bit. */
               | 0x00 <<  6  /* Debug Halt bit. Read only, write 0x00. */
               | 0x00 <<  5  /* Chain bit. */
               | 0x01 <<  4  /* Interrupt Pending bit. Write 0x01 to clear any pending interrupt. */
               | 0x01 <<  3  /* Interrupt Enable Bit. */
               | 0x01 <<  2  /* Load value from the reload register. */
               | 0x01 <<  1  /* Restart bit. */
               | 0x01 <<  0; /* Enable bit. */

      } else {
         /* The timer is NOT in use, so leave it disabled. force a reload and
          * clean any pending interrupt to make sure there are no surprises. */
         timerNControlRegister = 0x00
               | 0x00 << 16  /* Reload value for the watchdog window counter. */
               | 0x00 <<  9  /* Reserved. Write 0x00. */
               | 0x01 <<  8  /* Disable watchdog output bit.*/
               | 0x00 <<  7  /* Enable watchdog NMI bit. */
               | 0x00 <<  6  /* Debug Halt bit. Read only, write 0x00. */
               | 0x00 <<  5  /* Chain bit. */
               | 0x01 <<  4  /* Interrupt Pending bit. Write 0x01 to clear any pending interrupt. */
               | 0x00 <<  3  /* Interrupt Enable Bit. */
               | 0x01 <<  2  /* Load value from the reload register. */
               | 0x01 <<  1  /* Restart bit. */
               | 0x00 <<  0; /* Enable bit. */
      }

      grRegisterWrite(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_CONTROL_REGISTER(timerIndex), timerNControlRegister);
   }
}

/**
 * \brief Determines the processor clock frequency.
 *
 * See comments inside for an understanding of HOW the frequency is determined.
 */
void sparcAutodetectSystemClockFrequency()
{
   grPlugAndPlayAPBDeviceTableEntryType apbDeviceInfo;
   int32_t retCode;
   uint32_t scalerRegisterValue;

   /* Both MKPROM and GRMON automatically configure the first system timer's
    * prescaler so that it generates 100 ticks every seconds. This is
    * used here to detect the system clock frequency. */

   /* Detect the hardware address and irq information of the GPTIMER core */
   retCode = grWalkPlugAndPlayAPBDeviceTable(
         GRLIB_PNP_VENDOR_ID_GAISLER_RESEARCH,
         GRLIB_PNP_DEVICE_ID_GPTIMER,
         &apbDeviceInfo,
         0);

   /* At least one GPTIMER is required for this to work. */
   sparcAssert(retCode >= 0, "Failed to detect hardware GPTIMER0!");

   scalerRegisterValue = grRegisterRead(apbDeviceInfo.address, GRLIB_GPTIMER_SCALER_RELOAD_VALUE);

   /* GRMON/MKPROM seem to preconfigure the first GPTIMER module so that it generates a 1Mhz tick signal
    * at the output of the scaler. I haven't been able to find where this is documented, but
    * the implementation of the RTEMS port for LEON 3 processors rely on this too, and that port was
    * mostly coded by Gaisler Research. */
   sparcSystemFrequencyHz = (scalerRegisterValue + 1) * 1000 * 1000;

   /* Set the value of the system frequency on the Gaisler module; drivers will look for it there later */
   grSetSystemClockFrequencyValue(sparcSystemFrequencyHz);
}


/**
 * \brief Reads the CPU configuration data and determines the number of register windows that were implemented in the system.
 *
 * The window count information is stored on the global variable detected_sparc_register_windows.
 */
void sparcAutodetectProcesorRegisterWindowsSetSize()
{
   grCpuConfigType cpuConfig;

   /* Read the CPU configuration */
   grGetCPUConfig(&cpuConfig);

   detected_sparc_register_windows = cpuConfig.registersWindows;
}


/**
 * \brief Detects the base address of the IRQMP interrupt controller.
 *
 * The base address information is stored on a global variable for later reference by other functions
 * within the same module.
 */
void sparcAutodetectInterruptControllerAddress()
{
   grPlugAndPlayAPBDeviceTableEntryType apbDeviceInfo;
   int32_t retCode;

   /* Read the address of the interrupt controller from the APB PnP device
    * configuration tables */
   retCode = grWalkPlugAndPlayAPBDeviceTable(
         GRLIB_PNP_VENDOR_ID_GAISLER_RESEARCH,
         GRLIB_PNP_DEVICE_ID_IRQMP,
         &apbDeviceInfo,
         0);

   sparcAssert(retCode >= 0, "Could not find the interrupt controller!");

   sparcIRQMPBaseAddress = apbDeviceInfo.address;
}



/**
 * \brief Detects data and instruction cache information.
 */
void sparcAutodetectMemoryHierachyConfiguration()
{
   grCacheConfigType instructionCacheConfig;
   grCacheConfigType dataCacheConfig;

   /* Data and instruction caches information (currently not used) */
   grGetDCacheConfig(&dataCacheConfig);
   grGetICacheConfig(&instructionCacheConfig);

   /*
    *
    * Currently there is no use for this data
    *
    * */
}


/**
 * \brief Detects and configures the system timer.
 *
 * Uses the first GPTIMER module on the AMBA bus to generate the system ticks.
 */
void sparcSetupSystemTimer(void)
{
   grPlugAndPlayAPBDeviceTableEntryType apbDeviceInfo;
   int32_t retCode;

   /*
    * Configure the hardware timer and set the ISR for HardwareCounter
    * */

   /* Detect the hardware address and irq information of the timer module */
   retCode = grWalkPlugAndPlayAPBDeviceTable(
         GRLIB_PNP_VENDOR_ID_GAISLER_RESEARCH,
         GRLIB_PNP_DEVICE_ID_GPTIMER,
         &apbDeviceInfo,
         0);

   sparcAssert(retCode >= 0, "Failed to detect hardware GPTIMER0!");

   sparcGPTIMER0BaseAddress = apbDeviceInfo.address;
   sparcGPTIMER0IRQNumber   = apbDeviceInfo.irq;

   /* Register the interrupt service routine */
   sparcRegisterISR2Handler(OSEK_COUNTER_GPTIMER0_IRQHandler, apbDeviceInfo.irq);

   /* Configure the timer module */
   sparcSetModularTimerConfiguration();
}


/*==================[external functions definition]==========================*/


/**
 * \brief Registers a new ISR1 user interrupt handler.
 *
 * This is used only by the initialization code. Uses should never call this.
 *
 * @param newHandler Interrupt service routine pointer.
 * @param irq IRQ number to associate the handler to.
 */
void sparcRegisterISR1Handler(sparcIrqHandlerRef newHandler, sparcIrqNumber irq)
{
   uint32_t newInterruptMask;

   newInterruptMask = (1 << irq);

   sparcAssert((newInterruptMask & sparcISR1HandlersMask) == 0, "Duplicated IRQ registration");

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_INTERRUPT_CLEAR_REGISTER, newInterruptMask);

   sparcISR1HandlersMask |= newInterruptMask;

   sparcIRQHandlersTable[irq - 1] = newHandler;
}

/**
 * \brief Registers a new ISR2 user interrupt handler.
 *
 * This is used only by the initialization code. Uses should never call this.
 *
 * @param newHandler Interrupt service routine pointer.
 * @param irq IRQ number to associate the handler to.
 */
void sparcRegisterISR2Handler(sparcIrqHandlerRef newHandler, sparcIrqNumber irq)
{
   uint32_t newInterruptMask;

   newInterruptMask = (1 << irq);

   sparcAssert((newInterruptMask & sparcISR2HandlersMask) == 0, "Duplicated IRQ registration");

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_INTERRUPT_CLEAR_REGISTER, newInterruptMask);

   sparcISR2HandlersMask |= newInterruptMask;

   sparcIRQHandlersTable[irq - 1] = newHandler;
}

/**
 * \brief Clears an interrupt flag on the interrupt controller.
 *
 *  Users should not call this directly unless they are writing
 *  ISR1 interrupt service handlers.
 *
 *  For ISR2 interrupts, this function is called by the boilerplate
 *  code that is automatically generated during the OSEK-OS
 *  system generation phase of the build process.
 *
 *  FIXME I'm not sure that this function is accessible from user code
 *  if for use within ISR1 interrupt handler routines. This should
 *  be declared on the external section of the file and a function
 *  declaration should be added to the module header file.
 *
 * @param irq IRQ number of the interrupt whose flag must be cleared.
 */
void sparcClearInterrupt(sparcIrqNumber irq)
{
   uint32_t interruptBitMask;

   interruptBitMask = (1 << irq);

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_INTERRUPT_CLEAR_REGISTER, interruptBitMask);
}

/**
 * \brief Uses the interrupt controller to force an interrupt request on the system.
 *
 *  No one should ever call this. This is for exclusive use of the OSEK-OS test harness.
 */
void sparcForceInterrupt(sparcIrqNumber irq)
{
   uint32_t interruptBitMask;

   interruptBitMask = (1 << irq);

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_INTERRUPT_FORCE_REGISTER, interruptBitMask);
}

/**
 * \brief Enables all of the registered interrupts on the system interrupt controller.
 *
 * This enables both ISR1 and ISR2 registered system interrupts.
 */
void sparcEnableAllInterrupts(void)
{
   uint32_t previousProcessorInterruptLevel;

   sparcAssert(sparcIRQMPBaseAddress != 0, "The IRQMP base address has not been initialized!");

   /* Start of atomic code section */
   previousProcessorInterruptLevel = sparcSystemSetProcessorInterruptLevel(SPARC_NO_INTERRUPTS_PIL_LEVEL);

   sparcCurrentInterruptMask = sparcCurrentInterruptMask | (sparcISR1HandlersMask | sparcISR2HandlersMask);

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);

   /* End of atomic code section */
   sparcSystemSetProcessorInterruptLevel(previousProcessorInterruptLevel);
}

/**
 * \brief Disables all interrupts through on the system interrupt controller.
 */
void sparcDisableAllInterrupts(void)
{
   uint32_t previousProcessorInterruptLevel;

   sparcAssert(sparcIRQMPBaseAddress != 0, "The IRQMP base address has not been initialized!");

   /* Start of atomic code section */
   previousProcessorInterruptLevel = sparcSystemSetProcessorInterruptLevel(SPARC_NO_INTERRUPTS_PIL_LEVEL);

   sparcCurrentInterruptMask = sparcCurrentInterruptMask & (~(sparcISR1HandlersMask | sparcISR2HandlersMask));

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);

   /* End of atomic code section */
   sparcSystemSetProcessorInterruptLevel(previousProcessorInterruptLevel);
}

/**
 * \brief Enables all registered ISR2 interrupts on the interrupt controller.
 */
void sparcEnableISR2Interrupts(void)
{
   uint32_t previousProcessorInterruptLevel;

   sparcAssert(sparcIRQMPBaseAddress != 0, "The IRQMP base address has not been initialized!");

   /* Start of atomic code section */
   previousProcessorInterruptLevel = sparcSystemSetProcessorInterruptLevel(SPARC_NO_INTERRUPTS_PIL_LEVEL);

   sparcCurrentInterruptMask = sparcCurrentInterruptMask | (sparcISR2HandlersMask);

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);

   /* End of atomic code section */
   sparcSystemSetProcessorInterruptLevel(previousProcessorInterruptLevel);
}

/**
 * \brief Enables all registered ISR1 interrupts on the interrupt controller.
 */
void sparcDisableISR2Interrupts(void)
{
   uint32_t previousProcessorInterruptLevel;

   sparcAssert(sparcIRQMPBaseAddress != 0, "The IRQMP base address has not been initialized!");

   /* Start of atomic code section */
   previousProcessorInterruptLevel = sparcSystemSetProcessorInterruptLevel(SPARC_NO_INTERRUPTS_PIL_LEVEL);

   sparcCurrentInterruptMask = sparcCurrentInterruptMask & (~(sparcISR2HandlersMask));

   grRegisterWrite(sparcIRQMPBaseAddress, IRQMP_MP_INTERRUPT_MASK_REGISTER(0), sparcCurrentInterruptMask);

   /* End of atomic code section */
   sparcSystemSetProcessorInterruptLevel(previousProcessorInterruptLevel);
}

/**
 * \brief LEON3 specific initialization code.
 */
void StartOs_Arch_Cpu(void)
{
   /* Enable processor caches.
    *
    * After reset, the caches are disabled and a flush
    * operation must be performed to initialize the tags and valid bits
    * in them. Mkprom probably has probably already enabled them by now,
    * but better safe than sorry... */
   grEnableProcessorCaches();

   /* Detect system clock frequency */
   sparcAutodetectSystemClockFrequency();

   /* Find out the number for register windows */
   sparcAutodetectProcesorRegisterWindowsSetSize();

   /* Read information about the memory subsystem */
   sparcAutodetectMemoryHierachyConfiguration();

   /* Determine the base address of the interrupt controller */
   sparcAutodetectInterruptControllerAddress();
}

/**
 * \brief Checks the interrupt pending bits on the system timer module, and invokes the corresponding OSEK timer
 * increment routines.
 */
void sparcCheckPendingTimerInterrupts()
{
   uint32_t timersInUseMask;
   uint32_t timerNControlRegister;
   uint32_t timerIndex;

   timersInUseMask = sparcGetHardwareTimersInUseMask();

   /* Configure each individual timer. */
   for (timerIndex = 0; timerIndex < 8; timerIndex++)
   {
      /* Check whether this particular timer is in use by the current system
       * configuration */
      if ((timersInUseMask & (1 << timerIndex)) != 0)
      {
         timerNControlRegister = grRegisterRead(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_CONTROL_REGISTER(timerIndex));

         /* Is there an interrupt pending from this timer? */
         if ((timerNControlRegister & 0x00000010) != 0)
         {
            /* Clear the timer'sinterrupt pending flag and call the OSEK's counter administration
             * routines */

            timerNControlRegister = 0x00
                  | 0x00 << 16  /* Reload value for the watchdog window counter. */
                  | 0x00 <<  9  /* Reserved. Write 0x00. */
                  | 0x01 <<  8  /* Disable watchdog output bit.*/
                  | 0x00 <<  7  /* Enable watchdog NMI bit. */
                  | 0x00 <<  6  /* Debug Halt bit. Read only, write 0x00. */
                  | 0x00 <<  5  /* Chain bit. */
                  | 0x01 <<  4  /* Interrupt Pending bit. Write 0x01 to clear any pending interrupt. */
                  | 0x01 <<  3  /* Interrupt Enable Bit. */
                  | 0x00 <<  2  /* Load value from the reload register. */
                  | 0x01 <<  1  /* Restart bit. */
                  | 0x01 <<  0; /* Enable bit. */

            grRegisterWrite(sparcGPTIMER0BaseAddress, GRLIB_GPTIMER_CONTROL_REGISTER(timerIndex), timerNControlRegister);

#if (ALARMS_COUNT != 0)
            IntSecure_Start();
            IncrementCounter(sparcGetHardwareTimerID(timerIndex), 1);
            IntSecure_End();
#endif
         }
      }
   }

   /* Clear the interrupt pending bit in the IRQMP */
   sparcClearInterrupt(sparcGPTIMER0IRQNumber);
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

