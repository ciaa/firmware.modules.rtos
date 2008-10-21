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

#ifndef _LCD_H_
#define _LCD_H_
/** \brief LCD Header File
 **
 ** This file shall be included by all files using the LCD library
 **
 ** \file lcd.h
 **
 **/

/** \addtogroup Lcd LCD
 ** @{ */
/** \addtogroup Lcd_Global LCD Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081017 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 
#include "lcd_Cfg.h"		/* include lcd configuration */
#include "lcd_Arch.h"	/* include archtecture header file */

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Set Lcd cursor position
 **
 ** set the lcd to the indicated x y position.
 **
 ** \param[in]	posx LCD Position in the X axis
 ** \param[in] posy LCD position in the Y axis
 ** \return LCD_E_OK if no error
 ** 			LCD_E_ERROR if an error occurs
 **/
extern Lcd_ReturnType Lcd_SetPosition(Lcd_PosType posx, Lcd_PosType posy);

extern Lcd_ReturnType Lcd_Write(const Lcd_MsgRefType msg, Lcd_MsgLength length);

extern Lcd_ReturnType Lcd_GetPosition(Lcd_PosRefType posx, Lcd_PosRefType posy);

extern Lcd_ReturnType Lcd_Read(Lcd_MsgRefType msg, Lcd_MsgRefLength length, Lcd_MsgLength maxlength);

extern Lcd_ReturnType Lcd_Clear(void);

extern Lcd_ReturnType Lcd_Init(Lcd_ConfigType config);

extern Lcd_ReturnType Lcd_ShutDown(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _LCD_H_ */

