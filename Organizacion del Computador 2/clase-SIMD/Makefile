all:
	nasm -f elf64 -g -F dwarf -o simdEj.o simdEj.asm
	gcc -std=c99 -o simdEj -m64 -ggdb main.c  simdEj.o


clean:
	rm -f *~ simdEj *.o