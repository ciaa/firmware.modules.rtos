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

/** \brief OpenSEK Generator Read Configuration Class
 **
 ** This file implements the Configuration Class of the Generator
 **
 ** \file config.php
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
 * 20080713 v0.1.0 MaCe       - initial version
 */

/*==================[inclusions]=============================================*/
require_once("oilParser.php");

/*==================[class definition]=======================================*/
/** \brief configClass Configuration Class
 **
 ** This class implements the generation configuration class of OpenSEK
 **
 **/
class configClass {
	protected $config = array();

	function configClass()
	{		  
	}

	function parseOilFile($file)
	{
		$parser = new oilParserClass($file);

		$tmp = $parser->getOil();

		foreach ($tmp as $element)
		{
			$this->config[] = $element;
		}

	}

	function parseAutosarFile()
	{
	}

	function getValue($root, $type)
	{
		$ret = false;
		foreach ($this->config as $element)
		{
			if ( ($element["root"] == $root) &&
				  ($element["type"] == $type) )
			{
				return $element["value"];
			}
		}

		return $ret;
	}

	function getBase($db, $root)
	{
		$ret = array();

		foreach($db as $el)
		{
			if ( $el["root"] == $root )
			{
				$ret[] = $el;
			}
		}

		return $ret;
	}
		

	function getCount($root, $type)
	{
		$ret = 0;
		
		foreach ($this->config as $element)
		{
			if ( ( ($element["root"] == $root) && ($element["type"] == $type) ) ||
				  ( ($element["root"] == $root) && ($type == "*") ) )
			{
				$ret++;
			}
		}

		return $ret;
	}

	function getList($root, $type)
	{
		$ret = array();

		foreach ($this->config as $element)
      {
         if ( ( ($element["root"] == $root) && ($element["type"] == $type) ) ||
				  ( ($element["root"] == $root) && ($type == "*") ) )
         {
            $ret[] = $element["value"];
         }
      }

		return $ret;
	}

	function listAll()
	{
		$ret = array();

		$ret = $this->listar($this->config);

		return $ret;
	}

	function foo() {}

	private function listar($dbase)
	{
		static $ret = array();
		static $inst = -1;

		$inst++;	

		if ($inst == 0)
		{
			$dbase = $this->config;
		}

		var_dump($dbase);

		foreach ($dbase as $db)
		{
			$ret[] = $db["root"];
			if ( $db["cont"]!=NULL)
			{
				$this->listar($db);
			}
		}

		$inst--;
		
		return $ret;
	}

	private function getListIn($root, $dbase, $level)
	{
		$ret = array();

		foreach ($dbase as $db)
		{
			$ret[] = getListIn($root,$db, $level + 1);
		}

		return $ret;
		
	}

	function exist($root, $attr)
	{
		$attributes = $this->getAttributes($root);

		foreach ($attributes as $attribute)
		{
			if ($attribute == $attr)
			{
				return true;
			}
		}

		return false;
		
	}

	function getAttributes($root)
	{
		$ret = array();

      foreach ($this->config as $element)
      {
         if ( $element["root"] == $root )
         {
            $ret[] = $element["type"];
         }
      }

      return $ret;

	}
	
	function dump()
	{
		var_dump($this->config);
	}

}

$config = new configClass();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
?>
