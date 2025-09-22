#ifndef HISTORICO_H
    #define HISTORICO_H
    
    #include <stdbool.h>

    typedef struct historico_ HISTORICO;

    //funçoes que operam no historico do paciente: PILHA
    HISTORICO* criar_historico(); //pra criar um historico caso o paciente nao tenha
    void apagar_historico(HISTORICO** historico); //apagar historico caso paciente morra e pra salvar 
    void print_historico(HISTORICO* historico); //consultar o historico de alguem pelo ID
    bool inserir_procedimento(HISTORICO* historico, PROCEDIMENTO* procedimento); //empilhar
    bool retirar_procedimento(HISTORICO* historico); //desempilhar
    bool historico_cheio();
    bool historico_vazio(HISTORICO* historico);
    //função save e load aqui nao, vai estar no save e load lista

#endif