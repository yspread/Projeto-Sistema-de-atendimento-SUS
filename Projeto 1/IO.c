#include "IO.h"
#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if(!lista || !fila) 
        return false;
    
    PACIENTE *it; // Variável auxiliar 

    // Salvando os itens da lista

    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if(!fp_lista)
        return false;

    it = apagar_paciente_lista(lista);
    int chave;
    while(it != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = get_ID(it);
        fwrite(&chave, sizeof(int), 1, fp_lista);
        // Apaga o item removido
        apagar_paciente(&it);
        // Atualiza a variável auxiliar
        it = apagar_paciente_lista(lista);
    }
    // Libera memória
    apagar_lista(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if(!fp_fila)
        return false;

    it = chamar_para_atendimento(fila);
    while(it != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = get_ID(it);
        fwrite(&chave, sizeof(int), 1, fp_fila);
        // Apaga o item removido
        apagar_paciente(&it);
        // Atualiza a variável auxiliar
        it = chamar_para_atendimento(fila);
    }
    // Libera memória
    apagar_fila(&fila);
    fclose(fp_fila); fp_fila = NULL;

    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if(!*lista || !*fila) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        PACIENTE *it = criar_paciente(chave);
        LISTA_inserir(*lista, it);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        PACIENTE *it = criar_paciente(chave);
        inserir_paciente_triagem(*fila, it);
    }
    fclose(fp_fila); // Libera memória

    return true;
}