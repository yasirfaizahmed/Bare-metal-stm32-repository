# Bare-metal-stm32-repository
This repo is collection of all Bear-metal developed code and some references to utilize tools like GNU toolchain for ARM uP, Make, ST-link utility application(for debugging), GDB, Linker concepts etc.

## Contents
1. LIBRARIES         --> This directory contains the latest peripheral Drivers.
2. PROJECTS          --> This directory contains some sample sketches to test the peripheral Drivers present in /LIBRARIES
3. bare metal guide  --> some .txt and .png files for README.md 

## Requirements to get started
1. [GNU Arm embedded toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. [Make](http://gnuwin32.sourceforge.net/packages/make.htm) to compile and build files easily.
3. [Bash Environment, in my case Cygwin](https://cygwin.com/install.html) if you have git installed already in you machine you can launch git bash at your working directory as well.
4. ST-link v2 programmer, and ofcourse our Bluepill stm32f103C8
5. [stm32 stlink utility](https://www.st.com/en/development-tools/stsw-link004.html)


## Run the commands below at the working directory

Go to the sample sketch directory, for e.g. PRIJECTS/BLINKY0/ 

open up bash/cmd 

To build all the source files, startup files and to get their respective .o files.

      make all 

To make only the main, startup file respectively

      make main.o 
      make startup.o
 
To link all the object files and to create final .elf file

      make link
      
To get the .bin file from .elf file 

      make bin

      
To get the .map file of .elf file (just for references)

      make map
      
Once the .bin file is ready, just open the [stm32 stlink utility](https://www.st.com/en/development-tools/stsw-link004.html), go to Target>Program> select your .bin file and click start, that should download the .bin file to flash.
      
  
## Some stuff need to know before getting started

1. The memory map
2. Boot sequence
3. Vector table
4. Organisation of memory
5. Memory alignment
6. Building the program

### Memory map

since stm32f103 is 32bit uC it can access memory space of 4GB, but the uC itself has some internal mmemory to store program code, config registers, variables etc.
mainly the uC memory is divided into two ROM and RAM.

ROM - is of 512KB in general and consists of Alised memory, Flash memory, system memory

ROM is where the executable code gets stored alog with the already declared constants in the program since they will not change while the program is running its good to have them in ROM instead of RAM memory.

![Memory map](https://github.com/yasirfaizahmed/Bare-metal-stm32-repository/blob/master/Bear-metal%20guide/MemoryMap.png)



Aliased memory- This block of memory is mapped with Flash, wirting contents in Aliased memory will reflect the same in Flash memory, we cant write directly into flash but writing into the Aliased memory will give us the same result. both Aliased memory is of 128KB.

Flash memoery- this is where the code gets stored along with declared constants.Its divided into sections which are vector table section, .text section, .rodata section, .data section.

vector table section starts at 0x08000000 and it contains the address of the top of the stack, and from address 0x080000004 the vector table starts till the last Interupt handler address.

.text section holds the code memory and appears right after the vector table section is over

.rodata sections holds the declared constants.

.data section holds the declared variables and this section needs to be copied to SRAM which we will discuss later.

.bss section holds the uninitialized variable, even this needs to be copied to SRAM but needs to be initialized as 0.

SRAM - This is of 96KB and holds the variables which are needed for the program to run and since for fast computations we need very less access time and writing time these variables needs to stored in SRAM and not in ROM. there fore we have to copy the .data and .bss sections from FLASH to SRAM.

System memory- This is where the bootloader is written and its factory programmed and we do not have write access into it. and its of around 2KB.

### Boot sequence 

When power is applied to the MCU the Program Counter (PC) value will be 0 and will therefore start at address 0x0. Remember that the Program Counter holds the address of the next instruction to be performed. The value it expects at this address (0x0) would be the address that marks the top of the Stack memory (which is part of the SRAM). This address is then copied to the Stack Pointer (SP) register for later use. The Program Counter then steps to the next address which is 0x0000 0004 and expects the address of the reset handler at this location. This is typically the start address of where our program is stored. The MCU will then update the Program Counter with this address which means that the next instruction to be executed will be the first instruction in our program.

In our discussion on the memory we said that our program normally lives in the Flash memory which starts at 0x0800 0000 and we also said that we can’t write to the Aliased memory (which starts at 0x0). So how do we set the values of address 0x0000 0004 (which is in Aliased memory space) to point to the start of our program? Well, this is why the Aliased memory can be mapped, by selecting (with BOOT0 and BOOT1 pins) to boot from the Flash memory the Flash memory is actually mapped to the Aliased memory. This means that when the Program Counter looks at address 0x0 it’s actually looking at address 0x0800 0000. So since we can write to the Flash memory section we can provide the starting address of our program at address 0x0800 0004 which would be the same as 0x0000 0004. Typically the part of our program located at this address is called the startup code and will perform some initialization steps and then call the main() function in our C/C++ code.

### Vector table 

The vector table is a section of our flash memory that mostly holds the addresses of various handlers. In the boot sequence we said that the reset handler is located at address 0x0000 0004 and holds the address of our startup code. Well this is part of the vector table and for the STM32F103 it starts at address 0x0 and extends up to address 0x0000 014C. As a reminder, this is aliased memory, so if we are booting from Flash memory it would actually mean that the vector table extends from 0x0800 0000 to 0x0800 014C. If you have used interrupts before then this is also where the handlers (address to the code that will be run) is set.

### Organising the Memory

![mem sections](https://github.com/yasirfaizahmed/Bare-metal-stm32-repository/blob/master/Bear-metal%20guide/MemorySections.png)

Earlier we talked about how the memory in the MCU is mapped out to the different regions of the FLASH and SRAM memory. When our program is compiled the compiler also organises the program into different sections which we would need to fit to these regions. The most popular of these sections are the TEXT, DATA and BSS sections. This is done to separate for example, things like the instructions which is typically in read only memory from variables which should be in read/write memory. The read only memory is typically FLASH memory but does not have to be, it’s also possible to load instructions to the SRAM and execute them from there, but in this post we will use the FLASH memory as our read only memory.

The region that holds the instructions of our program goes into the TEXT section. The TEXT section is located in the FLASH memory and is typically only written to when we upload our program to the MCU. If our program contains constants the compiler knows that these values will always stay the same and there is no need for them to be in RAM. Therefore they can also be placed in FLASH memory and forms part of the RODATA (Read Only Data) section.
If our program had global or static variables (which lives for the whole lifetime of our program) then the compiler can already assign space (addresses) in RAM for it. The addresses it assigns to these variables will be in the BSS section which is in RAM memory.
Should we have global or static variables which have also been initialized (given a value) in our program then the compiler will assign the address in the DATA section and the value itself in the LMA (Load Memory Address) DATA section. When the MCU boots-up these values should then be copied from the LMA DATA to VMA (Virtual Memory Address) DATA section.

## Memory alignment

For the processor to efficiently fetch data the address from where it fetches data should be a multiple of the data type size. For example, if we retrieve a 32bit (word) value then the address must be a multiple of 4. So valid addresses would be 0x0800 0000, 0x0800 0004, etc. When using a 16 bit (half word) value the address must be a multiple of 2 and for 8bit addresses any address can be used. This is known as aligned memory access.

![mem align](https://github.com/yasirfaizahmed/Bare-metal-stm32-repository/blob/master/Bear-metal%20guide/MemAlign1.png)

Looking at the image above, imagine each block represents one byte of memory and the address of the byte is to the left of it. Green arrows would indicate valid addresses for word (32 bit) values. Yellow arrows would be valid for half word (16 bit) values and blue arrows for byte values.

If we try to read data from unaligned memory the processor would need to fetch the data twice and we would get a performance penalty. One solution to this problem is to use alignment instructions when data is assigned an address. Such an instruction would typically round the address up to the closest multiple of the data size. This works but at the cost of creating unused memory locations. In the image below we can see the effect of memory alignment.

![mem align](https://github.com/yasirfaizahmed/Bare-metal-stm32-repository/blob/master/Bear-metal%20guide/MemAlign2.png)

Take as example address 0x0000 0008 which holds a 2 byte value, the next value to be stored is a 4 byte value. But since we need to align the memory we can’t store it at address 0x0000 000A, the first available address would be 0x0000 000C which creates 2 bytes of unused space.

Normally the alignment is handled by the compiler but knowing about it helps to understand some other concepts. We can also use this to improve the memory use of our programs by packing our data in such a way that we don’t fragment the memory too much.








