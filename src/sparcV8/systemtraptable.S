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

/** \brief SPARC V8 System Calls service funcions
 **
 ** \file sparc/syscallservices.s
 ** \arch sparc
 **/


#include "sparcassembly.h"


/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

        !
        ! The following code is the SPARC v8 system trap table.
        !
        ! The table has 256 entries, each of which is 4 words long (16 bytes). Those
        ! four words are the preamble of the actual trap handler routine.
        !
        ! The code herein sets the following entry context for all the trap handle routines:
        !     %l0 = psr
        !     %l1 = PC
        !     %l2 = nPC
        !     %l3 = trap type number
        !

        .global sparc_system_trap_table
        .type   sparc_system_trap_table, #object

        .extern sparcDefaultTrapHandler, sparcWindowUnderflowTrapHandler, sparcWindowOverflowTrapHandler, sparcTaskContextAwareTrapHandler

        !
        ! The system trap table must be aligned to a multiple of 4096 bytes (lower 12 bits of the
        ! address must be 0).
        .align 4096

sparc_system_trap_table:

        !
        ! [ TRAP TYPE 0x00 ]
        !
        ! Priority    : 1
        ! Description : "Reset"
        !
trap_type_00:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x00, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x01 ]
        !
        ! Priority    : 5
        ! Description : "Text fault, instruction access exception"
        !
trap_type_01:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x01, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x02 ]
        !
        ! Priority    : 7
        ! Description : "Illegal instruction"
        !
trap_type_02:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x02, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x03 ]
        !
        ! Priority    : 6
        ! Description : "Privileged instruction"
        !
trap_type_03:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x03, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x04 ]
        !
        ! Priority    : 8
        ! Description : "Floating point disabled"
        !
trap_type_04:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x04, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x05 ]
        !
        ! Priority    : 9
        ! Description : "Window overflow"
        !
trap_type_05:
        mov     %psr, %l0
        sethi   %hi(sparcWindowOverflowTrapHandler), %l3
        jmpl    %l3 + %lo(sparcWindowOverflowTrapHandler), %g0
        mov     0x05, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x06 ]
        !
        ! Priority    : 9
        ! Description : "Window underflow"
        !
trap_type_06:
        mov     %psr, %l0
        sethi   %hi(sparcWindowUnderflowTrapHandler), %l3
        jmpl    %l3 + %lo(sparcWindowUnderflowTrapHandler), %g0
        mov     0x06, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x07 ]
        !
        ! Priority    : 10
        ! Description : "Memory address not aligned"
        !
trap_type_07:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x07, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x08 ]
        !
        ! Priority    : 11
        ! Description : "Floating point exception"
        !
trap_type_08:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x08, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x09 ]
        !
        ! Priority    : 13
        ! Description : "Data fault, data access exception"
        !
trap_type_09:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x09, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0a ]
        !
        ! Priority    : 14
        ! Description : "Tag overflow"
        !
trap_type_0a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0b ]
        !
        ! Priority    : 8
        ! Description : "Watchpoint detected"
        !
trap_type_0b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0c ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_0c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0d ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_0d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0e ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_0e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x0f ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_0f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x0f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x10 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_10:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x10, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x11 ]
        !
        ! Priority    : 31
        ! Description : "IRQ 1"
        !
trap_type_11:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x01, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x12 ]
        !
        ! Priority    : 30
        ! Description : "IRQ 2"
        !
trap_type_12:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x02, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x13 ]
        !
        ! Priority    : 29
        ! Description : "IRQ 3"
        !
trap_type_13:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x03, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x14 ]
        !
        ! Priority    : 28
        ! Description : "IRQ 4"
        !
trap_type_14:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x04, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x15 ]
        !
        ! Priority    : 27
        ! Description : "IRQ 5"
        !
trap_type_15:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x05, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x16 ]
        !
        ! Priority    : 26
        ! Description : "IRQ 6"
        !
trap_type_16:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x06, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x17 ]
        !
        ! Priority    : 25
        ! Description : "IRQ 7"
        !
trap_type_17:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x07, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x18 ]
        !
        ! Priority    : 24
        ! Description : "IRQ 8"
        !
trap_type_18:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x08, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x19 ]
        !
        ! Priority    : 23
        ! Description : "IRQ 9"
        !
trap_type_19:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x09, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1a ]
        !
        ! Priority    : 22
        ! Description : "IRQ 10"
        !
trap_type_1a:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0a, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1b ]
        !
        ! Priority    : 21
        ! Description : "IRQ 11"
        !
trap_type_1b:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0b, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1c ]
        !
        ! Priority    : 20
        ! Description : "IRQ 12"
        !
trap_type_1c:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0c, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1d ]
        !
        ! Priority    : 19
        ! Description : "IRQ 13"
        !
trap_type_1d:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0d, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1e ]
        !
        ! Priority    : 18
        ! Description : "IRQ 14"
        !
trap_type_1e:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0e, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x1f ]
        !
        ! Priority    : 17
        ! Description : "IRQ 15"
        !
trap_type_1f:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0f, %l3    ! Task context aware trap handlers table index, with bit 5 set to 0 to indicate this is an external interrupt trap handler.


        !
        ! [ TRAP TYPE 0x20 ]
        !
        ! Priority    : 4
        ! Description : "Register access error (you're hosed!)"
        !
trap_type_20:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x20, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x21 ]
        !
        ! Priority    : 3
        ! Description : "Text fault, instruction access error"
        !
trap_type_21:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x21, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x22 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_22:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x22, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x23 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_23:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x23, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x24 ]
        !
        ! Priority    : 8
        ! Description : "Coprocessor disabled"
        !
trap_type_24:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x24, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x25 ]
        !
        ! Priority    : 8
        ! Description : "FLUSH/IFLUSH not implemented"
        !
trap_type_25:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x25, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x26 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_26:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x26, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x27 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_27:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x27, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x28 ]
        !
        ! Priority    : 11
        ! Description : "Coprocessor exception"
        !
trap_type_28:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x28, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x29 ]
        !
        ! Priority    : 12
        ! Description : "Data access error"
        !
trap_type_29:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x29, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2a ]
        !
        ! Priority    : 15
        ! Description : "Division by zero exception"
        !
trap_type_2a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2b ]
        !
        ! Priority    : 2
        ! Description : "Data store error"
        !
trap_type_2b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2c ]
        !
        ! Priority    : 12
        ! Description : "Data access MMU miss"
        !
trap_type_2c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2d ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_2d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2e ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_2e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x2f ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_2f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x2f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x30 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_30:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x30, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x31 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_31:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x31, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x32 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_32:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x32, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x33 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_33:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x33, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x34 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_34:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x34, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x35 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_35:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x35, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x36 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_36:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x36, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x37 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_37:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x37, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x38 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_38:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x38, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x39 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_39:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x39, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3a ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_3a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3b ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_3b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3c ]
        !
        ! Priority    : 2
        ! Description : "Instruction access MMU miss"
        !
trap_type_3c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3d ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_3d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3e ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_3e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x3f ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_3f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x3f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x40 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_40:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x40, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x41 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_41:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x41, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x42 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_42:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x42, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x43 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_43:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x43, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x44 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_44:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x44, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x45 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_45:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x45, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x46 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_46:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x46, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x47 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_47:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x47, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x48 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_48:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x48, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x49 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_49:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x49, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4a ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4b ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4c ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4d ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4e ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x4f ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_4f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x4f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x50 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_50:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x50, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x51 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_51:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x51, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x52 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_52:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x52, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x53 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_53:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x53, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x54 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_54:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x54, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x55 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_55:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x55, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x56 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_56:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x56, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x57 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_57:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x57, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x58 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_58:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x58, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x59 ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_59:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x59, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5a ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5b ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5c ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5d ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5e ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x5f ]
        !
        ! Priority    : NONE
        ! Description : "Undefined"
        !
trap_type_5f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x5f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x60 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_60:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x60, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x61 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_61:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x61, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x62 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_62:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x62, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x63 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_63:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x63, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x64 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_64:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x64, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x65 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_65:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x65, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x66 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_66:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x66, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x67 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_67:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x67, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x68 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_68:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x68, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x69 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_69:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x69, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6a ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6b ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6c ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6d ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6e ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x6f ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_6f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x6f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x70 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_70:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x70, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x71 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_71:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x71, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x72 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_72:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x72, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x73 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_73:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x73, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x74 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_74:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x74, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x75 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_75:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x75, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x76 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_76:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x76, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x77 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_77:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x77, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x78 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_78:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x78, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x79 ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_79:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x79, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7a ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7b ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7c ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7d ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7e ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x7f ]
        !
        ! Priority    : NONE
        ! Description : "Implementation dependent"
        !
trap_type_7f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x7f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x80 ]
        !
        ! Priority    : 16
        ! Description : "SunOS 4.x system call"
        !
trap_type_80:
        mov     %psr, %l0
        sethi   %hi(syscall_trap_handler), %l3
        jmpl    %l3 + %lo(syscall_trap_handler), %g0
        mov     0x80, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x81 ]
        !
        ! Priority    : 16
        ! Description : "User breakpoint"
        !
trap_type_81:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x81, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x82 ]
        !
        ! Priority    : 16
        ! Description : "Set task context system service."
        !
trap_type_82:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x0000020, %l3    ! Task context aware trap handlers table index, with bit 5 set to 1 to indicate this is a software trap handler.


        !
        ! [ TRAP TYPE 0x83 ]
        !
        ! Priority    : 16
        ! Description : "Replace task context system service."
        !
trap_type_83:
        mov     %psr, %l0
        sethi   %hi(sparcTaskContextAwareTrapHandler), %l3
        jmpl    %l3 + %lo(sparcTaskContextAwareTrapHandler), %g0
        mov     0x00000021, %l3    ! Task context aware trap handlers table index, with bit 5 set to 1 to indicate this is a software trap handler.


        !
        ! [ TRAP TYPE 0x84 ]
        !
        ! Priority    : 16
        ! Description : "Clean windows"
        !
trap_type_84:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x84, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x85 ]
        !
        ! Priority    : 16
        ! Description : "Range check"
        !
trap_type_85:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x85, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x86 ]
        !
        ! Priority    : 16
        ! Description : "Handle unaligned references (Grrr!)"
        !
trap_type_86:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x86, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x87 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_87:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x87, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x88 ]
        !
        ! Priority    : 16
        ! Description : "System call (ta 0x8)"
        !
trap_type_88:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x88, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x89 ]
        !
        ! Priority    : 16
        ! Description : "Set trap0 address (lwp->lwp_pcb.pcb_trap0addr)"
        !
trap_type_89:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x89, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8a ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8b ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8c ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8d ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8e ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x8f ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_8f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x8f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x90 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_90:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x90, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x91 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_91:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x91, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x92 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_92:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x92, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x93 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_93:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x93, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x94 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_94:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x94, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x95 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_95:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x95, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x96 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_96:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x96, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x97 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_97:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x97, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x98 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_98:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x98, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x99 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_99:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x99, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9a ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9a:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9a, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9b ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9b:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9b, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9c ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9c:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9c, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9d ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9d:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9d, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9e ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9e:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9e, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0x9f ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_9f:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0x9f, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa0 ]
        !
        ! Priority    : 16
        ! Description : "Get condition codes"
        !
trap_type_a0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa1 ]
        !
        ! Priority    : 16
        ! Description : "Set condition codes"
        !
trap_type_a1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa2 ]
        !
        ! Priority    : 16
        ! Description : "Get PSR"
        !
trap_type_a2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa3 ]
        !
        ! Priority    : 16
        ! Description : "Set PSR (don't get excited...some fields only :-)"
        !
trap_type_a3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa4 ]
        !
        ! Priority    : 16
        ! Description : "Get timestamp"
        !
trap_type_a4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa5 ]
        !
        ! Priority    : 16
        ! Description : "Get LWP virtual time"
        !
trap_type_a5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa6 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_a6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa7 ]
        !
        ! Priority    : 16
        ! Description : "Get hi-res time"
        !
trap_type_a7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_a8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xa9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_a9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xa9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xaa ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_aa:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xaa, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xab ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ab:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xab, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xac ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ac:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xac, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xad ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ad:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xad, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xae ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ae:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xae, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xaf ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_af:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xaf, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb0 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb1 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb2 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb3 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb4 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb5 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb6 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb7 ]
        !
        ! Priority    : 16
        ! Description : "Trap tracing facility"
        !
trap_type_b7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_b8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xb9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_b9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xb9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xba ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ba:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xba, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xbb ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_bb:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xbb, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xbc ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_bc:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xbc, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xbd ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_bd:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xbd, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xbe ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_be:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xbe, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xbf ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_bf:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xbf, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc0 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc1 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc2 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc3 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc4 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc5 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc6 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc7 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xc9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_c9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xc9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xca ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ca:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xca, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xcb ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_cb:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xcb, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xcc ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_cc:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xcc, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xcd ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_cd:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xcd, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xce ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ce:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xce, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xcf ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_cf:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xcf, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd0 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd1 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd2 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd3 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd4 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd5 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd6 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd7 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xd9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_d9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xd9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xda ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_da:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xda, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xdb ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_db:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xdb, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xdc ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_dc:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xdc, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xdd ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_dd:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xdd, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xde ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_de:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xde, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xdf ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_df:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xdf, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe0 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe1 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe2 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe3 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe4 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe5 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe6 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe7 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xe9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_e9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xe9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xea ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ea:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xea, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xeb ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_eb:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xeb, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xec ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ec:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xec, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xed ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ed:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xed, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xee ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ee:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xee, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xef ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_ef:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xef, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf0 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f0:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf0, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf1 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f1:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf1, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf2 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f2:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf2, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf3 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f3:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf3, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf4 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f4:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf4, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf5 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f5:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf5, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf6 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f6:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf6, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf7 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f7:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf7, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf8 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f8:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf8, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xf9 ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_f9:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xf9, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xfa ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_fa:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xfa, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xfb ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_fb:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xfb, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xfc ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_fc:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xfc, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xfd ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_fd:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xfd, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xfe ]
        !
        ! Priority    : 16
        ! Description : "Not used (bad trap)"
        !
trap_type_fe:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xfe, %l3    ! trap type number stored in %l3


        !
        ! [ TRAP TYPE 0xff ]
        !
        ! Priority    : 16
        ! Description : "Drop to prom (or kadb)"
        !
trap_type_ff:
        mov     %psr, %l0
        sethi   %hi(sparcDefaultTrapHandler), %l3
        jmpl    %l3 + %lo(sparcDefaultTrapHandler), %g0
        mov     0xff, %l3    ! trap type number stored in %l3
