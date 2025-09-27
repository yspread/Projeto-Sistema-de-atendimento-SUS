#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct paciente_
{
    int ID;
    char nome[100];
    int tamanhoNome;
    HISTORICO *historico;
}PACIENTE;

int get_ID(PACIENTE *paciente) //função para retornar o ID do paciente
{
    return (paciente->ID);
}

HISTORICO *get_historico(PACIENTE *paciente) //função para retornar o historico do paciente
{
    return (paciente->historico);
}

char *get_nome(PACIENTE *paciente) //função para retornar o nome do paciente
{
    return (paciente->nome);
}

int get_tamanho_nome(PACIENTE *paciente)
{
    return (paciente->tamanhoNome);
}

bool apagar_paciente(PACIENTE **paciente)
{
    if (*paciente != NULL)
    {
        if(get_historico(*paciente) != NULL)
        {
            apagar_historico(get_historico(*paciente));
        }
        free(*paciente);
        *paciente = NULL;
        return (true);
    }
    return false;
}

PACIENTE* criar_paciente(int id, char *nome) //funcao para criar um paciente
{
    PACIENTE *paciente;

    paciente = (PACIENTE*) malloc (sizeof(PACIENTE));
    if (paciente != NULL)
    {
        paciente->ID = id;
        strcpy(paciente->nome, nome);
        paciente->tamanhoNome = strlen(nome);
        paciente->historico = criar_historico();
        return paciente;
    }
    return NULL;
}