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
<?php
/** \brief OpenDRV PWM Internal Arch Header File to be Generated
 **
 ** \file Pwm_Internal_Arch_Cfg.h.php
 **/
?>

#ifndef _PWM_INTERNAL_ARCH_CFG_H_
#define _PWM_INTERNAL_ARCH_CFG_H_
/** \brief OpenDRV PWM Internal Arch Generated Configuration Header File
 **
 ** This file contents the generated configuration of the PWM Driver
 **
 ** \file Pwm_Internal_Arch_Cfg.h
 **/

/** \addtogroup OpenDRV
 ** @{ */
/** \addtogroup OpenDRV_Pwm
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
 * 20090522 v0.1.0 MaCe	initial version
 */

<?php

$pwmconfig = $config->getList("/OpenDRV/Pwm","CONFIG");
if(count($pwmconfig)!=1)
{
	error("Wrong count of Pwm Driver configurations, at the moment only 1 config is allowed for the Pwm driver");
}

$pwmchannels = $config->getList("/OpenDRV/Pwm/" . $pwmconfig[0],"CHANNEL");

/* $port_mask = array_fill(0, 5, 0);
$port_dir = array_fill(0, 5, 0); */

$period0cte = 0;
$period1cte = 0;
$PWM_PWM0 = "DISABLE";
$PWM_PWM1 = "DISABLE";
$PWM_PWM0MCR = 0;
$PWM_PWM1MCR = 0;
$PWM_PWM0PCR = 0;
$PWM_PWM1PCR = 0;
$PWM_PWM0LER = 1;
$PWM_PWM1LER = 1;

foreach($pwmchannels as $pwmc)
{
	$name = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_NAME");
	$channel = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL");
	$class = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_CLASS");
	$dutycycle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_DUTYCYCLE_DEFAULT");
	$idle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_IDLE_STATE");
	$period = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_PERIOD_DEFAULT");
	$polarity = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_POLARITY");

	if ( ($channel > 12) || ($channel < 0) )
	{
		error("Invalid channek number: " . $pwmc . ". Only channels between 1 and 12 are available.");
	}
	if($class != "PWM_FIXED_PERIOD")
	{
		error("Error on PWM: " . $pwmc . ". Only class PWM_FIXED_PERIOD is supported");
	}
	if($polarity != "PWM_HIGH")
	{
		error("Error on PWM: " . $pwmc . ". Only polarity PWM_HIGH is supported.");
	}

	if ( ($channel > 0) && ($channel < 7) )
	{
		$PWM_PWM0 = "ENABLE";
		$PWM_PWM0MCR += ( 2 << ( ($channel-1) * 3 ) );
		$PWM_PWM0PCR += ( 1 << ($channel-1+9) );
		$PWM_PWM0LER += ( 1 << ($channel-1+1) );
		if($period != $period0cte)
		{
			if ($period0cte == 0)
			{
				$period0cte = $period;
			}
			else
			{
				error("All PWMs of block 0 shall have the same period, PWM: " . $pwmc . " has period $period which differ from $period0cte");
			}
		}
	}

	if ( ($channel > 6) && ($channel < 13) )
	{
		$PWM_PWM1 = "ENABLE";
		$PWM_PWM1MCR += ( 2 << ( ($channel-7) * 3 ) );
		$PWM_PWM1PCR += ( 1 << ($channel-7+9) );
		$PWM_PWM1LER += ( 1 << ($channel-7+1) );
		if($period != $period1cte)
		{
			if ($period1cte == 0)
			{
				$period1cte = $period;
			}
			else
			{
				error("All PWMs of block 1 shall have the same period, PWM: " . $pwmc . " has period $period which differ from $period1cte");
			}
		}
	}

/*	print "$pwmc\n";
	print "	$name\n";
	print "	$channel\n";
	print "	$class\n";
	print "	$dutycycle\n";
	print "	$idle\n";
	print "	$period\n";
	print "	$polarity\n"; */

}

?>
/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
<?php
print "/** \brief enables or disables PWM_PWM0 */\n";
if ($PWM_PWM0 == "ENABLE")
{
	print "#define PWM_PWM0 ENABLE\n\n";

	print "/** \brief PWM0 block match register for period\n";
	print " **\n";
	print " ** Confiugred Period: $period1cte -> frequency: " . (1/$period1cte) . " Hz\n";
	print " **/\n";
	print "#define PWM_PWM0MR0	" . ($period1cte * 1000000) . "\n\n";
	foreach($pwmchannels as $pwmc)
	{
		$name = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_NAME");
		$channel = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL");
		$class = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_CLASS");
		$dutycycle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_DUTYCYCLE_DEFAULT");
		$idle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_IDLE_STATE");
		$period = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_PERIOD_DEFAULT");
		$polarity = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_POLARITY");

		if ( ($channel > 6) && ($channel < 13) )
		{
			print "/** \brief enable PWM0 channel $channel */\n";
			print "#define PWM_PWM0_" . ($channel - 7) . "_ENABLE\n\n";

			print "/** \brief PWM0 channel $channel duty cycle */\n";
			print "#define PWM_PWM0_" . ($channel - 7) . "_DUTY " . intval( ( ($period1cte * 1000000) * $dutycycle ) / 32768 ) . "\n\n";
		}
	}
}
else
{
	print "#define PWM_PWM0 DISABLE\n\n";
}

print "/** \brief enables or disables PWM_PWM1 */\n";
if ($PWM_PWM1 == "ENABLE")
{
	print "#define PWM_PWM1 ENABLE\n\n";

	print "/** \brief PWM1 block match register for period\n";
	print " **\n";
	print " ** Confiugred Period: $period1cte -> frequency: " . (1/$period1cte) . " Hz\n";
	print " **/\n";
	print "#define PWM_PWM1MR0	" . ($period1cte * 1000000) . "\n\n";
	foreach($pwmchannels as $pwmc)
	{
		$name = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_NAME");
		$channel = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL");
		$class = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_CHANNEL_CLASS");
		$dutycycle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_DUTYCYCLE_DEFAULT");
		$idle = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_IDLE_STATE");
		$period = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_PERIOD_DEFAULT");
		$polarity = $config->getValue("/OpenDRV/Pwm/" . $pwmconfig[0] . "/" . $pwmc, "PWM_POLARITY");

		if ( ($channel > 6) && ($channel < 13) )
		{
			print "/** \brief enable PWM1 channel $channel */\n";
			print "#define PWM_PWM1_" . ($channel - 7) . "_ENABLE\n\n";

			print "/** \brief PWM1 channel $channel duty cycle */\n";
			print "#define PWM_PWM1_" . ($channel - 7) . "_DUTY " . intval( ( ($period1cte * 1000000) * $dutycycle ) / 32768 ) . "\n\n";
		}
	}
}
else
{
	print "#define PWM_PWM1 DISABLE\n\n";
}

print "/** \brief PWM0 Match Control Register */\n";
print "#define PWM_PWM0MCR $PWM_PWM0MCR\n\n";

print "/** \brief PWM1 Match Control Register */\n";
print "#define PWM_PWM1MCR $PWM_PWM1MCR\n\n";

print "/** \brief PWM0 Control Register */\n";
print "#define PWM_PWM0PCR $PWM_PWM0PCR\n\n";

print "/** \brief PWM1 Control Register */\n";
print "#define PWM_PWM1PCR $PWM_PWM1PCR\n\n";

print "/** \brief PWM0 Latch Enable Register */\n";
print "#define PWM_PWM0LER $PWM_PWM0LER\n\n";

print "/** \brief PWM1 Latch Enable Register */\n";
print "#define PWM_PWM1LER $PWM_PWM1LER\n\n";

?>

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _PWM_INTERNAL_ARCH_CFG_H_ */

