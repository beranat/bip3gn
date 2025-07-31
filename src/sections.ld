/* vim: tabstop=2 shiftwidth=2 noexpandtab colorcolumn=76:
****************************************************************************
* Beeper Engine (bip3gn) Copyright (C) 2025 madRat
****************************************************************************
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3 of the License.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/
****************************************************************************
* sections.ld - Link Sections Script
***************************************************************************/

_Min_Heap_Size = 0x0000;
_Min_Stack_Size = 0x0400;

_ram_start = ORIGIN(RAM);
_ram_end = ORIGIN(RAM) + LENGTH(RAM);

_rom_start = ORIGIN(FLASH);
_rom_end = ORIGIN(FLASH) + LENGTH(FLASH);

_estack = _ram_end;

ENTRY(Reset_Handler)

SECTIONS {
	.isr_vector : ALIGN(4) {
		__vectors_start = ABSOLUTE(.);
		__vectors_start__ = ABSOLUTE(.);
		KEEP(*(.isr_vector))
		*(.after_vectors .after_vectors*)
	} >FLASH

	.text : ALIGN(4) {
		*(.text .text*)
		KEEP(*(.eh_frame*))

		*(.glue_7)
		*(.glue_7t)

		KEEP(*(.init))
		KEEP(*(.fini))

		. = ALIGN(4);
		_etext = .;
	} >FLASH

	.rodata : ALIGN(4) {
		*(.rodata .rodata*)
		*(.constdata .constdata*)
	} >FLASH

  .preinit_array : ALIGN(4) {
    PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array_sysinit .preinit_array_sysinit*))
		KEEP(*(.preinit_array_platform .preinit_array_platform*))
		KEEP(*(.preinit_array .preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array : ALIGN(4) {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array : ALIGN(4) {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

	.ARM.extab : ALIGN(4) {
		*(.ARM.extab*)
		*(.gnu.linkonce.armextab.*)
	} >FLASH

	.ARM.exidx : ALIGN(4) {
		__exidx_start = .;
	   *(.ARM.exidx*)
	   *(.gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > FLASH

	/* Remove the debugging information from the standard libraries */
	/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

	.ARM.attributes 0 : { *(.ARM.attributes) }
	.stab		  0 : { *(.stab) }
	.stabstr	   0 : { *(.stabstr) }
	.stab.excl	 0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index	0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment	   0 : { *(.comment) }
	.debug		  0 : { *(.debug) }
	.line		   0 : { *(.line) }
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_info	 0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line	 0 : { *(.debug_line) }
	.debug_frame	0 : { *(.debug_frame) }
	.debug_str	  0 : { *(.debug_str) }
	.debug_loc	  0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }

	.data : ALIGN(4) {
		FILL(0xFF)
		_sidata = LOADADDR(.data);
		_sdata = . ;
		*(.data_begin .data_begin*)
		*(.data .data*)
		*(.data_end .data_end*)
		. = ALIGN(4);
		_edata = . ;
	} >RAM AT>FLASH

	.bss (NOLOAD) : ALIGN(4) {
		_sbss = .;
		*(.bss_begin .bss_begin*)
		*(.bss .bss*)
		*(.noinit .noinit*)
		*(COMMON)
		*(.bss_end .bss_end*)
		. = ALIGN(4);
		_ebss = . ;
	} >RAM

	._heap_stack (NOLOAD) : ALIGN(8) {
		PROVIDE(end = .);
		_stack_start = ABSOLUTE(_estack) - ABSOLUTE(end) - _Min_Stack_Size;
		. = . + _Min_Stack_Size;
	} >RAM
}
