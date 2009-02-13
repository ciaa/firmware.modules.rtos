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

#ifndef _DIO_H_
#define _DIO_H_
/** \brief OpenDRV DIO Header File
 **
 ** This file shall be included by all files using any OpenDRV DIO API.
 **
 ** \file Dio.h
 **
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Dio
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
 * 20090213 v0.1.1 MaCe raname Io driver to Dio
 * 20090125 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/
#include "Types.h"
#include "Dio_Cfg.h"
#include "Dio_Arch.h"

/*==================[macros]=================================================*/
/** \brief High state */
/* \req DIO089-1/2 Values used by the DIO Driver for the software level of
 *	Channels are either STD_HIGH or STD_LOW. */
/* \dev DIO089-1/2 the high state is called DIO_HIGH and not STD_HIGH */
#define DIO_HIGH	1

/** \brief Low state */
/* \req DIO089-2/2 Values used by the DIO Driver for the software level of
 * Channels are either STD_HIGH or STD_LOW. */
/* \dev DIO089-2/2 the low state is called DIO_LOW and not STD_LOW */
#define DIO_LOW	0

/** \brief Dio Invalid Channel Id error code */
/* \req DIO065-1/3 The Dio module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * DIO_E_PARAM_INVALID_CHANNEL_ID, DIO_E_PARAM_INVALID_PORT_ID and
 * DIO_E_PARAM_INVALID_GROUP_ID
 */
#define DIO_E_PARAM_INVALID_CHANNEL_ID				10

/** \brief Dio Invalid Port Id error code */
/* \req DIO065-2/3 The Dio module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * DIO_E_PARAM_INVALID_CHANNEL_ID, DIO_E_PARAM_INVALID_PORT_ID and
 * DIO_E_PARAM_INVALID_GROUP_ID
 */
#define DIO_E_PARAM_INVALID_PORT_ID					20

/** \brief Dio Invalid Group Id error code */
/* \req DIO065-3/3 The Dio module shall detect the following errors and
 * exceptions depending on its build version (development/production mode):
 * DIO_E_PARAM_INVALID_CHANNEL_ID, DIO_E_PARAM_INVALID_PORT_ID and
 * DIO_E_PARAM_INVALID_GROUP_ID
 */
#define DIO_E_PARAM_INVALID_GROUP_ID				31

#if (DioDevErrorDetect == DISABLE)
/** \brief Dio Driver Read Channel service 
 **
 ** This Dio driver service shall used to read the state of a specific
 ** channel. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] ChannelId IO of DIO Channel
 ** \return Dio_LevelType DIO_HIGH the physical level of the corresponding Pin is high
 **							  DIO_LOW the physical level of the corresponding Pin is low
 **/
#define /* Dio_LevelType */ Dio_ReadChannel( /* Dio_ChannelType */ ChannelId) \
	Dio_ReadChannel_Arch(ChannelId)

/** \brief Dio Driver Write Channel service 
 **
 ** This Dio driver service shall used to write the state of a specific
 ** channel. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] ChannelId IO of DIO Channel
 ** \param[in] Level Level
 ** \return None
 **/
#define /* void */ Dio_WriteChannel( /* Dio_ChannelType */ ChannelId, /* Dio_LevelType */ Level)	\
	Dio_WriteChannel_Arch(ChannelId, Level)

/** \brief Dio Read Port service 
 **
 ** This Dio driver service shall used to read the state of a specific
 ** port. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] PortId IO of DIO Channel
 ** \return Dio_PortLevelType Level of all channels of that port
 **/
#define /* Dio_PortLevelType */ Dio_ReadPort( /* Dio_PortType */ PortId)	\
	Dio_ReadPort_Arch(PortId)

/** \brief Dio Driver Write Port service 
 **
 ** This Dio driver service shall used to write the state of a specific
 ** port. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] PortId IO of DIO Channel
 ** \param[in] Level Level
 ** \return None
 **/
#define /* void */ Dio_WritePort( /*Dio_PortType */ PortId, /* Dio_PortLevelType */ Level)	\
	Dio_WritePort_Arch(PortId, Level)

#endif /* #if (DioDevErrorDetect == DISABLE) */

/*==================[typedef]================================================*/
/** \brief DIO driver configuration type definition */
typedef struct {
   Dio_ConfigArchType Dio_Arch;
} Dio_ConfigType;

/** \brief DIO driver configuration reference type definition */
typedef Dio_ConfigType* Dio_ConfigRefType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Dio driver init service
 **
 ** This Dio driver service shall be called to initialize the Dio driver. Calls
 ** to any other Dio driver service before initialization is not allowed.
 **
 ** \param[in] config pointer to the Dio driver configuration
 ** \return DIO_E_OK	if no error occurs
 ** \return DIO_E_PARAM if the configuration is invalid
 ** \return DIO_E_NOTOK if other error occurs
 **/
extern Dio_ReturnType Dio_Init(const Dio_ConfigRefType Config);

/** \brief Dio driver de-init service
 **
 ** This Dio driver service shall be called to de-initialize the Dio driver.
 **
 ** \return IO_E_OK if no error occurs
 ** \return IO_E_NOTOK if any error occurs
 **/
extern Dio_ReturnType Dio_ReInit();

#if (DioDevErrorDetect == ENABLE)
/** \brief Dio Driver Read Channel service 
 **
 ** This Dio driver service shall used to read the state of a specific
 ** channel. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] ChannelId IO of DIO Channel
 ** \return Dio_LevelType DIO_HIGH the physical level of the corresponding Pin is high
 **							  DIO_LOW the physical level of the corresponding Pin is low
 **/
extern Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/** \brief Dio Driver Write Channel service 
 **
 ** This Dio driver service shall used to write the state of a specific
 ** channel. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] ChannelId IO of DIO Channel
 ** \param[in] Level Level
 ** \return None
 **/
extern void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/** \brief Dio Read Port service 
 **
 ** This Dio driver service shall used to read the state of a specific
 ** port. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] PortId IO of DIO Channel
 ** \return Dio_PortLevelType Level of all channels of that port
 **/
extern Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/** \brief Dio Driver Write Port service 
 **
 ** This Dio driver service shall used to write the state of a specific
 ** port. This service is implemented as function if DioDevErrorDetect is
 ** ENABLE and as macro if DioDevErrorDetect is DISABLE
 **
 ** \param[in] PortId IO of DIO Channel
 ** \param[in] Level Level
 ** \return None
 **/
extern void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

#endif /* #if (DioDevErrorDetect == ENABLE) */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DIO_H_ */

