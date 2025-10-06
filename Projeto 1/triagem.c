#include <stdbool.h>
#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_MAX_FILA 100

typedef struct fila_ {
    NO *inicio; //ponteiros apontando para o inicio e fim da fila
    NO *fim;
    int tamanho; //precisamos guardar o tamanho da fila para verificar se ela está cheia ou vazia
}FILA;

typedef struct no_  {
    int ID;
    NO *proximo;
}NO;

FILA *criar_fila(void) {
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    if (fila != NULL) {
        fila-> inicio = NULL; //quando a fila eh criada, ela esta vazia, portanto os ponteiros de inicio e fim apontam para NULL
        fila-> fim = NULL;
        fila-> tamanho = 0;
    }
    return (fila);
}

bool inserir_paciente_triagem(FILA *fila, int ID)  {
    if (fila == NULL || fila_cheia(fila)) {
        return (false); //a fila nao existir ou estiver cheia, entao eh impossivel inserir pacientes
    }
    NO *novo_paciente = (NO *) malloc (sizeof(NO)); //alocando espaco do tamanho da struct NO para o novo_paciente, ja que ele eh um ponteiro para NO
    if(novo_paciente == NULL)return false;
    novo_paciente->ID = ID;
    novo_paciente->proximo = NULL; //como o novo paciente esta no fim da fila, nao ha proximo paciente para ele
    if (fila->inicio == NULL) { 
        fila->inicio = novo_paciente; //se a fila estiver vazia, o paciente entrara no inicio da fila
    }
    else {
    fila->fim->proximo = novo_paciente; //se a fila nao estiver vazia, o novo_paciente entra no fim da fila, tornando-se o "proximo" para quem era o ultimo antes
    }
    fila->fim = novo_paciente; //o novo_paciente eh colocado no fim da fila
    fila->tamanho++; //a fila aumenta de tamanho
    return (true);
}

int chamar_para_atendimento(FILA *fila) { //o paciente que esta no inicio da fila sera chamado para atendimento, entao deve ser tirado da fila e o proximo paciente agora esta no inicio
    if (fila == NULL || fila_vazia(fila)) {
        return (-1); //se a fila nao existe ou esta vazia, nao eh possivel remover pacientes
    }
    fila->tamanho--; //a fila reduz em 1 o seu tamanho
    NO *aux = fila->inicio; //vamos criar um ponteiro auxiliar para guardar o NO que tera memoria liberada
    int id_paciente_atendido = fila->inicio->ID;
    fila->inicio = aux->proximo; //o inicio agora eh o antigo proximo
    if (fila_vazia(fila)) {    //se a fila ficou vazia apos o paciente ser atendido, nao ha mais fim da fila
        fila->fim = NULL; //este eh o unico caso em que o atendimento de pacientes altera o fim da fila
    }
    free(aux); //liberamos o NO que era o antigo inicio
    return(id_paciente_atendido);
}


void apagar_fila(FILA **fila) //apaga a fila ao fechar o sistema apos salvar no disco os dados
{
    NO *auxiliar;
    if ((*fila != NULL) && (!fila_vazia(*fila))) //verifica se a fila nao esta vazia
    {
        while ((*fila)->inicio != NULL) //vamos percorrer a fila do inicio ao fim, itera enquanto o fim nao foi apagado ainda
        {
            auxiliar = (*fila)->inicio; //itero pela lista com o proprio ponteiro inicio
            (*fila)->inicio = (*fila)->inicio->proximo; //passa o inicio para o proximo no
            auxiliar->proximo = NULL; //apaga o ponteiro
            free (auxiliar);
            auxiliar = NULL;
        }
    }
    free (*fila);
    *fila = NULL;
}

bool fila_vazia(FILA *fila)  {
    if (fila != NULL && fila->tamanho == 0) { //para a filar estar vazia, ela precisa existir e ter tamanho 0
        return (true);
    }
    else {
        return (false);
    }
} //e se a fila nao existir?

bool fila_cheia(FILA *fila) {
    if (fila != NULL && fila-> tamanho >= TAM_MAX_FILA) { //se a fila existir e tiver 100 pacientes, entao ela esta cheia
        return (true);
    }
    else {
        return (false);
    }
}

int fila_get_tamanho(FILA *fila) { //uma funcao simples para retornar o tamanho da fila
    return (fila->tamanho); 
}

void fila_listar(FILA *fila, LISTA *lista)  {  //função que lista todos os pacientes na fila
    if (fila == NULL) { //se a fila nao existe, nao ha o que listar
        printf("A fila nao existe.\n");
        return;
    }
    if (fila->tamanho == 0)  { //para caso a fila esteja vazia
        printf("Fila Vazia!\n"); 
        return;
    }
    NO *aux = fila->inicio;   //vamos usar um ponteiro auxiliar para percorrer a fila
    while(aux != NULL)  { //o aux vai percorrer a fila até apontar para NULL, significando que nao ha mais pacientes
        PACIENTE *paciente = buscar_paciente(lista, aux->ID);
        char *nome = get_nome_paciente(paciente);
        printf("Nome: %s\nID: %d\n\n",nome, aux->ID);
        aux = aux->proximo;  //o ponteiro auxiliar vai apontando para o proximo da fila, ate apontar para NULL, chegando ao fim da fila
    }
    return;
}

bool buscar_paciente_fila(FILA* fila, int id) //verifica se um paciente ja esta na fila
{
    if(fila == NULL)return false;
    NO* aux = fila->inicio;
    while(aux != NULL){
        if(aux->ID == id)return true;
        aux = aux->proximo;
    }
    return false;
}