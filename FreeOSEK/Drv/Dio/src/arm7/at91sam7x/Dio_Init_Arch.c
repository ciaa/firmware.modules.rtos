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

/** \brief FreeOSEK Driver Dio Init Arch Implementation File
 **
 ** This file implements the Dio_Init_Arch API
 **
 ** \file arm7/at91sam7x/Dio_Init_Arch.c
 ** \arch arm7/at91sam7x
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */  
/** \addtogroup FreeOSEK_Drv_Dio
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Dio_Global
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
#include "Dio_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void InitPort_Arch(AT91S_PIO *pio, uint32 mask, uint32 dir);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/** \brief Initializes PIO port
 **
 ** \param[in] pio  A handle to the PIO controller to use (AT91C_BASE_PIOx)
 ** \param[in] mask Mask: every bit of this uint32 variable represents a pin
 ** of the current PIO peripheral. 0 = pin is not used, 1 = pin is used.
 ** \param[in] dir  Direction mask: every bit of this uint32 variable
 ** represents a pin of the current PIO peripheral. 0 = input, 1 = output.
 **/
static void InitPort_Arch(AT91S_PIO *pio, uint32 mask, uint32 dir)
{
	/* enable pins in use */
	pio->PIO_PER = mask;

	/* disable interrupts and pullup resistors for pins in use */
	pio->PIO_IDR = mask;
	pio->PIO_PPUDR = mask;

	/* set default output to 0 for output pins in use */
	pio->PIO_CODR = mask;

	/* set the direction of the pins */
	pio->PIO_ODR = ~mask;
	pio->PIO_OER = mask;
}

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_DIO_START_SEC_CODE
 * #include "MemMap.h" */

Dio_ReturnType Dio_Init_Arch
(
	Dio_ConfigRefType config
)
{
#if (DIO_PORTA_STATE == ENABLE)
	InitPort_Arch(AT91C_BASE_PIOA, DIO_PORTA_MASK, DIO_PORTA_DIR);
#endif
#if (DIO_PORTB_STATE == ENABLE)
	InitPort_Arch(AT91C_BASE_PIOB, DIO_PORTB_MASK, DIO_PORTB_DIR);
#endif
}

/** TODO */
/* #define OpenDRV_DIO_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

