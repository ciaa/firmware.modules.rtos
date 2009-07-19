<?php

$drvconfig = $config->getList("/DRV","GENERAL");

if (count($drvconfig) != 1)
{
	error("only one DRV DRIVERS configuration is allowed, " . count($drvconfig) . " were found.");
}
else
{
	$drvconfig = $drvconfig[0];
	print "# include sub drivers\n";
	$drivers = array ("StartUp", "Dio", "Eth", "Mcu", "Pwm", "Adc");
	foreach($drivers as $driver)
	{
		$value = $config->getValue("/DRV/" . $drvconfig , $driver);
		switch ($value)
		{
			case "ENABLE":
				print "include FreeOSEK$(DIR)Drv$(DIR)$driver$(DIR)mak$(DIR)Makefile\n";
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
