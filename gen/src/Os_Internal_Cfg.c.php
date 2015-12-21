/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
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

/** \brief FreeOSEK Os Generated Internal Configuration Implementation File
 **
 ** \file Os_Internal_Cfg.c
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
 * MaCe         Mariano Cerdeiro
 * JuCe         Juan Cecconi
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150619 v0.1.4 MaCe fix issue #279
 * 20141125 v0.1.3 JuCe additional stack for x86 ARCH
 * 20090719 v0.1.2 MaCe rename file to Os_
 * 20090128 v0.1.1 MaCe add OSEK_MEMMAP check
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
<?php
/* get tasks */
$tasks = getLocalList("/OSEK", "TASK");

foreach ($tasks as $task)
{
   print "/** \brief $task stack */\n";
   print "#if ( x86 == ARCH )\n";
   print "uint8 StackTask" . $task . "[" . $config->getValue("/OSEK/" . $task, "STACK") ." + TASK_STACK_ADDITIONAL_SIZE];\n";
   print "#else\n";
   print "uint8 StackTask" . $task . "[" . $config->getValue("/OSEK/" . $task, "STACK") ."];\n";
   print "#endif\n";
}
print "\n";

foreach ($tasks as $task)
{
   print "/** \brief $task context */\n";
   print "TaskContextType ContextTask" . $task . ";\n";
}
print "\n";

/* Ready List */
foreach ($priority as $prio)
{
   print "/** \brief Ready List for Priority $prio */\n";
   $count = 0;
   foreach ($tasks as $task)
   {
      if ($priority[$config->getValue("/OSEK/" . $task, "PRIORITY")] == $prio)
      {
         $count += $config->getValue("/OSEK/" . $task, "ACTIVATION");
      }
   }
   print "TaskType ReadyList" . $prio . "[" . $count . "];\n\n";
}

$counters = getLocalList("/OSEK", "COUNTER");
$alarms = getLocalList("/OSEK", "ALARM");

foreach ($counters as $counter)
{
   $countalarms = 0;
   foreach ($alarms as $alarm)
   {
      if ($counter == $config->getValue("/OSEK/" . $alarm,"COUNTER"))
      {
         $countalarms++;
      }
   }
   print "const AlarmType OSEK_ALARMLIST_" . $counter . "[" . $countalarms . "] = {\n";
   foreach ($alarms as $alarm)
   {
      if ($counter == $config->getValue("/OSEK/" . $alarm,"COUNTER"))
      {
         print "   $alarm, /* this alarm has to be incremented with this counter */\n";
      }
   }
   print "};\n\n";
}

?>

/*==================[external data definition]===============================*/
/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.         Osek P.
<?php
$pkey = array_keys($priority);
for($i = 0; $i < count($priority); $i++)
{
   print " * " . $pkey[$i] . "               " . $priority[$pkey[$i]] . "\n";
}
print " */\n";

?>

const TaskConstType TasksConst[TASKS_COUNT] = {
<?php
$count = 0;
/* create task const structure */
foreach ($tasks as $task)
{
   if ( $count++ != 0 ) print ",\n";
   print "   /* Task $task */\n";
   print "   {\n";
   print "       OSEK_TASK_$task,   /* task entry point */\n";
   print "       &ContextTask" . $task . ", /* pointer to task context */\n";
   print "       StackTask" . $task . ", /* pointer stack memory */\n";
   print "       sizeof(StackTask" . $task . "), /* stack size */\n";
   print "       " . $priority[$config->getValue("/OSEK/" . $task, "PRIORITY")] . ", /* task priority */\n";
   print "       " . $config->getValue("/OSEK/" . $task, "ACTIVATION"). ", /* task max activations */\n";
   print "       {\n";
   $extended = $config->getValue("/OSEK/" . $task, "TYPE");
   if($extended == "BASIC")
   {
      print "         0, /* basic task */\n";
   }
   elseif ($extended == "EXTENDED")
   {
      print "         1, /* extended task */\n";
   }
   else
   {
      error("Wrong definition of task type \"" . $extended . "\" for task \"" . $task . "\".");
   }
   $schedule = $config->getValue("/OSEK/" .$task, "SCHEDULE");
   if ($schedule == "FULL")
   {
      print "         1, /* preemtive task */\n";
   }
   elseif($schedule == "NON")
   {
      print "         0, /* non preemtive task */\n";
   }
   else
   {
      error("Wrong definition of task schedule \"" . $schedule . "\" for task \"" . $task . "\".");
   }
   print "         0\n";
   print "      }, /* task const flags */\n";
   $events = $config->getList("/OSEK/" . $task, "EVENT");
   $elist = "0 ";
   foreach ($events as $event)
   {
      $elist .= "| $event ";
   }
   print "      $elist, /* events mask */\n";
   $rlist = "0 ";
   $resources = $config->getList("/OSEK/" . $task, "RESOURCE");
   foreach($resources as $resource)
   {
      $rlist .= "| ( 1 << $resource ) ";
   }
   print "      $rlist,/* resources mask */\n";
   if (isset($definition["MCORE"]))
   {
      print "      " . $config->getValue("/OSEK/" . $task, "CORE") . " /* core */\n";
   }
   else
   {
      print "      0 /* core */\n";
   }
   print "   }";
}
print "\n";
?>
};

/** \brief RemoteTaskCore Array */
const TaskCoreType RemoteTasksCore[REMOTE_TASKS_COUNT] = {<?php
$rtasks = getRemoteList("/OSEK", "TASK");
for($i=0; $i<count($rtasks); $i++)
{
   print $config->getValue("/OSEK/$rtasks[$i]", "CORE");
   if ($i < (count($rtasks)-1))
   {
      print ", ";
   }
}
?>
};

/** \brief TaskVar Array */
TaskVariableType TasksVar[TASKS_COUNT];

<?php
$appmodes = $config->getList("/OSEK", "APPMODE");

foreach ($appmodes as $appmode)
{
   $tasksinmode = array();
   foreach($tasks as $task)
   {
      $taskappmodes = $config->getList("/OSEK/" . $task, "APPMODE");
      foreach ($taskappmodes as $taskappmode)
      {
         if ($taskappmode == $appmode)
         {
            $tasksinmode[] = $task;
         }
      }
   }
   if (count($tasksinmode) > 0)
   {
      $count = 0;
      print "/** \brief List of Auto Start Tasks in Application Mode $appmode */\n";
      print "const TaskType TasksAppMode" . $appmode . "[" . count($tasksinmode). "]  = {\n";
      foreach($tasksinmode as $task)
      {
         if ($count++ != 0) print ",\n";
         print "   $task";
      }
      print "\n};\n";
   }
}

print "/** \brief AutoStart Array */\n";
print "const AutoStartType AutoStart[" . count($appmodes) . "]  = {\n";
$count = 0;
foreach ($appmodes as $appmode)
{
   if ( $count++ != 0 ) print ",\n";
   print "   /* Application Mode $appmode */\n";
   print "   {\n";
   $tasksinmode = array();
   foreach($tasks as $task)
   {
      $taskappmodes = $config->getList("/OSEK/" . $task, "APPMODE");
      foreach ($taskappmodes as $taskappmode)
      {
         if ($taskappmode == $appmode)
         {
            $tasksinmode[] = $task;
         }
      }
   }
   print "      " . count($tasksinmode) .", /* Total Auto Start Tasks in this Application Mode */\n";
   if (count($tasksinmode)>0)
   {
      print "      (TaskRefType)TasksAppMode" . $appmode . " /* Pointer to the list of Auto Start Stacks on this Application Mode */\n";
   }
   else
   {
      print "      NULL /* no tasks on this mode */\n";
   }
   print "   }";
}
print "\n};\n";
?>

<?php
print "const ReadyConstType ReadyConst[" . count($priority) .  "] = { \n";
$c = 0;
foreach ($priority as $prio)
{
   if ($c++ != 0) print ",\n";
   print "   {\n";
   $count = 0;
   foreach ($tasks as $task)
   {
      if ($priority[$config->getValue("/OSEK/" . $task, "PRIORITY")] == $prio)
      {
         $count += $config->getValue("/OSEK/" . $task, "ACTIVATION");
      }
   }
   print "      $count, /* Length of this ready list */\n";
   print "      ReadyList" . $prio . " /* Pointer to the Ready List */\n";
   print "   }";
}
print "\n};\n\n";

print "/** TODO replace next line with: \n";
print " ** ReadyVarType ReadyVar[" . count($priority) . "] ; */\n";
print "ReadyVarType ReadyVar[" . count($priority) . "];\n";
?>

<?php
/* Resources Priorities */
$resources = $config->getList("/OSEK","RESOURCE");
print "/** \brief Resources Priorities */\n";
print "const TaskPriorityType ResourcesPriority[" . count($resources) . "]  = {\n";
$c = 0;
foreach ($resources as $resource)
{
   $count = 0;
   foreach ($tasks as $task)
   {
      $resorucestask = $config->getList("/OSEK/" . $task, "RESOURCE");
      foreach($resorucestask as $rt)
      {
         if ($rt == $resource)
         {
            if ($priority[$config->getValue("/OSEK/" . $task, "PRIORITY")] > $count)
            {
               $count = $priority[$config->getValue("/OSEK/" . $task, "PRIORITY")];
            }
         }
      }
   }
   if ($c++ != 0) print ",\n";
   print "   $count";

}
print "\n};\n";

$alarms = getLocalList("/OSEK", "ALARM");
print "/** TODO replace next line with: \n";
print " ** AlarmVarType AlarmsVar[" . count($alarms) . "]; */\n";
print "AlarmVarType AlarmsVar[" . count($alarms) . "];\n\n";

print "const AlarmConstType AlarmsConst[" . count($alarms) . "]  = {\n";
$count = 0;
foreach ($alarms as $alarm)
{
   if ($count++ != 0)
   {
      print ",\n";
   }
   print "   {\n";
   print "      OSEK_COUNTER_" . $config->getValue("/OSEK/" . $alarm, "COUNTER") . ", /* Counter */\n";
   $action = $config->getValue("/OSEK/" . $alarm, "ACTION");
   print "      " . $action . ", /* Alarm action */\n";
   print "      {\n";
   switch ($action)
   {
   case "INCREMENT":
      print "         NULL, /* no callback */\n";
      print "         0, /* no task id */\n";
      print "         0, /* no event */\n";
      print "         OSEK_COUNTER_" . $config->getValue("/OSEK/" . $alarm . "/INCREMENT","COUNTER") . " /* counter */\n";
      break;
   case "ACTIVATETASK":
      print "         NULL, /* no callback */\n";
      print "         " . $config->getValue("/OSEK/" . $alarm . "/ACTIVATETASK","TASK") . ", /* TaskID */\n";
      print "         0, /* no event */\n";
      print "         0 /* no counter */\n";
      break;
   case "SETEVENT":
      print "         NULL, /* no callback */\n";
      print "         " . $config->getValue("/OSEK/" . $alarm . "/SETEVENT","TASK") . ", /* TaskID */\n";
      print "         " . $config->getValue("/OSEK/" . $alarm . "/SETEVENT","EVENT") . ", /* no event */\n";
      print "         0 /* no counter */\n";
      break;
   case "ALARMCALLBACK":
      print "         OSEK_CALLBACK_" . $config->getValue("/OSEK/" . $alarm . "/ALARMCALLBACK", "ALARMCALLBACKNAME") . ", /* callback */\n";
      print "         0, /* no taskid */\n";
      print "         0, /* no event */\n";
      print "         0 /* no counter */\n";
      break;
   default:
      error("Alarm $alarm has an invalid action: $action");
      break;
   }
   print "      },\n";
   print "   }";

}
print "\n};\n\n";

print "const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {\n";
$count = 0;
foreach ($alarms as $alarm)
{
   if ($config->getValue("/OSEK/" . $alarm, "AUTOSTART") == "TRUE")
   {
      if ($count++ != 0)
      {
         print ",\n";
      }
      print "  {\n";

      print "      " . $config->getValue("/OSEK/" . $alarm, "APPMODE") . ", /* Application Mode */\n";
      // print "      OSEK_COUNTER_" . $config->getValue("/OSEK/" . $alarm, "COUNTER") . ", /* Counter */\n";
      print "      $alarm, /* Alarms */\n";
      print "      " . $config->getValue("/OSEK/" . $alarm, "ALARMTIME") . ", /* Alarm Time */\n";
      print "      " . $config->getValue("/OSEK/" . $alarm, "CYCLETIME") . " /* Alarm Time */\n";
      print "   }";
   }
}
print "\n};\n\n";

$counters = getLocalList("/OSEK", "COUNTER");

print "CounterVarType CountersVar[" . count($counters) . "];\n\n";

$alarms = $config->getList("/OSEK","ALARM");
$count = 0;
print "const CounterConstType CountersConst[" . count($counters) . "] = {\n";
foreach ($counters as $counter)
{
   if ($count++!=0)
   {
      print ",\n";
   }
   print "   {\n";
   $countalarms = 0;
   foreach ($alarms as $alarm)
   {
      if ($counter == $config->getValue("/OSEK/" . $alarm,"COUNTER"))
      {
         $countalarms++;
      }
   }
   print "      $countalarms, /* quantity of alarms for this counter */\n";
   print "      (AlarmType*)OSEK_ALARMLIST_" . $counter . ", /* alarms list */\n";
   print "      " . $config->getValue("/OSEK/" . $counter,"MAXALLOWEDVALUE") . ", /* max allowed value */\n";
   print "      " . $config->getValue("/OSEK/" . $counter,"MINCYCLE") . ", /* min cycle */\n";
   print "      " . $config->getValue("/OSEK/" . $counter,"TICKSPERBASE") . " /* ticks per base */\n";
   print "   }";
}
print "\n};\n\n";

?>

/** TODO replace the next line with
 ** uint8 ApplicationMode; */
uint8 ApplicationMode;

/** TODO replace the next line with
 ** uint8 ErrorHookRunning; */
uint8 ErrorHookRunning;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
<?php
$intnames = getLocalList("/OSEK", "ISR");
foreach ($intnames as $int)
{
   $inttype = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $intcat = $config->getValue("/OSEK/" . $int,"CATEGORY");

   if ($intcat == 2)
   {?>
void OSEK_ISR2_<?php print $int;?>(void)
{
   /* store the calling context in a variable */
   ContextType actualContext = GetCallingContext();
   /* set isr 2 context */
   SetActualContext(CONTEXT_ISR2);

   /* trigger isr 2 */
   OSEK_ISR_<?php print $int;?>();

   /* reset context */
   SetActualContext(actualContext);

#if (NON_PREEMPTIVE == OSEK_DISABLE)
   /* check if the actual task is preemptive */
   if ( ( CONTEXT_TASK == actualContext ) &&
        ( TasksConst[GetRunningTask()].ConstFlags.Preemtive ) )
   {
      /* this shall force a call to the scheduler */
      PostIsr2_Arch(isr);
   }
#endif /* #if (NON_PREEMPTIVE == OSEK_ENABLE) */
}

<?php }

}
?>

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

