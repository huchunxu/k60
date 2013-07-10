/*
 *
 *
 */
MEMORY
{
    flash  : ORIGIN = 0x00000000, LENGTH = 512k
    sram   : ORIGIN = 0x1FFF0000, LENGTH = 128k
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm") 
OUTPUT_ARCH(arm)

SEARCH_DIR(.)
GROUP(-lgcc -lc -lm -lcs3 -lcs3unhosted)

ENTRY(system_start)


/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__cs3_start_c main __cs3_stack __cs3_heap_end)
/* force exit to be picked up in a hosted or os environment */
/* EXTERN(exit atexit) */


PROVIDE(__cs3_heap_start = _end);
PROVIDE(__cs3_heap_end = __cs3_region_start_ram + __cs3_region_size_ram);
PROVIDE(__cs3_region_num = (__cs3_regions_end - __cs3_regions) / 20);
/*__libc_fini = _fini;*/
PROVIDE(__cs3_stack = __cs3_region_start_ram + __cs3_region_size_ram);

SECTIONS
{
	
	. = ALIGN(4);
	/* .text */	
	.text :     
    {	
        __text = . ; 
        KEEP(*(.vector))
        *(.text*)
        *(.glue_7t)
        *(.glue_7)
    } > sram

	.eh_frame_hdr : ALIGN (4)
  	{
    	KEEP (*(.eh_frame_hdr))
  	} > sram

 	.eh_frame : ALIGN (4)
  	{
    	KEEP (*(.eh_frame))
  	} > sram

	/* .ARM.exidx is sorted, so has to go in its own output section.  */
  	__exidx_start = .;
  	.ARM.exidx :
  	{
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
  	} > sram
  	__exidx_end = .;

   	.rodata : ALIGN(4)
	{ 
		*(.rodata .rodata.* .gnu.linkonce.r.*)

    	. = ALIGN(4);
    	__cs3_regions = .;
    	LONG (0)
    	LONG (__cs3_region_init_ram)
    	LONG (__cs3_region_start_ram)
    	LONG (__cs3_region_init_size_ram)
    	LONG (__cs3_region_zero_size_ram)
    	__cs3_regions_end = .;

    	. = ALIGN (8);
    	_etext = .;
	} > sram 
	
	. = ALIGN(4);
    __idata_start = . ;
    .data   :  ALIGN(8) 
    {
		__cs3_region_start_ram = .;
        __data_start = . ;
        *(vtable)
        *(.data*)
    	_edata = .;
    } > sram
     __idata_end = __idata_start + SIZEOF(.data);
    _edata  =  . ;
    PROVIDE (edata = .);

    .bss       :
    {
        __bss_start = .	;
    	*(.shbss)
    	*(.bss .bss.* .gnu.linkonce.b.*)
    	*(COMMON)
    	. = ALIGN (8);
    	*(.sram.b .bss.sram)
    } > sram
     _end = .		;
    __bss_end = .;
    PROVIDE (end = .)	;

	/* __cs3_region_end_ram is deprecated */
  __onchip_ram_end = 0x1FFF0000 + LENGTH(sram);
  __cs3_region_end_ram = 0x1FFF0000 + LENGTH(sram);
  __cs3_region_size_ram = __cs3_region_end_ram - __cs3_region_start_ram;
  __cs3_region_init_ram = LOADADDR (.data);
  __cs3_region_init_size_ram = _edata - ADDR (.data);
  __cs3_region_zero_size_ram = _end - _edata;
	
  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
 
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to 
     the beginning of the section so we begin them at 0.  */

  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }

  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }

  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }

  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }

  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) }
}