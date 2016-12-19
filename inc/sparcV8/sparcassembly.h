/* Copyright 2016, Gerardo Puga (UNLP)
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

#ifndef _SPARC_SPARCASMCONSTANTS_H_
#define _SPARC_SPARCASMCONSTANTS_H_

/** \brief SPARC Architecture Support Header File
 **
 ** \file sparcV8/sparcsyscalls.h
 ** \arch sparcV8
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/


/*==================[macros]=================================================*/


#define SPARC_DEFAULT_REGISTER_WINDOW_COUNT 8

#define SPARC_PSR_IMPL_MASK       0xf0000000
#define SPARC_PSR_VER_MASK        0x0f000000
#define SPARC_PSR_ICC_MASK        0x00f00000
#define SPARC_PSR_RESERVED_MASK   0x000fc000
#define SPARC_PSR_EC_MASK         0x00002000
#define SPARC_PSR_EF_MASK         0x00001000
#define SPARC_PSR_PIL_MASK        0x00000f00
#define SPARC_PSR_S_MASK          0x00000080
#define SPARC_PSR_PS_MASK         0x00000040
#define SPARC_PSR_ET_MASK         0x00000020
#define SPARC_PSR_CWP_MASK        0x0000001f

#define SPARC_NON_RESTORABLE_BITS_IN_PSR (SPARC_PSR_IMPL_MASK | SPARC_PSR_VER_MASK | SPARC_PSR_RESERVED_MASK | SPARC_PSR_ET_MASK | SPARC_PSR_CWP_MASK)


#define SPARC_INITIAL_PSR_VALUE_IN_TASK_CONTEXT (SPARC_PSR_EF_MASK | SPARC_PSR_S_MASK | SPARC_PSR_PS_MASK)


/** \brief Amount of bytes to reserve on a thread's stack in order to store its integer context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 */
#define SPARC_STACK_BARE_MINIMUM_STACK_FRAME_RESERVATION_SIZE 96


/** \brief Amount of bytes to reserve on a thread's stack in order to store its integer context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 */
#define SPARC_STACK_BASE_CONTEXT_RESERVATION_SIZE 80


/** \brief Amount of bytes to reserve on a thread's stack in order to store its floating point context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 * */
#define SPARC_STACK_FP_CONTEXT_RESERVATION_SIZE 0

#define SPARC_SYSCALL_SERVICE_SW_TRAP_NUMBER              0x00
#define SPARC_CALL_DEBUGGER_SW_TRAP_NUMBER                0x01
#define SPARC_SET_TASK_CONTEXT_SERVICE_SW_TRAP_NUMBER     0x02
#define SPARC_REPLACE_TASK_CONTEXT_SERVICE_SW_TRAP_NUMBER 0x03


#define SPARC_SYSCALL_ID_DISABLE_TRAPS       0x00


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* _SPARC_SPARCASMCONSTANTS_H_ */
