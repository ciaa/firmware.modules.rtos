/* Copyright 2008, 2009, Mariano Cerdeiro
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

/** \brief FreeOSEK Driver PWM Init Arch implementation file
 **
 ** This file implements the Pwm_Init_Arch API
 **
 ** \file arm7/lpc2xxx/Pwm_Init_Arch.c
 ** \arch arm7/lpc2xxx
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Pwm
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Pwm_Internal
 ** @{ */
/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090522 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Pwm_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** TODO */
/* #define OpenDRV_Pwm_START_SEC_CODE
 * #include "MemMap.h" */

void Pwm_Init_Arch
(
	const Pwm_ConfigType * config
)
{
#if (PWM_PWM0 == ENABLE)
	/* set PWM0TCR:	bit 0 enable counter
							bit 1 reset rounter
							bit 2 reserved
							bit 3 PWM enable
							bit 4 master disable
							bit 7.5 reserved */
	PWM0TCR = 1;

	/* set PWM0CTCR:	bit 1.0 mode 00	timer mode
											 01	counter mode
											 10	counter mode
											 11	counter mode
							bit 3.2 counter input */
	PWM0CTCR = 0;

	/* set PWM0MCR:	bit 0 interrupt PWMMR0
							bit 1 reset PWMMR0
							bit 2 stop PWMMR0 */
	PWM0MCR = PWM_PWM0MCR;

	/* set PWM0CCR */
	PWM0CCR = 0;

	/* set PWM0PCR */
	PWM0PCR = PWM_PWM0PCR;

	/* set PWM0LER */
	PWM0LER = PWM_PWM0LER;

	/* set PWM0PR */
	PWM0PR = 12;

	/* set PWM0MR0 */
	PWM0MR0 = PWM_PWM0MR0;

#if (defined PWM_PWM0_0_ENABLE)
	PWM0MR1 = PWM_PWM0_0_DUTY;
#endif

#if (defined PWM_PWM0_1_ENABLE)
	PWM0MR2 = PWM_PWM0_1_DUTY;
#endif

#if (defined PWM_PWM0_2_ENABLE)
	PWM0MR3 = PWM_PWM0_2_DUTY;
#endif

#if (defined PWM_PWM0_3_ENABLE)
	PWM0MR4 = PWM_PWM0_3_DUTY;
#endif

#if (defined PWM_PWM0_4_ENABLE)
	PWM0MR5 = PWM_PWM0_4_DUTY;
#endif

#if (defined PWM_PWM0_5_ENABLE)
	PWM0MR6 = PWM_PWM0_5_DUTY;
#endif
#endif

#if (PWM_PWM1 == ENABLE)
	/* set PWM1TCR:	bit 0 enable counter
							bit 1 reset rounter
							bit 2 reserved
							bit 3 PWM enable
							bit 4 master disable
							bit 7.5 reserved */
	PWM1TCR = 1;

	/* set PWM1CTCR:	bit 1.0 mode 00	timer mode
											 01	counter mode
											 10	counter mode
											 11	counter mode
							bit 3.2 counter input */
	PWM1CTCR = 0;

	/* set PWM1MCR:	bit 0 interrupt PWMMR0
							bit 1 reset PWMMR0
							bit 2 stop PWMMR0 */
	PWM1MCR = PWM_PWM1MCR;

	/* set PWM1CCR */
	PWM1CCR = 0;

	/* set PWM1PCR */
	PWM1PCR = PWM_PWM1PCR;

	/* set PWM1LER */
	PWM1LER = PWM_PWM1LER;

	/* set PWM1PR */
	PWM1PR = 12;

	/* set PWM1MR0 */
	PWM1MR0 = PWM_PWM1MR0;

#if (defined PWM_PWM1_0_ENABLE)
	PWM1MR1 = PWM_PWM1_0_DUTY;
#endif

#if (defined PWM_PWM1_1_ENABLE)
	PWM1MR2 = PWM_PWM1_1_DUTY;
#endif

#if (defined PWM_PWM1_2_ENABLE)
	PWM1MR3 = PWM_PWM1_2_DUTY;
#endif

#if (defined PWM_PWM1_3_ENABLE)
	PWM1MR4 = PWM_PWM1_3_DUTY;
#endif

#if (defined PWM_PWM1_4_ENABLE)
	PWM1MR5 = PWM_PWM1_4_DUTY;
#endif

#if (defined PWM_PWM1_5_ENABLE)
	PWM1MR6 = PWM_PWM1_5_DUTY;
#endif
#endif
}



/** TODO */
/* #define OpenDRV_Pwm_STOP_SEC_CODE
 * #include "MemMap.h" */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

