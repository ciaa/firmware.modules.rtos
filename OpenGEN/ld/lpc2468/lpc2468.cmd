
ENTRY(_startup)


MEMORY 
{
	flash : ORIGIN = 0x00000000, LENGTH = 512K
	ram	: ORIGIN = 0x40000200, LENGTH = 64K
}

SEC_STACK_END = 0x4000FEDC;

SECTIONS 
{
	. = 0;
	
	_startup = .;
/* : { StartUp_Asm.s(*) } > flash */

	SEC_CODE :
	{
		*(.text)
		*(.rodata)
		*(.glue_7)
		*(.glue_7t)
		SEC_END_CODE = .;
	} > flash

	SEC_DATA_INIT :
	{
		SEC_START_DATA_INIT = .;
		*(.data)
		SEC_END_DATA_INIT = .;
	} > ram AT > flash

	. = ALIGN(4);

	/* SEC_DATA : */
	.bss :
	{
		SEC_START_DATA = .;
		*(.bss)
	} > ram
	. = ALIGN(4);
	SEC_END_DATA = . ;

	SEC_DATA_NOINIT :
	{
		SEC_START_DATA_NOINIT = .;
		
	} > ram
	. = ALIGN(4);
	SEC_END_DATA_NOINIT = . ;


}
	END = .;
