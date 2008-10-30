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

#ifndef _FILE_H_
#define _FILE_H_
/** \brief OpenFILE Header File
 **
 ** This file shall be included by all files using any OpenFILE API.
 **
 ** \file file.h
 **
 **/

/** \addtogroup OpenFILE OpenFILE
 ** @{ */
/** \addtogroup OpenFILE_Global OpenFILE Global
 ** \ingroup OpenFILE
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081028 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "File_Cfg.h"
#include "File_Arch.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef unsigned int File_FileType;

typedef File_FileType FILE;

typedef char

typedef File_FileNameType* File_FileNameRefType; 

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Schedule this Task if higher priority Task are Active
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used from non preemtive tasks.
 **
 ** \return E_OK if no error
 ** \return E_OS_CALLEVEL if call at interrupt level
 ** \return E_OS_RESOURCE if the calling task occupies resources
 **/
extern File_ReturnType File_Open(File_FileNameRefType FileName, File_FileAccessType AccessType, File_FileRefType File);
extern File_ReturnType File_Close();
extern File_ReturnType File_Seek();
extern File_ReturnType File_Write();
extern File_ReturnType File_Read();


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_H_ */

