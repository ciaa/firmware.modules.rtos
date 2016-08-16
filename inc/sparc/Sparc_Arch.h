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

#ifndef _SPARC_ARCH_H_
#define _SPARC_ARCH_H_

/** \brief SPARC Architecture Support Header File
 **
 ** \file sparc/Os_Internal_Arch.h
 ** \arch sparc
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/** \brief Bit mask for the PIL field in the PSR register
 **/
#define SPARC_PSR_PIL_MASK 0x0f00

/** \brief Bit mask for the ET bit in the PSR register
 **/
#define SPARC_PSR_ET_MASK  0x0020

/** \brief Bit mask for the CWP field in the PSR register
 **/
#define SPARC_PSR_CWP_MASK 0x001f


/** \brief Amount of bytes to reserve on a thread's stack in order to store its integer context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 **/
#define SPARC_STACK_BARE_MINIMUM_STACK_FRAME_RESERVATION_SIZE 92


/** \brief Amount of bytes to reserve on a thread's stack in order to store its integer context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 **/
#define SPARC_STACK_BASE_CONTEXT_RESERVATION_SIZE 80

/** \brief Amount of bytes to reserve on a thread's stack in order to store its floating point context information.
 *
 * For alignments reasons this number must be a multiple of 8 (double word).
 **/
#define SPARC_STACK_FP_CONTEXT_RESERVATION_SIZE 0


/** \brief Software trap number for syscall services.
 **/
#define SPARC_SYSCALL_SERVICE_TRAP_NUMBER 0x00

/** \brief Software trap number for the CallTask service.
 **/
#define SPARC_CALLTASK_SERVICE_TRAP_NUMBER 0x02

/** \brief Software trap number for the JmpTask service.
 **/
#define SPARC_CALLTASK_SERVICE_TRAP_NUMBER 0x03


/** \brief Syscall service ID - Disable traps.
 **/
#define SPARC_SYSCALL_ID_DISABLE_TRAPS 0x00

/** \brief Syscall service ID - Mask interrupts
 **/
#define SPARC_SYSCALL_ID_MASK_INTR     0x01

/** \brief Syscall service ID - Unmask interrupts
 **/
#define SPARC_SYSCALL_ID_UNMASK_INTR   0x02

/** \brief Syscall service ID - Reboot system
 **/
#define SPARC_SYSCALL_ID_REBOOT_SYSTEM 0x03



/*==================[typedef]================================================*/
/*****************************************************************************
 * Please define here all needed types that will be used only internal by
 * the OS and only for this architecture and which will not depend on the
 * configuration. Normally this section should be empty.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external data declaration]==============================*/
/*****************************************************************************
 * Please declare here all exported data defined in Osek_Internal_Arch.c
 * that will be visible only internal to the OS for this architecture.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external functions declaration]=========================*/

/*
 * Syscall service functions, defined in syscallservices.s
 * */

void sparcSystemServiceEnableTraps();

void sparcSystemServiceDisableTraps();

void sparcSystemServiceMaskInterrupts();

void sparcSystemServiceUnMaskInterrupts();

void sparcSystemServiceRebootSystem();

void sparcSystemServiceCallDebugger();

void sparcSystemServiceTriggerCallTask();

void sparcSystemServiceTriggerJmpTask();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */

