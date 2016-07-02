/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 * Copyright 2016 Franco Bucafusco
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

<?php
/** \brief FreeOSEK File to be Generated
 **
 ** \file Os_Cfg.h.php
 **
 **/
?>

#ifndef _OS_CFG_H_
#define _OS_CFG_H_
/** \brief FreeOSEK Os Generated Configuration Header File
 **
 ** This file contents the generated configuration of FreeOSEK Os
 **
 ** \file Os_Cfg.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Global
 ** @{ */


/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Definition of the  DeclareTask Macro */
#define DeclareTask(name) void OSEK_TASK_ ## name (void)

#define OSEK_OS_INTERRUPT_MASK ((InterruptFlagsType)0xFFFFFFFFU)

<?php
$this->loadHelper("modules/rtos/gen/ginc/Multicore.php");
$this->loadHelper("modules/rtos/gen/ginc/Platform.php");

/* Definitions of Tasks : Tasks that will be executed within the local core */
/* TODO: validate that tasks has different names */
$tasks = $this->helper->multicore->getLocalList("/OSEK", "TASK");
$remote_tasks = $this->helper->multicore->getRemoteList("/OSEK", "TASK");
$os = $this->config->getList("/OSEK","OS");

$count = 0;
foreach ($tasks as $task)
{
   print "/** \brief Task Definition */\n";
   print "#define $task $count\n";
   $count++;
}
print "\n";

/* Definitions of Tasks : Tasks that will be executed within the remote core*/
if (count($remote_tasks) > 0)
{
   foreach ($remote_tasks as $task)
   {
      print "/** \brief Remote Task Definition */\n";
      print "#define $task $count\n";
      $count++;
   }
   print "\n";
}

/* Define the Applications Modes */
$appmodes = $this->config->getList("/OSEK","APPMODE");

foreach ($appmodes as $count=>$appmode)
{
   print "/** \brief Definition of the Application Mode $appmode */\n";
   print "#define " . $appmode . " " . $count . "\n";
}
print "\n";

/* Define the Events */

/* the max ammount of events is defined by the bit width of EventMaskType type */
$max_amount_events = $this->helper->platform->getIntWidth();

//print("cant eventos max ".$max_amount_events."\n");

$flags_shared_event = $max_amount_events; /* it stores the number of bit for flags that are shared across tasks */

$matriz    = array( ); /* it stores the events' name for each task */
$matrix_n  = array();  /* it stores the events' assigned number for each task */

$events = $this->config->getList("/OSEK","EVENT");
//$nro_evs= max(array_keys($events))+1;
$nro_evs= count($events);
#print("cantidad de eventos: $nro_evs \n");

/* task/events matrix creation, and various validations */
$task_index = 0;
foreach( $tasks as $task )
{
   $empty_array = array();
   $temp_array = $this->config->getList("/OSEK/". $task , "EVENT"  );

   /*for each task we get the defined events*/
   array_push( $matriz , $temp_array );
   array_push( $matrix_n , $empty_array );

   $nro_ev_task = count($matriz[$task_index]); #max(array_keys($matriz[$task_index]));

   /* Task Type validation: validates that this task is extended */
   $extended = $this->config->getValue("/OSEK/" . $task, "TYPE");

   if ($extended != "EXTENDED" && $nro_ev_task>0 )
   {
      trigger_error("===== OIL ERROR: The task $task should be TYPE: EXTENDED =====\n", E_USER_ERROR);
   }
   else
   {
      if ($nro_ev_task == 0 && $extended != "BASIC")
      {
         trigger_error("===== OIL WARNING: The task $task could be TYPE: BASIC =====\n", E_USER_WARNING);
      }
   }

   /* Task Event Validation: validates that the defined event within the task is globally defined */
   foreach( $matriz[$task_index] as $evi )
   {
      /* search the task event in the global event array */
      $key = array_search( $events , $matriz[$task_index] );
      if( $key !== false )
      {
         trigger_error("===== OIL ERROR: The event $evi for task $task is not globally defined =====\n", E_USER_ERROR);
         /* stops execution */
      }
      else
      {
      }
   }

   $task_index++;
}


/* generation of the shared events between tasks */
print "\n/** \brief Shared events across tasks */\n\n";
$ev_index   = 0;

foreach( $events as $ev ) //para cada evento, lo busco en cada array de eventos para la tarea
{
   //print( "//Procesando evento  $ev \n" );
   $task_index = 0;

   $count=0;                  //almacena la cuenta de cuantas tareas tiene el evento
   $task_single_event = "";   //almacena la ultima tarea en la cual encontro el evento

   foreach( $tasks as $task )
   {
      #$events_for_task = $this->config->getList("/OSEK/". $task , "EVENT"  );
      $key = array_search( $ev, $matriz[$task_index] );

      if( $key !== false ) //busco el evento en el array de eventos de la tarea.
      {
         /* lo encontro */
         $count++;
      }

      $task_index++;
   }

   //print_r("\n$ev $count \n" );

   if($count>1)
   {
      /* there is more that one task with the current event */
      $flags_shared_event--;

      if($flags_shared_event<0 )
      {
         trigger_error("===== OIL ERROR: There are more than $max_amount_events events defined.  =====\n", E_USER_ERROR);
         /* stops execution */
      }

      print "/** \brief Definition of the Event: $ev */\n";
      print "#define " . $ev . " 0x" . sprintf ("%xU", (1<<$flags_shared_event)) . "\n";

      /* this shared's event number is stored in matrix_n */
      $task_index = 0;
      foreach( $tasks as $task )
      {
            $key = array_search( $ev, $matriz[$task_index] );  //EL EVENTO TIENE QUE EXISTIR SI O SI.
         unset($matriz[$task_index][$key]); //LO SACO DE LA TABLA DE EVENTOS DE LA TAREA
         array_push( $matrix_n[$task_index] , $flags_shared_event );
         $task_index++;
      }
   }

   $ev_index++;
}
//print_r($matriz);
print "\n\n/** \brief Exclusive events for each task */\n\n";
$task_index = 0;
foreach( $tasks as $task )
{
   $flags_exc_event = 0;  /* it stores the number of bit for flags that are exclusively for one task */

   foreach( $matriz[$task_index] as $ev )
   {
      if($flags_exc_event>$max_amount_events )
      {
         throw new Exception("===== OIL ERROR: There are more than $max_amount_events events defined.  =====\n");
         /* stops execution */
      }

      print "/** \brief Definition of the Event: $ev for task: $task*/\n";
      print "#define " . $ev . " 0x" . sprintf ("%xU", (1<<$flags_exc_event)) . "\n";

      $temp = $flags_exc_event;
      array_push( $matrix_n[$task_index] , $temp );

      $flags_exc_event++;
   }

   $task_index++;
}

/* Last validation: check if events repeats  */
$task_index       =0;
foreach ($matrix_n as $array)
{
   #print_r($array);
   $count_values = array_count_values($matrix_n[$task_index]) ;  /* it counts the times that repeats an event number, all of them should be 1*/
   #print_r($count_values);
   foreach ($count_values as $key => $value)
   {
      #print_r($value);
      if($value>1)
      {
         throw new Exception("===== OIL ERROR: There are more events that the task can handle.  =====\n");
         /* stops execution */
      }
   }
   $task_index ++;
}
print "\n";

//$events = $this->config->getList("/OSEK","EVENT");

//foreach ($events as $count=>$event)
//{
//   print "/** \brief Definition of the Event $event */\n";
//   print "#define " . $event . " 0x" . sprintf ("%xU", (1<<$count)) . "\n";
//}
//print "\n";

/* Define the Resources */
$resources = $this->config->getList("/OSEK","RESOURCE");

foreach ($resources as $count=>$resource)
{
   print "/** \brief Definition of the resource $resource */\n";
   print "#define " . $resource . " ((ResourceType)" . $count . ")\n";
}
print "\n";

/* Define the Alarms */
$alarms = $this->helper->multicore->getLocalList("/OSEK", "ALARM");

foreach ($alarms as $count=>$alarm)
{
   print "/** \brief Definition of the Alarm $alarm */\n";
   print "#define " . $alarm . " " . $count . "\n";
}
print "\n";

/* Define the Counters */
$counters = $this->helper->multicore->getLocalList("/OSEK", "COUNTER");

foreach ($counters as $count=>$counter)
{
   print "/** \brief Definition of the Counter $counter */\n";
   print "#define " . $counter . " " . $count . "\n";
}
print "\n";

$errorhook=$this->config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
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

$memmap = $this->config->getValue("/OSEK/" . $os[0],"MEMMAP");
print "/** \brief OSEK_MEMMAP macro (OSEK_DISABLE not MemMap is used for FreeOSEK, OSEK_ENABLE\n ** MemMap is used for FreeOSEK) */\n";
if ($memmap == "TRUE")
{
   print "#define OSEK_MEMMAP OSEK_ENABLE\n";
}
elseif ($memmap == "FALSE")
{
   print "#define OSEK_MEMMAP OSEK_DISABLE\n";
}
else
{
   $this->log->warning("MEMMAP configuration not found in FreeOSEK configuration, disabling as default");
   print "#define OSEK_MEMMAP OSEK_DISABLE\n";
}

$osattr = $this->config->getValue("/OSEK/" . $os[0],"STATUS");
if ($osattr == "EXTENDED") : ?>
/** \brief Schedule this Task if higher priority Task are Active
 **
 ** \remarks if the system is configured with extended errors the
 **          function Schedule is implemented as a macro and calls the
 **          internal function Schedule_Int. If Standard errores are
 **          configured the function Schedule is implemented as a function.
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used from non preemtive tasks.
 **
 ** \return E_OK if no error
 ** \return E_OS_CALLEVEL if call at interrupt level
 ** \return E_OS_RESOURCE if the calling task occupies resources
 **/
#define Schedule() Schedule_Int(TRUE)
<?php
   endif;
?>

/*==================[typedef]================================================*/
/** \brief Type definition of StatusType
 **
 ** This type is used to represent the status returned by all FreeOSEK APIs
 **/
/* \req OSEK_SYS_1.1 */
typedef unsigned char StatusType;


/*==================[external data declaration]==============================*/
<?php
$errorhook=$this->config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
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

/*==================[external functions declaration]=========================*/
<?php
$pretaskhook=$this->config->getValue("/OSEK/" . $os[0],"PRETASKHOOK");
if ($pretaskhook == "TRUE")
{
   print "/** \brief Pre Task Hook */\n";
   print "extern void PreTaskHook(void);\n\n";
}
$posttaskhook=$this->config->getValue("/OSEK/" . $os[0],"POSTTASKHOOK");
if ($posttaskhook == "TRUE")
{
   print "/** \brief Post Task Hook */\n";
   print "extern void PostTaskHook(void);\n\n";
}
$shutdownhook=$this->config->getValue("/OSEK/" . $os[0],"SHUTDOWNHOOK");
if ($shutdownhook == "TRUE")
{
   print "/** \brief Shutdown Hook */\n";
   print "extern void ShutdownHook(void);\n\n";
}
$startuphook=$this->config->getValue("/OSEK/" . $os[0],"STARTUPHOOK");
if ($startuphook == "TRUE")
{
   print "/** \brief Startup Hook */\n";
   print "extern void StartupHook(void);\n\n";
}
$errorhook=$this->config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
   print "/** \brief Error Hook */\n";
   print "extern void ErrorHook(void);\n\n";
}

/* Declare Tasks */

foreach ($tasks as $count=>$task)
{
   print "/** \brief Task Declaration of Task $task */\n";
   print "DeclareTask($task);\n";
}
print "\n";

$intnames = $this->helper->multicore->getLocalList("/OSEK", "ISR");

foreach ($intnames as $count=>$int)
{
   print "/** \brief ISR Declaration */\n";
   print "extern void OSEK_ISR_$int(void); /* Interrupt Handler $int */\n";
}
print "\n";

$alarms = $this->helper->multicore->getLocalList("/OSEK", "ALARM");

foreach ($alarms as $count=>$alarm)
{
   $action = $this->config->getValue("/OSEK/" . $alarm, "ACTION");
   if ($action == "ALARMCALLBACK")
   {
      print "/** \brief Alarm Callback declaration */\n";
      print "extern void OSEK_CALLBACK_" . $this->config->getValue("/OSEK/" . $alarm . "/ALARMCALLBACK", "ALARMCALLBACKNAME") . "(void);\n";
   }
}
print "\n";

$osattr = $this->config->getValue("/OSEK/" . $os[0],"STATUS"); ?>
/** \brief Schedule this Task if higher priority Task are Active
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used from non preemtive tasks.
 **
 ** \remarks This interface may be used by the end user over the
 **          macro Schedule or from the system itself. Therefore
 **          the parameter PerformChecks is provided. When
 **          the user calls the scheduler the checks shall be
 **          performed if the error checking is set as extended.
 **          If the system calls the Schedule no error checking
 **          shall be performed, the system shall be trusted.
 **
 ** \param[in] PerformChecks indicates if the function shall or not
 **                          perform the extended checks. This parameter
 **                          is only available if the error checks are set
 **                          to extended.
 ** \return E_OK if no error
 ** \return E_OS_CALLEVEL if call at interrupt level
 ** \return E_OS_RESOURCE if the calling task occupies resources
 **/
<?php if ($osattr == "EXTENDED") : ?>
extern StatusType Schedule_Int(boolean PerformChecks);
<?php elseif ($osattr == "STANDARD") : ?>
extern StatusType Schedule(void);
<?php endif; ?>

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_CFG_H_ */
