<?php

$drivers = $config->getList("/OpenDRV","DRIVER");

$count = 0;
foreach ($drivers as $driver)
{
	if ($driver == "GenConfig")
	{
		$count ++;
	}
}

if ($count != 1)
{
	error("only one OpenDRV DRIVERS configuration is allowed, " . count($drivers) . " were found.");
}
else
{
	print "# include sub drivers\n";
	$drivers = array ("StartUp", "Dio", "Eth", "Clk");
	foreach($drivers as $driver)
	{
		$value = $config->getValue("/OpenDRV/GenConfig", $driver);
		switch ($value)
		{
			case "ENABLE":
				print "include OpenDRV$(DIR)$driver$(DIR)mak$(DIR)Makefile\n";
				break;
			case "DISABLE":
				break;
			default:
				error("$driver driver is not configured as ENABLE neither as DISABLE");
				break;
		}
	}
	
}

?>
