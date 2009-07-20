<?php

$value = $config->getValue("/DRV/Eth" , "MAC");
if ($value == "")
{
	error("No MAC was configured on the Eth Driver configuration");
}
print "MAC = $value\n\n";

$value = $config->getValue("/DRV/Eth" , "PHY");
if ($value == "")
{
	error("No PHY was configured on the Eth Driver configuration");
}
print "PHY = $value\n";

?>
