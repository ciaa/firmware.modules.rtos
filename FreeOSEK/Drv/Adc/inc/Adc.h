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

#ifndef _ADC_H_
#define _ADC_H_
/** \brief FreeOSEK Driver ADC Header File
 **
 ** This file shall be included by all files using any OpenDRV ADC API.
 **
 ** \file Adc.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Drv Drivers
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Adc Analoge Digital Converter
 ** @{ */
/** \addtogroup FreeOSEK_Drv_Adc_Global Global
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
#include "Types.h"
#include "Adc_Cfg.h"
#include "Adc_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/** \brief This is the type of data structure containing the initialization
 ** data for the ADC driver
 **/
typedef struct {
	Adc_ConfigArchType Adc_Arch;
} Adc_ConfigType;

/** \brief Type of channel resolution in number of bits. (This is not an API
 ** type).
 **/
typedef uint8 Adc_ResolutionType;

/** \brief Current status of the conversion of the requested ADC channel group.
 **
 ** Possible values are:
 **	- ADC_IDLE					The conversion of the specified group has not
 **									been started. No result is available.
 **	- ADC_BUSY					The conversion of the specific group has been
 **									started and is still on going. So far no result
 **									is available.
 **	- ADC_COMPLETED			A conversion round (which is no the final one)
 **									of the specified group has been finished. A
 **									result is available for all channels of the
 **									group.
 **	- ADC_STREAM_COMPLETED	The result buffer is completely filled. For each
 **									channel of the selected group the number of
 **									samples to be acquired is available.
 **/
typedef enum {
	ADC_IDLE,
	ADC_BUSY,
	ADC_COMPLETED,
	ADC_STREAM_COMPLETED
} Adc_StatusType;

/** \brief Type of configuring the trigger source for and ADC Channel group.
 **
 ** Possible values are:
 **	- ADC_TRIGG_SRC_SW	Group triggerd by a software API call.
 **	- ADC_TRIGG_SRC_HW	Group triggerd by a hardware event.
 **/
typedef enum {
	ADC_TRIGG_SRC_SW,
	ADC_TRIGG_SRC_HW
} Adc_TriggerSourceType;

/** \brief Type of configuring the conversion mode of an ADC Channel group.
 **
 ** Possible values are:
 **	- ADC_CONV_MODE_ONESHOT		Exactly one conversion of each channel in an
 **										ADC channel group is performed after the
 **										configured trigger event. In case of ‘group
 **										trigger source software’, a started One-Shot
 **										conversion can be stopped by a software API
 **										call. In case of ‘group trigger source
 **										hardware’, a started One-Shot conversion
 **										can be stopped by disabling the trigger event
 **										(if supported by hardware).
 **	- ADC_CONV_MODE_CONTINUOUS	Repeated conversions of each ADC channel in an
 **										ADC channel group are performed. 'Continuous
 **										conversion mode' is only available for 'group
 **										trigger source software'. A started
 **										'Continuous conversion' can be stopped by a
 **										software API call.
 **/
typedef enum {
	ADC_CONV_MODE_ONESHOT,
	ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;

/** \brief Priority level of the channel. Lowest priority is 0, hieghst 255.
 **/
typedef uint8 Adc_GroupPriorityType;

/** \brief Type to assignment of channels to channel group (this is not an API
 ** type).*/
typedef struct {
	
} Adc_GroupDefType;

/** \brief Numeric ID of an ADC HW Unit.
 **/
typedef uint8 Adc_HwUnitType;

/** \brief Type of configuring the streaming access mode buffer type.
 **
 ** Possible values are:
 **	- ADC_STREAM_BUFFER_LINEAR		The ADC Driver stops the conversion as soon
 **											as the stream buffer is full (number of
 **											samples reached).
 **	- ADC_STREAM_BUFFER_CIRCULAR	The ADC Driver continues the conversion
 **											even if the stream buffer is full (number
 **											of samples reached) by wrapping around the
 **											stream buffer itself.
 **/
typedef enum {
	ADC_STREAM_BUFFER_LINEAR,
	ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;

/** \brief Type of configuring the access mode to group conversion results.
 **
 ** Possile values are:
 **	- ADC_ACCESS_MODE_SINGLE		Single value access mode.
 **	- ADC_ACCESS_MODE_STREAMING	Streaming access mode.
 **/
typedef enum {
	ADC_ACCESS_MODE_SINGLE,
	ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;

/** \brief Type for configuring on which edge the hardware trigger signal the
 ** driver should react. i.e. start the conversion (only if supported by the
 ** ADC hardware).
 **
 ** Possible values are:
 **	- ADC_HW_TRIG_RISING_EDGE	React on the rising edge of the hardware
 **										trigger signal (only if supported by the ADC
 **										hardware).
 **	- ADC_HW_TRIG_FALLING_EDGE React on the falling edge of the hardware
 **										trigger signal (only if supported by the ADC
 **										hardware).
 **	- ADC_HW_TRIG_BOTH_EDGES	React on both edges of the hardware trigger
 **										signal (only if supported by the ADC
 **										hardware).
 **/
typedef enum {
	ADC_HW_TRIG_RISING_EDGE,
	ADC_HW_TRIG_FALLING_EDGE,
	ADC_HW_TRIG_BOTH_EDGES
} Adc_HwTriggerSingalType;

/** \brief Type of configuring the prioritization mechanism.
 **
 ** Possible values are:
 **	- ADC_PRIORITY_NONE	priority mechanism is not available
 **	- ADC_PRIORITY_HW		Hardware priortiy mechanism is available only
 **	- ADC_PRIORITY_HW_SW Hardware and software priority mechanism is available
 **/
typedef enum {
	ADC_PRIORITY_NONE,
	ADC_PRIORITY_HW,
	ADC_PRIORITY_HW_SW
} Adc_PriorityImplementationType;

/** \brief Replacement mechanism, which is used on ADC group level, if a group
 ** conversion is interrupted by a group which has a higher priority.
 **
 ** Possible values are:
 **	- ADC_GROUP_REPL_ABORT_RESTART	Abort/Restart mechanism is used on group
 **												level, if a group is interrupted by a
 **												higher priority group. The complete
 **												conversion round of the interrupted
 **												group (all group channels)is restarted
 **												after the higher priority group
 **												conversion is finished. If the group is
 **												configured in streaming access mode,
 **												only the results of the interrupted
 **												conversion round are discarded. Results
 **												of previous conversion rounds which are
 **												already written to the result buffer
 **												are not affected.
 **	- ADC_GROUP_REPL_SUSPEND_RESUME	Suspend/Resume mechanism is used on
 **												group level, if a group is interrupted
 **												by a higher priority group. The
 **												converions round of the interrupted
 **												group is completed after the higher
 **												priority group conversion is finished.
 **/
typedef enum {
	ADC_GROUP_REPL_ABORT_RESTART,
	ADC_GROUP_REPL_SUSPEND_RESUME
} Adc_GroupReplacementType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Initializes the ADC hardware units and driver
 **
 ** This ADC driver service shall be called to initialize the ADC driver. Calls
 ** to any other ADC driver service before initialization is not allowed.
 **
 ** \param[in] ConfigPtr pointer to the Adc driver configuration
 **/
extern void Adc_Init
(
	const Adc_ConfigType * ConfigPtr
);

/** \brief Set the ADC Result BUffer
 **
 ** Initializes the group specific ADC result buffer pointer as configured (see
 ** ADC291) to point to the DataBufferPtr address which is passed as parameter.
 ** The ADC driver stores all group conversion results to result buffer
 ** addressed with the result buffer pointer. Adc_SetupResultBuffer determines
 ** the address of the result buffer. After reset, before a group conversion
 ** can be started, an initialization of the ADC result buffer pointer is
 ** required.
 **
 ** \param[in] Group Numeric ID of requested ADC channel group.
 ** \param[out] DataBufferPtr	ADC result buffer pointer is initialized with
 **									the value of the data buffer pointer.
 ** \return E_OK		result buffer pointer initialized correctly.
 **			E_NOT_OK	operation failed development error occured.
 **/
extern Std_ReturnType Adc_SetupResultBuffer
(
	Adc_GroupType Group,
	Adc_ValueGroupType* DataBufferPtr
);

/** \brief Start the conversion of all channels of the requested ADC channel
 ** group.
 **
 ** \param[in] Group Numeric ID of requested ADC Channel group.
 **/
extern void Adc_StartGroupConversion
(
	Adc_GroupType Group
);

/** \brief Reads Group conversion result
 **
 ** Reads the group conversion result of the last completed conversion round of
 ** the requested group and stores the channel values starting at the
 ** DataBufferPtr address. The group channel values are stored in ascending
 ** channel number order (in contrast to the storage layout of the result
 ** buffer if streaming access is configured).
 **
 ** \param[in] Group Numeric ID of requested ADC channel group.
 ** \param[out] DataBufferPtr ADC result buffer pointer is initialized with
 **									the value of the data buffer pointer.
 ** \return E_OK		results are available and written to the data buffer.
 **			E_NOT_OK	no results are available or development error occured.
 **/
extern Std_ReturnType Adc_ReadGroup
(
	Adc_GroupType Group,
	Adc_ValueGroupType* DataBufferPtr
);

/** \brief Returns the conversion status of the requested ADC Channel group.
 **
 ** \param[in] Group Numeric ID of requested ADC Channel group.
 ** \return ADC_IDLE					The conversion of the specified group has not
 **										been started. No result is available.
 **			ADC_BUSY					The conversion of the specific group has been
 **										started and is still on going. So far no result
 **										is available.
 **			ADC_COMPLETED			A conversion round (which is no the final one)
 **										of the specified group has been finished. A
 **										result is available for all channels of the
 **										group.
 **			ADC_STREAM_COMPLETED	The result buffer is completely filled. For each
 **										channel of the selected group the number of
 **										samples to be acquired is available.
 **/
extern Adc_StatusType Adc_GetGroupStatus
(
	Adc_GroupType Group
);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _ADC_H_ */

