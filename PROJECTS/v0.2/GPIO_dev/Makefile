CC = arm-none-eabi-gcc
FLAGS = -mcpu=cortex-m3 -mthumb -Wall


all : main.o startup.o stm32f103xx_GPIO_driver.o

main.o : main.c 
	$(CC) main.c  $(FLAGS) -c -o obj/main.o
    
startup.o : startup/startup.c	
	$(CC) startup/startup.c $(FLAGS) -c -o obj/startup.o
    
stm32f103xx_GPIO_driver.o : driver/src/stm32f103xx_GPIO_driver.c
	$(CC) driver/src/stm32f103xx_GPIO_driver.c  $(FLAGS) -c -o obj/stm32f103xx_GPIO_driver.o

link : linker.ld obj/main.o obj/startup.o 
	$(CC) obj/main.o obj/startup.o obj/stm32f103xx_GPIO_driver.o $(FLAGS) -nostdlib -T linker.ld -o obj/final.elf
	
bin : obj/final.elf 
	arm-none-eabi-objcopy obj/final.elf obj/final.bin -O binary


map : linker.ld main.o startup.o
	$(CC) main.o startup.o $(FLAGS) -Wl,-Map=obj/final.map -nostdlib -T linker.ld -o final.elf


clean : 
	rm -rf obj/*.o obj/*.elf obj/*.map obj/*.bin
	
	
