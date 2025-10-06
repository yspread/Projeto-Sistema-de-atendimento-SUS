#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct lista_  //lista encadeada
{
    NO *inicio;  //o ponteiro que aponta pro inicio é basicamente a lista em si
    NO *fim;
    int tamanho;
}LISTA;

typedef struct no_
{
    PACIENTE *paciente;
    NO *proximo;
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
    if ((*lista != NULL) && (!lista_vazia(*lista)))
    {
        while ((*lista)->inicio != NULL) 
        {
            auxiliar = (*lista)->inicio; 
            (*lista)->inicio = (*lista)->inicio->proximo;
            apagar_paciente(&(auxiliar->paciente));
            auxiliar->proximo = NULL;
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
        if(novoPaciente == NULL)return false;
        novoPaciente->paciente = paciente;
        novoPaciente->proximo = NULL; //o novo paciente nao tera ninguem como proximo, por enquanto
        if (lista->inicio == NULL)
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
        if (procura != NULL) //significa que o paciente foi encontrado (esta na lista)
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
            apagar_paciente(&procura->paciente);
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

PACIENTE *remover_paciente_inicio_lista(LISTA *lista) //fiz uma funcao para remover diretamente do inicio para usar na funcao save
{
    if (lista == NULL || lista_vazia(lista))
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

        lista->tamanho--;

        if(lista->inicio == NULL){
            lista->fim = NULL;
        }
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
    return NULL;
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
            printf("{\nPACIENTE: %s\nID: %d\n}\n", get_nome_paciente(procura->paciente), get_ID(procura->paciente));
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

int get_lista_tamanho(LISTA *lista)
{
    return lista->tamanho;
}