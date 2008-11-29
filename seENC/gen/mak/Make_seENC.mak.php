
SEENC_OBJ +=		\
<?php
	$configs = $config->getList("/seENC","SUBMODULES");

	if (count($configs) != 1)
	{
		error("more than one SUBMODULE defined in the seENC configuration");
	}

/*	var_dump($config);

	$submods = $config->getList("/seENC/" . $config[0] ,"*");

	foreach ($submods as $submod)
	{
		print "$submod\n";
#		$val = $config->getValue("/seENC/" . $config[0], $submod);
	} */
?>
