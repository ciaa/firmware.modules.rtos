/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

#ifndef _OS_INTERNAL_CFG_H_
#define _OS_INTERNAL_CFG_H_
/** \brief FreeOSEK Os Generated Internal Configuration Header File
 **
 ** This file content the internal generated configuration of FreeOSEK Os
 **
 ** \file Os_Internal_Cfg.h
 **
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
 * 20090719 v0.1.7 MaCe rename file to Os_
 * 20090331 v0.1.6 MaCe add USERESSCHEDULER evaluation
 * 20090330 v0.1.5 MaCe add NO_EVENTS macro
 * 20090327 v0.1.4 MaCe add declaration of the start task for the app. modes
 * 20090131 v0.1.3 MaCe add extern to CountersVar declaration
 * 20090130 v0.1.2 MaCe add OSEK_MEMMAP check
 * 20090128 v0.1.1 MaCe remove ENABLE and DISABLE macro, now defined in OpenGEN
 * 20080713 v0.1.0 MaCe	initial version
 */  
/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
/** \brief ERROR_CHECKING_STANDARD */
#define ERROR_CHECKING_STANDARD   1

/** \brief ERROR_CHECKING_EXTENDED */
#define ERROR_CHECKING_EXTENDED   2

/** \brief Count of task */
#define TASKS_COUNT	3U

/** \brief Count of resources */
#define RESOURCES_COUNT 0

/** \brief Error Checking Type */
#define ERROR_CHECKING_TYPE	ERROR_CHECKING_EXTENDED
/** \brief pre task hook enable-disable macro */
#define HOOK_PRETASKHOOK DISABLE
/** \brief post task hook enable-disable macro */
#define HOOK_POSTTASKHOOK DISABLE
/** \brief error hook enable-disable macro */
#define HOOK_ERRORHOOK DISABLE
/** \brief startup hook enable-disable macro */
#define HOOK_STARTUPHOOK DISABLE
/** \brief shutdown hook enable-disable macro */
#define HOOK_SHUTDOWNHOOK DISABLE

#define READYLISTS_COUNT 3
#define SetError_Api(api)   ( Osek_ErrorApi = (api) )
#define SetError_Param1(param1) ( Osek_ErrorParam1 = (uint32)(param1) )
#define SetError_Param2(param2) ( Osek_ErrorParam2 = (uint32)(param2) )
#define SetError_Param3(param3) ( Osek_ErrorParam3 = (uint32)(param3) )
#define SetError_Ret(ret) ( Osek_ErrorRet = (uint32)(ret) )
#define SetError_Msg(msg) 
/* { printf ("Error found in file: \"%s\" line \"%d\" ", __FILE__, __LINE__); printf(msg); } */
#define SetError_ErrorHook()			\
	{											\
		ErrorHookRunning = (uint8)1U;	\
		ErrorHook();						\
		ErrorHookRunning = (uint8)0U;	\
	}

#define ALARM_AUTOSTART_COUNT 1

#define	OSEK_COUNTER_HardwareCounter 0
#define	OSEK_COUNTER_SoftwareCounter 1
/** \brief ALARMS_COUNT define */
#define ALARMS_COUNT 3

/** \brief NON_PREEMPTIVE macro definition */
#define NON_PREEMPTIVE	ENABLE

/** \brief NO_EVENTS macro definition */
#define NO_EVENTS ENABLE

/** \brief NO_RES_SCHEDULER macro definition */
#define NO_RES_SCHEDULER ENABLE


/*==================[typedef]================================================*/
typedef unsigned char TaskPriorityType;

typedef struct {
   unsigned int Extended : 1;
   unsigned int Preemtive : 1;
   unsigned int State : 2;
} TaskFlagsType;

typedef uint8 TaskActivationsType;

typedef uint32 TaskEventsType;

typedef uint32 TaskResourcesType;

typedef uint8* StackPtrType;

typedef uint16f StackSizeType;

typedef void (* EntryPointType)(void);

typedef void (* CallbackType)(void);

typedef uint8 TaskTotalType;

/** \brief Task Constant type definition
 **
 ** This structure defines all constants and constant pointers
 ** needed to manage a task
 **
 ** \param EntryPoint pointer to the entry point for this task
 ** \param Priority static priority of this task
 ** \param MaxActivations maximal activations for this task
 **/
typedef struct {
	EntryPointType EntryPoint;
	TaskContextRefType TaskContext;
	StackPtrType StackPtr;
	StackSizeType StackSize;
	TaskPriorityType StaticPriority;
	TaskActivationsType MaxActivations;
	TaskFlagsType ConstFlags;
	TaskEventsType EventsMask;
	TaskResourcesType ResourcesMask;
} TaskConstType;

/** \brief Task Variable type definition
 **
 ** This structure defines all variables needed to manage a task
 **
 ** \param ActualPriority actual priority of this task
 ** \param Activations actual activations on this task
 ** \param Flags flags variable of this task
 ** \param Events of this task
 ** \param Resource of this task
 **/
typedef struct {
	TaskPriorityType ActualPriority;
	TaskActivationsType Activations;
	TaskFlagsType Flags;
	TaskEventsType Events;
	TaskEventsType EventsWait; 
	TaskResourcesType Resources;
} TaskVariableType;

/** \brief Auto Start Structure Type
 **
 ** \param Total taks on this application mode
 ** \param Reference to the tasks on this Application Mode
 **/
typedef struct {
	TaskTotalType TotalTasks;
	TaskRefType TasksRef;
} AutoStartType;

/** \brief Ready List Constatn Type
 **
 ** \param ListLength Lenght of the Ready List
 ** \param TaskRef Reference to the Ready Array for this Priority
 **/
typedef struct {
	TaskTotalType ListLength;
	TaskRefType TaskRef;
} ReadyConstType;

/** \brief Ready List Variable Type
 **
 ** \param ListStart first valid componet on the list
 ** \param ListCount count of valid components on this list
 **/
typedef struct {
	TaskTotalType ListStart;
	TaskTotalType ListCount;
} ReadyVarType;

/** \brief Alarm State
 **
 ** This type defines the possibly states of one alarm which are:
 ** 0 disable
 ** 1 enable
 **/
typedef uint8 AlarmStateType;

/** \brief Alarm Time */
typedef uint32 AlarmTimeType;

/** \brief Alarm Cycle Time */
typedef uint32 AlarmCycleTimeType;

/** \brief Counter Type */
typedef uint8 CounterType;

/** \brief Counter Increment Type */
typedef uint32f CounterIncrementType;

/** \brief Alarm Increment Type */
typedef uint32f AlarmIncrementType;

/** \brief Alarm Action Type */
typedef enum {
	ALARMCALLBACK = 0,
	SETEVENT = 1,
	ACTIVATETASK = 2,
	INCREMENT = 3
} AlarmActionType;

/** \brief Alarm Action Info Type
 **
 ** This type has extra information of the Alarm action
 **/
typedef struct {
	CallbackType CallbackFunction;
	TaskType TaskID;
   EventMaskType Event;
	CounterType Counter;
} AlarmActionInfoType;

/** \brief Alarm Variable Type */
typedef struct {
	AlarmStateType AlarmState;
	AlarmTimeType AlarmTime;
	AlarmCycleTimeType AlarmCycleTime;
} AlarmVarType;

/** \brief Alarm Constant Type */
typedef struct {
	CounterType Counter;
	AlarmActionType AlarmAction;
	AlarmActionInfoType AlarmActionInfo;
} AlarmConstType;

/** \brief Auto Start Alarm Type */
typedef struct {
	AppModeType Mode;
	AlarmType Alarm;
	AlarmTimeType AlarmTime;
	AlarmCycleTimeType AlarmCycleTime;
} AutoStartAlarmType;

typedef struct {
	uint8	AlarmsCount;
	AlarmType* AlarmRef;
	TickType MaxAllowedValue;
	TickType MinCycle;
	TickType TicksPerBase;
} CounterConstType;

typedef struct {
	TickType Time;
} CounterVarType;

/*==================[external data declaration]==============================*/
/** \brief ErrorHookRunning
 **
 ** This variable is used to check if the error hook is been executed.
 ** 0 ErrorHook is not been executed
 ** 1 ErrorHook is been executed.
 **/
extern uint8 ErrorHookRunning;

/** \brief Tasks Constants
 **
 ** Contents all constant and constant pointer needed to
 ** manage all FreeOSEK tasks
 **/
extern const TaskConstType TasksConst[TASKS_COUNT];

/** \brief Tasks Variable
 **
 ** Contents all variables needed to manage all FreeOSEK tasks
 **/
extern TaskVariableType TasksVar[TASKS_COUNT];

/** \brief Application Mode
 **
 ** This variable contents the actual running application mode
 **/
extern uint8 ApplicationMode;

/** \brief List of Auto Start Tasks in Application Mode AppMode1 */
extern const TaskType TasksAppModeAppMode1[1];
/** \brief AutoStart Array */
extern const AutoStartType AutoStart[1];

/** \brief Resources Priorities */
extern const TaskPriorityType ResourcesPriority[0];

/** \brief Ready Const List */
extern const ReadyConstType ReadyConst[3];

/** \brief Ready Variable List */
extern ReadyVarType ReadyVar[3];

/** \brief Resources Priorities */
extern const TaskPriorityType ResourcesPriority[0];

/** \brief Alarms Variable Structure */
extern AlarmVarType AlarmsVar[3];

/** \brief Alarms Constant Structure */
extern const AlarmConstType AlarmsConst[3];

/** \brief Alarms Constant Structure */
extern const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT];

/** \brief Counter Var Structure */
extern CounterVarType CountersVar[2];

/** \brief Counter Const Structure */
extern const CounterConstType CountersConst[2];
/*==================[external functions declaration]=========================*/
#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_START_SEC_CODE
#include "MemMap.h"
#endif


#if (OSEK_MEMMAP == ENABLE)
#define FreeOSEK_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_CFG_H_ */
