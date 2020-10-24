CC       = gcc
CASFLAGS = -Og -c -S
CFLAGS   = -Og -c

TARGET = src.c
ASRESULT = asm.s
RESULT = src
DISASFILE = disassemble.txt

.PHONY : all clean asm

all :
	$(CC) $(CFLAGS) $(TARGET) -o $(RESULT)
	objdump -S $(RESULT) > $(DISASFILE)
	vi $(DISASFILE)

asm :
	$(CC) $(CASFLAGS) $(TARGET) -o $(ASRESULT) 

clean :
	rm *.s
	rm $(RESULT)

