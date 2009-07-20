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

#ifndef _PWM_H_
#define _PWM_H_
/** \brief FreeOSEK Driver PWM Header File
 **
 ** This file shall be included by all files using any OpenDRV PWM API.
 **
 ** \file Pwm.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Pwm Pulse Width Modulator
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Pwm_Global Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090522 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Pwm_Cfg.h"
#include "Pwm_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/** \brief Output state of a PWM channel
 **
 ** PWM_HIGH the PWM channel is in high state
 ** PWM_LOW the PWM channel is in low state
 **/
/* \req PWM108 */
typedef enum {
	PWM_HIGH,
	PWM_LOW
} Pwm_OutputStateType;

/** \brief Definition of type of edge notification of a PWM channel
 **
 ** PWM_RISING_EDGE	Notification will be called when a rising edge occurs
 **						on the PWM output signal
 ** PWM_FALLING_EGE	Notification will be called when a falling edge occurs
 **						on the PWM output signal
 ** PWM_BOTH_EDGES	Notification will be called when either a rising edge
 **						or falling edge occur on the PWM output signal
 **/
/* \req PWM109 */
typedef enum {
	PWM_RISING_EDGE,
	PWM_FALLING_EGE,
	PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;

/** \brief Defines the class of a PWM channel
 **
 ** PWM_VARIABLE_PERIOD			The PWM channel has a variable period. The duty
 **									cycle and the period can be changed.
 ** PWM_FIXED_PERIOD				The PWM channel has a fixed period. Only the duty
 **									cycle can be changed.
 ** PWM_FIXED_PERIOD_SHIFTED	The PWM channel has a fixed shifted period.
 **									Impossible to change it ( only if supported by
 **									hardware)
 **/
/* \req PWM110 */
typedef enum {
	PWM_VARIABLE_PERIOD,
	PWM_FIXED_PERIOD,
	PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

/** \brief This is the type of data structure containing the initialization
 ** data for the PWM driver
 **/
/* \req PWM111 */
typedef struct {
	Pwm_ConfigArchType Pwm_Arch;
} Pwm_ConfigType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Pwm driver init service
 **
 ** This Pwm driver service shall be called to initialize the Pwm driver. Calls
 ** to any other Pwm driver service before initialization is not allowed.
 **
 ** \param[in] ConfigPtr pointer to the Pwm driver configuration
 **/
extern void Pwm_Init
(
	const Pwm_ConfigType * ConfigPtr
);

/** \brief Pwm driver deinit service
 **
 ** This service shall be called to de-initializate the Pwm driver.
 **/
extern void Pwm_DeInit
(
	void
);

/** \brief Pwm service to set the duty cycle of the PWM channel
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 ** \param[in] DutyCycle Min = 0x0000 Max = 0xFFFF
 **/
extern void Pwm_SetDutyCycle
(
	Pwm_ChannelType ChannelNumber,
	uint16 DutyCycle
);

/** \brief Pwm service to set the period and the duty cycle of the PWM channel
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 ** \param[in] Period Period of the PWM signal
 ** \param[in] DutyCycle Min = 0x0000 Max = 0xFFFF
 **/
extern void Pwm_SetPeriodAndDuty
(
	Pwm_ChannelType ChannelNumber,
	Pwm_PeriodType Period,
	uint16 DutyCycle
);

/** \brief Pwm service to set the PWM output to the configured Idle state
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 **/
extern void Pwm_SetOutputToIdle
(
	Pwm_ChannelType ChannelNumber
);

/** \brief Pwm service to read the internal sate of the PWM output signal
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 ** \return Pwm_OutputStateType	PWM_HIGH the PWM output state is high
 **										PWM_LOW the PWM output state is low
 **/
extern Pwm_OutputStateType Pwm_GetOutputState
(
	Pwm_ChannelType ChannelNumber
);

/** \brief Pwm service to disable PWM signal edge notification
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 **/
extern void Pwm_DisableNotification
(
	Pwm_ChannelType ChannelNumber
);

/** \brief Pwm service to enable PWM signal edge notification
 **
 ** \param[in] ChannelNumber Numeric identifier of the PWM
 ** \param[in] Notification Types of notifications are	PWM_RISING_EDGE
 **																		PWM_FALLING_EDGE
 **																		PWM_BOTH_EDGES
 **/
extern void Pwm_EnableNotification
(
	Pwm_ChannelType ChannelNumber,
	Pwm_EdgeNotificationType Notification
);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _PWM_H_ */

