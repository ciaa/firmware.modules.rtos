/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

<?php
/** \brief OpenDRV File to be Generated
 **
 ** \file Mcu_Cfg.h.php
 **/
?>

#ifndef _MCU_CFG_H_
#define _MCU_CFG_H_
/** \brief OpenDRV Mcu Generated Configuration Header File
 **
 ** This file contents the generated configuration of the MicroController Unit
 ** driver.
 **
 ** \file Mcu_Cfg.h
 **/

/** \addtogroup OpenDRV
 ** @{ */ 
/** \addtogroup OpenDRV_Mcu
 ** \ingroup OpenDRV
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090215 v0.1.1 MaCe	raname the driver to Mcu
 * 20090124 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Mcu Development Error Detection Macro */
/* \req MCU100 The McuDevErrorDetect enables the development error detection.
 * (ENABLE the development error detection is enable, DISABLE the development
 * error detection is disable)
 */
/* \dev The McuDevErrorDetect macro can be ENABLE or DISABLE, this is not
 * conform to the specification */
/** TODO this has to be a configurable parameter in function of the Dio oil
 ** configuration. */
#define McuDevErrorDetect	ENABLE

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MCU_CFG_H_ */

