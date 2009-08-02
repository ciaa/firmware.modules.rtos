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

/** \brief FreeOSEK Com SendMessage Implementation File
 **
 ** This file implements the SendMessage API
 **
 ** \file SendMessage.c
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
 * 20090708 v0.1.0 MaCe initial version
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

/* SendMessage is not necesarry if no transmitted message are defined */
#if ( COM_SENDMESSAGE == ENABLE )
StatusType SendMessage
(
	MessageIdentifier Message,
	ApplicationDataRef DataRef
)
{
	StatusType ret = E_OK;		/* return value */
	Com_NetType txnet;			/* tx net message index */
	Com_PDUType txpdu;			/* tx pdu message index */
	uint16 loopi;					/* loop variable */
	uint16 tmp = 0;				/* tmp data */
	uint16 size;					/* size in bits */
	uint8* dstbuf;					/* buffer to save the data */
	uint8 shift;					/* value to shift */
	uint8 remainbits;				/* remian bits to be copied */

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) 
	/* check that the message is on range */
	if ( Message > COM_TX_MAX_MESSAGE )
	{
		/* in other case return an error */
		ret = E_COM_ID;
	}
	/* check that the message is not zero-length neither dynamic-lenght neither
		a rx message */
	else if (! ( ( Com_TxMsgObjsCst[Message].Flags.Prop == COM_MSG_PROP_TX_STAT_INT ) ||
					 ( Com_TxMsgObjsCst[Message].Flags.Prop == COM_MSG_PROP_TX_STAT_EXT ) ) )
	{
		/* in other case return an error */
		ret = E_COM_ID;
	}
	else
	{
#endif /* #if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)  */

		/* SendMessage main functionality */

		/* check communication type */
		if ( Com_TxMsgObjsCst[Message].Flags.Prop & COM_MSG_PROP_EXTERNAL )
		{
			/* implement the external communication */

			/* get network message */
			txnet = Com_TxMsgObjsCst[Message].Net;

			/* get PDU message */
			txpdu = Com_TxNetObjsCst[txnet].PDU;

			/* get buffer */
			dstbuf = Com_TxMsgObjsCst[Message].Data;

			if ( Com_TxNetObjsCst[txnet].Flags.DataInt == COM_NM_DI_BYTEARRAY )
			{
				/* process data as array */
				/* all bytes are alligned to 8 bits */
				/* always 8 bits are copied */

				/* copy the data to the underlayer PDU */
				/* less 3 bits of Com_TxMsgObjsCst[Message].Size shall be 0, 
					byte alligned */
				for ( loopi = 0; loopi < ( Com_TxMsgObjsCst[Message].Size >> 3 ); loopi++)
				{
					dstbuf[loopi] = DataRef[loopi];
				}
			}
			else
			{
				/* process unsigned integer */
				shift = Com_TxNetObjsCst[txnet].Flags.Offset;
				remainbits = Com_TxMsgObjsCst[Message].Size;

				if ( Com_TxNetObjsCst[txnet].Flags.BitOrd == COM_NM_BO_LITTLEENDIAN )
				{
					/* little-endian */

					/* first byte */
					tmp = dstbuf[0];
					tmp &= ( 0xFF >> ( 8 - shift ) );
					tmp |= ( DataRef[loopi] << shift);
					dstbuf[0] = (uint8)tmp;
					tmp >>= 8;
					remainbits -= ( 8 - shift );

					/* midle bytes */
					for (loopi = 1; loopi < ( Com_TxMsgObjsCst[Message].Size >> 3 ) - 1; loopi++)
					{
						tmp |= ( DataRef[loopi] << shift);
						dstbuf[loopi] = (uint8)tmp;
						tmp >>= 8;
						remainbits -= 8;
					}

					/* last byte */
					dstbuf[loopi] &= 0xff << remainbits;
					dstbuf[loopi] |= (uint8)tmp;		
				}
				else
				{
					/* big-endian */
				}

				
			}

			/* check if the unter layer tx has to be triggered only to be done if:
					- the message has property triggered
					- the underlayer I-PDU is configured != to periodic */
			if ( ( Com_TxMsgObjsCst[Message].Flags.Trans == COM_MSG_TRANS_TRIGGERED ) &&
				  ( Com_TxPduObjsCst[txpdu].Flags.Prop != COM_TX_PDU_PERIODIC ) )
			{
				/* trigger the transmission of the I-PDU */
				Com_TxTrigger[Com_TxPduObjsCst[txpdu].Layer](Com_TxPduObjsCst[txpdu].LayerPDU);
			}
		}
		else
		{
			/* implement the internal communication */
			/* TODO */
		}

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
#endif /* #if ( (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) && \
			(HOOK_ERRORHOOK == ENABLE) ) */

	return ret;
}
#endif /* #if ( COM_SENDMESSAGE == ENABLE ) */

#if (COM_MEMMAP == ENABLE)
#define OpenCOM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

