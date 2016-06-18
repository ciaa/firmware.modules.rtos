/* Copyright 2016, Franco Bucafusco
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

#ifndef _OS_ARCH_H_
#define _OS_ARCH_H_

/** \brief FreeOSEK Os Architecture Dependent Header File
 **
 ** This file is included form os.h and defines macros
 ** and types which depends on the architecture.
 **
 ** \file msp430/Os_Arch.h
 ** \arch msp430
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Global
 ** @{ */

 /*
  * Initials     Name
  * ---------------------------
  * FBUC         Franco Bucafusco
  *
  */


/*
 * modification history (new versions first)
 * ----------------------------------------------------------
 * 20160222 v0.1.0 FBUC initial version
 */

/*==================[inclusions]=============================================*/

#include "Os_Internal_Arch_Cfg.h"

/*==================[macros]=================================================*/
/*****************************************************************************
 * Please define here all needed macros that will be visiblsee to the OS user
 * for this architecutre. This means that anyone including os.h will have
 * access to this definitions if the actual architecutre is used.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/** \brief Enable All Interrupts Arch */
#define EnableAllInterrupts_Arch() ResumeAllInterrupts_Arch()

/** \brief Disable All Interrupts Arch */
#define DisableAllInterrupts_Arch() SuspendAllInterrupts_Arch()


/** \brief  All Interrupts Arch Common Objects
 **
 ** This macro shall define common objects to imlement  Suspend and  Resume
 **/
#define  CommonAllInterrupts()   volatile unsigned short SR_BACK___;


/** \brief Suspend All Interrupts Arch
 **
 ** This macro shall suspend (disable) all interrupts.
 ** NOTE: the nop operation after the dint instruction was inserted
 **         to workarround the hw bug cpu39 describer in slaz314h.pdf
 **       Also noted in Slau208, page 59.
 **/

#define SuspendAllInterrupts_Arch()  SR_BACK___ = _get_SR_register(); \
                                     _disable_interrupts() ;
 
//#define SuspendAllInterrupts_Arch()   _disable_interrupts() ;


/** \brief Resume All Interrupts Arch
**
** This macro shall resume (enable) all interrupts.
**/

#define ResumeAllInterrupts_Arch() if( SR_BACK___ & GIE )      \
                                   {                           \
                                      _enable_interrupts() ;  \
                                   }                           \


//#define ResumeAllInterrupts_Arch() _enable_interrupts() ;


/** \brief Resume OS Interrupts Arch
 **
 ** This macro shall resume (enable) all interrupts configured on the
 ** FreeOSEK OIL configuration file as ISR2.
 **/
#define ResumeOSInterrupts_Arch() Enable_ISR2_Arch()

/** \brief Suspend OS Interrupts Arch
 **
 ** This macro shall suspend (disable) all interrupts configured on the
 ** FreeOSEK OIL configuration file as ISR2.
 **/
#define SuspendOSInterrupts_Arch() Disable_ISR2_Arch()

/*==================[typedef]================================================*/
/*****************************************************************************
 * Please define here all needed types that will be visible to the OS user
 * for this architecutre. This means that anyone including os.h will have
 * access to these type definitions if the actual architecutre is used.
 * Normaly no type has to be declared here.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external data declaration]==============================*/
/*****************************************************************************
 * Please declare here all exported data defined in Osek_Arch.c that will
 * be visible to the OS user for this architectire. This means that anyone
 * including os.h will have access to these variables, if the actual
 * architecutre is used. Normaly no variables has to be declared here.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external functions declaration]=========================*/
/*****************************************************************************
 * Please declare here all exported functions defined in Osek_Arch.c that will
 * be visible to the OS user for this architectire. This means that anyone
 * including os.h will have access to these variables, if the actual
 * architecutre is used. Normaly no variables has to be declared here.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_ARCH_H_ */
