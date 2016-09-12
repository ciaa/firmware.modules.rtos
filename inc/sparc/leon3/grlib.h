
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

#define GRLIB_PNP_VENDOR_ID_ANY                      0x00
#define GRLIB_PNP_VENDOR_ID_GAISLER_RESEARCH         0x01
#define GRLIB_PNP_VENDOR_ID_PENDER_ELECTRONIC_DESIGN 0x02
#define GRLIB_PNP_VENDOR_ID_EUROPEAN_SPACE_AGENCY    0x04
#define GRLIB_PNP_VENDOR_ID_ASTRIUM_EADS             0x06
#define GRLIB_PNP_VENDOR_ID_OPEN_CHIP                0x07
#define GRLIB_PNP_VENDOR_ID_OPEN_CORES               0x08
#define GRLIB_PNP_VENDOR_ID_VARIOUS_CONTRIBUTIONS    0x09
#define GRLIB_PNP_VENDOR_ID_DLR                      0x0a

#define GRLIB_PNP_DEVICE_ID_ANY                      0x00
#define GRLIB_PNP_DEVICE_ID_APBCTRL                  0x06

#define GRLIB_PNP_BAR_ENTRY_TYPE_APBIOSPACE          0x01
#define GRLIB_PNP_BAR_ENTRY_TYPE_AHBMEMORYSPACE      0x02
#define GRLIB_PNP_BAR_ENTRY_TYPE_AHBIOSPACE          0x03


/*==================[typedef]================================================*/


typedef uint32 grDeviceAddress;


typedef uint32 grDeviceRegisterValue;


typedef struct {
    uint32 clockSwitchingEnabled;    /**< Clock switching enabled (CDS). If set, switching between AHB and CPU frequency is available. */
    uint32 cpuClockFrequency;        /**< CPU clock frequency (CF). CPU core runs at (CF+1) times AHB frequency. */
    uint32 loadDelay;                /**< Load delay. If set, the pipeline uses a 2-cycle load delay. Otherwise, a 1-cycle
                                          load delay is used. generated from the lddel generic parameter in the VHDL model. */
    uint32 fpuOption;                /**< FPU option. "00" = no FPU; "01" = GRFPU;  "10" = Meiko FPU, "11" = GRFPU-Lite. */
    uint32 macInstructionAvailable;  /**< If set, the optional mutiply-accumulate (MAC) instruction is available. */
    uint32 sparcV8MulDivAvailable;   /**< If set, the SPARC V8 multiply and divide instructions are available. */
    uint32 registersWindows;         /**< Number of implemented register windows corresonds to NWIN+1. */
} grCpuConfigType;


typedef struct {
   uint32 lockingImplemented;       /**< Cache locking (CL). Set if cache locking is implemented. */
   uint32 replacementPolicy;        /**< Cache replacement policy (REPL). 00 - no replacement policy (direct-mapped cache), 01 - least
                                         recently used (LRU), 10- least recently replaced (LRR), 11 - random. */
   uint32 snoopingImplemented;      /**< Cache snooping (SN). Set if snooping is implemented. */
   uint32 associativity;            /**< Cache associativity (SETS). Number of sets in the cache: 000 - direct mapping, 001 - 2-way associative,
                                         010 - 3-way associative, 011 - 4-way associative. */
   uint32 setSize;                  /**< Indicates the size (Kbytes) of each cache set. Size = 2^SIZE. */
   uint32 localRamImplemented;      /**< Set if local scratch pad ram is implemented. */
   uint32 lineSize;                 /**< Indicates the size (words) of each cache line. Line size = 2^LSZ. */
   uint32 localRamsize;             /**< LRSZ (Local Ram Size). Indicates de size (Kbytes) of the implemented
                                         local scratch pad ram. Local ram size = 2^LRSZ. */
   uint32 localRamStartAddress;     /**< Indicate the 8 most significant bits of the local ram start address. */
   uint32 mmuPresent;               /**< this bit is set to '1' if an MMU is present. */
} grCacheConfigType;


typedef struct {

   uint32 validEntry;

   uint32 address;
   uint32 mask;
   uint32 type;
   uint32 prefetchableFlag;
   uint32 cacheableFlag;

} grPlugAndPlayAHBBankAddressRegisterEntryType;

typedef struct {

   uint32 vendorId;
   uint32 deviceId;
   uint32 version;
   uint32 irq;

   grPlugAndPlayAHBBankAddressRegisterEntryType bankAddressRegisters[4];

} grPlugAndPlayAHBDeviceTableEntryType;

typedef struct {

   uint32 vendorId;
   uint32 deviceId;
   uint32 ctFlag;
   uint32 version;
   uint32 irq;
   uint32 address;
   uint32 mask;
   uint32 type;

} grPlugAndPlayAPBDeviceTableEntryType;


/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/


void grRegisterWrite(grDeviceAddress baseAddr, grDeviceAddress offset, grDeviceRegisterValue newValue);
grDeviceRegisterValue grRegisterRead(grDeviceAddress baseAddr, grDeviceAddress offset);


sint32 grWalkPlugAndPlayAHBDeviceTable(uint32 vendorId, uint32 deviceId, grPlugAndPlayAHBDeviceTableEntryType *ahbDeviceInfo, sint32 ahbDeviceIndex);
sint32 grWalkPlugAndPlayAPBDeviceTable(uint32 vendorId, uint32 deviceId, grPlugAndPlayAPBDeviceTableEntryType *apbDeviceInfo, sint32 apbDeviceIndex);


void grEnableProcessorCaches();
void grGetCPUConfig(grCpuConfigType *config);
void grGetICacheConfig(grCacheConfigType *config);
void grGetDCacheConfig(grCacheConfigType *config);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _GAISLER_GRLIB_H_ */

