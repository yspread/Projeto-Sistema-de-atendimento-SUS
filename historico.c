#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARS 100 //quantidade maxima de caracteres no historico

typedef struct historico_
{
    char *procedimentos[10]; //vetor de strings, armazena os procedimentos
    int contador_chars; //contador para ver se a quantidade de char do historico estourou o limite (100)
}HISTORICO;

