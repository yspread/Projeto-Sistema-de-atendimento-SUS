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

void apagar_paciente(PACIENTE *paciente)
{
    
}