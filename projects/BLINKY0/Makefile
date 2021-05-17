CC = arm-none-eabi-gcc
FLAGS = -mcpu=cortex-m3 -mthumb


all : main.o startup.o 

main.o : main.c 
	$(CC) main.c $(FLAGS) -c -o main.o
startup.o : startupfile.c	
	$(CC) startupfile.c $(FLAGS) -c -o startup.o
	

link : linker.ld main.o startup.o 
	$(CC) main.o startup.o $(FLAGS) -nostdlib -T linker.ld -o final.elf
	
bin : final.elf 
	arm-none-eabi-objcopy final.elf final.bin -O binary


map : linker.ld main.o startup.o
	$(CC) main.o startup.o $(FLAGS) -Wl,-Map=final.map -nostdlib -T linker.ld -o final.elf


clean : 
	rm -rf *.o *.elf *.map
	
	
