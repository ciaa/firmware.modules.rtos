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

#ifndef _ADC_ARCH_H_
#define _ADC_ARCH_H_
/** \brief FreeOSEK Driver ADC Arch Header File
 **
 ** ADC Arch Header File
 **
 ** \file arm7/lpc2xxx/Adc_Arch.h
 ** \arch arm7/lpc2xxx
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Adc
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Adc_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090528 v0.1.0 MaCe	initial version
 */

/*==================[inclusions]=============================================*/
#include "lpc2468.h"
#include "Adc_Arch_Cfg.h"

/*==================[macros]=================================================*/
#if (AdcDevErrorDetect == DISABLE)
#endif /* #if (AdcDevErrorDetect == DISABLE) */
/*==================[typedef]================================================*/
/** \brief Numeric ID of an ADC channel
 **/
typedef uint8 Adc_ChannelType;

/** \brief Numeric ID of an ADC channel group
 **/
typedef uint8 Adc_GroupType;

/** \brief Type for reading the converted values of a channel group (raw,
 ** without further scaling, right aligned).
 **/
typedef uint8 Adc_ValueGroupType;

/** \brief Type of clock input for the conversion unit to select different
 ** clock sources, if provided by hardware. (This is not an API type).
 **/
typedef uint8 Adc_ClockSourceType;

/** \brief Type of clock prescaler factor. (This is not an API type).
 **/
typedef uint8 Adc_PrescalerType;

/** \brief Type of conversion time, i.e. the time during which the sampled
 ** analoge value is converted into digital representation. (This is not an
 ** API type). */
typedef uint8 Adc_ConversionTimeType;

/** \brief Type of sampling time, i.e. the time during which the is sampled,
 ** (in clock-cycles). (This is not an API type).
 **/
typedef uint32 Adc_SamplingTimeType;

/** \brief Type of reference voltage source. (This is not an API type).
 **/
typedef uint16 Adc_VoltageSourceType;

/** \brief Type for configuring the number of group conversions in streaming
 ** access mode (in single acess mode, parameter is 1).
 **/
typedef uint8 Adc_StreamNumSampleType;

/** \brief Type for the reload value of the ADC module embedded timer (only
 ** if supported by the ADC hardware).
 **/
typedef uint8 Adc_HwTriggerTimerType;

/** \brief This is the type of data structure containing the initialization
 ** data for the ADC driver which is hardware specific
 **/
typedef struct {
} Adc_ConfigArchType;


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ADC_ARCH_H_ */

