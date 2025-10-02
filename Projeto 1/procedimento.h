#ifndef PROCEDIMENTO_H
    #define PROCEDIMENTO_H

    typedef struct procedimento_ PROCEDIMENTO;
    PROCEDIMENTO* criar_procedimento(char* str);
    void apagar_procedimento(PROCEDIMENTO** p);
    int procedimento_tamanho(PROCEDIMENTO* p);
    char *get_nome_procedimento(PROCEDIMENTO *p);
    int get_size(PROCEDIMENTO *p);
    void print_procedimento(PROCEDIMENTO* p);
    bool procedimento_cheio(PROCEDIMENTO* p);
#endif