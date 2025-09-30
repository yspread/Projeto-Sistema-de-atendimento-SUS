#include "paciente.h"
#include "triagem.h"
#include "historico.h"
#include "lista.h"
#include "procedimento.h"
#include "IO.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void imprime_menu();

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
                if (buscar_paciente(lista, id) == NULL)
                {
                    printf("Digite o nome do paciente:\n");
                    scanf("%s", nome);
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
                    inserir_paciente_triagem(fila, paciente);
                    printf("Paciente inserido na fila para a triagem.\n");
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
                if (!apagar_paciente_lista(lista, id))
                {
                    printf("Não existe um paciente com esse id no sistema\n");
                }
                else
                {
                    printf("Paciente removido do sistema.\n");
                }
                break;
            }

            case 3:
            {
                printf("Digite o ID do paciente a adicionar um procedimento no historico:\n");
                int id;
                scanf("%d", &id);
                PACIENTE *paciente = buscar_paciente(lista, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    char texto[10];
                    printf("Digite o procedimento a ser adicionado\n");
                    scanf("%s", texto);
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

            case 4:
            {
                printf("Digite o ID do paciente a remover um procedimento de seu historico (sera removido o procedimento mais recente).\n");
                int id;
                scanf("%d", &id);
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
                PACIENTE *paciente = chamar_para_atendimento(fila);
                if (paciente == NULL)
                {
                    printf("A fila esta vazia.\n");
                }
                else
                {
                    int id = get_ID(paciente);
                    char *nome = get_nome(paciente);
                    printf("Paciente chamado para atendimento.\n");
                    printf("Nome: %s", nome);
                    printf("ID: %d", id);
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
                PACIENTE *paciente = buscar_paciente(lista, id);
                print_historico(get_historico(paciente));
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
    /*
    INTERFACE DO USUARIO
    3- ADICIONAR PROCEDIMENTO
    4- REMOVER PROCEDIMENTO
        esses 2 sao puxados pelo ID do paciente e adicionar
        informar oque foi adicionado/deletado
        informar caso nao exista o procedimento ou se o paciente nao existir
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
    printf("8. Sair\n\n");
    return;
}