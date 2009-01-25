<?php

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

/** \brief OpenSEK Generator
 **
 ** This file implements the OpenSEK Generator
 **
 ** \file generator.php
 **
 **/

/** \addtogroup OpenSEK
 ** @{ */
/** \addtogroup Generator
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20080812 MaCe initial version
 */

/*==================[inclusions]=============================================*/
require_once("config.php");

/*=================[user functions]============================================*/
$errors = 0;
$warnings = 0;
$generating = false;

/** \brief Info Generator Function
 **
 ** This function shall be used to report generation information to the user.
 ** Please don't use this function for report warnings or errors.
 **
 ** \param[in] msg string containing the information message to be reported
 **/
function info($msg)
{
	global $verbose;
	global $generating;
	if($generating == true)
	   ob_end_flush();
	if ($verbose)
	{
		print "INFO: " . $msg . "\n";
	}
	if($generating == true)
	ob_start('ob_file_callback');
}

/** \brief Warning Generator Function
 **
 ** This function shall be used to report warnings information to the user.
 ** Don't use this function to report information or errors.
 **
 ** \param[in] msg string containing the warning message to be reported.
 **/
function warning($msg)
{
	ob_end_flush();
	print "WARNING: " . $msg . "\n";
	global $warnings;
	$warnings++;
	ob_start('ob_file_callback');
}

/** \brief Error Generator Function
 **
 ** This function shall be used to report error information to the user.
 ** The generation process will continues to provide all error to the user.
 ** If you wan to report an error and to abort the generation use the
 ** abort function.
 ** Don't use this function to report information or warnings.
 **
 ** \param[in] msg string containing the error message to be reported.
 **/
function error($msg)
{
	global $error;
	ob_end_flush();
	print "ERROR: " . $msg . "\n";
	global $errors;
	$errors++;
	$error = true;
	ob_start('ob_file_callback');
}

/** \brief Abort Generator Function
 **
 ** This function shall be used to report an error and abort the generation.
 ** Don't use this function to report information or warnings.
 **
 ** \param[in] msg string containing the error message to be reported.
 **/
function halt($msg)
{
	ob_end_flush();
	error($msg);
	exit(1);
}

/*=================[end of user functions]=====================================*/

/*=================[global variables]==========================================*/
$verbose = false;
$path = "";

function ob_file_callback($buffer)
{
	global $ob_file;
	fwrite($ob_file,$buffer);
}

function printCmdLine()
{
	print "INFO: the generator was called as follow:\nINFO: ";
	foreach ($_SERVER['argv'] as $arg)
	{
		print "$arg ";
	}
	print "\n";
}

$args = $_SERVER['argv'];
$path = array_shift($args);

$path = substr($path,0, strlen($path)-strlen("/generator.php"));

print "OpenSEK Generator - Copyright 2008, Mariano Cerdeiro - http://www.openosek.com.ar\n\n";

foreach ($args as $arg)
{
	switch ($arg)
	{
		case "--cmdline":
			printCmdLine();
			break;
		case "-l":
			print "INFO: ------ LICENSE START ------\n";
			print "INFO: OpenSEK Generator is part of OpenOSEK.\nINFO: \n";
			print "INFO: OpenSEK is free software: you can redistribute it and/or modify\n";
			print "INFO: it under the terms of the GNU General Public License as published by\n";
			print "INFO: the Free Software Foundation, either version 3 of the License, or\n";
			print "INFO: (at your option) any later version.\nINFO: \n";
			print "INFO: OpenSEK is distributed in the hope that it will be useful,\n";
			print "INFO: but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
			print "INFO: MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
			print "INFO: GNU General Public License for more details.\n";
			print "INFO: You should have received a copy of the GNU General Public License\n";
			print "INFO: along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.\n";
			print "INFO: ------- LICENSE END -------\n";
			break;
		case "-h":
		case "--help":
			print "php generator.php [-l] [-h] [--cmdline] -c <CONFIG_1> [<CONFIG_2>] -o <OUTPUTDIR> -f <GENFILE_1> [<GENFILE_2>]\n";
			print "      -c   indicate the configuration input files\n";
			print	"      -o   output directory\n";
			print "      -f   indicate the files to be generated\n";
			print "   optional parameters:\n";
			print "      -h   display this help\n";
			print "      -l   displays a short license overview\n";
			print "      --cmdline print the command line\n";
			exit();
			break;
		case "-v":
			$verbose = true;
			break;
		case "-c":
		case "-o":
		case "-f":
			$oldarg = $arg;
			break;
		default:
			switch($oldarg)
				{
					case "-c":
						/* add a config file */
						$configfiles[] = $arg;
						break;
					case "-o":
						/* add an output dir */
						$outputdir[]= $arg;
						break;
					case "-f":
						/* add generated file */
						$genfiles[] = $arg;
						break;
					default:
						halt("invalid argument: " . $arg);
						break;
				}
			break;
	}
}

if (count($configfiles)==0)
{
	halt("at least one config file shall be provided");
}

if (count($outputdir)!=1)
{
	halt("exactly one output directory shall be provided");
}

if (count($genfiles)==0)
{
	halt("at least one file to be generated shall be provided");
}

if ($verbose)
{
	info("list of configuration files:");
	$count = 1;
	foreach ($configfiles as $file)
	{
		info("configuration file " . $count++ . ": " . $file);
	}

	info("list of files to be generated:");
	$count = 1;
	foreach ($genfiles as $file)
	{
		info("generated file " . $count++ . ": " . $file);
	}

	info("output directory: " . $outputdir[0]);
}

foreach ($configfiles as $file)
{
	info("reading " . $file);
	$config->parseOilFile($file);
}

foreach ($genfiles as $file)
{
	$outfile = $file;
	$outfile = substr($outfile, 0, strlen($outfile)-4);
	//print "info aca: pos: ". strpos($outile, "a",1);
	#while(strpos($outfile,"gen")!==FALSE)
	{
		#print "si: $outfile - ";
		$outfile = substr($outfile, strpos($outfile, "gen")+3);
		#print "$outfile\n";
	}
   $outfile = $outputdir[0] . $outfile;
	info("generating ". $file . " to " . $outfile);
	global $ob_file;
	$ob_file = fopen($outfile, "w");
	ob_start('ob_file_callback');
	$generating=true;
	require_once($file);
	$generating=false;
	ob_end_flush();
	fclose($ob_file);
}

info("Generation Finished with WARNINGS: $warnings and ERRORS: $errors");
if ($errors > 0)
{
	exit(1);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
?>
