#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool SAVE(LISTA *lista, FILA *fila)
{
    if (!lista || !fila) //lista ou fila vazia
    {
        return false; //salvamento mal sucedido
    }

    PACIENTE *paciente; //auxiliar

    //primeiro vamos salvar a lista
    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if(!fp_lista)
    {
        return false;
    }
    paciente = remover_paciente_inicio_lista(lista);
    //agora pegar os campos da struct paciente
    int id, tamanhoNome;
    char *nome;
    HISTORICO *historico;
    while (paciente != NULL)
    {
        //escreve o ID no arquivo
        tamanhoNome = get_tamanho_nome(paciente);
        fwrite(&tamanhoNome, sizeof(int), 1, fp_lista);
        nome = get_nome(paciente);
        fwrite(&nome, sizeof(char), strlen(nome), fp_lista);
        id = get_ID(paciente);
        fwrite(&id, sizeof(int), 1, fp_lista);
        historico = get_historico(paciente);
        /*
        FAZER OPERAÇÕES E SALVAR O HISTORICO
        */
        apagar_paciente(paciente); //agora que o paciente esta salvo, é apagado da memoria
        paciente = remover_paciente_inicio_lista; //paciente agora é o proximo
    }

    apagar_lista(&lista);
    fclose(fp_lista);
    fp_lista = NULL;

    //agora salvar a fila
    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if(!fp_fila)
    {
        return false;
    }
    /*
    FAZER AQUI O SAVE DA FILA
    */
    return true;
}

bool LOAD(LISTA **lista, FILA **fila)
{
    if(!*lista || !*fila)
    { 
        return false;
    }
}