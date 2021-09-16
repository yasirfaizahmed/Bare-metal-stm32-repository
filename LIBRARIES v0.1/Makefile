CC = arm-none-eabi-gcc
FLAGS = -mcpu=cortex-m3 -mthumb


all : main.o startup.o CLOCK_DRIVER0.o GPIO_DRIVER2.o UART_DRIVER1.o

main.o : main.c 
	$(CC) main.c -I inc $(FLAGS) -c -o obj/main.o
startup.o : src/startupfile.c	
	$(CC) src/startupfile.c $(FLAGS) -c -o obj/startup.o
CLOCK_DRIVER0.o : src/CLOCK_DRIVER0.c
	$(CC) src/CLOCK_DRIVER0.c -I inc $(FLAGS) -c -o obj/CLOCK_DRIVER0.o
GPIO_DRIVER2.o : src/GPIO_DRIVER2.c
	$(CC) src/GPIO_DRIVER2.c -I inc $(FLAGS) -c -o obj/GPIO_DRIVER2.o
UART_DRIVER1.o : src/UART_DRIVER0.c
	$(CC) src/UART_DRIVER1.c -I inc $(FLAGS) -c -o obj/UART_DRIVER1.o

link : linker.ld obj/main.o obj/startup.o 
	$(CC) obj/main.o obj/startup.o obj/CLOCK_DRIVER0.o obj/GPIO_DRIVER2.o obj/UART_DRIVER1.o $(FLAGS) -nostdlib -T linker.ld -o obj/final.elf
	
bin : obj/final.elf 
	arm-none-eabi-objcopy obj/final.elf obj/final.bin -O binary


map : linker.ld main.o startup.o
	$(CC) obj/main.o obj/startup.o obj/CLOCK_DRIVER0.o obj/GPIO_DRIVER2.o obj/UART_DRIVER1.o $(FLAGS) -Wl,-Map=obj/final.map -nostdlib -T linker.ld -o final.elf


clean : 
	rm -rf obj/*.o obj/*.elf obj/*.map obj/*.bin
	
update_library :
	cp ./inc/. -r ../../LIBRARIES/Headers
	cp ./src/. -r ../../LIBRARIES/Sources
	cp linker.ld ../../LIBRARIES
	cp Makefile ../../LIBRARIES
	

include_files : 
	mkdir inc
	cp ../../LIBRARIES/Headers/* -r ./inc/
	mkdir src
	cp ../../LIBRARIES/Sources/* -r ./src/
	cp ../../LIBRARIES/linker.ld .


	
	
	
