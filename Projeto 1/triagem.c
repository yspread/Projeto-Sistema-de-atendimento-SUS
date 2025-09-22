#include <stdbool.h>
#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct fila_ {
    NO *inicio; //ponteiros apontando para o inicio e fim da fila
    NO *fim;
    int tamanho; //precisamos guardar o tamanho da fila para verificar se ela está cheia ou vazia
}FILA;

typedef struct no_
{
    PACIENTE *paciente;
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

bool inserir_paciente_triagem(FILA *fila, PACIENTE *paciente)  {
    if (fila == NULL || fila_cheia(fila)) {
        return (false); //a fila nao existir ou estiver cheia, entao eh impossivel inserir pacientes
    }
    NO *novo_paciente = (NO *) malloc (sizeof(NO)); //alocando espaco do tamanho da struct NO para o novo_paciente, ja que ele eh um ponteiro para NO
    novo_paciente->paciente = paciente;
    novo_paciente->proximo = NULL; //como o novo paciente esta no fim da fila, nao ha proximo paciente para ele
    if (fila->inicio = NULL) { 
        fila->inicio = novo_paciente; //se a fila estiver vazia, o paciente entrara no inicio da fila
    }
    else {
    fila->fim->proximo = novo_paciente; //se a fila nao estiver vazia, o novo_paciente entra no fim da fila, tornando-se o "proximo" para quem era o ultimo antes
    }
    fila->fim = novo_paciente; //o novo_paciente eh colocado no fim da fila
    fila->tamanho++; //a fila aumenta de tamanho
    return (true);
}

void chamar_para_atendimento(FILA *fila) { //o paciente que esta no inicio da fila sera chamado para atendimento, entao deve ser tirado da fila e o proximo paciente agora esta no inicio
    if (fila == NULL || fila_vazia(fila)) {
        return (NULL); //se a fila nao existe ou esta vazia, nao eh possivel remover pacientes
    }
    fila->tamanho--; //a fila reduz em 1 o seu tamanho
    NO *aux = fila->inicio; //vamos criar um ponteiro auxiliar para guardar o NO que tera memoria liberada
    PACIENTE *paciente_atendido = fila->inicio->paciente; //vamos criar um ponteiro para guardar e retornar as informacoes do paciente que sera removido da fila (atendido)
    fila->inicio = aux->proximo; //o inicio agora eh o antigo proximo
    if (fila_vazia(fila)) {    //se a fila ficou vazia apos o paciente ser atendido, nao ha mais fim da fila
        fila->fim = NULL; //este eh o unico caso em que o atendimento de pacientes altera o fim da fila
    }
    free(aux); //liberamos o NO que era o antigo inicio
    return(paciente_atendido);
}


void apagar_fila(FILA *fila)  { //para apagar a fila, vamos desfazer todos o NOS que a compoem e dar free neles e na estrutura da fila em si, sem a perda de informacoes dos pacientes
    if (fila == NULL) {
        return; //se a fila nao existir, a operacao eh impossivel, entao apenas retorna
    }
    while (!fila_vazia(fila)) {  //vamos percorrer todos os NOS da fila para desfaze-los, efetivamente retirando as pessoas da fila ate que ela fique vazia
        NO *aux = fila->inicio;   //para isso, vamos usar uma logica parecida com a da funcao chamar_para_atendimento, utilizando um NO auxiliar para nao perder informacoes
        fila->inicio = aux->proximo; //quando so houver 1 paciente restando, este passo fara com que o inicio aponte para NULL, e o proximo free(aux) decretara a liberacao de todos os NOS da fila
        free(aux);
        fila->tamanho--;
    }
    free(fila); //agora que a fila esta vazia e nao ha mais NOS na fila, podemos libera-la
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
    if (fila != NULL && fila-> tamanho == 100) { //se a fila existir e tiver 100 pacientes, entao ela esta cheia
        return (true);
    }
    else {
        return (false);
    }
}

int fila_get_tamanho(FILA *fila) { //uma funcao simples para retornar o tamanho da fila
    return (fila->tamanho); 
}

void fila_listar(FILA *fila)  {  //função que lista todos os pacientes na fila
    if (fila == NULL) { //se a fila nao existe, nao ha o que listar
        printf("Essa fila não existe");
        return;
    }
    if (fila->tamanho == 0)  { //para caso a fila esteja vazia
        printf("Fila Vazia!"); 
        return;
    }
    NO *aux = fila->inicio;   //vamos usar um ponteiro auxiliar para percorrer a fila
    while(aux != NULL)  { //o aux vai percorrer a fila até apontar para NULL, significando que nao ha mais pacientes
        printf("Paciente: %s\nID: %d\n\n", get_nome(aux->paciente), get_ID(aux->paciente));  //impressao do nome e ID do paciente acessado neste momento por aux
        aux = aux->proximo;  //o ponteiro auxiliar vai apontando para o proximo da fila, ate apontar para NULL, chegando ao fim da fila
    }
    return;
}

