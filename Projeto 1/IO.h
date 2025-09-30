#ifndef IO_H
    #define IO_H
    #include <stdbool.h>
    #include "lista.h"
    #include "triagem.h"

    bool save(LISTA *lista, FILA *fila); // Salva os itens da lista e da fila em arquivos
    bool load(LISTA **lista, FILA **fila); // Carrega os itens dos arquivos na lista e na fila
	  
#endif
