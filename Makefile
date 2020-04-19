led.bin: blingbling.o 
	arm-linux-gnueabi-ld -Ttext 0x40000000 -o led.elf $^
	arm-linux-gnueabi-objcopy -O binary led.elf led.bin
	arm-linux-gnueabi-objdump -D led.elf > led.dis	
%.o : %.S
	arm-linux-gnueabi-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gnueabi-gcc -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis -f
