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

#ifndef _COM_H_
#define _COM_H_
/** \brief FreeOSEK Com Header File
 **
 ** This file shall be included by all files using any OpenCOM API
 **
 ** \file com.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Com Communication
 ** @{ */
/** \addtogroup FreeOSEK_Com_Global Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090322 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Types.h"		/* include standard types header file */
#include "os.h"			/* include os header file */
#include "Com_Cfg.h"		/* include COM configuration header file */

/*==================[macros]=================================================*/
/** \brief Definition return value E_COM_ID */
#define E_COM_ID					((StatusType)1U)
/** \brief Definition return value E_COM_LENGTH */
#define E_COM_LENGTH				((StatusType)2U)
/** \brief Definition return value E_COM_LIMIT */
#define E_COM_LIMIT				((StatusType)3U)
/** \brief Definition return value E_COM_NOMSG */
#define E_COM_NOMSG				((StatusType)4U)

/** \brief COM Shutdown Mode type immediate */
#define COM_SHUTDOWN_IMMEDIATE	((COMShutdownModeType)1U)

/** \brief COM false value
 **
 ** this macro is used for FlagValue, CalloutReturnType types and for
 ** the ReadFlag_, COMCallout interfaces
 **/
#define COM_FALSE					0U

/** \brief COM true value
 **
 ** this macro is used for FlagValue, CalloutReturnType types and for
 ** the ReadFlag_, COMCallout interfaces
 **/
#define COM_TRUE					1U

/*==================[typedef]================================================*/
/** \brief COM Application Mode type definition */
typedef uint8 COMApplicationModeType;

/** \brief COM Shutdown Mode type definition */
typedef uint8 COMShutdownModeType;

/** \brief Callout return type definition 
 **
 ** Indicates at the exit of a callout whether the IL shall continue or abandon
 ** further processing of the current message or I-PDU.
 **/
typedef uint8 CalloutReturnType;

/** \brief Communication Service Id type definition
 **
 ** Unique identifier for an OSEK COM service.
 **/
typedef enum
{
	COMServiceId_COMApplicationMode,
	COMServiceId_GetMessageStatus,
	COMServiceId_InitMessage,
	COMServiceId_ReceiveDynamicMessage,
	COMServiceId_ReceiveMessage,
	COMServiceId_SendDynamicMessage,
	COMServiceId_SendMessage,
	COMServiceId_SendZeroMessage,
	COMServiceId_StartCOM,
	COMServiceId_StartPeriodic,
	COMServiceId_StopCOM
} COMServiceIdType;

/** \brief Application Data Reference type definition */
typedef void* ApplicationDataRef;

/** \brief Length Reference type definition */
typedef uint16* LengthRef;

/** \brief Flag Value type definition
 **
 ** Current State of a message flag
 **/
typedef uint8 FlagValue;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Start Communication
 **
 ** The service StartCOM starts and initialises the OSEK COM implementation
 ** in the requested application mode. If StartCOM fails, initialisation of
 ** the OSEK COM implementation aborts and StartCOM returns a status code as
 ** specified below. StartCOM shall be called from within a task if an
 ** OSEK-compliant operating system is used. Before returning, the service
 ** StartCOM calls the application function StartCOMExtension.

 **
 ** \param[in] Mode COM application mode
 ** \return
 **/
extern StatusType StartCOM
(
	COMApplicationModeType Mode
);

/** \brief Stop COM
 **
 ** TODO add information
 **/
extern StatusType StopCOM
(
	COMShutdownModeType Mode
);

/** \brief Get COM Application Mode
 **
 ** TODO add information
 **/
extern COMApplicationModeType GetCOMApplicationMode
(
	void
);

extern StatusType InitMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef
);

extern StatusType StartPeriodic
(
	void
);

extern StatusType StopPeriodic
(
	void
);

extern StatusType SendMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef
);

extern StatusType ReceiveMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef
);

extern StatusType SendDynamicMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef,
	LengthRef Length
);

extern StatusType ReceiveDynamicMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef,
	LengthRef Length
);

extern StatusType SendZeroMessage
(
	MessageIdentifier Message
);

extern StatusType GetMessageStatus
(
	MessageIdentifier Message
);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_H_ */

