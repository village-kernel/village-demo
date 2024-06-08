OUTPUT_FORMAT("elf32-i386", "elf32-i386","elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
	. = 0;
	ImageBase = .;
	
	/* .hash and/or .gnu.hash MUST come first! */
	.hash : { *(.hash) }
	.gnu.hash : { *(.gnu.hash) }
	.eh_frame : { *(.eh_frame) }
	.gcc_except_table : { *(.gcc_except_table*) }

	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		 _etext = .; 
	}

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	}

	.x86.extab : { *(.gcc_except_table.*  .got.plt ) }
	.x86 : {
		__exidx_start = .;
		*(.x86.extab*)
		__exidx_end = .;
	}

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(SORT(.preinit_array.*)))
		KEEP (*(SORT(.preinit_array*)))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	}

	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(SORT(.init_array*)))
		KEEP (*(SORT(.ctors*)))
		PROVIDE_HIDDEN (__init_array_end = .);
	}

	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(SORT(.fini_array*)))
		KEEP (*(SORT(.dtors*)))
		PROVIDE_HIDDEN (__fini_array_end = .);
	}

	_sidata = LOADADDR(.data);

	.data :
	{
		. = ALIGN(4);
		_sdata = .;  
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .; 
	}

	.bss :
	{
		. = ALIGN(4);
		_sbss = .; 
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss*)
		*(COMMON)

		. = ALIGN(4);
		_ebss = .; 
		__bss_end__ = _ebss;
	}

	._user_heap_stack :
	{
		. = ALIGN(4);
		PROVIDE ( end = . );
		PROVIDE ( _end = . );
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(4);
	}

	/*/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}*/
}
