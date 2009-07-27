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

/** \brief FreeOSEK Com ReceiveMessage Implementation File
 **
 ** This file implements the ReceiveMessage API
 **
 ** \file ReceiveMessage.c
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Com
 ** @{ */
/** \addtogroup FreeOSEK_Com_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090710 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Com_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#if (COM_MEMMAP == ENABLE)
#define OpenCOM_START_SEC_CODE
#include "MemMap.h"
#endif

StatusType ReceiveMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef
)
{

	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) 
	/* first rx id is COM_TX_MAX_MESSAGE, so remove this offset */
	Message -= COM_TX_MAX_MESSAGE;

	/* check that the message identifier is on range */
	if ( Message > COM_RX_MAX_MESSAGE )
	{
		/* in other case return an error */
		ret = E_COM_ID;
	}
	/* check that the message is not zero-length neither dynamic-lenght neither
		a tx message */
	else if (! ( ( Com_RxMessageObjectsConst[Message].Flags.MsgProp == COM_MSG_PROP_RX_STAT_INT ) ||
					 ( Com_RxMessageObjectsConst[Message].Flags.MsgProp == COM_MSG_PROP_RX_STAT_EXT ) ) )
	{
		/* in other case return an error */
		ret = E_COM_ID;
	}
	else
	{
#endif /* #if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)  */
#if ( COM_QUEUED_MESSAGES == ENABLE )
		/* TODO for QUEUED messages */
		if ( 1 /* TODO */ )
		{
			ret = E_COM_NOMSG;
		}
		else if ( 1 /* TODO */ )
		{
			ret = E_COM_LIMIT;
			
			/* clear overflow flag */
			/* TODO */

#endif  /* #if ( COM_QUEUED_MESSAGES == ENABLE ) */

			/* ReceiveMessage main functionality */

			/* receive message */
			/* TODO */

			/* clear notifications flags */
			/* TODO */

#if ( COM_QUEUED_MESSAGES == ENABLE )
		}
#endif /* #if ( COM_QUEUED_MESSAGES == ENABLE ) */

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) 
	}
#endif /* #if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)  */

#if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
		(HOOK_ERRORHOOK == ENABLE) )
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(COMServiceId_SendMessage);
		SetError_Param1(Message);
		SetError_Param2(DataRef);
		SetError_Ret(ret);
		SetError_Msg("SendMessage returns != than E_OK");
		SetError_ErrorHook();
	}
#endif

	return ret;
}

#if (COM_MEMMAP == ENABLE)
#define OpenCOM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

