ENTRY (Reset_Handler)

MEMORY{
	FLASH(rx):ORIGIN =0x08000000, LENGTH =64K	
	SRAM(rwx):ORIGIN =0x20000000, LENGTH =20K
}

SECTIONS{
	.text :{	 		/*contains all the vectors, executable code and rodata*/
		*(.vectors)
		*(.text)
		*(.rodata)
		. = ALIGN(4);	/*aligning to neareast multiple of 4*/
		_etext = .;		/*_etext = location counter = FLASH ORIGIN + size of all the above sections merged*/
	}> FLASH			/*both lma and vma are FLASH*/
	
	_ld_data = LOADADDR(.data);
	.data :{	
		_sdata = .;		/*_sdata = vma i.e., SRAM*/
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;		/*_edata = _sdata + size of all the above sections merged*/
	}> SRAM AT> FLASH	/*vma is SRAM and lma is FLASH*/
	
	
	.bss :{	
		_sbss = .;		/*_sbss = vma i.e., SRAM*/
		*(.bss)
		*(.bss.*)
		*(.COMMON)		/* Uninitialized variables are placed in COMMON section for object files */
		. = ALIGN(4);
		_ebss = .;		
	}> SRAM	
}
