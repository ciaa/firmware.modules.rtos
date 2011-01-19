/* Copyright 2008, 2009, 2011, Mariano Cerdeiro
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

#ifndef _OS_INTERNAL_ARCH_H_
#define _OS_INTERNAL_ARCH_H_
/** \brief FreeOSEK Os Internal Architecture Dependent Header File
 **
 ** \file avr/Os_Internal_Arch.h
 ** \arch avr
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
  * 20110114 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** This define makes the Osek_Internal.h file to include the
 ** Osek_Internal_Arch_Cpu file which is not standard for all architectures 
 **/
#define OSEK_INLCUDE_INTERNAL_ARCH_CPU

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
#define osekpause()			\
	{								\
	}

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define CallTask(actualtask, nexttask)											\
	{																						\
		Osek_OldTaskPtr_Arch =														\
			(void*)TasksConst[actualtask].TaskContext;						\
		Osek_NewTaskPtr_Arch = 														\
			(void*)TasksConst[nexttask].TaskContext;							\
		__asm__ __volatile__ (														\
			"push	r0																\n\t"	\
			"in r0, __SREG__													\n\t"	\
			"cli																	\n\t"	\
			"push	r0																\n\t"	\
			"push	r1																\n\t"	\
			"clr	r1																\n\t"	\
			"push	r2																\n\t"	\
			"push	r3																\n\t"	\
			"push	r4																\n\t"	\
			"push	r5																\n\t"	\
			"push	r6																\n\t"	\
			"push	r7																\n\t"	\
			"push	r8																\n\t"	\
			"push	r9																\n\t"	\
			"push	r10															\n\t"	\
			"push	r11															\n\t"	\
			"push	r12															\n\t"	\
			"push	r13															\n\t"	\
			"push	r14															\n\t"	\
			"push	r15															\n\t"	\
			"push	r16															\n\t"	\
			"push	r17															\n\t"	\
			"push	r18															\n\t"	\
			"push	r19															\n\t"	\
			"push	r20															\n\t"	\
			"push	r21															\n\t"	\
			"push	r22															\n\t"	\
			"push	r23															\n\t"	\
			"push	r24															\n\t"	\
			"push	r25															\n\t"	\
			"push	r26															\n\t"	\
			"push	r27															\n\t"	\
			"push	r28															\n\t"	\
			"push	r29															\n\t"	\
			"push	r30															\n\t"	\
			"push	r31															\n\t"	\
			"lds r26, Osek_OldTaskPtr_Arch								\n\t"	\
			"lds r27, Osek_OldTaskPtr_Arch + 1							\n\t"	\
			"in r0, __SP_L__													\n\t"	\
			"st x+, r0															\n\t"	\
			"in r0, __SP_H__													\n\t"	\
			"st x+, r0															\n\t"	\
			"lds r26, Osek_NewTaskPtr_Arch								\n\t"	\
			"lds r27, Osek_NewTaskPtr_Arch + 1							\n\t"	\
			"ld r28, x+															\n\t"	\
			"out __SP_L__, r28												\n\t"	\
			"ld r29, x+															\n\t"	\
			"out __SP_H__, r29												\n\t"	\
			"pop r31																\n\t"	\
			"pop r30																\n\t"	\
			"pop r29																\n\t"	\
			"pop r28																\n\t"	\
			"pop r27																\n\t"	\
			"pop r26																\n\t"	\
			"pop r25																\n\t"	\
			"pop r24																\n\t"	\
			"pop r23																\n\t"	\
			"pop r22																\n\t"	\
			"pop r21																\n\t"	\
			"pop r20																\n\t"	\
			"pop r19																\n\t"	\
			"pop r18																\n\t"	\
			"pop r17																\n\t"	\
			"pop r16																\n\t"	\
			"pop r15																\n\t"	\
			"pop r14																\n\t"	\
			"pop r13																\n\t"	\
			"pop r12																\n\t"	\
			"pop r11																\n\t"	\
			"pop r10																\n\t"	\
			"pop r9																\n\t"	\
			"pop r8																\n\t"	\
			"pop r7																\n\t"	\
			"pop r6																\n\t"	\
			"pop r5																\n\t"	\
			"pop r4																\n\t"	\
			"pop r3																\n\t"	\
			"pop r2																\n\t"	\
			"pop r1																\n\t"	\
			"pop r0																\n\t"	\
			"out __SREG__, r0													\n\t"	\
			"pop r0																\n\t"	\
			"ret																	\n\t" \
			);																				\
	}



/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define JmpTask(task)															\
	{																					\
		Osek_NewTaskPtr_Arch = (void*)TasksConst[task].TaskContext;		\
		__asm__ __volatile__ (														\
			"lds r26, Osek_NewTaskPtr_Arch								\n\t"	\
			"lds r27, Osek_NewTaskPtr_Arch + 1							\n\t"	\
			"ld r28, x+															\n\t"	\
			"out __SP_L__, r28												\n\t"	\
			"ld r29, x+															\n\t"	\
			"out __SP_H__, r29												\n\t"	\
			"pop r31																\n\t"	\
			"pop r30																\n\t"	\
			"pop r29																\n\t"	\
			"pop r28																\n\t"	\
			"pop r27																\n\t"	\
			"pop r26																\n\t"	\
			"pop r25																\n\t"	\
			"pop r24																\n\t"	\
			"pop r23																\n\t"	\
			"pop r22																\n\t"	\
			"pop r21																\n\t"	\
			"pop r20																\n\t"	\
			"pop r19																\n\t"	\
			"pop r18																\n\t"	\
			"pop r17																\n\t"	\
			"pop r16																\n\t"	\
			"pop r15																\n\t"	\
			"pop r14																\n\t"	\
			"pop r13																\n\t"	\
			"pop r12																\n\t"	\
			"pop r11																\n\t"	\
			"pop r10																\n\t"	\
			"pop r9																\n\t"	\
			"pop r8																\n\t"	\
			"pop r7																\n\t"	\
			"pop r6																\n\t"	\
			"pop r5																\n\t"	\
			"pop r4																\n\t"	\
			"pop r3																\n\t"	\
			"pop r2																\n\t"	\
			"pop r1																\n\t"	\
			"pop r0																\n\t"	\
			"out __SREG__, r0													\n\t"	\
			"pop r0																\n\t"	\
			"ret																	\n\t" \
			);																				\
	}

/** \brief Save context
 **
 ** Jonas Mitschang task switch for AT90CAN128 based on FreeRTOS
 ** task switch.
 **/
#define SaveContext(task) 														\
	{																					\
		Osek_OldTaskPtr_Arch = (void*)TasksConst[task].TaskContext;		\
		__asm__ __volatile__ (														\
			"push	r0																\n\t"	\
			"in r0, __SREG__													\n\t"	\
			"cli																	\n\t"	\
			"push	r0																\n\t"	\
			"push	r1																\n\t"	\
			"clr	r1																\n\t"	\
			"push	r2																\n\t"	\
			"push	r3																\n\t"	\
			"push	r4																\n\t"	\
			"push	r5																\n\t"	\
			"push	r6																\n\t"	\
			"push	r7																\n\t"	\
			"push	r8																\n\t"	\
			"push	r9																\n\t"	\
			"push	r10															\n\t"	\
			"push	r11															\n\t"	\
			"push	r12															\n\t"	\
			"push	r13															\n\t"	\
			"push	r14															\n\t"	\
			"push	r15															\n\t"	\
			"push	r16															\n\t"	\
			"push	r17															\n\t"	\
			"push	r18															\n\t"	\
			"push	r19															\n\t"	\
			"push	r20															\n\t"	\
			"push	r21															\n\t"	\
			"push	r22															\n\t"	\
			"push	r23															\n\t"	\
			"push	r24															\n\t"	\
			"push	r25															\n\t"	\
			"push	r26															\n\t"	\
			"push	r27															\n\t"	\
			"push	r28															\n\t"	\
			"push	r29															\n\t"	\
			"push	r30															\n\t"	\
			"push	r31															\n\t"	\
			"lds r26, Osek_OldTaskPtr_Arch								\n\t"	\
			"lds r27, Osek_OldTaskPtr_Arch + 1							\n\t"	\
			"in r0, __SP_L__													\n\t"	\
			"st x+, r0															\n\t"	\
			"in r0, __SP_H__													\n\t"	\
			"st x+, r0															\n\t"	\
			);																		\
	}

/** \brief Set the entry point for a task */
#define SetEntryPoint(task)															\
	{																							\
		/* init entry point */															\
		uint8* stackPtr = (uint8*) TasksConst[task].TaskContext;				\
		*stackPtr = (uint8)((uint16)TasksConst[task].EntryPoint & 0xFF);				\
		stackPtr++;																			\
		*stackPtr = (uint8)(((uint16)TasksConst[task].EntryPoint >> 8 ) & 0xFF);	\
	}

/** \brief */
#define ResetStack(task)											\
	{																		\
		/* init stack */												\
		TasksConst[task].TaskContext->reg_stack_low =		\
			(uint8)((uint16)(TasksConst[task].StackPtr + 	\
			TasksConst[task].StackSize - 32) & 0xFF);			\
		TasksConst[task].TaskContext->reg_stack_high =		\
			(uint8)(((uint16)(TasksConst[task].StackPtr + 	\
			TasksConst[task].StackSize - 32) >> 8 ) & 0xFF);\
   }

#define ISR_NMI      0
#define ISR_CTR      1
#define ISR_CANRX    2
#define ISR_CANTX    3

#define EnableOSInterrupts()															\
	{																							\
		/** TODO */																			\
	}

#define EnableInterrupts()		\
	{									\
		/** TODO */					\
	}

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

#define SavePosixStack() \
   {                                   \
      /* save actual win esp */        \
   }

/** \brief Pre Call Service
 **
 ** This macro shall be called before calling any posix system service
 **/
#define PreCallService()

/** \brief Post Call Service
 **
 ** This macro shall be called after calling any posix system service
 **/
#define PostCallService()

/** \brief Normal User Mode */
#define MODE_USR			0x10
/** \brief FIQ Processing Fast Interrupts Mode */
#define MODE_FIQ			0x11     
/** \brief IRQ Processing Standard Interrupts Mode */
#define MODE_IRQ			0x12
/** \brief Supervisor Processing Software Interrupts Mode */
#define MODE_SVC			0x13
/** \brief Abort Processing memory Faults Mode */
#define MODE_ABT			0x17
/** \brief Undefined Processing Undefined Instructions Mode */
#define MODE_UND			0x1B
/** \brief System Running Priviledged Operating System Tasks Mode */
#define MODE_SYS			0x1F

/** \brief Set ARM7 Mode
 **
 ** \param[in] mode can be:
 **					MODE_USR to set to user mode
 **					MODE_FIQ to set to fast interrut mode
 **					MODE_IRQ to set to interrupt mode
 **					MODE_SVC to set to supervisor processing mode
 **					MODE_ABT to set to abort mode
 **					MODE_UND to set to undefined mode
 **					MODE_SYS to set to system mode
 **/
#define SetArm7Mode(mode)			\
	{										\
	}

/** \brief ShutdownOs Arch service
 **/
#define	ShutdownOs_Arch()

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
/** \brief Osek New Task Pointer for ARM Architecture
 **
 ** This variable content the pointer to the new task.
 **/
extern void* Osek_NewTaskPtr_Arch;

/** \brief Osek Old Task Pointer for ARM Architecture
 **
 ** This variable content the pointer to the old task.
 **/
extern void* Osek_OldTaskPtr_Arch;

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */
