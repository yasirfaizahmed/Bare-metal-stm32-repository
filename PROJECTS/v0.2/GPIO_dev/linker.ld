ENTRY(Reset_Handler)

MEMORY{
    FLASH(rx): ORIGIN =0x08000000, LENGTH = 64K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH = 20K
}

SECTIONS{
    .text :{
        *(.vectors);
        *(.text);
        *(.rodata);
        . = ALIGN(4);
        _etext = .;
    }> FLASH
    
    _ld_data = LOADADDR(.data);
    .data :{
        _sdata = .;
        *(.data);
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT > FLASH
    
    .bss :{
        _sbss = .;
        *(.bss);
        . = ALIGN(4);
        _ebss = .;
    }> SRAM
}