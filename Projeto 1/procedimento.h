#ifndef PROCEDIMENTO_H
    #define PROCEDIMENTO_H

    typedef struct procedimento_ PROCEDIMENTO;
    PROCEDIMENTO* criar_procedimento(char* str);
    void apagar_procedimento(PROCEDIMENTO** p);
    int procedimento_tamanho(PROCEDIMENTO* p);
#endif