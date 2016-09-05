/* Copyright 2016, Gerardo Puga (UNLP)
 *
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

#ifndef _GAISLER_GRLIB_H_
#define _GAISLER_GRLIB_H_

/** \brief FreeOSEK Internal Architecture CPU Auxiliar Header File
 **
 ** \file sparc/leon3/grlib.h
 ** \arch sparc/leon3
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[cpu macros]=============================================*/


/*==================[inclusions]=============================================*/


/*==================[macros]=================================================*/


#define IRQMP_INTERRUPT_LEVEL_REGISTER                       (0x00)
#define IRQMP_INTERRUPT_PENDING_REGISTER                     (0x04)
#define IRQMP_INTERRUPT_FORCE_REGISTER                       (0x08)
#define IRQMP_INTERRUPT_CLEAR_REGISTER                       (0x0c)
#define IRQMP_MULTIPROCESSOR_STATUS_REGISTER                 (0x10)
#define IRQMP_INTERRUPT_BROADCAST_REGISTER                   (0x14)
#define IRQMP_MP_INTERRUPT_MASK_REGISTER(cpu)                (0x40 + 0x04 * (cpu))
#define IRQMP_MP_INTERRUPT_FORCE_REGISTER(cpu)               (0x80 + 0x04 * (cpu))
#define IRQMP_MP_EXTENDED_INTERRUPT_ACKNOLEDGE_REGISTER(cpu) (0xc4 + 0x04 * (cpu))


/*==================[typedef]================================================*/


typedef uint32 grDeviceAddress;

typedef uint32 grDeviceRegisterValue;

/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/


void grRegisterWrite(grDeviceAddress baseAddr, grDeviceAddress offset, grDeviceRegisterValue newValue);

grDeviceRegisterValue grRegisterRead(grDeviceAddress baseAddr, grDeviceAddress offset);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _GAISLER_GRLIB_H_ */

