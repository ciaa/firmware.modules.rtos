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

/** \brief OpenSEK ClearEvent Implementation File
 **
 ** This file implements the ClearEvent API
 **
 ** \file ClearEvent.c
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup OpenSEK_Global
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * KLi          Kang Li
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090128 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20081113 v0.1.1 KLi  Added memory layout attribute macros
 * 20080814 v0.1.0 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#if (OSEK_MEMMAP == ENABLE)
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"
#endif

StatusType ClearEvent
(
	EventMaskType Mask
)
{
	/* \req OSEK_SYS_3.16 The system service StatusType
	 * ClearEvent ( EventMaskType Mask ) shall be defined */

	/* \req OSEK_SYS_3.16.2 Possible return values in Standard mode is E_OK */
	StatusType ret = E_OK;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if ( !TasksConst[GetRunningTask()].ConstFlags.Extended )
	{
		/* \req OSEK_SYS_3.16.3-1/2 Extra possible return values in Extended
		 * mode are E_OS_ACCESS, E_OS_CALLEVEL */
		ret = E_OS_ACCESS;
	}
	else if ( GetCallingContext() != CONTEXT_TASK )
	{
		/* \req OSEK_SYS_3.16.3-2/2 Extra possible return values in Extended
		 * mode are E_OS_ACCESS, E_OS_CALLEVEL */
		ret = E_OS_CALLEVEL;
	}
	else
#endif
	{
		/* enter to critical code */
		IntSecure_Start();

		/* \req OSEK_SYS_3.16.1 The events of the extended task calling ClearEvent
		 * are cleared according to the event mask Mask */
		TasksVar[GetRunningTask()].Events &=
			(EventMaskType)~( Mask & TasksConst[GetRunningTask()].EventsMask );

		/* finish cirtical code */
		IntSecure_End();

	}

#if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
		(HOOK_ERRORHOOK == ENABLE) )
	/* \req OSEK_ERR_1.3-9/xx The ErrorHook hook routine shall be called if a
	 * system service returns a StatusType value not equal to E_OK.*/
	/* \req OSEK_ERR_1.3.1-9/xx The hook routine ErrorHook is not called if a
	 * system service is called from the ErrorHook itself. */
   if ( ( ret != E_OK ) && (ErrorHookRunning != 1))
	{
		SetError_Api(OSServiceId_ClearEvent);
		SetError_Param1(Mask);
		SetError_Ret(ret);
		SetError_Msg("ClearEvent returns != than E_OK");
		SetError_ErrorHook();
	}
#endif

	return ret;
}

#if (OSEK_MEMMAP == ENABLE)
#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

