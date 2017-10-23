/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2016, Gerardo Puga (UNLP)
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _OS_INTERNAL_ARCH_CFG_H_
#define _OS_INTERNAL_ARCH_CFG_H_

/** \brief FreeOSEK Os Generated Internal Architecture Configuration Header File
 **
 ** This file content the internal generated architecture dependent
 ** configuration of FreeOSEK.
 **
 ** \file sparc/Os_Internal_Arch_Cfg.h
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/


#include "sparcassembly.h"


/*==================[typedef]================================================*/


/** \brief Task Context Type */
typedef struct {
   
   /* The following data field nees to be aligned on a 8-byte boundary, so that I can use ldd and std
      instructions when loading/storing it from the context handling code. */
   uint32 TaskContextData[(SPARC_STACK_BASE_CONTEXT_RESERVATION_SIZE + SPARC_STACK_FP_CONTEXT_RESERVATION_SIZE) / 4] __attribute__ ((aligned (8))); /* TODO Ask mariano about this attribute, he won't be happy like this... */
   
} TaskContextType;


/** \brief Task Context Type */
typedef TaskContextType* TaskContextRefType;


/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/


void OSEK_COUNTER_GPTIMER0_IRQHandler(void);

void sparcSetupUserISRs(void);

uint32 sparcGetHardwareTimersInUseMask(void);

uint32 sparcGetHardwareTimerID(uint32 hwTimerIndex);



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_CFG_H_ */

