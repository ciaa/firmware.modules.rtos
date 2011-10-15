/** \brief Linker script for Atmel AT91SAM7X512
 **
 ** Based on lpc_e2468.cmd.
 ** The application will be running from internal flash.
 **
 ** \file arm7/at91sam7x/at91sam7x512.lds
 ** \arch arm7/at91sam7x
 **/

/*
 * Initials     Name
 * ---------------------------
 * KT           Tamas Kenderes
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20111015 v0.1.0 KT	initial version
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)

MEMORY
{
    ram (W!RX) : ORIGIN = 0x200000, LENGTH = 0x20000
    flash (RX) : ORIGIN = 0x100000, LENGTH = 0x80000
}

_stack_end = 0x220000;

SECTIONS 
{
	. = 0;
	startup : { out/lib/Drv_StartUp.a(.text) } > flash

	.text :
	{
		. = ALIGN(4);
		_text = .;
		*(.text)
		*(SEC_CODE)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		. = ALIGN(4);
		_etext = .;
	} >flash

	.data :
	{
		. = ALIGN(4);
		_data = .;
		*(.data)
		*(SEC_DATA)
		. = ALIGN(4);
		_edata = .;
	} >ram AT >flash

	.bss :
	{
		. = ALIGN(4);
		_bss_start = .;
		*(.bss)
	} >ram

	. = ALIGN(4);
	_bss_end = . ;
}
	_end = .;
