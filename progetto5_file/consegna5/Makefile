assembler: main.o table.o parser.o
	gcc -o assembler main.o table.o parser.o

main.o: main.c table.h parser.h
	gcc -c main.c

table.o: table.c table.h
	gcc -c table.c

parser.o: parser.c parser.h table.h
	gcc -c parser.c

clean:
	rm *.o assembler