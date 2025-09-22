#include <stdbool.h>
#include <string.h>
#include "historico.h"
#include "procedimento.h"
#define MAX_CHARS 100 //quantidade maxima de caracteres no historico
#define MAX_PROCEDIMENTOS 10 //quantidade maxima de procedimentos no historico

typedef struct no_
{
    PROCEDIMENTO* procedimento;
    NO* anterior;
}NO;


typedef struct historico_
{
    int ContadorChars; //contador para ver se a quantidade de char do historico estourou o limite (100)
    int ContadorProcedimentos; //contador para ver se a quantidade de procedimentos do historico estourou o limite (10)
    NO* topo;
}HISTORICO;

HISTORICO* criar_historico()
{
    HISTORICO* historico = malloc(sizeof(HISTORICO));
    if(historico != NULL){
        historico->topo = NULL;
        historico->ContadorChars = 0;
        historico->ContadorProcedimentos = 0;
    }
    return historico;
}

void apagar_historico(HISTORICO** historico)
{
    if((*historico) != NULL && (!historico_vazio(*historico))){
        while((*historico)->topo != NULL){
            retirar_procedimento(*historico);
        }
    }
    free(*historico);
    *historico = NULL;
}

void print_historico(HISTORICO* historico)
{
    NO* p = historico->topo;
    while(p != NULL){
        print_procedimento(p->procedimento);
        p = p->anterior;
    }
}

bool inserir_procedimento(HISTORICO* historico, PROCEDIMENTO* procedimento)
{
    if(historico->ContadorChars + procedimento_tamanho(procedimento) <= 100 && historico->ContadorProcedimentos < 10){
        NO* p = malloc(sizeof(NO));
        if(p != NULL){
            p->procedimento = procedimento;
            p->anterior = historico->topo;
            historico->topo = p;
            historico->ContadorChars += procedimento_tamanho(procedimento);
            historico->ContadorProcedimentos++;
            return true;
        }
    }
    return false;
}

bool retirar_procedimento(HISTORICO* historico)
{
    if(historico != NULL && !historico_vazio(historico)){
        NO* p = historico->topo;
        PROCEDIMENTO* procedimento = p->procedimento;

        historico->topo = historico->topo->anterior;

        apagar_procedimento(procedimento);
        p->anterior = NULL;
        free(p);
        p = NULL;

        return true;
    }
    return false;
}

bool historico_vazio(HISTORICO* historico)
{
    if(historico != NULL){
        return ((historico->ContadorProcedimentos) == 0);
    }
    return false;
}