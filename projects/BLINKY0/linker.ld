ENTRY (Reset_Handler)	//runs when reset button is pressed

MEMORY{
	FLASH(rx) : ORIGIN=0x08000000, LENGTH=512K
	SRAM(rwx) : ORIGIN=0x20000000, LENGTH=96K
}

SECTION{
	.text :{	//.text in FLASH consists code memory in following order .vectors .text .rodata 
		*(.vectors)
		*(.text)
		*(.rodata)
		end_of_text = .;	//end_of_text = (FLASH ORIGIN) + (size of the above sections combined)	
	}> FLASH	//both vma and lma are FLAH
	
	
	.data :{	//.data section is to placed in both FLASH and alos in SRAM
		*(.data)
	}> SRAM AT>FLASH	//vma is SRAM, lma is FLASH
	
	
	.bss :{	//.bss only in SRAM
		*(.bss)
	}> SRAM	//both vma and lma are SRAM
}
