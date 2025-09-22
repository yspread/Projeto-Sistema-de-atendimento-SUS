#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    /*
    ANTES DE TUDO, DEVE-SE CRIAR A LISTA E A FILA E CARREGAR O ARQUIVO
    */
   
    int comando;
    imprime_menu();
    while (true) //isso sempre vai acontecer enquanto o programa roda, a nao ser no caso 8, que ai finaliza a função
    {
        scanf("%d", comando);
        //execução baseada no comando escolhido
        switch (comando)
        {
            case 1: //registrar paciente
            /* code */
            break;

            case 2: //registrar paciente
            /* code */
            break;

            case 3:
            /* code */
            break;

            case 4:
            /* code */
            break;

            case 5: //chamar para atendimento um paciente
            {

            }
            case 6:
            /* code */
            break;

            case 7:
            /* code */
            break;

            case 8: //sai o sistema
            {
                printf("Saindo do sistema.");
                //inserir aqui o salvamento
                return 0;
            }
        
            default: //comando invalido inserido pelo usuario
            {
                printf("Comando inválido!"); //se o comando for invalido, avisar, reenviar as opcoes e perguntar dnv
                break;
            }
        }
        imprime_menu(); //pede nova inserção de comando
    }
    /*
    INTERFACE DO USUARIO
    1- REGISTRAR PACIENTE
        se ele ja esta: inserir e botar na lista de espera(triagem)
        se for repetido, avisar
        DEVO CRIAR UM PACIENTE COM OS DADOS FORNECIDOS PELO USUARIO E AI INSERIR NA LISTA E NA FILA
    2- REGISTRAR OBITO DO PACIENTE
        se ele morrer, APAGAR REGISTRO DA LISTA
        ele so morre se ja tiver sido chamado pra atendimento, entao nao precisa tirar da fila
        reportar sucesso ou nao (nao entendi direito como isso nao daria certo, mas blz)
    3- ADICIONAR PROCEDIMENTO
    4- REMOVER PROCEDIMENTO
        esses 2 sao puxados pelo ID do paciente e adicionar
        informar oque foi adicionado/deletado
        informar caso nao exista o procedimento ou se o paciente nao existir
    5- CHAMAR PARA ATENDIMENTO
        tirar da fila
        avisar se a fila estiver vazia
    6- MOSTRAR FILA
        so printar
    7- MOSTRAR HISTORICO DE ALGUEM
        puxar pelo ID
    8- SAIR
        a interface deve continuar sendo apresentada pro usuario enquanto ele nao chamar pela saida
        SALVAR TUDO (lista, fila, historicos)
        ou fazer TAD proprio
        ou adicionar save e load em cada TAD
    */
}

void imprime_menu()
{
    printf("Digite o valor correspondente a operacao que você deseja realizar:\n");
    printf("1. Registrar paciente\n");
    printf("2. Registrar óbito de paciente\n");
    printf("3. Adicionar procedimento ao histórico médico do paciente\n");
    printf("4. Desfazer procedimento do histórico médico do paciente\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar histórico do paciente\n");
    printf("8. Sair\n");
    return;
}