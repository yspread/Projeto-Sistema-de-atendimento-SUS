all:
	gcc main.c triagem.o historico.o lista.o procedimento.o paciente.o IO.o -Wall -std=c99

clean:
	rm -f *.o *.zip main

run:
	./main

guarana:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

IO.o:
	gcc -c io.c

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