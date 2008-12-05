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
/** \brief OpenSEK File to be Generated
 **
 ** \file Osek_Cfg.h.php
 **
 **/
?>

#ifndef _OSEK_CFG_H_
#define _OSEK_CFG_H_
/** \brief OpenSEK Generated Configuration Header File
 **
 ** This file contents the generated configuration of OpenSEK
 **
 ** \file Osek_Cfg.h
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */ 
/** \addtogroup OpenSEK_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080810 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Definition of the  DeclareTask Macro */
#define DeclareTask(name)	void OSEK_TASK_ ## name (void)

#define OSEK_OS_INTERRUPT_MASK ((InterruptFlagsType)0xFFFFFFFFU)

<?php
/* Definitions of Tasks */
$tasks = $config->getList("/OSEK","TASK");
$count = 0;
foreach ($tasks as $task)
{
	print "/** \brief Task Definition */\n";
	print "#define $task $count\n";
	$count++;
}
print "\n";

/* Define the Applications Modes */
$appmodes = $config->getList("/OSEK","APPMODE");
$count = 0;
foreach ($appmodes as $appmode)
{
	print "/** \brief Definition of the Application Mode $appmode */\n";
	print "#define " . $appmode . " " . $count++ . "\n";
}
print "\n";

/* Define the Events */
$events = $config->getList("/OSEK","EVENT");
$count = 0;
foreach ($events as $event)
{
	print "/** \brief Definition of the Event $event */\n";
	print "#define " . $event . " " . (1<<$count++) . "\n";
}
print "\n";

/* Define the Resources */
$resources = $config->getList("/OSEK","RESOURCE");
$count = 0;
foreach ($resources as $resource)
{
	print "/** \brief Definition of the resource $resource */\n";
	print "#define " . $resource . " " . $count++ . "\n";
}
print "\n";

/* Define the Alarms */
$alarms = $config->getList("/OSEK","ALARM");
$count = 0;
foreach ($alarms as $alarm)
{
   print "/** \brief Definition of the Alarm $alarm */\n";
   print "#define " . $alarm . " " . $count++ . "\n";
}
print "\n";

$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
?>
/** \brief OS Error Get Service Id */
/* \req OSEK_ERR_0.1 The macro OSErrorGetServiceId() shall provide the service
 * identifier with a OSServiceIdType type where the error has been risen
 * \req OSEK_ERR_0.1.1 Possibly return values are: OSServiceId_xxxx, where
 * xxxx is the name of the system service
 */
#define OSErrorGetServiceId() (Osek_ErrorApi)

#define OSErrorGetParam1() (Osek_ErrorParam1)

#define OSErrorGetParam2() (Osek_ErrorParam2)

#define OSErrorGetParam3() (Osek_ErrorParam3)

#define OSErrorGetRet() (Osek_ErrorRet)

<?php
}
?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
#define OpenSEK_START_SEC_DATA
#include "MemMap.h"

<?php
$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
?>
/** \brief Error Api Variable
 **
 ** This variable contents the api which generate the last error
 **/
extern unsigned int Osek_ErrorApi;

/** \brief Error Param1 Variable
 **
 ** This variable contents the first parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam1;

/** \brief Error Param2 Variable
 **
 ** This variable contents the second parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam2;

/** \brief Error Param3 Variable
 **
 ** This variable contents the third parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam3;

/** \brief Error Return Variable
 **
 ** This variable contents return value of the api which has generated
 ** the last error.
 **/
extern unsigned int Osek_ErrorRet;

<?php
}
?>

#define OpenSEK_STOP_SEC_DATA
#include "MemMap.h"

/*==================[external functions declaration]=========================*/
#define OpenSEK_START_SEC_CODE
#include "MemMap.h"
<?php
$pretaskhook=$config->getValue("/OSEK/" . $os[0],"PRETASKHOOK");
if ($pretaskhook == "TRUE")
{
	print "/** \brief Pre Task Hook */\n";
	print "extern void PreTaskHook(void) ATTRIBUTES();\n\n";
}
$posttaskhook=$config->getValue("/OSEK/" . $os[0],"POSTTASKHOOK");
if ($posttaskhook == "TRUE")
{
   print "/** \brief Post Task Hook */\n";
   print "extern void PostTaskHook(void) ATTRIBUTES();\n\n";
}
$shutdownhook=$config->getValue("/OSEK/" . $os[0],"SHUTDOWNHOOK");
if ($shutdownhook == "TRUE")
{
   print "/** \brief Shutdown Hook */\n";
   print "extern void ShutdownHook(void) ATTRIBUTES();\n\n";
}
$startuphook=$config->getValue("/OSEK/" . $os[0],"STARTUPHOOK");
if ($startuphook == "TRUE")
{
   print "/** \brief Startup Hook */\n";
   print "extern void StartupHook(void) ATTRIBUTES();\n\n";
}
$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
   print "/** \brief Error Hook */\n";
   print "extern void ErrorHook(void) ATTRIBUTES();\n\n";
}

/* Declare Tasks */
$count = 0;
foreach ($tasks as $task)
{
	print "/** \brief Task Declaration of Task $task */\n";
	print "DeclareTask($task) ATTRIBUTES();\n";
}
print "\n";

$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
	print "/** \brief ISR Declaration */\n";
	print "extern void OSEK_ISR_$int(void) ATTRIBUTES(); /* Interrupt Handler $int */\n";
}
print "\n";

$alarms = $config->getList("/OSEK","ALARM");
foreach ($alarms as $alarm)
{
	$action = $config->getValue("/OSEK/" . $alarm, "ACTION");
	if ($action == "ALARMCALLBACK")
	{
		print "/** \brief Alarm Callback declaration */\n";
		print "extern void OSEK_CALLBACK_" . $config->getValue("/OSEK/" . $alarm . "/ALARMCALLBACK", "CALLBACK") . "(void) ATTRIBUTES();\n";
	}
}
print "\n";

?>

#define OpenSEK_STOP_SEC_CODE
#include "MemMap.h"

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_CFG_H_ */
