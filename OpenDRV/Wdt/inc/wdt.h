/* Copyright 2008, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
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

#ifndef _WDT_H_
#define _WDT_H_
/** \brief OpenDRV WDT Header File
 **
 ** This file shall be included by all files using any OpenDRV WDT API.
 **
 ** \file wdt.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Wdt
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
 * v0.1.0 20081128 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Gen_Types.h"
#include "Wdt_Cfg.h"
#include "Wdt_Arch.h"

/*==================[macros]=================================================*/
/** \brief WDT driver set
 **
 ** This WDT driver service shall be called to reset the WDT. If this service
 ** is not called on time a reset may occur.
 **
 **/
#define Wdt_Set()									\
	{													\
		Wdt_Set_Arch();							\
	}
		
/*==================[typedef]================================================*/
/** \brief WDT driver return type definition */
typedef uint8 Wdt_ReturnType;

/** \brief WDT driver configuration type definition */
typedef struct {
	Wdt_ConfigArchType Wdt_Arch;
} Wdt_ConfigType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Watch Dog Timer driver init service
 **
 ** This WDT driver service shall be called to initialize the WDT driver. Calls
 ** to any other WDT driver service before initialization is not allowed.
 **
 ** \param[in] config pointer to the WDT driver configuration
 ** \return WDT_E_OK	if no error occurs
 ** \return WDT_E_PARAM if the configuration is invalid
 ** \return WDT_E_NOTOK if other error occurs
 **/
extern Wdt_ReturnType Wdt_Init(Wdt_ConfigType const * config);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _WDT_H_ */

