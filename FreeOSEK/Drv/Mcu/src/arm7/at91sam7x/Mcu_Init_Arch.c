/* Copyright 2011 Tamas Kenderes
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface.
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 *
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief FreeOSEK Driver Mcu Init Arch implementation file
 **
 ** This file implements the Mcu_Init_Arch API
 **
 ** The implementation is based on the file board_lowlevel.c in at91lib
 ** supplied by Atmel Corporation.
 **
 ** \file arm7/at91sam7x/Mcu_Init_Arch.c
 ** \arch arm7/at91sam7x
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Mcu
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Mcu_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.0 KT	initial version
 */

/*==================[inclusions]=============================================*/
#include "Mcu_Internal.h"
#include "Mcu_Internal_Arch.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void Mcu_DefaultSpuriousHandler(void);
static void Mcu_DefaultFiqHandler(void);
static void Mcu_DefaultIrqHandler(void);
static Mcu_RemapType Mcu_GetCurrentRemap(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/** \brief Default spurious interrupt handler. Infinite loop. */
static void Mcu_DefaultSpuriousHandler(void)
{
	while (1);
}

/** \brief Default handler for fast interrupt requests. Infinite loop. */
static void Mcu_DefaultFiqHandler(void)
{
	while (1);
}

/** \brief Default handler for standard interrupt requests. Infinite loop. */
static void Mcu_DefaultIrqHandler(void)
{
	while (1);
}

/** \brief Checks the current status of memory remapping
 ** \return MCU_REMAP_RAM if the internal RAM is mirrored in the remap area
 ** \return MCU_REMAP_FLASH if the internal flash is mirrored in the remap area
 **/
static Mcu_RemapType Mcu_GetCurrentRemap(void)
{
	uint32 *remap = (uint32 *) 0;
	uint32 *ram = (uint32 *) AT91C_ISRAM;

	/*
	 * Modify the first address in RAM and see if this affects the remap area
	 */
	uint32 temp = *ram;
	*ram = temp + 1;
	if (*remap == *ram)
	{
		*ram = temp;
		return MCU_REMAP_RAM;
	}
	else
	{
		*ram = temp;
		return MCU_REMAP_FLASH;
	}
}

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_MCU_START_SEC_CODE
 * #include "MemMap.h" */

Mcu_ReturnType Mcu_Init_Arch
(
	const Mcu_ConfigType* ConfigPtr
)
{
	uint8f loopi;

	/*
	 * Set flash wait states in the EFC
	 * 48MHz = 1 wait state
	 */
#if (CPU == at91sam7x512)
	AT91C_BASE_EFC0->EFC_FMR = AT91C_MC_FWS_1FWS;
	AT91C_BASE_EFC1->EFC_FMR = AT91C_MC_FWS_1FWS;
#elif (CPU == at91sam7x128) || (CPU == at91sam7x256)
	AT91C_BASE_MC->MC_FMR = AT91C_MC_FWS_1FWS;
#else
	#error Wrong CPU defined
#endif

	/*
	 * Initialize AIC
	 */
	AT91C_BASE_AIC->AIC_IDCR = 0xFFFFFFFF;
	AT91C_BASE_AIC->AIC_SVR[0] = (uint32) Mcu_DefaultFiqHandler;
	for (loopi = 1; loopi < 31; loopi++)
	{
		AT91C_BASE_AIC->AIC_SVR[loopi] = (uint32) Mcu_DefaultIrqHandler;
	}
	AT91C_BASE_AIC->AIC_SPU = (uint32) Mcu_DefaultSpuriousHandler;

	/* Unstack nested interrupts */
	for (loopi = 0; loopi < 8 ; loopi++)
	{
		AT91C_BASE_AIC->AIC_EOICR = 0;
	}

	/* Enable Debug mode */
	AT91C_BASE_AIC->AIC_DCR = AT91C_AIC_DCR_PROT;

	/*
	 * Initialize Watchdog
	 */
	AT91C_BASE_WDTC->WDTC_WDMR = AT91C_WDTC_WDDIS;

	/*
	 * Remap memory
	 * Currently the memory is not remapped.
	 */
	/*
	if (MCU_REMAP_FLASH == Mcu_GetCurrentRemap())
	{
		AT91C_BASE_MC->MC_RCR = AT91C_MC_RCB;
	}
	*/

	/*
	 * Disable RTT and PIT interrupts
	 */
	AT91C_BASE_RTTC->RTTC_RTMR &= ~(AT91C_RTTC_ALMIEN | AT91C_RTTC_RTTINCIEN);
	AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITIEN;
}

/** TODO */
/* #define OpenDRV_MCU_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

