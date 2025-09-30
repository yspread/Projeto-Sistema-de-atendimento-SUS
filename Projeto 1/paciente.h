#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    #include "historico.h"

    typedef struct paciente_ PACIENTE;

    HISTORICO *get_historico(PACIENTE *paciente);  //para conseguir acessar o historico diretamente                        
    int get_ID(PACIENTE *paciente); //função para que eu consiga acessar o id diretamente do paciente
    char *get_nome(PACIENTE *paciente); //função para que eu consiga acessar o nome do paciente diretamente
    bool apagar_paciente(PACIENTE *paciente); //apaga paciente (necessário para o save load)
    PACIENTE* criar_paciente(int id, char* nome);
    int get_tamanho_nome(PACIENTE *paciente);
    
#endif