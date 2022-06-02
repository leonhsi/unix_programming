WRITE1 = test_write1
ALARM1 = test_alarm1
ALARM2 = test_alarm2
ALARM3 = test_alarm3
JMP1 = test_jmp1

all: start libmini.h libmini.c libmini64.asm
	yasm -f elf64 -DYASM -D__x86_64__ -DPIC libmini64.asm -o libmini64.o
	gcc -c -g -Wall -fno-stack-protector -fPIC -nostdlib libmini.c
	gcc -shared -fno-stack-protector -fPIC -nostdlib -o libmini.so libmini64.o libmini.o 

start:
	yasm -f elf64 -DYASM -D__x86_64__ -DPIC start.asm -I. -o start.o 

write1: start
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI $(WRITE1)/write1.c -o $(WRITE1)/write1.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $(WRITE1)/write1 $(WRITE1)/write1.o start.o -L. -L.. -lmini
	rm $(WRITE1)/write1.o

alarm1: start
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI $(ALARM1)/alarm1.c -o $(ALARM1)/alarm1.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $(ALARM1)/alarm1 $(ALARM1)/alarm1.o start.o -L. -L.. -lmini
	rm $(ALARM1)/alarm1.o

alarm2: start
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI $(ALARM2)/alarm2.c -o $(ALARM2)/alarm2.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $(ALARM2)/alarm2 $(ALARM2)/alarm2.o start.o -L. -L.. -lmini
	rm $(ALARM2)/alarm2.o

alarm3: start
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI $(ALARM3)/alarm3.c -o $(ALARM3)/alarm3.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $(ALARM3)/alarm3 $(ALARM3)/alarm3.o start.o -L. -L.. -lmini
	rm $(ALARM3)/alarm3.o

jmp1: start
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI $(JMP1)/jmp1.c -o $(JMP1)/jmp1.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $(JMP1)/jmp1 $(JMP1)/jmp1.o start.o -L. -L.. -lmini
	rm $(JMP1)/jmp1.o

clean:
	rm *.o libmini.so 
	rm $(WRITE1)/write1 $(ALARM1)/alarm1 $(ALARM2)/alarm2 $(ALARM3)/alarm3.o $(JMP1)/jmp1.o
