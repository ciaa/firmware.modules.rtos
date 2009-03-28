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
/** \brief OpenCOM Header File
 **
 ** This file shall be included by all files using any OpenCOM API
 **
 ** \file com.h
 **
 **/

/** \addtogroup OpenCOM OpenCOM
 ** @{ */
/** \addtogroup OpenCOM_Global OpenCOM Global
 ** \ingroup FreeOSEK
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
#include "Com_Arch.h"	/* include COM Arch header file */

/*==================[macros]=================================================*/
#ifndef E_OK
/** \brief Definition return value E_OK */
#define E_OK					((StatusType)0U)
#elif (E_OK != ((StatusType)0U))
#error E_OK defined with a wrong value
#endif
/** \brief Definition return value E_COM_ID */
#define E_COM_ID					((StatusType)1U)
/** \brief Definition return value E_COM_LENGTH */
#define E_COM_LENGTH				((StatusType)2U)
/** \brief Definition return value E_COM_LIMIT */
#define E_COM_LIMIT				((StatusType)3U)
/** \brief Definition return value E_COM_NOMSG */
#define E_COM_NOMSG				((StatusType)4U)

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Start COM
 **
 ** TODO add information
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
	LenghtRef Length
);

extern StatusType SendZeroMessage
(
	MessageIdentifier Message
);

extern StatusType GetMessageState
(
	MessageIdentifier Message
);



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _COM_H_ */

