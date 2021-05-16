# Bare-metal-stm32-repository
This repo is collection of all Bear-metal developed code and some references to utilize tools like GCC, Make, OpenOCD, GDB, Linkers etc.

## Requirements to get started
1. [GNU Arm embedded toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. [Make](http://gnuwin32.sourceforge.net/packages/make.htm) to compile and build files easily.
3. [Bash Environment, in my case Cygwin](https://cygwin.com/install.html) if you have git installed already in you machine you can launch git bash at your working directory as well.
4. ST-link v2 programmer, and ofcourse our Bluepill stm32f103C8



## Run the commands below at the working directory

To build all the source files, startup files and to get their respective .o files.

      make all 

To make only the main, startup file respectively

      make main.o 
      make startup.o
 
To link all the object files and to create final .elf file

      make link
      
To get the .map file of .elf file

      make map
      
  
## Some stuff need to know before getting started

1. The memory map
2. Boot sequence
3. Vector table
4. Organisation of memory
5. Memory alignment
6. Instruction set
7. Building the program

### Memory map

since stm32f103 is 32bit uC it can access memory space of 4GB, but the uC itself has some internal mmemory to store program code, config registers, variables etc.
mainly the uC memory is divided into two ROM and RAM.

ROM - is of 512KB in general and consists of Alised memory, Flash memory, system memory
ROM is where the executable code gets stored alog with the already declared constants in the program since they will not change while the program is running its good to have them in ROM instead of RAM memory.
![Memory map](https://github.com/yasirfaizahmed/Bare-metal-stm32-repository/blob/master/BARE_METAL_GUID/MemoryMap.png)
Aliased, Flash, System memory is all of 128KB each 
Aliased - This block of memory is mapped with Flash, wirting contents in Aliased memory will reflect the same in Flash memory, we cant write directly into flash but writing into the Aliased memory will give us the same result.
Flash - this is where the code gets stored along with declared constants.



