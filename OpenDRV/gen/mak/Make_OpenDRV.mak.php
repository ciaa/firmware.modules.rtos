<?php

$drvconfig = $config->getList("/OpenDRV","GENERAL");

if (count($drvconfig) != 1)
{
	error("only one OpenDRV DRIVERS configuration is allowed, " . count($drvconfig) . " were found.");
}
else
{
	$drvconfig = $drvconfig[0];
	print "# include sub drivers\n";
	$drivers = array ("StartUp", "Dio", "Eth", "Mcu", "Pwm");
	foreach($drivers as $driver)
	{
		$value = $config->getValue("/OpenDRV/" . $drvconfig , $driver);
		switch ($value)
		{
			case "ENABLE":
				print "include OpenDRV$(DIR)$driver$(DIR)mak$(DIR)Makefile\n";
				break;
			case "DISABLE":
				break;
			default:
				warning("$driver driver is not configured as ENABLE neither as DISABLE, disabled as default");
				break;
		}
	}
	
}

?>
