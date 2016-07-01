<?php
/* Copyright 2015, Pablo Ridolfi
 * Copyright 2016 Carlos Pantelides
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Generator multicore functions
 **
 ** This file implements auxiliary functions for multicore generation
 **
 ** \file Multicore.php
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup Generator
 ** @{ */

/*==================[inclusions]=============================================*/
require_once('Helper.php');
/*=================[user functions]==========================================*/

class Multicore extends Helper
{

   public function __construct($config, $definitions, $log)
   {
      parent::__construct($config, $definitions, $log);
   }

   /**   \brief Get array of elements defined for the local core
   *    \param root Root element to search into
   *    \param type Type to filter inside Root
   *    \return array of local elements
   */
   function getLocalList($root, $type)
   {

      $list = $this->config->getList($root,$type);
      $ret = array();

      if (isset($this->definitions["MCORE"]))
      {
         $core = $this->definitions["MCORE"];
         for ($i=0; $i < count($list); $i++)
         {
            $current_core = $this->config->getValue("/OSEK/$list[$i]","CORE");
            if ($current_core == $core)
            {
               array_push($ret,$list[$i]);
            }
         }
      }
      else
      {
         $ret = $list;
      }
      return $ret;
   }

   /**   \brief Get array of elements defined for the remote core
   *    \param root Root element to search into
   *    \param type Type to filter inside Root
   *    \return array of remote elements
   */
   function getRemoteList($root, $type)
   {
      $ret = array();
      if (isset($this->definitions["MCORE"]))
      {
         $list = $this->config->getList($root,$type);
         $core = $this->definitions["MCORE"];
         for ($i=0; $i < count($list); $i++)
         {
            $current_core = $this->config->getValue("/OSEK/$list[$i]","CORE");
            if ($current_core != $core)
            {
               array_push($ret,$list[$i]);
            }
         }
      }
      return $ret;
   }
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
?>
