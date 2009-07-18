<?php

$value = $config->getValue("/OpenDRV/Eth" , "MAC");
if ($value == "")
{
	error("No MAC was configured on the Eth Driver configuration");
}
print "MAC = $value\n\n";

$value = $config->getValue("/OpenDRV/Eth" , "PHY");
if ($value == "")
{
	error("No PHY was configured on the Eth Driver configuration");
}
print "PHY = $value\n";

?>
