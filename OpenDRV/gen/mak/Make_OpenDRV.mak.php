<?php $drivers = $config->getList("/OpenDRV","OpenDRV");

if (count($drivers) != 1)
{
	error("more than one OpenDRV configuration");
}
else
{

}

?>
