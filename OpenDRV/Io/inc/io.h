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

#ifndef _IO_H_
#define _IO_H_
/** \brief OpenDRV IO Header File
 **
 ** This file shall be included by all files using any OpenDRV IO API.
 **
 ** \file io.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Clk
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
 * v0.1.0 20081126 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Gen_Types.h"
#include "Io_Cfg.h"
#include "Io_Arch.h"

/*==================[macros]=================================================*/
/** \brief IO driver set port service
 **
 ** This IO driver service shall be called to set a port to a specified value.
 ** The bits not configured of this port will stay unchaged. Writing to an
 ** input is not defined.
 **
 ** \param[in] port indicates the port to be set
 ** \param[in] value indicate the value to be set to this port
 ** \return IO_E_OK is always returned
 **/
#define Io_SetPort(port, value) 				\
	IO_E_OK;											\
	{													\
		Io_SetPort_Arch(port, value, mask);	\
	}

/** \brief IO driver set pin service
 **
 ** This IO driver service shall be called to set a pint to a specific value.
 **
 ** \param[in] pin indicates the pin to be set
 ** \param[in] value indicates the value to be set to this pin
 ** \return IO_E_OK is always returned
 **/
#define Io_SetPin(pin, value)					\
	IO_E_OK;											\
	{													\
		Io_SetPort_Arch(port, value);			\
	}

/** \brief IO driver get port service
 **
 ** This IO driver service shall be called to get the status of a specific port.
 **
 ** \param[in] port inidcates the port to be readed
 ** \param[out] value the value of the readed port is set to this variable
 ** \return IO_E_OK is always returned
 **/
#define Io_GetPort(port, value)				\
	IO_E_OK;											\
	{													\
		Io_GetPort_Arch(port, value);			\
	}

/** \brief IO driver get pin service 
 **
 ** This IO driver service shall be called to get the state of a specific pin
 **
 ** \param[in] pin indicates the pin to be readed
 ** \param[out] value the status of the readed port is set to this variable
 ** \return IO_E_OK is always returned
 **/
#define Io_GetPin(pin, value)					\
	IO_E_OK;											\
	{													\
		Io_GetPint_Arch(pin, value)			\
	}													
		
/*==================[typedef]================================================*/
/** \brief IO driver return type definition */
typedef uint8 Io_ReturnType;

/** \brief IO driver configuration type definition */
typedef struct {
	Io_ConfigArchType Io_Arch;
} Io_ConfigType;

/** \brief IO driver configuration reference type definition */
typedef Io_ConfigType* Io_ConfigRefType;

/** \brief IO driver port type configuration */
typedef uint8 Io_PortType;

/** \brief IO driver port value type definition */
#if   (IO_PORT_BITS_WIDTH == 8)
typedef uint8 Io_PortValue;
#elif (IO_PORT_BITS_WIDTH == 16)
typedef uint16 Io_PortValue;
#elif (IO_PORT_BITS_WIDHT == 32)
typedef uint32 Io_PortValue;
#else
#error invalid IO_PORT_BITS_WIDHT value
#endif

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief IO driver init service
 **
 ** This IO driver service shall be called to initialize the IO driver. Calls
 ** to any other IO driver service before initialization is not allowed.
 **
 ** \param[in] config pointer to the IO driver configuration
 ** \return IO_E_OK	if no error occurs
 ** \return IO_E_PARAM if the configuration is invalid
 ** \return IO_E_NOTOK if other error occurs
 **/
extern Io_ReturnType Io_Init(const Io_ConfigRefType config);

/** \brief IO driver re init service
 **
 ** This IO driver service shall be called to re initialize the IO driver.
 ** This services allows the user to change the port configuration on the go.
 **
 ** \param[in] config pointer to the new IO driver configuration
 ** \return IO_E_OK if no error occurs
 ** \return IO_E_PARAM if the configuration is invalid
 ** \return IO_E_NOTOK if other error occurs
 **/
extern Io_RetunrType Io_ReInit(const Io_ConfigRefType config);

/** \brief IO driver de-init service
 **
 ** This IO driver service shall be called to de-initialize the IO driver.
 **
 ** \return IO_E_OK if no error occurs
 ** \return IO_E_NOTOK if any error occurs
 **/
extern Io_ReturnType Io_DeInit();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CLK_H_ */

