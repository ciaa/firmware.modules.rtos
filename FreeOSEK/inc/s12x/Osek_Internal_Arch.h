/* Copyright 2008, 2009, Mariano Cerdeiro
 * Copyright 2008, Kang Li
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

#ifndef _OSEK_INTERNAL_ARCH_H_
#define _OSEK_INTERNAL_ARCH_H_
/** \brief FreeOSEK Internal Architecture Dependent Header File
 **
 ** \file s12x/Osek_Internal_Arch.h
 ** \arch s12x
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Internal
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 * KLi                        Kang Li
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081101 KLi	initial version
 */  

/*==================[inclusions]=============================================*/

#include <MC9S12XEP100.h>
#include <stddef.h>

/*==================[macros]=================================================*/
/** \brief Lenght of the Message Queue */

/** \brief Interrupt Secure Start Macro
 **
 ** This macro shall be used to disable the interrupts
 **/
#define IntSecure_Start() SuspendAllInterrupts()

/** \brief Interrupt Secure End Macro
 **
 ** This macro shall be used to restore the interrupts
 **/
#define IntSecure_End() ResumeAllInterrupts()

/** \brief osekpause
 **
 **/
#define osekpause()  		\
   {                 		\
	   __asm WAI;		\
   }

/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
void JmpTask(TaskType task); 

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define CallTask(task)															\
	{																					\
	   __asm LDAB (task);                                       \
	   __asm SWI;                                                  \
	}

/** \brief Save context */
#define SaveContext(task) \
   {                                   \
   }
   
#define GET_PPAGE(far_fn_ptr)   ((uint8)(far_fn_ptr))
#define GET_RPAGE(far_data_ptr) ((uint8)((uint32)(far_data_ptr) >> 12))
#define GET_DATA_LOCAL_ADDR(far_data_ptr) ((uint16)(((uint32)(far_data_ptr) & 0x00000FFF))|0x00001000)
/** \brief Set the entry point for a task */
#define SetEntryPoint(task)   \
   {                          \
      TasksConst[(task)].TaskContext->ppage = GET_PPAGE(TasksConst[(task)].EntryPoint); \
      TasksConst[(task)].TaskContext->rpage = GET_RPAGE(TasksConst[(task)].StackPtr); \
      TasksConst[(task)].TaskContext->sp = GET_DATA_LOCAL_ADDR((uint32)TasksConst[(task)].StackPtr + (uint32)TasksConst[(task)].StackSize - 10); \
   }

/** \brief */
void ResetStack(TaskType task);

#define ISR_NMI      0
#define ISR_CTR      1
#define ISR_CANRX    2
#define ISR_CANTX    3

#define EnableOSInterrupts()

#define EnableInterrupts()	{ __asm CLI; }

/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the counter
 **
 ** \param[in] CounterID id of the counter to be readed
 ** \return Actual value of the counter
 **/
#define GetCounter_Arch(CounterID) (CountersVar[CounterID].Time)

/** \brief Pre ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is started
 **/
#define PreIsr2_Arch(isr)

/** \brief Post ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is finished
 **/
#define PostIsr2_Arch(isr)


/*==================[typedef]================================================*/
/** \brief uint8 type definition */
typedef unsigned char uint8;

/** \brief sint8 type definition */
typedef signed char sint8;

/** \brief uint16 type definition */
typedef unsigned short uint16;

/** \brief sint16 type definition */
typedef signed short sint16;

/** \brief uint32 type definition */
typedef unsigned long uint32;

/** \brief sint32 type definition */
typedef signed long sint32;

/** \brief uint8_least type definition */
typedef unsigned int uint8_least;

/** \brief sint8_least type definition */
typedef signed int sint8_least;

/** \brief uint16_least type definition */
typedef unsigned int uint16_least;

/** \brief sint16_least type definition */
typedef signed int sint16_least;

/** \brief uint32_least type definition */
typedef unsigned long uint32_least;

/** \brief sint32_least type definition */
typedef signed long sint32_least;

/** \brief falg type definition */
typedef unsigned char flag;

typedef union
{
   void (* far far_fn_ptr)(void);
   struct
   {
      uint16 pc;
      uint8 ppage;
   } context;
} far_fn_ptr_type;

/*==================[external data declaration]==============================*/
/** \brief Signal Event
 **/
/* extern struct sigevent SignalEvent; */

/** \brief Osek Hardware Timer 0
 **/
/* extern uint32 OsekHWTimer0; */


/*==================[external functions declaration]=========================*/

extern StatusType SetEvent(TaskType TaskID, EventMaskType Mask);


extern void OSEK_ISR_HWTimer0(void);

extern void OSEK_ISR_HWTimer1(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_H_ */

