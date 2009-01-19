/****************************************************************************
 *  
 * Project: LPC-E2468 blinking led demo
 *
 * Copyright: Ivan Vasilev, Olimex Ltd. All rights reserved.
 * 
 * File: $File lpc_e2468.cmd $
 * Description: Board-specific USB initialization
 * Developer: Ivan Vasilev, <ivan at l123.org>
 *
 * Last change: $Date: 2008-04-08 09:23:26 +0300 (вторник, 08 Април 2008) $
 * Revision: $Revision: 4 $
 * Id: $Id: lcp_e2468.cmd 4 2008-04-08 06:23:26Z Ivan $
 * Author: $Author: Ivan $
 *
 *  This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 ****************************************************************************/
 
ENTRY(_startup)

/* LPC-2468 memory map */
MEMORY 
{
	flash     		: ORIGIN = 0,          LENGTH = 512K
	ram   			: ORIGIN = 0x40000200, LENGTH = 64K
}

/* we may get averwritten by the ISP/IAP */
_stack_end = 0x4000FEDC;

SECTIONS 
{
	. = 0;
	
	startup : { out/obj/StartUp.o(.text) } >flash

	.text :
	{
		*(.text)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		_etext = .;
	} >flash

	.data :
	{
		_data = .;
		*(.data)
		_edata = .;
	} >ram AT >flash

	.bss :
	{
		_bss_start = .;
		*(.bss)
	} >ram

	. = ALIGN(4);
	_bss_end = . ;
}
	_end = .;
