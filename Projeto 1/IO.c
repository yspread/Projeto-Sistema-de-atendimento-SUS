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
    
    PACIENTE *paciente; // Variável auxiliar 

    // Salvando os itens da lista

    FILE *fp_lista = fopen("lista.bin", "wb");
    if(!fp_lista)
        return false;

    paciente = apagar_paciente_lista(lista);
    int chave;
    while(paciente != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = get_ID(paciente);
        fwrite(&chave, sizeof(int), 1, fp_lista);
        // Apaga o item removido
        apagar_paciente(&paciente);
        // Atualiza a variável auxiliar
        paciente = apagar_paciente_lista(lista, chave);
    }
    // Libera memória
    apagar_lista(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila.bin", "wb");
    if(!fp_fila)
        return false;

    paciente = chamar_para_atendimento(fila);
    while(paciente != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = get_ID(paciente);
        fwrite(&chave, sizeof(int), 1, fp_fila);
        // Apaga o item removido
        apagar_paciente(&paciente);
        // Atualiza a variável auxiliar
        paciente = chamar_para_atendimento(fila);
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

    FILE *fp_lista = fopen("lista.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        PACIENTE *paciente = criar_paciente(chave);
        LISTA_inserir(*lista, chave);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        PACIENTE *paciente = criar_paciente(chave);
        inserir_paciente_triagem(*fila, paciente);
    }
    fclose(fp_fila); // Libera memória

    return true;
}