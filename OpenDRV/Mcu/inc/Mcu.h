/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking OpenSEK statically or dynamically with other modules is making a
 * combined work based on OpenSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of OpenSEK give
 * you permission to combine OpenSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with OpenSEK solely through the OpenSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for OpenSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of OpenSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * OpenSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _MCU_H_
#define _MCU_H_
/** \brief OpenDRV Mcu Header File
 **
 ** This file shall be included by all files using any OpenDRV Mcu API.
 **
 ** \file Mcu.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Mcu
 ** \ingroup OpenDRV
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090215 v0.1.1 MaCe	raname the driver to Mcu
 * 20081126 v0.1.0 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Mcu_Cfg.h"
#include "Mcu_Arch.h"

/*==================[macros]=================================================*/
/** \brief Mcu Configuration error code */
/* \req MCU012-1/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_PARAM_CONFIG			0x0A

/** \brief Mcu Clock error code */
/* \req MCU012-2/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_PARAM_CLOCK			0x0B

/** \brief Mcu Mode error code */
/* \req MCU012-3/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_PARAM_MODE			0x0C

/** \brief Mcu Ram Section error code */
/* \req MCU012-4/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_PARAM_RAMSECTION	0x0D

/** \brief Mcu Pll Not Locked error code */
/* \req MCU012-5/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_PLL_NOT_LOCKED		0x0E

/** \brief Mcu UnInit error code */
/* \req MCU012-6/6 The Mcu module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * MCU_E_PARAM_CONFIG, MCU_E_PARAM_CLOCK, MCU_E_PARAM_MODE,
 * MCU_E_PARAM_RAMSECTION, MCU_E_PLL_NOT_LOCKED and MCU_E_UNINIT.
 */
#define MCU_E_UNINIT					0x0F

/** \brief Mcu Pll Locked define for Mcu_PllStatusType */
#define MCU_PLL_LOCKED				0x01

/** \brief Mcu Pll UnLocked define for Mcu_PllStatusType */
#define MCU_PLL_UNLOCKED			0x02

/** \brief Mcu Pll Undefined Status define for Mcu_PllStatusType */
#define MCU_PLL_STATUS_UNDEFINED	0x03

/** \brief Mcu Power On Reset define for Mcu_ResetType */
#define MCU_POWER_ON_RESET			0x01

/** \brief Mcu Watchdog Reset define for Mcu_ResetType */
#define MCU_WATCHDOG_RESET			0x02

/** \brief Mcu Software Reset define for Mcu_ResetType */
#define MCU_SW_RESET					0x03

/** \brief Mcu Undefined Reset define for Mcu_ResetType */
#define MCU_RESET_UNDEFINED 		0x04

/*==================[typedef]================================================*/
/** \brief Mcu Return type definition */
typedef uint8 Mcu_ReturnType;

/** \brief Mcu Configuration Type */
/* \req MCU131 The structure Mcu_ConfigType is an external data structure (i.e.
 * implementation specific) and shall contain the initialization data for the
 * MCU module. It shall contain:
 *  - MCU dependent properties
 *  - Reset Configuration
 *  - Definition of MCU modes
 *  - Definition of Clock settings
 *  - Definition of RAM sections 
 */
/* \dev TODO */
/* \req MCU054  The structure Mcu_ConfigType shall provide a configurable
 * (enable/disable) clock failure notification if the MCU provides an interrupt
 * for such detection. Error reporting shall follow the DEM procedures (see
 * also MCU051). In case of other HW detection mechanisms e.g., the generation
 * of a trap, this notification shall be disabled and the failure reporting
 * shall be done outside the MCU driver.
 */
/* \dev TODO */
/* \req MCU035 The definitions for each MCU mode within the structure
 * Mcu_ConfigType shall contain: (depending on MCU)
 *  - MCU specific properties
 *  - Change of CPU clock
 *  - Change of Peripheral clock
 *  - Change of PLL settings
 *  - Change of MCU power supply
 */
/* \dev TODO */
/* \req MCU031 The definitions for each Clock setting within the structure
 * Mcu_ConfigType shall contain:
 *  - MCU specific properties as, e.g., clock safety features and special clock distri-
 *    bution settings
 *  - PLL settings /start lock options
 *  - Internal oscillator setting
 */
/* \dev TODO */
/* \req MCU030 The definitions for each RAM section within the structure
 * Mcu_ConfigType shall contain:
 *  - RAM section base address
 *  - Section size
 *  - Data pre-setting to be initialized
 * Usage of linker symbols instead of scalar values is allowed.
 */
/* \dev TODO */
typedef struct {
	Mcu_ConfigArchType Mcu_Arch;
} Mcu_ConfigType;

/** \brief Mcu Configuration Reference type definition */
typedef Mcu_ConfigType* Mcu_ConfigRefType;

/** \brief Mcu Pll Status type definition
 **
 ** This is a status value returned by the function Mcu_GetPllStatus of the
 ** MCU module. Valid values are:
 ** - MCU_PLL_LOCKED if the PLL is locked
 ** - MCU_PLL_UNLOCKED if the PLL is unlocked
 ** - MCU_PLL_STATUS_UNDEFINED if the PLL Status is unknown.
 **/
typedef uint8f Mcu_PllStatusType;

/** \brief Mcu Clock type definition 
 **
 ** Specifies the identification (ID) for a clock setting, which is configured
 ** in the configuration structure
 **/
typedef uint8 Mcu_ClockType;

/** \brief Mcu Reset type definition
 **
 ** This status value indicates the reason of the last reset, possibly values
 ** are:
 **  - MCU_POWER_ON_RESET	Power On Reset (default)
 **  - MCU_WATCHDOG_RESET	Internal Watchdog Timer Reset
 **  - MCU_SW_RESET			Software Reset
 **  - MCU_RESET_UNDEFINED Reset Undefined
 **/
typedef uint8 Mcu_ResetType;

/** \brief Mcu Row Reset type definition */
typedef uint8 Mcu_RawResetType;

/** \brief Mcu Mode type definition */
typedef uint8 Mcu_ModeType;

/** \brief Mcu Ram Section type definition */
typedef uint8 Mcu_RamSectionType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Mcu Init service
 **
 ** This service initializes the MCU driver.
 **
 ** \param[in] ConfigPtr Pointer to MCU driver configuration set.
 ** \return void
 **/
extern void Mcu_Init(const Mcu_ConfigType* ConfigPtr);

/** \brief Mcu Init Clock service
 **
 ** This service initializes the PLL and other MCU specific clock options.
 **
 ** \param[in] ConfigSettings Clock Settings
 ** \return E_OK Command has been accepted
 **			E_NOT_OK Command has not been accepted
 **/
extern Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSettings);

/** TODO ALL */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MCU_H_ */

