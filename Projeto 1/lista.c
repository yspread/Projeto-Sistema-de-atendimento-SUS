#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct lista_  //lista encadeada, talvez seja duplamente
{
    NO *inicio;  //o ponteiro que aponta pro inicio é basicamente a lista em si
    NO *fim;
    int tamanho;
}LISTA;

typedef struct no_
{
    PACIENTE *paciente;
    NO *proximo;
    //talvez eu faça duplamente encadeada com NO *anterior
}NO;

LISTA *criar_lista() //funcao para alocar memoria para a lista
{
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
    if (lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;    
    }
    return lista;
}

void apagar_lista(LISTA **lista) //apaga a lista ao fechar o sistema apos salvar no disco os dados
{
    NO *auxiliar;
    if ((*lista != NULL) && (!lista_vazia(*lista))) //se a lista nao esta vazia
    {
        while ((*lista)->fim != NULL) //vou percorrer a lista do inicio ao fim, itera enquanto o fim nao foi apagado ainda
        {
            auxiliar = (*lista)->inicio; //itero pela lista com o proprio ponteiro inicio
            (*lista)->inicio = (*lista)->inicio->proximo; //passo o inicio para o proximo no
            apagar_paciente_lista(*lista, get_ID(&auxiliar->paciente)); //apago o paciente contido no no auxiliar
            auxiliar->proximo = NULL; //apago o ponteiro
            free (auxiliar);
            auxiliar = NULL;
        }
    }
    free (*lista);
    *lista = NULL; 
}

bool inserir_paciente_lista(LISTA *lista, PACIENTE *paciente) //adiciona um novo paciente ao final da lista
{
    if (lista != NULL)
    {
        //criando o no que se refere ao paciente inserido, para coloca-lo na cadeia
        NO *novoPaciente = (NO *) malloc (sizeof(NO));
        novoPaciente->paciente = paciente;
        novoPaciente->proximo = NULL; //o novo paciente nao tera ninguem como proximo, por enquanto
        if (lista->inicio = NULL)
        {
            lista->inicio = novoPaciente;
        }
        else
        {
            lista->fim->proximo = novoPaciente; //primeiro coloca na lista o novo paciente, que vem depois do final
        }
        lista->fim = novoPaciente; //agora fim aponta para o novo final da lista
        lista->tamanho++; //atualiza o tamanho da lista
        return (true); //operacao bem sucedida
    }
    else
    {
        return (false); //operacao mal sucedida
    }
}

bool apagar_paciente_lista(LISTA *lista, int ID) //apagar um paciente da lista, ocorre quando ele morre
{
    if (lista != NULL && !lista_vazia(lista))
    {
        NO *auxiliar = NULL;
        NO *procura = lista->inicio;
        while (procura != NULL && (get_ID(procura->paciente)) != ID) //loop que itera pela lista procurando compatibilidade entre IDs
        {
            auxiliar = procura;    //enquanto nao se acha a compatibilidade, passa pro proximo ate achar, aonde o procura é o no procurado
            procura = procura->proximo;
        }
        if (procura != NULL) //significa que o paciente nao foi encontrado (não esta na lista)
        {
            if (procura == lista->inicio) //se o paciente em questao estiver no inicio, mudar o inicio da lista
            {
                lista->inicio = procura->proximo;
                procura->proximo = NULL; //transforma em NULL o ponteiro do no do paciente apagado
            }
            else
            {
                auxiliar->proximo = procura->proximo; //ponteiro auxiliar corresponde ao que vem antes do procura
                procura->proximo = NULL;
            }
            if (procura == lista->fim) //se o desejado estiver no fim da lista, deve se atualizar o indicador do final da lista
            {
                lista->fim = auxiliar; //aponta para o anterior
            }
            lista->tamanho--;
            free(procura);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

PACIENTE *remover_paciente_inicio_lista(LISTA *lista)
{
    if (lista = NULL && lista_vazia(lista))
    {
        return NULL;
    }
    else
    {
        //nao apago o paciente na função pois ele é apagado apos ser salvo
        NO *auxiliar = lista->inicio->proximo;
        PACIENTE *pacienteAux = lista->inicio->paciente;
        lista->inicio->paciente = NULL;
        lista->inicio->proximo = NULL;
        free(lista->inicio);
        lista->inicio = auxiliar;
        return (pacienteAux);
    }
}

PACIENTE *buscar_paciente(LISTA *lista, int ID) //busca um paciente pelo ID fornecido
{
    NO *procura; //itera pela lista
    if (lista->inicio == NULL)
    {
        return NULL;
    }
    else
    {
        procura = lista->inicio;
        while (procura != NULL)
        {
            if (get_ID(procura->paciente) == ID)
            {
                return(procura->paciente); //achou
            }
            procura = procura->proximo; //passa pro proximo no   
        }
    }    
}

void listar_pacientes(LISTA* lista) //imprime toda a relação de pacientes
{
    NO *procura; //itera pela lista
    if (lista_vazia(lista))  //caso a lista esteja vazia, informamos ao usuario
    {
        printf("A lista de pacientes esta vazia");
        return;
    }
    else
    {
        procura = lista->inicio;
        while(procura != NULL)
        {
            printf("{\nPACIENTE: %s\nID: %d\n}\n", get_nome(procura->paciente), get_ID(procura->paciente));
            procura = procura->proximo; //passa para o proximo
        }
    }
}

bool lista_vazia(LISTA *lista) //verifica se a lista esta vazia
{
    if ((lista != NULL) && lista->inicio == NULL)
    {
        return true; //se o inicio apontar para null, nao tem nenhum elemento na lista
    }
    return false;
}