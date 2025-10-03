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

void imprime_menu();
void clean_buffer();

int main()
{
    LISTA *lista = criar_lista();
    FILA *fila = criar_fila();
    if (load(&lista, &fila) == false)
    {
        printf("Não foi possível abrir os arquivos salvos.");
    }
    
    int comando;
    imprime_menu();
    while (true) //isso sempre vai acontecer enquanto o programa roda, a nao ser no caso 8, que ai finaliza a função
    {
        scanf("%d", &comando);
        clean_buffer();
        //execução baseada no comando escolhido
        switch (comando)
        {
            case 1: //registrar paciente
            {
                int id;
                char nome[100];
                PACIENTE *paciente;
                printf("Digite o ID do paciente:\n");
                scanf("%d", &id);
                clean_buffer();
                if(id <= 0){
                    printf("ID invalido\n");
                    break;
                }
                if (buscar_paciente(lista, id) == NULL)
                {
                    printf("Digite o nome do paciente:\n");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    paciente = criar_paciente(id, nome);
                    if (paciente == NULL)
                    {
                        printf("Nao foi possivel registrar o paciente.\n");
                    }
                    else
                    {
                        inserir_paciente_lista(lista, paciente);
                        printf("Paciente registrado com sucesso\n");
                    }
                }
                else
                {
                    printf("Paciente já registrado.\n");
                }
                if (fila_cheia(fila) == false)
                {
                    if(buscar_paciente_fila(fila, id)){
                        printf("Paciente já está na fila.\n");
                    }
                    else{
                        inserir_paciente_triagem(fila, id);
                        printf("Paciente inserido na fila para a triagem.\n");
                    }
                }
                else
                {
                    printf("Fila cheia! Nao foi possivel adicionar o paciente na fila\n");
                }
                break;
            }

            case 2: //registrar obito do paciente
            {
                printf("Digite o ID do paciente a ser removido da lista:\n");
                int id;
                scanf("%d", &id);
                clean_buffer();
                if(buscar_paciente_fila(fila, id)){
                    printf("Paciente está na fila.\n");
                }
                else {
                    if (!apagar_paciente_lista(lista, id))
                    {
                        printf("Não existe um paciente com esse id no sistema\n");
                    }
                    else
                    {
                        printf("Paciente removido do sistema.\n");
                    }
                }
                break;
            }

            case 3://adicionar procedimento
            {
                printf("Digite o ID do paciente a adicionar um procedimento no historico:\n");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = buscar_paciente(lista, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    char texto[100];
                    printf("Digite o procedimento a ser adicionado\n");
                    fgets(texto, 100, stdin);
                    texto[strcspn(texto, "\n")] = '\0';
                    PROCEDIMENTO *procedimento = criar_procedimento(texto);
                    if (inserir_procedimento(get_historico(paciente), procedimento))
                    {
                        printf("Procedimento inserido no historico do paciente com sucesso\n");
                    }
                    else
                    {
                        printf("Nao foi possivel inserir o procedimento.\n");
                    }
                }
                break;
            }

            case 4://remover procedimento
            {
                printf("Digite o ID do paciente a remover um procedimento de seu historico (sera removido o procedimento mais recente).\n");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = buscar_paciente(lista, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    if (historico_vazio(get_historico(paciente)))
                    {
                        printf("O historico do paciente esta vazio.\n");
                    }
                    else
                    {
                        if (retirar_procedimento(get_historico(paciente)))
                        {
                            printf("Procedimento retirado com sucesso.\n");
                        }
                        else
                        {
                            printf("Não foi possivel retirar o procedimento.\n");
                        }
                    }    
                }
                break;
            }

            case 5: //chamar o proximo da fila para atendimento
            {
                int id = chamar_para_atendimento(fila);
                if (id == -1)
                {
                    printf("A fila esta vazia.\n");
                }
                else
                {
                    PACIENTE* paciente = buscar_paciente(lista, id);
                    char *nome = get_nome(paciente);
                    printf("Paciente chamado para atendimento.\n");
                    printf("Nome: %s\n", nome);
                    printf("ID: %d\n", id);
                }
                break;
            }
            case 6:
            {
                //printar a fila de espera
                fila_listar(fila);                
                break;
            }

            case 7:
            {
                //printar o historico de um paciente pelo id
                printf("Digite o id do paciente para ver seu histórico\n");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = buscar_paciente(lista, id);
                if(paciente == NULL){
                    printf("Paciente não encontrado\n");
                }
                else print_historico(get_historico(paciente));
                break;
            }

            case 8: //sai o sistema
            {
                printf("Saindo do sistema.\n");
                if (save(lista, fila) == false)
                {
                    printf("Não foi possível salvar a lista e a fila.\n");
                    apagar_fila(&fila);
                    apagar_lista(&lista);
                }
                return 0;
            }
        
            default: //comando invalido inserido pelo usuario
            {
                printf("Comando inválido!\n"); //se o comando for invalido, avisar, reenviar as opcoes e perguntar dnv
                break;
            }
        }
        imprime_menu(); //pede nova inserção de comando
    }
    
}

void imprime_menu()
{
    printf("\nPressione enter para continuar\n");
    clean_buffer();
    printf("Digite o valor correspondente a operacao que você deseja realizar:\n");
    printf("1. Registrar paciente\n");
    printf("2. Registrar óbito de paciente\n");
    printf("3. Adicionar procedimento ao histórico médico do paciente\n");
    printf("4. Desfazer procedimento do histórico médico do paciente\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar histórico do paciente\n");
    printf("8. Sair\n\n");
    return;
}

void clean_buffer()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}