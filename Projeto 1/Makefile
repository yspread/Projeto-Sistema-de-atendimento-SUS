all:triagem.o historico.o lista.o procedimento.o paciente.o IO.o
	gcc main.c triagem.o historico.o lista.o procedimento.o paciente.o IO.o -o main -Wall -std=c99 -pedantic-errors 

clean:
	rm -f *.o *.zip *.bin main

run:
	./main

guarana:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

IO.o:
	gcc -c IO.c

historico.o:
	gcc -c historico.c

lista.o:
	gcc -c lista.c

paciente.o:
	gcc -c paciente.c

procedimento.o:
	gcc -c procedimento.c

triagem.o:
	gcc -c triagem.c