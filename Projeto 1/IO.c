#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include "IO.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool save(LISTA *lista, FILA *fila)
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
    int TamanhoLista = list_tamanho(lista);
    fwrite(&TamanhoLista, sizeof(int), 1, fp_lista);
    
    paciente = remover_paciente_inicio_lista(lista);
    //pegar os campos da struct paciente
    int id, tamanhoNome;
    char *nome;
    HISTORICO *historico;

    
    while (paciente != NULL)
    {
        //escreve paciente por paciente no arquivo da lista
        tamanhoNome = get_tamanho_nome(paciente);
        fwrite(&tamanhoNome, sizeof(int), 1, fp_lista); //necessario para quando for dar load
        nome = get_nome(paciente);
        fwrite(nome, sizeof(char), tamanhoNome, fp_lista);
        id = get_ID(paciente);
        fwrite(&id, sizeof(int), 1, fp_lista);
        historico = get_historico(paciente);
        if (historico != NULL)
        {
            int tamanhoHistorico = get_tamanho_historico(historico);
            fwrite(&tamanhoHistorico, sizeof(int), 1, fp_lista);
            while(tamanhoHistorico > 0)
            {    
                PROCEDIMENTO *topo = get_topo(historico);
                int tamanhoProcedimento = get_size(topo);
                fwrite(&tamanhoProcedimento, sizeof(int), 1, fp_lista);
                char *nomeProcedimento = get_nome_procedimento(topo);
                fwrite(nomeProcedimento, sizeof(char), tamanhoProcedimento, fp_lista);
                retirar_procedimento(historico);
                tamanhoHistorico--;
            }
        }
        else{
            int tamanhoHistorico = 0;
            fwrite(&tamanhoHistorico, sizeof(int), 1, fp_lista);
        }
        apagar_paciente(&paciente); //agora que o paciente esta salvo, é apagado da memoria(apaga o historico junto)
        paciente = remover_paciente_inicio_lista(lista); //paciente agora é o proximo
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
    int TamanhoFila = fila_get_tamanho(fila);
    fwrite(&TamanhoFila, sizeof(int), 1 ,fp_fila);

    id = chamar_para_atendimento(fila); //aqui o chamar atendimento serve pra remover o primeiro da fila
    while (id != -1)
    {
        fwrite(&id, sizeof(int), 1, fp_fila);
        id = chamar_para_atendimento(fila);
    }
    apagar_fila(&fila);
    fclose(fp_fila);
    fp_fila = NULL;
    return true;
}

bool load(LISTA **lista, FILA **fila)
{
    if(!*lista || !*fila)
    { 
        return false;
    }
    int tamanhoNome, tamanhoHistorico;
    int id;
    char *nome;
    PACIENTE *paciente;

    //carregando a lista
    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if(!fp_lista)
    {
        return false;
    }
    int TamanhoLista;
    fread(&TamanhoLista, sizeof(int), 1, fp_lista);
    for(int j = 0; j < TamanhoLista; j++)
    {
        fread(&tamanhoNome, sizeof(int), 1, fp_lista);  // Ler tamanho primeiro
    
        nome = malloc((tamanhoNome + 1) * sizeof(char));
        fread(nome, sizeof(char), tamanhoNome, fp_lista);
        nome[tamanhoNome] = '\0';

        fread(&id, sizeof(int), 1, fp_lista);
        paciente = criar_paciente(id, nome);

        free(nome);
        nome = NULL;

        fread(&tamanhoHistorico, sizeof(int), 1, fp_lista);
        PROCEDIMENTO *procedimentos[tamanhoHistorico]; //vai armazenar os procedimentos lidos, que depois serao empilhados na ordem reversa do vetor 
        for (int i = 0; i < tamanhoHistorico; i++)
        {
            int tamanhoProcedimento;
            fread(&tamanhoProcedimento, sizeof(int), 1, fp_lista);

            char *nomeProcedimento;
            nomeProcedimento = malloc((tamanhoProcedimento + 1) * sizeof(char));
            fread(nomeProcedimento, sizeof(char), tamanhoProcedimento, fp_lista);
            nomeProcedimento[tamanhoProcedimento] = '\0';

            procedimentos[i] = criar_procedimento(nomeProcedimento);
            free(nomeProcedimento);
            nomeProcedimento = NULL;
        }
        for (int i = tamanhoHistorico - 1; i >= 0 ; i--) //empilhando os procedimentos
        {
            inserir_procedimento(get_historico(paciente), procedimentos[i]);
        }
        inserir_paciente_lista(*lista, paciente);


    }
    fclose(fp_lista);

    //agora carregando a fila
    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if(!fp_fila)
    {
        return false;
    }
    int TamanhoFila;
    fread(&TamanhoFila, sizeof(int), 1, fp_fila);
    for(int j = 0; j < TamanhoFila; j++)
    {
        fread(&id, sizeof(int), 1, fp_fila);
        inserir_paciente_triagem(*fila, id);
    }
    fclose(fp_fila);

    return true;
}