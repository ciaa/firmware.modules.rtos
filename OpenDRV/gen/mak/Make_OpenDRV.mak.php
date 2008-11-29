<?php

$drivers = $config->getList("/OpenDRV","DRIVERS");

if (count($drivers) != 1)
{
	error("only one OpenDRV DRIVERS configuration is allowed, " . count($dirvers) . " were found.");
}
else
{

}

?>
