#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct procedimento_
{
    char* nome;
    int size;
};

PROCEDIMENTO* criar_procedimento(char* str)
{
    PROCEDIMENTO* aux;

    aux = malloc(sizeof(PROCEDIMENTO));

    aux->nome = malloc(sizeof(str)); //alocando espaço para copiar o nome do procedimento
    strcpy(aux->nome, str); //copiando o nome fornecido para o nome do procedimento

    aux->size = strlen(str); //definindo a quantidade de caracteres em cada procedimento

    return aux;
}

void apagar_procedimento(PROCEDIMENTO** p)
{
    free((*p)->nome);
    (*p)->nome = NULL;

    free(p);
    p = NULL;
}

int procedimento_tamanho(PROCEDIMENTO* p)
{
    return p->size;
}

void print_procedimento(PROCEDIMENTO* p)
{
    printf("%s\n", p->nome);
}